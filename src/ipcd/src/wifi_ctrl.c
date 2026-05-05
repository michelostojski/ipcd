/*
 * wifi_ctrl.c — wifi STA/AP orchestration.
 *
 * STA: write a fresh wpa_supplicant.conf with current creds, spawn
 *      wpa_supplicant -B, then udhcpc -b on wlan0.
 * AP : ifconfig wlan1 + hostapd -B + udhcpd.
 *
 * We launch helpers as detached children (fork+exec, no daemonisation
 * by us — wpa_supplicant -B and hostapd -B daemonise themselves; udhcpc
 * -b too). To stop, we use pkill by name + iface for clean teardown.
 *
 * Why pkill: simpler than tracking PIDs across reconfigs and matches
 * how the original Anyka scripts do it.
 *
 * Scan: in STA mode wpa_cli is the natural tool. We trigger scan and
 * read the table. Output is converted to a tiny JSON array.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>

#include "ipcd.h"

/* ---------------------------------------------------------------- */
/* small helpers                                                    */
/* ---------------------------------------------------------------- */
static int run_cmd(const char *fmt, ...)
{
    char cmd[512];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(cmd, sizeof(cmd), fmt, ap);
    va_end(ap);
    int rc = system(cmd);
    if (rc == -1) return -1;
    return WIFEXITED(rc) ? WEXITSTATUS(rc) : -1;
}

static int run_cmd_capture(char *out, size_t cap, const char *fmt, ...)
{
    char cmd[512];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(cmd, sizeof(cmd), fmt, ap);
    va_end(ap);
    FILE *p = popen(cmd, "r");
    if (!p) return -1;
    size_t n = fread(out, 1, cap - 1, p);
    out[n] = 0;
    return pclose(p) == 0 ? (int)n : -1;
}

/* Quote-escape an arbitrary byte string for a wpa_supplicant.conf
 * "..." literal. Backslash and dquote get escaped; everything else
 * passes through. WPA-PSK passphrases are 8..63 ASCII printable
 * chars by spec, but better safe than sorry. */
static void wpa_quote(const char *in, char *out, size_t cap)
{
    size_t o = 0;
    for (size_t i = 0; in[i] && o + 2 < cap; i++) {
        if (in[i] == '\\' || in[i] == '"') out[o++] = '\\';
        out[o++] = in[i];
    }
    out[o] = 0;
}

/* ---------------------------------------------------------------- */
/* STA                                                              */
/* ---------------------------------------------------------------- */
static int write_wpa_conf(const struct wifi_cfg *cfg)
{
    FILE *f = fopen(WPA_SUPPLICANT_RUN, "w");
    if (!f) return -1;

    char ssid_q[160], psk_q[280];
    wpa_quote(cfg->ssid, ssid_q, sizeof(ssid_q));
    wpa_quote(cfg->psk,  psk_q,  sizeof(psk_q));

    /* Network block matching the configuration that's known to work
     * on this hardware (verified against the user's manual wifi.sh
     * script which successfully associates and gets DHCP).
     *
     *  - key_mgmt: list WPA-PSK + SAE so we cover both WPA2 and WPA3
     *    networks. The atbm chip negotiates whichever the AP offers.
     *  - pairwise / group: include CCMP-256 explicitly. Some WPA3 APs
     *    (the user's router included) advertise CCMP-256 as required
     *    pairwise/group cipher; without it in our list, association
     *    succeeds but key install / 4-way handshake yields a driver
     *    state where DHCP frames silently get dropped.
     *  - ieee80211w=1: PMF capable, required by WPA3.
     *  - both psk and sae_password: psk for WPA2 path, sae_password
     *    for WPA3 path. Same string is fine for both (8-63 char rule
     *    only matters for psk).
     */
    fprintf(f,
        "ctrl_interface=%s\n"
        "ap_scan=1\n"
        "network={\n"
        "    ssid=\"%s\"\n"
        "    key_mgmt=WPA-PSK SAE\n"
        "    pairwise=CCMP CCMP-256\n"
        "    group=CCMP CCMP-256\n"
        "    ieee80211w=1\n"
        "    psk=\"%s\"\n"
        "    sae_password=\"%s\"\n"
        "    scan_ssid=0\n"
        "}\n",
        WPA_CTRL_DIR, ssid_q, psk_q, psk_q);
    fclose(f);
    chmod(WPA_SUPPLICANT_RUN, 0600);
    return 0;
}

