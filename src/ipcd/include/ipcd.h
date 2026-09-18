/*
 * ipcd.h — IP Cam Daemon, single-binary public API.
 *
 * Replaces the proxycam + proxy_capture pair with one process.
 * Every module's externally visible symbols live here, so other
 * modules don't have to chase per-module headers.
 *
 * Module map:
 *   netmgr (main.c)  state machine, signal handling, glue
 *   wifi   (wifi_*.c, dns_spoof.c, button.c, led.c, timesync.c)
 *                    wifi STA/AP, captive portal, NTP, button, LED
 *   cap    (cap_*.c) VI/VENC pipeline (ex-proxy_capture)
 *   rtsp   (rtsp_server.c) RTSP/RTP server on :8554
 *   ir     (ir.c)    day/night detector + IR-LED driver
 *   stats  (stats.c) per-second sampling for the stats UI
 *   http   (http_srv.c) embedded HTTP/1.1 on :80
 *   web    (web_assets.c) embedded HTML/CSS/JS blobs
 */
#ifndef IPCD_H
#define IPCD_H

#include <stdint.h>
#include <stddef.h>
#include <pthread.h>
#include <sys/types.h>

/* Version, exposed across modules. Overridable from the Makefile
 * for git-based version stamping. */
#ifndef IPCD_VERSION
#define IPCD_VERSION "0.3.0"
#endif

/* ---------------------------------------------------------------- */
/* Build-time paths                                                 */
/* ---------------------------------------------------------------- */
#define WIFI_CONF_PATH        "/etc/config/wifi.conf"
#define IPCD_CONF_PATH        "/etc/config/ipcd.conf"
#define HOSTAPD_CONF_PATH     "/etc/config/hostapd.conf"
#define UDHCPD_CONF_PATH      "/etc/config/udhcpd.conf"
#define WPA_SUPPLICANT_RUN    "/var/run/ipcd_wpa.conf"
#define WPA_CTRL_DIR          "/var/run/wpa_supplicant"
#define HOSTAPD_CTRL_DIR      "/tmp/hostapd"
#define INPUT_EVENT_DEV       "/dev/input/event0"

#define LED_BLUE              "/sys/class/leds/blue_led"
#define LED_RED               "/sys/class/leds/red_led"
#define LED_WIFI              "/sys/class/leds/wifi_pwr"

#define STA_IFACE             "wlan0"
#define AP_IFACE              "wlan1"
#define AP_LOCAL_IP           "10.1.8.1"
#define AP_NETMASK            "255.255.255.0"

#define STA_CONNECT_TIMEOUT_S    30
#define STA_RETRIES_BEFORE_AP     3
#define BUTTON_HOLD_MS_RESET   5000

/* Listening ports */
#define HTTP_PORT            80
#define RTSP_PORT_DEFAULT  8554

/* Where loose web assets live at runtime if IPCD_WEB_RUNTIME=1.
 * Useful for iterating on HTML without recompiling. */
#define WEB_RUNTIME_DIR      "/mnt/ipcd/web"

/* ---------------------------------------------------------------- */
/* netmgr state                                                     */
/* ---------------------------------------------------------------- */
typedef enum {
    PCS_BOOT       = 0,
    PCS_STA_TRY    = 1,
    PCS_STA_OK     = 2,
    PCS_AP_MODE    = 3,
    PCS_REBOOTING  = 4,
} pc_state_t;

const char *pc_state_name(pc_state_t s);
pc_state_t  g_get_state(void);
void        g_set_state(pc_state_t s);

/* ---------------------------------------------------------------- */
/* Wi-Fi credentials                                                */
/* ---------------------------------------------------------------- */
struct wifi_cfg {
    char ssid[64];
    char psk [128];
    int  configured;
};

int  wifi_cfg_load(struct wifi_cfg *out);
int  wifi_cfg_save(const struct wifi_cfg *in);
int  wifi_cfg_wipe(void);

