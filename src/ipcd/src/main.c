/*
 * main.c — ipcd top-level: netmgr state machine + module wiring.
 *
 * Boot flow (unchanged from proxycam):
 *   1) Read /etc/config/wifi.conf
 *   2) configured? → STA attempt → online (capture+rtsp+hls live)
 *      not configured? → AP mode (HTTP on :80, captive portal helper)
 *   3) Reset button (long-press) → wipe wifi.conf + reboot
 *
 * What changed vs proxycam:
 *   - capture is now an in-process module (cap_pipeline.c), not a fork
 *     of /mnt/proxy_capture. The launch side becomes:
 *         capture_start(&cfg);   // returns immediately, spawns threads
 *         capture_stop();        // joins all threads
 *   - stats sampler thread runs whenever capture is up, so the /stats
 *     page has fresh data as soon as the user navigates there.
 *   - HLS muxer is started by capture_start() if cfg.hls_enable=1.
 *
 * Signal handling: SIGTERM/SIGINT flip g_run; the SIGCHLD handler is
 * still installed for completeness (e.g. wpa_supplicant child reaped),
 * but capture is no longer a child process so it's purely cosmetic.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <getopt.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "ipcd.h"

/* IPCD_VERSION is defined in ipcd.h */

/* ---------------------------------------------------------------- */
/* Globals                                                          */
/* ---------------------------------------------------------------- */
struct global_state G = {
    .mtx = PTHREAD_MUTEX_INITIALIZER,
    .st  = PCS_BOOT,
    .cfg_pending_cv = PTHREAD_COND_INITIALIZER,
};

const char *pc_state_name(pc_state_t s)
{
    switch (s) {
    case PCS_BOOT:      return "boot";
    case PCS_STA_TRY:   return "connecting";
    case PCS_STA_OK:    return "online";
    case PCS_AP_MODE:   return "provisioning";
    case PCS_REBOOTING: return "rebooting";
    }
    return "?";
}

void g_set_state(pc_state_t s)
{
    pthread_mutex_lock(&G.mtx);
    G.st = s;
    pthread_mutex_unlock(&G.mtx);

    /* LED policy:
     *   AP mode   → blue blink slow (1Hz)
     *   STA_TRY   → blue blink fast (4Hz)
     *   STA_OK    → blue solid
     *   else      → off
     */
    switch (s) {
    case PCS_AP_MODE:  led_set(LED_BLUE, LED_BLINK_SLOW); break;
    case PCS_STA_TRY:  led_set(LED_BLUE, LED_BLINK_FAST); break;
    case PCS_STA_OK:   led_set(LED_BLUE, LED_ON);         break;
    default:           led_set(LED_BLUE, LED_OFF);        break;
    }
}

pc_state_t g_get_state(void)
{
    pthread_mutex_lock(&G.mtx);
    pc_state_t s = G.st;
    pthread_mutex_unlock(&G.mtx);
    return s;
}

/* ---------------------------------------------------------------- */
/* Signal handling                                                  */
/* ---------------------------------------------------------------- */
static volatile sig_atomic_t g_run = 1;

static void on_term(int s) { (void)s; g_run = 0; }

/* NOTE on SIGCHLD: we deliberately do NOT install a handler.
 *
 * An earlier version of this code installed a handler that called
 * `waitpid(-1, NULL, WNOHANG)` to reap any child. It looked harmless
 * — "purely defensive" was the comment. It was not.
 *
 * `system()` and `popen()` work by forking a /bin/sh, then calling
 * waitpid() on that specific pid to get the command's exit status.
 * If our SIGCHLD handler races them and reaps the sh first, the
 * libc waitpid returns -1/ECHILD and `system()` returns -1 — which
 * we were interpreting as "the command failed". Result: every shell
 * command we ran (`hostapd -B`, `udhcpd`, `ifconfig`, ...) was
 * reported as failed even when the underlying program ran fine.
 *
 * That cost us roughly five rounds of debugging on AP-mode startup
 * where the symptoms (false hostapd failure, false ifconfig failure,
 * false udhcpd failure) all pointed at the wrong things.
 *
 * The actual children we care about are all daemonised:
 *   - wpa_supplicant -B, hostapd -B, udhcpd, udhcpc -b
 *     all double-fork and reparent to init; we never see their
 *     SIGCHLD.
 * Anything that's not daemonised, we wait for synchronously through
 * `system()`. There's no zombie scenario left to defend against.
 *
 * If a future child is ever NOT daemonised and NOT waited on, prefer
 * tracking its pid explicitly and reaping it directly, rather than
 * reintroducing a wildcard handler.
 */