int wifi_start_sta(const struct wifi_cfg *cfg)
{
    if (!cfg->configured) { errno = EINVAL; return -1; }

    /* Critical cleanup before spawning a new supplicant:
     *   1) Kill any wpa_supplicant currently running (e.g. the
     *      scan-only instance from AP mode, or a stale one).
     *   2) Remove the ctrl_interface socket file, which a previous
     *      unclean exit (or our own kill -9) may have left around;
     *      otherwise the new supplicant errors out with
     *      "ctrl_iface exists and seems to be in use - cannot override it".
     *   3) Bring the iface down briefly to clear residual driver
     *      state from the scan-only association attempts.
     */
    run_cmd("killall -q wpa_supplicant");
    /* Give it a moment to actually exit before we delete the ctrl file */
    for (int i = 0; i < 10; i++) {
        if (system("pgrep -x wpa_supplicant >/dev/null 2>&1") != 0) break;
        usleep(100 * 1000);
    }
    /* Force kill if still alive */
    run_cmd("killall -q -9 wpa_supplicant 2>/dev/null");
    usleep(100 * 1000);
    run_cmd("rm -f %s/%s 2>/dev/null", WPA_CTRL_DIR, STA_IFACE);

    if (write_wpa_conf(cfg) != 0) return -1;

    /* Bounce the iface to drop any half-state from previous attempt */
    run_cmd("ifconfig %s down 2>/dev/null", STA_IFACE);
    usleep(200 * 1000);
    run_cmd("ifconfig %s up", STA_IFACE);

    /* -B background, -D nl80211 (driver), -i iface, -c conf */
    if (run_cmd("wpa_supplicant -B -D nl80211 -i %s -c %s",
                STA_IFACE, WPA_SUPPLICANT_RUN) != 0) {
        /* some atbm builds register as "wext" instead — fallback */
        run_cmd("wpa_supplicant -B -D wext -i %s -c %s",
                STA_IFACE, WPA_SUPPLICANT_RUN);
    }

    /* Wait for association before launching DHCP. The atbm603x
     * driver, after `WLAN_CIPHER_SUITE_AES_CMAC` key install,
     * needs a few seconds before it reliably forwards data frames —
     * if udhcpc starts immediately, its DISCOVER packets get dropped
     * by the driver ("[wlan0]:[8] deliver slow" → "connecting done"
     * → DHCP timeout). The user's working wifi.sh script sleeps 5s
     * for the same reason.
     *
     * We poll wpa_cli status for "wpa_state=COMPLETED" which means
     * the 4-way handshake finished and keys are installed. Then we
     * give the driver an extra grace period before DHCP. */
    fprintf(stderr, "[wifi] waiting for association...\n");
    int associated = 0;
    for (int i = 0; i < 30; i++) {  /* up to 15s */
        usleep(500 * 1000);
        char st[256];
        int n = run_cmd_capture(st, sizeof(st),
            "wpa_cli -i %s status 2>/dev/null", STA_IFACE);
        if (n > 0 && strstr(st, "wpa_state=COMPLETED")) {
            fprintf(stderr, "[wifi] associated (wpa_state=COMPLETED)\n");
            associated = 1;
            break;
        }
    }
    if (!associated) {
        /* The most common cause on cold boot is low entropy: the
         * 4-way handshake on this driver (atbm603x) sometimes
         * stalls during PTK derivation if /dev/urandom hasn't yet
         * accumulated enough entropy. The supplicant logs nothing
         * useful — it just sits in "connecting" forever. A clean
         * relaunch typically fixes it because by then the kernel
         * has gathered more interrupt-driven entropy.
         *
         * We signal the failure type via the return value so the
         * caller (try_sta) can decide whether to retry. */
        fprintf(stderr, "[wifi] association did not complete in 15s\n");
        return WIFI_STA_NOT_ASSOCIATED;
    }

    /* Driver settle time. Even after wpa_state=COMPLETED, the atbm
     * data path needs ~3s to be reliable. Empirical. */
    sleep(3);

    /* Get DHCP lease in background. -t 5: 5 retries, then give up. */
    run_cmd("udhcpc -i %s -t 5 -T 3 -A 5", STA_IFACE);

    return WIFI_STA_OK;
}