/* ---------------------------------------------------------------- */
/* Wi-Fi control                                                    */
/* ---------------------------------------------------------------- */
/* wifi_start_sta return codes. Distinguishing "not associated"
 * from generic failure lets the caller (main.c try_sta) retry
 * specifically on the entropy-related case where a clean
 * relaunch typically succeeds. */
#define WIFI_STA_OK              0
#define WIFI_STA_NOT_ASSOCIATED  2   /* 4-way handshake stalled */
/* (any other negative value is a hard error) */

int  wifi_start_sta(const struct wifi_cfg *cfg);
int  wifi_stop_sta (void);
int  wifi_start_ap (void);
int  wifi_stop_ap  (void);
int  wifi_start_scan_only(void);
int  wifi_sta_has_ip(char ip_out[16]);
int  wifi_sta_scan(char *json_out, size_t cap);

/* ---------------------------------------------------------------- */
/* IR mode (full IR API is further down; the type is needed earlier */
/* by struct capture_cfg, hence the forward typedef here).         */
/* ---------------------------------------------------------------- */
typedef enum {
    IR_MODE_OFF         = 0,    /* day forced */
    IR_MODE_AUTO        = 1,    /* let the SDK switch based on luma */
    IR_MODE_FORCE_NIGHT = 2,    /* night forced (for testing) */
} ir_mode_t;

/* ---------------------------------------------------------------- */
/* Capture (ex-proxy_capture)                                      */
/* ---------------------------------------------------------------- */
typedef enum {
    CAP_CODEC_H264 = 0,
    CAP_CODEC_HEVC = 1,
} cap_codec_t;

struct capture_cfg {
    int           rtsp_port;
    const char   *sensor_cfg_path;     /* NULL -> default */
    int           enable_main, enable_sub;
    int           main_w, main_h, main_kbps;
    int           sub_w,  sub_h,  sub_kbps;
    int           fps, gop_sec;
    cap_codec_t   main_codec, sub_codec;
    unsigned int  max_exp_lines;       /* 0 = no cap */
    int           feed_watchdog;
    int           ir_enable;           /* 1 = call ir_init() */
    ir_mode_t     ir_initial_mode;     /* default IR_MODE_AUTO */
};

void capture_cfg_defaults(struct capture_cfg *cfg);

/* Snapshot of the running capture config; safe to call from any
 * thread. Implemented in main.c. */
void capture_cfg_get(struct capture_cfg *out);

/* Replace the running config + persist to /etc/config/ipcd.conf.
 * After this returns, callers wanting changes to take effect must
 * also call capture_stop() + capture_start() (unless they only
 * touched runtime-tunable fields, in which case capture_apply_runtime
 * is enough). */
int  capture_cfg_set(const struct capture_cfg *in);

/* Start the whole VI/VENC + RTSP pipeline. Returns 0 on success.
 * Spawns its own threads; this call returns immediately. */
int  capture_start(const struct capture_cfg *cfg);

/* Tear everything down: VI, VENC, RTSP, HLS, stream workers.
 * Blocks until threads have joined. */
void capture_stop(void);
void cap_set_chroma(int color);

int  capture_is_running(void);

/* Re-apply only the live-tunable parameters of cfg (currently:
 * main_kbps, sub_kbps). Returns 0 on success. Doesn't touch VENC
 * codec, fps, or stream enable flags — those need a full
 * capture_stop() + capture_start() cycle. */
int  capture_apply_runtime(const struct capture_cfg *cfg);

/* ---------------------------------------------------------------- */
/* Persistent config (/etc/config/ipcd.conf)                       */
/* ---------------------------------------------------------------- */
/* Load file into cfg. Returns 0 if loaded, -1 if file missing. The
 * cfg should be pre-populated with defaults; only keys actually
 * present in the file are overwritten. */
int  ipcd_cfg_load(struct capture_cfg *cfg);