/* ---------------------------------------------------------------- */
/* STA attempt — with retry on association failure                  */
/*                                                                  */
/* On cold boot the atbm603x driver's 4-way handshake can stall    */
/* during PTK derivation due to low /dev/urandom entropy. The fix  */
/* is to retry: relaunching wpa_supplicant after a few seconds     */
/* works reliably because the kernel has gathered more entropy by  */
/* then. We try up to 3 times with a 3-second backoff.             */
/*                                                                  */
/* DHCP timeouts (associated but no IP) get NO retry here — they    */
/* most likely mean the AP/router is the issue, not us. The caller */
/* falls back to AP mode after this returns 0.                     */
/* ---------------------------------------------------------------- */
#define STA_ASSOC_RETRIES  3

static int try_sta(const struct wifi_cfg *cfg)
{
    g_set_state(PCS_STA_TRY);
    fprintf(stderr, "[netmgr] STA: connecting to '%s'\n", cfg->ssid);

    int started_ok = 0;
    for (int attempt = 1; attempt <= STA_ASSOC_RETRIES; attempt++) {
        int rc = wifi_start_sta(cfg);
        if (rc == WIFI_STA_OK) {
            started_ok = 1;
            break;
        }
        if (rc == WIFI_STA_NOT_ASSOCIATED && attempt < STA_ASSOC_RETRIES) {
            fprintf(stderr,
                "[netmgr] STA: association failed (attempt %d/%d) — "
                "retrying in 3s (likely entropy issue at cold boot)\n",
                attempt, STA_ASSOC_RETRIES);
            sleep(3);
            continue;
        }
        /* Hard error or last association-failure attempt — give up. */
        fprintf(stderr, "[netmgr] STA: start failed (rc=%d)\n", rc);
        return 0;
    }
    if (!started_ok) return 0;

    char ip[16] = "";
    for (int i = 0; i < STA_CONNECT_TIMEOUT_S; i++) {
        sleep(1);
        if (wifi_sta_has_ip(ip)) {
            fprintf(stderr, "[netmgr] STA: got IP %s\n", ip);
            pthread_mutex_lock(&G.mtx);
            strncpy(G.sta_ip, ip, sizeof(G.sta_ip) - 1);
            pthread_mutex_unlock(&G.mtx);
            return 1;
        }
    }
    fprintf(stderr, "[netmgr] STA: timeout, no IP\n");
    return 0;
}

/* ---------------------------------------------------------------- */
/* AP mode                                                          */
/* ---------------------------------------------------------------- */
static void run_ap_loop(void)
{
    fprintf(stderr, "[netmgr] entering AP mode\n");
    wifi_stop_sta();
    int ap_attempts = 0;
    while (wifi_start_ap() != 0) {
        ap_attempts++;
        if (ap_attempts >= 3) {
            fprintf(stderr,
                "[netmgr] AP start failed %d times — giving up, "
                "scan-only fallback will still let UI work over wired/usb\n",
                ap_attempts);
            break;
        }
        fprintf(stderr,
            "[netmgr] AP start failed (attempt %d/3) — retrying in 5s\n",
            ap_attempts);
        sleep(5);
    }
    if (wifi_start_scan_only() != 0) {
        fprintf(stderr,
            "[netmgr] scan-only supplicant failed (scan in UI won't work)\n");
    }
    if (dns_spoof_start() != 0) {
        fprintf(stderr, "[netmgr] dns spoofer failed (captive portal manual)\n");
    }
    g_set_state(PCS_AP_MODE);

    for (;;) {
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        ts.tv_sec += 1;

        pthread_mutex_lock(&G.mtx);
        int got = G.cfg_pending;
        if (!got) pthread_cond_timedwait(&G.cfg_pending_cv, &G.mtx, &ts);
        got = G.cfg_pending;
        if (got) G.cfg_pending = 0;
        pthread_mutex_unlock(&G.mtx);

        if (got) break;
        if (!g_run) return;
    }

    fprintf(stderr, "[netmgr] new credentials received, leaving AP\n");
    dns_spoof_stop();
    wifi_stop_ap();
    wifi_stop_sta();
    sleep(1);
}