int wifi_stop_sta(void)
{
    run_cmd("killall -q udhcpc");
    run_cmd("killall -q wpa_supplicant");
    /* Best-effort wait + force */
    for (int i = 0; i < 5; i++) {
        if (system("pgrep -x wpa_supplicant >/dev/null 2>&1") != 0) break;
        usleep(100 * 1000);
    }
    run_cmd("killall -q -9 wpa_supplicant 2>/dev/null");
    /* Clean up ctrl_interface socket */
    run_cmd("rm -f %s/%s 2>/dev/null", WPA_CTRL_DIR, STA_IFACE);
    run_cmd("ifconfig %s down 2>/dev/null", STA_IFACE);
    return 0;
}

/* Scan-only mode: bring wpa_supplicant up on STA_IFACE with NO
 * configured networks, so it can perform scans on demand but won't
 * try to associate. Used during AP mode so the web UI's "Scan" button
 * has something to talk to. The atbm chip has separate wlan0/wlan1
 * VIFs and tolerates this concurrent-with-AP setup; the radio briefly
 * leaves the AP channel during scan, which is acceptable for a few
 * seconds while the user is provisioning. */
int wifi_start_scan_only(void)
{
    /* Make sure no other wpa_supplicant / leftover ctrl file */
    run_cmd("killall -q wpa_supplicant");
    usleep(200 * 1000);
    run_cmd("rm -f %s/%s 2>/dev/null", WPA_CTRL_DIR, STA_IFACE);

    FILE *f = fopen(WPA_SUPPLICANT_RUN, "w");
    if (!f) return -1;
    fprintf(f,
        "ctrl_interface=%s\n"
        "ap_scan=1\n"
        /* No network={} blocks — wpa_supplicant will sit idle but
         * still accept scan/scan_results commands via wpa_cli. */
        ,
        WPA_CTRL_DIR);
    fclose(f);
    chmod(WPA_SUPPLICANT_RUN, 0600);

    run_cmd("ifconfig %s up", STA_IFACE);

    if (run_cmd("wpa_supplicant -B -D nl80211 -i %s -c %s",
                STA_IFACE, WPA_SUPPLICANT_RUN) != 0) {
        run_cmd("wpa_supplicant -B -D wext -i %s -c %s",
                STA_IFACE, WPA_SUPPLICANT_RUN);
    }
    /* No udhcpc — we don't want a lease in this mode. */
    return 0;
}

int wifi_sta_has_ip(char ip_out[16])
{
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0) return 0;
    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, STA_IFACE, IFNAMSIZ - 1);
    int got = (ioctl(s, SIOCGIFADDR, &ifr) == 0);
    close(s);
    if (!got) { ip_out[0] = 0; return 0; }
    struct sockaddr_in *sin = (struct sockaddr_in *)&ifr.ifr_addr;
    snprintf(ip_out, 16, "%s", inet_ntoa(sin->sin_addr));
    return ip_out[0] != 0 && strcmp(ip_out, "0.0.0.0") != 0;
}

/* ---------------------------------------------------------------- */
/* AP                                                               */
/* ---------------------------------------------------------------- */

/* Was the AP successfully brought up? Two checks:
 *
 *  1) hostapd's per-iface ctrl_iface socket exists at
 *     /tmp/hostapd/<iface>. This appears only after hostapd has
 *     completed nl80211 setup and is serving — it's the canonical
 *     "ready" signal that wpa_cli/hostapd_cli rely on.
 *
 *  2) The iface has its expected IPv4 address up (we set it via
 *     ifconfig before launching hostapd).
 *
 * We can't trust the return code of `hostapd -B` alone: on this
 * device the entropy pool is small at boot, and hostapd's parent
 * sometimes times out waiting for the daemonised child to signal
 * "init done" via its internal pipe — even though the child does
 * eventually finish init and reach AP-ENABLED. We've seen the
 * parent return non-zero while AP-ENABLED appears in the log
 * milliseconds later. Polling the ctrl_iface socket sidesteps
 * the entire question. */
static int hostapd_iface_ready(void)
{
    char path[128];
    snprintf(path, sizeof(path), "%s/%s", HOSTAPD_CTRL_DIR, AP_IFACE);
    struct stat st;
    return (stat(path, &st) == 0);
}