/* Atomic save of cfg to /etc/config/ipcd.conf. Writes via .tmp +
 * rename so a power-off mid-write doesn't corrupt the file. */
int  ipcd_cfg_save(const struct capture_cfg *cfg);

/* Render cfg as JSON for the GET /api/config endpoint. */
size_t ipcd_cfg_to_json(const struct capture_cfg *cfg, char *out, size_t cap);

/* ---------------------------------------------------------------- */
/* RTSP server                                                      */
/* ---------------------------------------------------------------- */
enum rtsp_codec {
    RTSP_CODEC_NONE = 0,
    RTSP_CODEC_H264,
    RTSP_CODEC_H265,
};
enum rtsp_au_kind {
    RTSP_AU_NORMAL = 0,
    RTSP_AU_IDR    = 1,
};
#define RTSP_MAX_STREAMS  2

int  rtsp_server_init(int listen_port,
                      const enum rtsp_codec stream_codecs[RTSP_MAX_STREAMS]);
void rtsp_server_shutdown(void);
int  rtsp_server_push_au(int stream_idx, uint64_t ts_ms,
                         const uint8_t * const *nals,
                         const size_t *nal_lens,
                         int nal_count, enum rtsp_au_kind kind);
int  rtsp_server_active_clients(void);    /* used by /api/stats */

/* ---------------------------------------------------------------- */
/* IR / day-night automatic switching                              */
/* ---------------------------------------------------------------- */
/* Mode is currently always AUTO when enabled (manual override
 * possible via the API for debug). The actual GPIO / IR-cut /
 * IR-LED toggling is delegated to the SDK via
 * ak_vpss_set_auto_day_night_param() — that function reads the
 * current scene luma from the ISP, applies hysteresis, and drives
 * the GPIOs registered by the kernel ircut/irled drivers. */

int  ir_init(void);
void ir_shutdown(void);
int  ir_set_mode(ir_mode_t mode);
ir_mode_t ir_get_mode(void);
/* Last reported scene luma + computed level. level: 0 = day, 1 = night */
int  ir_get_level(void);
unsigned int ir_get_luma(void);

/* Threshold accessors: which=0 reads/writes night_to_day_lum,
 * which=1 reads/writes day_to_night_lum. */
void         ir_set_threshold(int which, unsigned int value);
unsigned int ir_get_threshold(int which);

/* ---------------------------------------------------------------- */
/* Stats                                                            */
/* ---------------------------------------------------------------- */
struct stats_stream_now {
    int      enabled;
    int      width, height, fps_target;
    int      kbps_target;
    /* Live, last-second window: */
    double   fps_actual;
    double   kbps_actual;
    uint32_t total_frames;
    uint32_t total_keyframes;
    uint32_t push_fails;
    uint32_t max_frame_bytes;
    uint64_t total_bytes;
    /* Codec name for UI: "h264" / "h265" */
    const char *codec;
    /* Sparkline rings: 60 samples, oldest first. */
    uint16_t fps_hist[60];
    uint16_t kbps_hist[60];
};

struct stats_snapshot {
    /* Wi-Fi / system */
    pc_state_t  state;
    char        state_name[16];
    char        ssid[64];
    char        ip[16];
    int         configured;
    /* Capture */
    struct stats_stream_now streams[2];
    int         rtsp_clients;
    /* Day/night */
    int         ir_mode;       /* ir_mode_t */
    int         ir_level;      /* 0 day, 1 night */
    unsigned    ir_luma;
    /* Process */
    long        uptime_s;
    long        rss_kb;
};

/* Called by stream_worker on each completed frame. */
void stats_record_frame(int stream_idx, uint32_t bytes,
                        int is_keyframe, int push_failed);

/* Setup: declare what each stream is configured for (called by
 * capture init). After this, stats_record_frame can be called. */
void stats_init(void);
void stats_set_stream_cfg(int idx, int enabled, int w, int h,
                          int fps_target, int kbps_target,
                          cap_codec_t codec);