/* ---------------------------------------------------------------- */
/* Online loop                                                      */
/* ---------------------------------------------------------------- */
/* CLI-derived capture configuration. Populated in main() via getopt
 * + ipcd_cfg_load; passed to capture_start() each time we go online.
 * The HTTP /api/config endpoint reads & writes a snapshot of this
 * via the cfg_get/_set wrappers below to avoid races with main(). */
static struct capture_cfg g_capture_cfg;
static pthread_mutex_t    g_capture_cfg_mtx = PTHREAD_MUTEX_INITIALIZER;

void capture_cfg_get(struct capture_cfg *out)
{
    if (!out) return;
    pthread_mutex_lock(&g_capture_cfg_mtx);
    *out = g_capture_cfg;
    pthread_mutex_unlock(&g_capture_cfg_mtx);
}

/* Replace the current capture config and persist it to disk.
 * Returns 0 on success. The caller is responsible for calling
 * capture_stop() + capture_start() afterwards if any non-runtime
 * field changed (codec, fps, enable_*, rtsp_port, sensor_cfg). */
int capture_cfg_set(const struct capture_cfg *in)
{
    if (!in) return -1;
    pthread_mutex_lock(&g_capture_cfg_mtx);
    g_capture_cfg = *in;
    pthread_mutex_unlock(&g_capture_cfg_mtx);
    return ipcd_cfg_save(in);
}

static void run_online_loop(void)
{
    g_set_state(PCS_STA_OK);

    /* One-shot NTP, then daemon */
    timesync_oneshot();
    timesync_daemon_start();

    /* Capture: in-process. The config was prepared in main() from
     * defaults + command-line overrides. */
    if (capture_start(&g_capture_cfg) != 0) {
        fprintf(stderr,
            "[netmgr] capture_start failed: %s\n", strerror(errno));
    } else {
        /* Stats sampler is only useful while capture is alive. */
        stats_sampler_start();
    }

    int lost_secs = 0;
    while (g_run) {
        sleep(2);

        char ip[16] = "";
        if (wifi_sta_has_ip(ip)) {
            lost_secs = 0;
        } else {
            lost_secs += 2;
            if (lost_secs >= 20) {
                fprintf(stderr, "[netmgr] link down >20s, re-association\n");
                break;
            }
        }

        /* If user posted new creds via /api/save while online, also
         * re-provision: tear capture, re-run STA. */
        pthread_mutex_lock(&G.mtx);
        int reconf = G.cfg_pending;
        if (reconf) G.cfg_pending = 0;
        pthread_mutex_unlock(&G.mtx);
        if (reconf) {
            fprintf(stderr, "[netmgr] credentials updated while online\n");
            break;
        }

        /* Auto-restart capture if it died (e.g. SDK threw an error
         * and the supervisor returned). */
        if (!capture_is_running()) {
            fprintf(stderr, "[netmgr] capture not running, relaunching\n");
            stats_sampler_stop();   /* stops cleanly even if not started */
            if (capture_start(&g_capture_cfg) == 0) stats_sampler_start();
        }
    }

    stats_sampler_stop();
    capture_stop();
    wifi_stop_sta();
}

/* ---------------------------------------------------------------- */
/* Top-level state loop                                             */
/* ---------------------------------------------------------------- */
static void mainloop(void)
{
    int sta_failures = 0;

    while (g_run) {
        wifi_cfg_load(&G.cfg);

        if (!G.cfg.configured) {
            run_ap_loop();
            sta_failures = 0;
            continue;
        }

        if (try_sta(&G.cfg)) {
            sta_failures = 0;
            run_online_loop();
        } else {
            sta_failures++;
            wifi_stop_sta();
            if (sta_failures >= STA_RETRIES_BEFORE_AP) {
                fprintf(stderr,
                    "[netmgr] %d STA failures, falling back to AP\n",
                    sta_failures);
                run_ap_loop();
                sta_failures = 0;
            } else {
                fprintf(stderr, "[netmgr] retry %d/%d in 5s\n",
                    sta_failures, STA_RETRIES_BEFORE_AP);
                sleep(5);
            }
        }
    }
}