/* Best-effort cleanup of any half-started AP state.
 *
 * IMPORTANT: do NOT bring wlan1 down here. The atbm driver tears
 * down and re-creates the iface on every iftype change (visible in
 * dmesg as `atbm_remove_interface` followed by `Interface ID:1 of
 * type:N added`). If we `ifconfig wlan1 down` and then immediately
 * try `ifconfig wlan1 ... up`, the driver is still mid-recreation
 * in STA mode (type 2) and the `up` fails. hostapd, when launched,
 * does its own iftype-set-to-AP via nl80211 — that's the only path
 * this driver reliably accepts.
 *
 * What we *do* clean up:
 *   - hostapd processes (with grace period before SIGKILL)
 *   - the leftover ctrl_iface socket (so a fresh hostapd doesn't
 *     refuse to start with "ctrl_iface exists and seems to be in use")
 *   - udhcpd
 *
 * The mon.<iface> monitor interface is auto-cleaned by hostapd on
 * its own startup when it claims the iface, so we don't touch it. */
static void ap_cleanup_residual(void)
{
    run_cmd("killall -q udhcpd 2>/dev/null");
    run_cmd("killall -q hostapd 2>/dev/null");
    /* Wait briefly for hostapd to actually die before clearing the
     * ctrl socket, otherwise it can rewrite it on the way out. */
    for (int i = 0; i < 10; i++) {
        if (system("pgrep -x hostapd >/dev/null 2>&1") != 0) break;
        usleep(100 * 1000);
    }
    run_cmd("killall -q -9 hostapd 2>/dev/null");
    run_cmd("rm -f %s/%s 2>/dev/null", HOSTAPD_CTRL_DIR, AP_IFACE);
}

int wifi_start_ap(void)
{
    /* In case STA path left something running */
    wifi_stop_sta();

    /* Drop any half-state from a previous attempt before we touch
     * the iface again. This is what makes a retry actually retry-
     * able instead of compounding the failure. */
    ap_cleanup_residual();

    /* Don't pre-`ifconfig up` wlan1 — hostapd handles iftype + bring-
     * up via nl80211. On a cold boot wlan1 may not even be in AP
     * iftype yet (atbm creates it as STA by default), and ifconfig
     * with an IP would fail. We assign the AP's static IP *after*
     * hostapd has the iface in AP mode and up. */

    /* Launch hostapd. We poll the ctrl_iface socket for readiness
     * rather than just trusting `hostapd -B`'s exit code: even when
     * the parent exits 0, the daemonised child may still be a tick
     * away from accepting connections. Cheap insurance. */
    run_cmd("hostapd -B %s 2>&1", HOSTAPD_CONF_PATH);

    /* Poll for readiness up to 12s. The signal we trust is hostapd's
     * per-iface ctrl_iface socket at /tmp/hostapd/<iface>: it's
     * created only after nl80211 setup is done and hostapd is
     * serving. */
    int ready = 0;
    for (int i = 0; i < 60; i++) {  /* 60 * 200ms = 12s */
        usleep(200 * 1000);
        if (hostapd_iface_ready()) {
            ready = 1;
            break;
        }
        /* If hostapd died early (e.g. config error), bail out fast. */
        if (i > 3 && system("pgrep -x hostapd >/dev/null 2>&1") != 0) {
            fprintf(stderr, "[wifi] hostapd exited during init\n");
            break;
        }
    }
    if (!ready) {
        fprintf(stderr, "[wifi] AP did not become ready within 12s\n");
        ap_cleanup_residual();
        return -1;
    }

    /* Make sure wlan1 has the expected static IP. The original code
     * did `ifconfig ... up` BEFORE hostapd; that's what we restore
     * here in spirit, but we also tolerate the case where hostapd
     * has already brought the iface up by the time we check. */
    run_cmd("ifconfig %s %s netmask %s 2>/dev/null",
            AP_IFACE, AP_LOCAL_IP, AP_NETMASK);

    /* Now check the truth: does wlan1 have a non-zero IPv4 address?
     * Retry briefly in case the kernel's address-set takes a moment
     * to be readable via SIOCGIFADDR. */
    char actual_ip[16] = {0};
    int  ip_ok = 0;
    for (int i = 0; i < 10; i++) {
        int s = socket(AF_INET, SOCK_DGRAM, 0);
        if (s >= 0) {
            struct ifreq ifr;
            memset(&ifr, 0, sizeof(ifr));
            strncpy(ifr.ifr_name, AP_IFACE, IFNAMSIZ - 1);
            if (ioctl(s, SIOCGIFADDR, &ifr) == 0) {
                struct sockaddr_in *sin = (struct sockaddr_in *)&ifr.ifr_addr;
                snprintf(actual_ip, sizeof(actual_ip), "%s",
                         inet_ntoa(sin->sin_addr));
                if (actual_ip[0] && strcmp(actual_ip, "0.0.0.0") != 0) {
                    ip_ok = 1;
                    close(s);
                    break;
                }
            }
            close(s);
        }
        usleep(200 * 1000);
    }
    if (!ip_ok) {
        fprintf(stderr, "[wifi] %s has no IP after AP up — aborting\n",
                AP_IFACE);
        ap_cleanup_residual();
        return -1;
    }
    if (strcmp(actual_ip, AP_LOCAL_IP) != 0) {
        /* Got *some* IP but not the one we wanted. Log it and
         * continue — captive portal will follow whatever the iface
         * actually has. dnsmasq/dns_spoof reads the iface address. */
        fprintf(stderr, "[wifi] %s ip = %s (expected %s, continuing)\n",
                AP_IFACE, actual_ip, AP_LOCAL_IP);
    } else {
        fprintf(stderr, "[wifi] %s ip = %s\n", AP_IFACE, actual_ip);
    }

    fprintf(stderr, "[wifi] AP up on %s (%s, ssid per %s)\n",
            AP_IFACE, AP_LOCAL_IP, HOSTAPD_CONF_PATH);

    /* DHCP server. Cross-check via pgrep that it's actually running
     * after the start command — same readiness pattern as hostapd. */
    run_cmd("udhcpd %s 2>&1", UDHCPD_CONF_PATH);
    usleep(300 * 1000);
    if (system("pgrep -x udhcpd >/dev/null 2>&1") != 0) {
        fprintf(stderr, "[wifi] udhcpd not running after start "
                        "(clients will need static IP)\n");
    }
    return 0;
}