/* Sampling thread: should be started after capture is up. */
int  stats_sampler_start(void);
void stats_sampler_stop(void);

/* Atomic snapshot. Caller passes in a struct, we fill it under
 * the stats mutex. Cheap. */
void stats_get(struct stats_snapshot *out);
/* Same, but only emits the JSON. Returns bytes written. */
size_t stats_to_json(char *buf, size_t cap);

/* ---------------------------------------------------------------- */
/* HTTP server                                                      */
/* ---------------------------------------------------------------- */
int  http_server_start(int port);
void http_server_stop (void);

/* ---------------------------------------------------------------- */
/* Web assets                                                       */
/*                                                                  */
/* By default, HTML/CSS/JS are baked into the binary via xxd. If    */
/* the env var IPCD_WEB_RUNTIME=1 is set at startup, web_get_asset  */
/* tries WEB_RUNTIME_DIR first (mtime-cached). Fallback is always   */
/* the embedded blob.                                              */
/* ---------------------------------------------------------------- */
struct web_asset {
    const char *name;            /* e.g. "index.html" */
    const char *ctype;           /* e.g. "text/html; charset=utf-8" */
    const unsigned char *data;   /* embedded blob */
    unsigned int len;
};

void web_init(void);   /* called once at startup */

/* Returns asset by exact filename. NULL if not found.
 *
 * NB: the returned pointer is stable for the lifetime of the
 * process when serving from the embedded blob, but when serving
 * from runtime files it points into a per-request malloc that the
 * caller must free via web_release() exactly once. To make the
 * caller's job simple, we always return a heap copy and you always
 * call web_release(). It's a couple hundred bytes per request, no
 * big deal on this device.
 */
struct web_asset_buf {
    const char    *ctype;
    unsigned char *data;
    size_t         len;
    int            owns;     /* 1 = malloc'd, must free */
};
int  web_get(const char *name, struct web_asset_buf *out);
void web_release(struct web_asset_buf *buf);

/* ---------------------------------------------------------------- */
/* Audio output (audio_out.c) — speaker for two-way audio talkback */
/*                                                                  */
/* The module owns the AO (audio output) channel and the amp        */
/* GPIO. It exposes a push API for callers (HTTP /talkback handler  */
/* and eventually ONVIF Profile T backchannel) that decodes and    */
/* mixes their data into the playback ring.                         */
/* ---------------------------------------------------------------- */

/* Codec identifiers — keep in sync with the ?codec= URL param on
 * /talkback and with the RTP payload types we accept. */
#define AUDIO_CODEC_PCM    0
#define AUDIO_CODEC_G711U  1   /* µ-law, RTP PT=0 */
#define AUDIO_CODEC_G711A  2   /* A-law, RTP PT=8 */
#define AUDIO_CODEC_AAC    3   /* TODO via SDK adec */

/* Initialize the speaker subsystem: opens AO channel, enables the
 * amp GPIO, starts the playback thread. Idempotent. Returns 0 on
 * success. Failure is non-fatal at the daemon level — talkback
 * just won't work, but everything else continues. */
int  audio_out_init(void);
void audio_out_shutdown(void);

/* True if the speaker is up and accepting frames. */
int  audio_out_is_available(void);

/* Push 16-bit signed mono PCM at the AO sample rate (16 kHz).
 * Returns 0 on success. */
int  audio_out_push_pcm(const int16_t *samples, size_t n_samples);

/* Push 8 kHz G.711 µ-law or A-law bytes. They are decoded to PCM
 * and upsampled to 16 kHz before being queued. */
int  audio_out_push_g711(int codec, const uint8_t *buf, size_t len);

/* Flush trailing tail of the ring (<AO_FRAME_BYTES) with silence
 * padding to mono-alignment. Called at end of /talkback so the
 * last few bytes don't sit in the ring forever. */
void audio_out_flush(void);