/* ---------------------------------------------------------------- */
/* main                                                             */
/* ---------------------------------------------------------------- */
/* ---------------------------------------------------------------- */
/* CLI                                                              */
/* ---------------------------------------------------------------- */
static void usage(const char *prog)
{
    fprintf(stderr,
        "ipcd " IPCD_VERSION " — IP Cam Daemon\n"
        "\n"
        "usage: %s [options]\n"
        "\n"
        "  -h, --help              show this help and exit\n"
        "  -v, --version           print version and exit\n"
        "\n"
        "Capture / encode\n"
        "  --rtsp-port PORT        RTSP listen port (default 8554)\n"
        "  --sensor-cfg PATH       sensor config file path\n"
        "  --fps N                 capture / encode frame rate (default 15)\n"
        "  --main-kbps KBPS        main stream target bitrate (default 2000)\n"
        "  --sub-kbps KBPS         sub stream target bitrate (default 300)\n"
        "  --main-codec h264|h265  encoder for main (default h264)\n"
        "  --sub-codec h264|h265   encoder for sub  (default h264)\n"
        "  --no-main               do not capture main stream\n"
        "  --no-sub                do not capture sub stream\n"
        "  --no-watchdog           do not feed /dev/watchdog\n"
        "\n"
        "Day/night\n"
        "  --no-ir                 disable automatic IR-cut switching\n"
        "\n"
        "Persistent config: settings saved via the /config web UI go\n"
        "into " IPCD_CONF_PATH " and override the CLI defaults at\n"
        "the next startup.\n"
        "\n"
        "After startup the camera serves:\n"
        "  http://<ip>/            wifi setup UI (AP mode)\n"
        "  http://<ip>/stats       live metrics\n"
        "  http://<ip>/config      capture parameters editor\n"
        "  rtsp://<ip>:8554/main   1080p stream\n"
        "  rtsp://<ip>:8554/sub    360p stream\n",
        prog);
}

/* Returns 0 to continue starting up, non-zero to exit with that code.
 *
 * Note: we do NOT call capture_cfg_defaults() here. The caller seeds
 * g_capture_cfg with defaults first, then optionally overlays the
 * persistent config file, then calls us so CLI wins over both.
 * (If a flag isn't passed on the command line, the corresponding
 * field is left untouched.) */
static int parse_args(int argc, char **argv)
{
    static struct option longopts[] = {
        { "help",         no_argument,       NULL, 'h' },
        { "version",      no_argument,       NULL, 'v' },
        { "rtsp-port",    required_argument, NULL,  1  },
        { "sensor-cfg",   required_argument, NULL,  2  },
        { "fps",          required_argument, NULL,  3  },
        { "main-kbps",    required_argument, NULL,  4  },
        { "sub-kbps",     required_argument, NULL,  5  },
        { "main-codec",   required_argument, NULL,  6  },
        { "sub-codec",    required_argument, NULL,  7  },
        { "no-main",      no_argument,       NULL,  8  },
        { "no-sub",       no_argument,       NULL,  9  },
        { "no-watchdog",  no_argument,       NULL, 10  },
        { "no-ir",        no_argument,       NULL, 12  },
        { NULL, 0, NULL, 0 }
    };

    int c;
    while ((c = getopt_long(argc, argv, "hv", longopts, NULL)) != -1) {
        switch (c) {
        case 'h': usage(argv[0]); return 1;
        case 'v': fprintf(stderr, "ipcd " IPCD_VERSION "\n"); return 1;
        case 1: {
            int p = atoi(optarg);
            if (p <= 0 || p > 65535) {
                fprintf(stderr, "invalid --rtsp-port\n"); return 2;
            }
            g_capture_cfg.rtsp_port = p; break;
        }
        case 2: g_capture_cfg.sensor_cfg_path = optarg; break;
        case 3: {
            int f = atoi(optarg);
            if (f <= 0 || f > 60) {
                fprintf(stderr, "invalid --fps\n"); return 2;
            }
            g_capture_cfg.fps = f; break;
        }
        case 4: g_capture_cfg.main_kbps = atoi(optarg); break;
        case 5: g_capture_cfg.sub_kbps  = atoi(optarg); break;
        case 6: case 7: {
            cap_codec_t k;
            if (!strcasecmp(optarg, "h264") || !strcasecmp(optarg, "avc")) {
                k = CAP_CODEC_H264;
            } else if (!strcasecmp(optarg, "h265") || !strcasecmp(optarg, "hevc")) {
                k = CAP_CODEC_HEVC;
            } else {
                fprintf(stderr, "invalid codec '%s' (h264 or h265)\n", optarg);
                return 2;
            }
            if (c == 6) g_capture_cfg.main_codec = k;
            else        g_capture_cfg.sub_codec  = k;
            break;
        }
        case  8: g_capture_cfg.enable_main   = 0; break;
        case  9: g_capture_cfg.enable_sub    = 0; break;
        case 10: g_capture_cfg.feed_watchdog = 0; break;
        case 12: g_capture_cfg.ir_enable     = 0; break;
        default:
            usage(argv[0]); return 2;
        }
    }

    if (!g_capture_cfg.enable_main && !g_capture_cfg.enable_sub) {
        fprintf(stderr, "error: --no-main and --no-sub together leave nothing to capture\n");
        return 2;
    }
    return 0;
}