int wifi_stop_ap(void)
{
    /* Routed through the same cleanup helper as start, so behaviour
     * is symmetric and we can't accidentally diverge the two paths. */
    ap_cleanup_residual();
    return 0;
}

/* ---------------------------------------------------------------- */
/* SCAN — uses wpa_cli on the persistent scan-only supplicant       */
/* started by wifi_start_scan_only() during AP mode. The atbm chip  */
/* has dual VIFs (wlan0/wlan1) and tolerates a scan-only supplicant */
/* on wlan0 while hostapd runs on wlan1.                            */
/*                                                                  */
/* Earlier we worried this would taint the driver and break the     */
/* next STA association — but the actual cause of that DHCP failure */
/* was timing (driver data path needs a few seconds to be stable    */
/* after key install). With wifi_start_sta() now waiting for        */
/* wpa_state=COMPLETED + 5s settle before launching udhcpc, the     */
/* persistent scan-only path is fine.                               */
/*                                                                  */
/* Stopping hostapd during scan was a non-starter: when the AP      */
/* drops, Android kicks the user out of the captive portal page     */
/* and the scan results never make it back to the browser.          */
/* ---------------------------------------------------------------- */
static int wpa_cli_ping(void)
{
    char buf[64];
    int n = run_cmd_capture(buf, sizeof(buf),
        "wpa_cli -i %s ping 2>/dev/null", STA_IFACE);
    if (n <= 0) return 0;
    return strstr(buf, "PONG") != NULL;
}