/* Speaker volume in dB (SDK accepts roughly [-90..+20], we clamp
 * to [-40..+10] which is the practical useful range). 0 dB is
 * full DAC scale ("loud"); -12 dB is conversational; -40 dB is
 * effectively silent.
 *
 * audio_out_set_volume_db applies to the live AO handle if open
 * (immediate effect, no restart) and is also remembered for any
 * later AO re-open. */
void audio_out_set_volume_db(int db);
int  audio_out_get_volume_db(void);

/* ---------------------------------------------------------------- */
/* audio_in (audio_in.c) — mic capture + AEC + AENC G.711µ          */
/*                                                                  */
/* The module captures from the AI device with hardware AEC         */
/* (echo cancellation against the AO speaker output) and encodes   */
/* to G.711 µ-law for RTP packetization in the RTSP server.         */
/* ---------------------------------------------------------------- */

/* Initialize. Lazy: registers the module but does NOT open the
 * SDK chain yet. The SDK chain (AI + AEC + AENC + bind +
 * capture) is opened on first audio_in_acquire() call.
 *
 * Returns 0 on success. Non-fatal: even if it fails, video
 * works fine and the SDP simply won't advertise audio. */
int  audio_in_init(void);

/* Shutdown: stops chain if open, frees everything. */
void audio_in_shutdown(void);

/* True when the module is up. Note: this returns true even when
 * the SDK chain is closed (refcount == 0); the SDP advertises
 * audio always, and acquire() opens the chain on demand. */
int  audio_in_is_available(void);

/* Acquire / release the audio stream. Reference-counted.
 * The first acquire() opens the SDK chain (AI+AEC+AENC+bind+
 * capture); the matching last release() closes it. This avoids
 * burning CPU on AEC convolution + capture thread when no
 * client is asking for mic audio.
 *
 * acquire() returns 0 on success, -1 if the SDK chain failed
 * to open. release() is a void.
 *
 * Calls are paired: every acquire() must have a matching
 * release(). Typical use: audio_streamer_thread calls
 * acquire() at start, release() before exit. */
int  audio_in_acquire(void);
void audio_in_release(void);

/* Master enable: when 0, the mic is fully off — no SDK chain,
 * no SDP audio entry, no acquire() succeeds. Default 1.
 * Settable via /api/config audio_in_enable=0|1. */
void audio_in_set_enable(int enable);
int  audio_in_get_enable(void);

/* AEC toggle: when 0, the AEC convolution is bypassed. The mic
 * still works but echo from speaker→mic isn't cancelled. AEC
 * costs significant CPU on this single-core SoC; bypassing it
 * helps recover video fps when audio is active. Default 1.
 * Settable via /api/config audio_aec_enable=0|1. */
void audio_in_set_aec_enable(int enable);
int  audio_in_get_aec_enable(void);

/* Pull one G.711 µ-law encoded frame.
 *
 * On entry: *len is the size of the out buffer.
 * On success: returns 0, *len is the bytes actually written.
 * On no-frame: returns -1, *len = 0.
 * On not-initialized: returns -2.
 *
 * Typical frame size is 160 bytes (20 ms @ 8 kHz). */
int  audio_in_get_frame(uint8_t *out, size_t *len);

/* ---------------------------------------------------------------- */
/* ONVIF (onvif*.c) — SOAP services for Profile S + events         */
/*                                                                  */
/* Endpoints (all served by http_srv.c, routed to onvif_dispatch):  */
/*   POST /onvif/device_service                                    */
/*   POST /onvif/media_service                                     */
/*   POST /onvif/events_service                                    */
/*                                                                  */
/* WS-Discovery (separate UDP listener on port 3702 multicast):    */
/*   handled by onvif_wsd.c thread.                                 */
/* ---------------------------------------------------------------- */

/* Initialize the ONVIF subsystem: starts the WS-Discovery thread,
 * registers internal state. Idempotent. Returns 0 on success. */
int  onvif_init(void);