/* ---------------------------------------------------------------- */
/* main                                                             */
/* ---------------------------------------------------------------- */
int main(int argc, char **argv)
{
    G.boot_time = time(NULL);

    /* Layered config: each layer overrides the previous one.
     *
     *   1. capture_cfg_defaults — hardcoded sensible defaults
     *   2. /etc/config/ipcd.conf — persisted via the web /config UI
     *   3. CLI args — explicit flags from argv
     *
     * That ordering means a one-shot CLI invocation (e.g. for
     * debug: --fps 30 --no-watchdog) takes effect even if the user
     * has saved a different fps via the web. The persisted config
     * is only used when the CLI doesn't say otherwise. */
    capture_cfg_defaults(&g_capture_cfg);
    ipcd_cfg_load(&g_capture_cfg);

    int rc = parse_args(argc, argv);
    if (rc != 0) return (rc == 1) ? 0 : rc;

    fprintf(stderr,
        "ipcd " IPCD_VERSION " starting "
        "(rtsp=%d, fps=%d, main=%s, sub=%s, ir=%s)\n",
        g_capture_cfg.rtsp_port,
        g_capture_cfg.fps,
        g_capture_cfg.main_codec == CAP_CODEC_HEVC ? "h265" : "h264",
        g_capture_cfg.sub_codec  == CAP_CODEC_HEVC ? "h265" : "h264",
        g_capture_cfg.ir_enable  ? "auto" : "off");

    /* Signals — see the long comment near on_term about why we
     * don't install a SIGCHLD handler. */
    struct sigaction sa = {0};
    sa.sa_handler = on_term;
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGINT,  &sa, NULL);
    signal(SIGPIPE, SIG_IGN);

    /* LEDs: clear initial state. red_led was set by main.sh, leave it
     * be (boot indicator). We own blue_led from here on. */
    led_set(LED_RED, LED_OFF);
	led_set(LED_BLUE, LED_OFF);

    /* Modules with one-shot init */
    web_init();        /* picks up IPCD_WEB_RUNTIME=1 if set */
    stats_init();
    auth_init();       /* loads creds from cfgfile + seeds nonce secret */
    onvif_init();      /* WS-Discovery + events subsystem */

    /* Speaker for two-way audio talkback. Non-fatal if the SDK
     * AO symbols don't resolve — talkback simply won't work but
     * everything else continues normally. */
    audio_out_init();

    /* Mic capture for RTSP audio stream. Must come AFTER
     * audio_out_init: the AEC engine needs AO open as far-end
     * reference, otherwise echo cancellation has nothing to
     * subtract. Non-fatal if it fails — the RTSP stream simply
     * won't have audio. */
    audio_in_init();

    /* HTTP server runs forever; serves the /api/ endpoints in any
     * state, the wifi config UI in AP mode, the stats/live UIs in
     * STA mode. */
    if (http_server_start(HTTP_PORT) != 0) {
        fprintf(stderr,
            "[main] http_server_start failed: %s\n", strerror(errno));
        /* Not fatal — keep going so the user can ssh in */
    }

    button_thread_start();

    mainloop();

    /* Shutdown */
    fprintf(stderr, "[main] shutting down\n");
    g_set_state(PCS_REBOOTING);
    onvif_shutdown();
    audio_in_shutdown();
    audio_out_shutdown();
    http_server_stop();
    stats_sampler_stop();
    capture_stop();
    wifi_stop_sta();
    wifi_stop_ap();
    led_set(LED_BLUE, LED_OFF);
    return 0;
}