int wifi_sta_scan(char *json_out, size_t cap)
{
    /* In STA_OK mode wpa_supplicant is already running with the
     * configured network.  We must NOT kill/restart it — that would
     * drop the WiFi connection.  Instead we just issue a scan
     * command on the existing ctrl socket.  If the supplicant is
     * busy (roaming / DHCP renewal) it replies FAIL-BUSY; we retry
     * a few times before giving up.
     *
     * In AP_MODE the scan-only supplicant may or may not be up yet.
     * If wpa_cli ping fails we bring it up with wifi_start_scan_only,
     * which is safe because in AP mode there is no STA connection to
     * protect. */
    if (!wpa_cli_ping()) {
        if (g_get_state() == PCS_STA_OK) {
            /* STA supplicant not responding — unusual but possible
             * right after association.  Give it a short grace period
             * before declaring failure. */
            for (int i = 0; i < 6; i++) {
                usleep(300 * 1000);
                if (wpa_cli_ping()) break;
            }
        }
        if (!wpa_cli_ping()) {
            /* Only start scan-only supplicant when we're not online. */
            if (g_get_state() != PCS_STA_OK) {
                fprintf(stderr, "[scan] supplicant not responding, starting scan-only\n");
                wifi_start_scan_only();
                for (int i = 0; i < 15; i++) {
                    usleep(200 * 1000);
                    if (wpa_cli_ping()) break;
                }
            }
            if (!wpa_cli_ping()) {
                fprintf(stderr, "[scan] supplicant still not responding\n");
                snprintf(json_out, cap, "[]");
                return -1;
            }
        }
    }

    /* Trigger scan — retry on FAIL-BUSY (supplicant is mid-roam or
     * processing a previous scan). */
    char rb[64];
    for (int attempt = 0; attempt < 5; attempt++) {
        run_cmd_capture(rb, sizeof(rb),
            "wpa_cli -i %s scan 2>&1", STA_IFACE);
        if (strstr(rb, "FAIL-BUSY") == NULL) break;
        usleep(600 * 1000);
    }

    /* Poll for results up to 8 seconds. scan_results returns the
     * cached BSS table which gets populated as the scan progresses. */
    char buf[8192];
    int n = -1;
    int got_results = 0;
    for (int i = 0; i < 16; i++) {
        usleep(500 * 1000);
        n = run_cmd_capture(buf, sizeof(buf),
            "wpa_cli -i %s scan_results 2>/dev/null", STA_IFACE);
        if (n > 0) {
            char *first_nl = strchr(buf, '\n');
            if (first_nl && first_nl[1] != 0) {
                got_results = 1;
                break;
            }
        }
    }
    if (!got_results) {
        snprintf(json_out, cap, "[]");
        return -1;
    }

    /* scan_results output:
     *   bssid / frequency / signal level / flags / ssid
     *   aa:bb:cc:dd:ee:ff  2412  -55  [WPA2-PSK-CCMP][ESS]  MyNet
     * First line is header. Tab-separated. SSID may contain spaces.
     */
    size_t o = 0;
    o += snprintf(json_out + o, cap - o, "[");
    int first = 1;

    char *p = buf;
    /* skip first header line */
    char *nl = strchr(p, '\n');
    if (nl) p = nl + 1;

    while (*p) {
        char *line_end = strchr(p, '\n');
        if (!line_end) line_end = p + strlen(p);

        char line[512];
        size_t L = (size_t)(line_end - p);
        if (L >= sizeof(line)) L = sizeof(line) - 1;
        memcpy(line, p, L); line[L] = 0;

        /* Split by tabs: bssid / freq / sig / flags / ssid */
        char *t1 = strchr(line, '\t');     /* after bssid */
        char *t2 = t1 ? strchr(t1+1, '\t') : NULL;  /* after freq */
        char *t3 = t2 ? strchr(t2+1, '\t') : NULL;  /* after sig  */
        char *t4 = t3 ? strchr(t3+1, '\t') : NULL;  /* after flags */
        if (t1 && t2 && t3 && t4) {
            *t1 = *t2 = *t3 = *t4 = 0;
            const char *bssid = line;
            int  sig   = atoi(t2 + 1);
            const char *flags = t3 + 1;
            const char *ssid  = t4 + 1;
            int sec = (strstr(flags, "WPA") || strstr(flags, "WEP")) ? 1 : 0;

            if (ssid[0]) {
                if (!first && o + 2 < cap) json_out[o++] = ',';
                /* JSON-escape ssid: just escape backslash and dquote */
                char esc[128]; size_t eo = 0;
                for (size_t i = 0; ssid[i] && eo + 2 < sizeof(esc); i++) {
                    if (ssid[i] == '"' || ssid[i] == '\\') esc[eo++] = '\\';
                    esc[eo++] = ssid[i];
                }
                esc[eo] = 0;
                int w = snprintf(json_out + o, cap - o,
                    "{\"ssid\":\"%s\",\"bssid\":\"%s\",\"sig\":%d,\"sec\":%d}",
                    esc, bssid, sig, sec);
                if (w > 0 && (size_t)w < cap - o) o += (size_t)w;
                first = 0;
            }
        }
        if (*line_end == 0) break;
        p = line_end + 1;
    }

    if (o + 2 < cap) { json_out[o++] = ']'; json_out[o] = 0; }
    return 0;
}