/* Tear down. Stops the WSD thread, frees state. */
void onvif_shutdown(void);

/* Dispatch a SOAP POST. The caller (http_srv.c) provides:
 *   - service_path: "/onvif/device_service" etc.
 *   - query: the URL query string (may be empty), used by event
 *     subscriptions to carry the subscription token in ?token=...
 *   - request_body: the XML SOAP envelope (NUL-terminated)
 *   - host_header: contents of the HTTP Host: header (e.g.
 *     "192.168.1.42:80") used to build absolute URLs in the
 *     response.
 *
 * Writes the SOAP response into out_buf, sets *out_len. Returns
 * 0 on success (HTTP 200 OK). On SOAP fault still returns 0 — the
 * HTTP layer is happy, the fault travels in the body. Returns -1
 * only on out-of-memory. */
int  onvif_dispatch(const char *service_path,
                    const char *query,
                    const char *request_body,
                    const char *host_header,
                    char       *out_buf,
                    size_t      out_cap,
                    size_t     *out_len);

/* Helpers exposed for cross-module use */
int  onvif_check_ws_security(const char *soap_xml);
int  onvif_b64_encode(const uint8_t *in, size_t len,
                      char *out, size_t cap);
int  onvif_b64_decode(const char *in, uint8_t *out, size_t cap);

/* Internal cross-module entry points (not for general use). */
int  onvif_wsd_start(void);
void onvif_wsd_stop(void);
int  onvif_events_init(void);
void onvif_events_shutdown(void);
int  onvif_events_dispatch(const char *op, const char *query,
                           const char *body,
                           const char *host, int port,
                           char *out, size_t cap, size_t *out_len);
  /* PTZ (onvif_ptz.c) */
size_t onvif_ptz_dispatch(const char *op, const char *body,
                          char *out, size_t cap);

/* Motion detection threshold — sum of per-block deltas from
 * ak_vpss_md_get_stat (range 0..1536*255). Default 1500.
 * Higher value = less sensitive. Live-tunable, no restart needed. */
void motion_set_threshold(int t);
int  motion_get_threshold(void);

/* ---------------------------------------------------------------- */
/* Snapshot (snapshot.c) — JPEG snapshot via on-demand VENC channel */
/*                                                                  */
/* The module owns a third VENC channel (chn_id=2) that's opened    */
/* only when needed and closed after a TTL of inactivity.           */
/*                                                                  */
/* Lifecycle wrt. capture:                                          */
/*   capture_start()  -> snapshot_init(vi_sub_chn_id)               */
/*   capture_stop()   -> snapshot_shutdown()                        */
/*                                                                  */
/* Both must happen in that order; snapshot piggybacks on the VI   */
/* sub channel of the running capture.                             */
/* ---------------------------------------------------------------- */

/* Initialize. vi_sub_chn_id is the VI channel ID of the sub stream
 * (typically 1) — the snapshot channel binds to the same source.
 * Returns 0 on success. */
int  snapshot_init(int vi_sub_chn_id);

/* Tear down. Closes the JPEG VENC channel if open, joins the
 * encoder thread. Idempotent. */
void snapshot_shutdown(void);

/* True if the module can currently service requests (initialized,
 * not in the permanent failure state). */
int  snapshot_is_available(void);

/* Block-and-fetch a fresh JPEG. On success, *out_buf is heap-
 * allocated (caller MUST free()) and *out_len is the byte count.
 * Worst-case latency is ~2s (tunable via SNAPSHOT_REQ_TIMEOUT_MS
 * in snapshot.c). Returns -1 on error or timeout. */
int  snapshot_get_jpeg(uint8_t **out_buf, size_t *out_len);

/* ---------------------------------------------------------------- */
/* Auth (auth.c) — shared HTTP Digest / RTSP / ONVIF credentials   */
/*                                                                  */
/* One single user/password pair guards everything that needs it.  */
/* When the password is empty, auth is *disabled* — endpoints stay */
/* wide open for backwards compat and easy first-boot.             */
/*                                                                  */
/* Persisted in /etc/config/ipcd.conf (keys: http_user, http_pass). */
/* ---------------------------------------------------------------- */
typedef enum {
    AUTH_OK     = 0,    /* credentials match */
    AUTH_NEEDED = 1,    /* missing/malformed Authorization header */
    AUTH_FAIL   = 2,    /* present but wrong */
} auth_result_t;

/* Initialize the auth module: pulls user/pass out of cfgfile, seeds
 * the nonce HMAC secret with /dev/urandom + clock_gettime. Safe to
 * call multiple times (re-reads creds, keeps the secret stable so
 * existing nonces survive). Call at startup AND after a successful
 * password change. */
void auth_init(void);

/* True if a password is configured (i.e. auth is active). */
int  auth_is_configured(void);

/* Returns the configured username (empty string if not configured).
 * Pointer is to internal storage, valid until next auth_set_creds(). */
const char *auth_get_user(void);

/* Returns the configured password (empty string if not configured).
 * Same caveat as auth_get_user. Exposed for WS-Security
 * UsernameToken-Digest which needs cleartext per spec. */
const char *auth_get_pass(void);

/* Replace user + password atomically. Pass empty pass to disable
 * auth entirely. Persists via ipcd_cfg_save() and re-runs auth_init.
 * Returns 0 on success. */
int  auth_set_creds(const char *user, const char *pass);

/* Validate a Digest Authorization header against (method, uri).
 *  - 'authz_value': everything *after* "Authorization: " up to CRLF
 *                   (or NULL if header absent)
 *  - 'method':      "GET", "POST", "DESCRIBE", etc.
 *  - 'uri':         request-URI (path + query) — must match the digest
 *
 * If auth_is_configured() returns false, this always returns AUTH_OK
 * (auth disabled, free pass).
 *
 * On AUTH_NEEDED the caller should send a 401 with auth_make_challenge.
 * On AUTH_FAIL the caller may send 401 (with a *fresh* nonce) or 403.
 */
auth_result_t auth_http_check(const char *authz_value,
                              const char *method,
                              const char *uri);

/* Same, but for RTSP. Accepts both Digest and Basic (Basic is a
 * fallback for older clients; Frigate uses Digest). */
auth_result_t auth_rtsp_check(const char *authz_value,
                              const char *method,
                              const char *uri);

/* Build a "Digest realm=..., nonce=..., qop=auth, algorithm=MD5"
 * value (without the "WWW-Authenticate: " prefix and CRLF) into out.
 * Returns bytes written, 0 on error. */
size_t auth_make_challenge(char *out, size_t cap);

/* Internal use: parse a key="value" or key=token from a comma-
 * separated header value. Used by both http and rtsp paths and by
 * the future ONVIF UsernameToken parser, hence exposed here. */
int  auth_parse_kv(const char *src, const char *key,
                   char *out, size_t cap);

/* ---------------------------------------------------------------- */
/* timesync, led, button, dns_spoof                                 */
/* ---------------------------------------------------------------- */
int  timesync_oneshot(void);
int  timesync_daemon_start(void);

typedef enum { LED_OFF, LED_ON, LED_BLINK_SLOW, LED_BLINK_FAST } led_mode_t;
int  led_set(const char *led_path, led_mode_t mode);

int  button_thread_start(void);

int  dns_spoof_start(void);
void dns_spoof_stop (void);

/* ---------------------------------------------------------------- */
/* Global state                                                     */
/* ---------------------------------------------------------------- */
struct global_state {
    pthread_mutex_t mtx;
    pc_state_t      st;
    char            sta_ip[16];
    struct wifi_cfg cfg;
    int             cfg_pending;
    pthread_cond_t  cfg_pending_cv;
    /* Boot time, used by stats. */
    time_t          boot_time;
};
extern struct global_state G;

#endif /* IPCD_H */
