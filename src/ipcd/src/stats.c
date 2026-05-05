/*
 * stats.c — per-second sampling of capture/RTSP/system metrics.
 *
 * Architecture:
 *
 *   stream_worker ─────► stats_record_frame()  (called per frame)
 *                              │
 *                              │ atomically increments
 *                              ▼
 *                        live counters (under stats.mtx)
 *
 *   sampler thread ───► every 1s: snapshot live counters, compute
 *                       deltas (= per-second rates), push into
 *                       60-sample ring buffer, reset deltas.
 *
 *   HTTP /api/stats ──► stats_get() / stats_to_json() (lock + memcpy)
 *
 * The sample period is 1s (matches HLS_TARGET_DUR_MS / 2 — close
 * enough). The ring window is 60 samples = 1 minute of history,
 * which is enough for the sparkline UX.
 *
 * Memory budget: a single snapshot is ~700 B; the sparkline rings
 * are 2 streams × 60 samples × 4 B = 480 B. Negligible.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <pthread.h>
#include <sys/stat.h>

#include "ipcd.h"

/* ---------------------------------------------------------------- */
/* Live counters — written by stream_worker on every frame          */
/* ---------------------------------------------------------------- */
struct live_counters {
    uint32_t frames;
    uint32_t keyframes;
    uint32_t push_fails;
    uint32_t max_frame_bytes;
    uint64_t bytes;
    /* Cumulative since process start (for the totals fields) */
    uint32_t total_frames;
    uint32_t total_keyframes;
    uint32_t total_push_fails;
    uint64_t total_bytes;
};

static struct {
    pthread_mutex_t mtx;
    int             initialized;

    /* Per-stream config (set once when capture starts) */
    struct {
        int         enabled;
        int         width, height, fps_target, kbps_target;
        cap_codec_t codec;
    } scfg[2];

    /* Live counters (cleared each sampling tick) */
    struct live_counters live[2];

    /* Latest computed per-second rates (filled by sampler) */
    double fps_now[2];
    double kbps_now[2];

    /* Sparkline rings (60 samples) */
    uint16_t fps_ring[2][60];
    uint16_t kbps_ring[2][60];
    int      ring_head;     /* next slot to write; oldest = (head - 60 + 60) % 60 */
    int      ring_filled;   /* sample count up to 60 */

    /* Sampler thread */
    pthread_t sampler_tid;
    int       sampler_run;
    int       sampler_started;
} S = {
    .mtx = PTHREAD_MUTEX_INITIALIZER,
};

void stats_init(void)
{
    pthread_mutex_lock(&S.mtx);
    if (!S.initialized) {
        memset(&S.live, 0, sizeof(S.live));
        memset(&S.fps_ring, 0, sizeof(S.fps_ring));
        memset(&S.kbps_ring, 0, sizeof(S.kbps_ring));
        S.ring_head = 0;
        S.ring_filled = 0;
        S.initialized = 1;
    }
    pthread_mutex_unlock(&S.mtx);
}

void stats_set_stream_cfg(int idx, int enabled, int w, int h,
                          int fps_target, int kbps_target,
                          cap_codec_t codec)
{
    if (idx < 0 || idx >= 2) return;
    pthread_mutex_lock(&S.mtx);
    S.scfg[idx].enabled     = enabled;
    S.scfg[idx].width       = w;
    S.scfg[idx].height      = h;
    S.scfg[idx].fps_target  = fps_target;
    S.scfg[idx].kbps_target = kbps_target;
    S.scfg[idx].codec       = codec;
    pthread_mutex_unlock(&S.mtx);
}

void stats_record_frame(int stream_idx, uint32_t bytes,
                        int is_keyframe, int push_failed)
{
    if (stream_idx < 0 || stream_idx >= 2) return;
    pthread_mutex_lock(&S.mtx);
    struct live_counters *L = &S.live[stream_idx];
    L->frames++;
    L->bytes += bytes;
    if (bytes > L->max_frame_bytes) L->max_frame_bytes = bytes;
    if (is_keyframe) L->keyframes++;
    if (push_failed) L->push_fails++;
    L->total_frames++;
    L->total_bytes += bytes;
    if (is_keyframe) L->total_keyframes++;
    if (push_failed) L->total_push_fails++;
    pthread_mutex_unlock(&S.mtx);
}

/* ---------------------------------------------------------------- */
/* Sampler: 1Hz; computes rates, advances ring                     */
/* ---------------------------------------------------------------- */
static void sample_tick(void)
{
    pthread_mutex_lock(&S.mtx);
    int slot = S.ring_head;
    for (int i = 0; i < 2; i++) {
        struct live_counters *L = &S.live[i];
        double fps  = (double)L->frames;
        /* bytes -> kbps (kilobits per second). 1s window. */
        double kbps = ((double)L->bytes * 8.0) / 1000.0;
        S.fps_now[i]  = fps;
        S.kbps_now[i] = kbps;
        /* Saturate to u16 so the ring is small. fps caps at 65535
         * which is absurd but harmless; kbps could in principle
         * exceed 65535 (= 65 Mbps) but that's well outside what
         * this hardware does. */
        S.fps_ring[i][slot]  = (uint16_t)(fps  > 65535 ? 65535 : fps);
        S.kbps_ring[i][slot] = (uint16_t)(kbps > 65535 ? 65535 : kbps);
        L->frames = 0;
        L->keyframes = 0;
        L->bytes = 0;
        L->max_frame_bytes = 0;
        L->push_fails = 0;
    }
    S.ring_head = (slot + 1) % 60;
    if (S.ring_filled < 60) S.ring_filled++;
    pthread_mutex_unlock(&S.mtx);
}

static void *sampler_thread(void *arg)
{
    (void)arg;
    /* Align to next second boundary so the sparkline ticks
     * predictably (cosmetic). */
    while (S.sampler_run) {
        sleep(1);
        if (!S.sampler_run) break;
        sample_tick();
    }
    return NULL;
}

int stats_sampler_start(void)
{
    if (S.sampler_started) return 0;
    S.sampler_run = 1;
    if (pthread_create(&S.sampler_tid, NULL, sampler_thread, NULL) != 0) {
        S.sampler_run = 0;
        return -1;
    }
    S.sampler_started = 1;
    return 0;
}

void stats_sampler_stop(void)
{
    if (!S.sampler_started) return;
    S.sampler_run = 0;
    pthread_join(S.sampler_tid, NULL);
    S.sampler_started = 0;
}

/* ---------------------------------------------------------------- */
/* Process RSS (best-effort, /proc/self/status)                    */
/* ---------------------------------------------------------------- */
static long read_rss_kb(void)
{
    FILE *f = fopen("/proc/self/status", "r");
    if (!f) return -1;
    char line[256];
    long rss = -1;
    while (fgets(line, sizeof(line), f)) {
        if (!strncmp(line, "VmRSS:", 6)) {
            rss = strtol(line + 6, NULL, 10);
            break;
        }
    }
    fclose(f);
    return rss;
}

static const char *codec_name(cap_codec_t c)
{
    return c == CAP_CODEC_HEVC ? "h265" : "h264";
}

/* ---------------------------------------------------------------- */
/* Snapshot                                                         */
/* ---------------------------------------------------------------- */
void stats_get(struct stats_snapshot *out)
{
    if (!out) return;
    memset(out, 0, sizeof(*out));

    /* Wi-Fi / state — pulls from G */
    pthread_mutex_lock(&G.mtx);
    out->state = G.st;
    snprintf(out->state_name, sizeof(out->state_name), "%s",
             pc_state_name(G.st));
    snprintf(out->ssid, sizeof(out->ssid), "%s", G.cfg.ssid);
    out->configured = G.cfg.configured;
    pthread_mutex_unlock(&G.mtx);

    char ip[16] = "";
    wifi_sta_has_ip(ip);
    snprintf(out->ip, sizeof(out->ip), "%s", ip);

    /* Capture stats */
    pthread_mutex_lock(&S.mtx);
    for (int i = 0; i < 2; i++) {
        out->streams[i].enabled        = S.scfg[i].enabled;
        out->streams[i].width          = S.scfg[i].width;
        out->streams[i].height         = S.scfg[i].height;
        out->streams[i].fps_target     = S.scfg[i].fps_target;
        out->streams[i].kbps_target    = S.scfg[i].kbps_target;
        out->streams[i].fps_actual     = S.fps_now[i];
        out->streams[i].kbps_actual    = S.kbps_now[i];
        out->streams[i].total_frames   = S.live[i].total_frames;
        out->streams[i].total_keyframes= S.live[i].total_keyframes;
        out->streams[i].push_fails     = S.live[i].total_push_fails;
        out->streams[i].max_frame_bytes= S.live[i].max_frame_bytes;
        out->streams[i].total_bytes    = S.live[i].total_bytes;
        out->streams[i].codec          = codec_name(S.scfg[i].codec);

        /* Rings: copy out in chronological order (oldest first) */
        if (S.ring_filled < 60) {
            /* History only partially filled. Pad the front with
             * zeros so the UI gets a consistent 60-sample array. */
            int gap = 60 - S.ring_filled;
            memset(out->streams[i].fps_hist,  0, gap * sizeof(uint16_t));
            memset(out->streams[i].kbps_hist, 0, gap * sizeof(uint16_t));
            for (int k = 0; k < S.ring_filled; k++) {
                int src = (S.ring_head - S.ring_filled + k + 60) % 60;
                out->streams[i].fps_hist[gap + k]  = S.fps_ring[i][src];
                out->streams[i].kbps_hist[gap + k] = S.kbps_ring[i][src];
            }
        } else {
            for (int k = 0; k < 60; k++) {
                int src = (S.ring_head + k) % 60;
                out->streams[i].fps_hist[k]  = S.fps_ring[i][src];
                out->streams[i].kbps_hist[k] = S.kbps_ring[i][src];
            }
        }
    }
    pthread_mutex_unlock(&S.mtx);

    /* RTSP / HLS */
    out->rtsp_clients = rtsp_server_active_clients();
    out->ir_mode      = (int)ir_get_mode();
    out->ir_level     = ir_get_level();
    out->ir_luma      = ir_get_luma();

    /* Process */
    out->uptime_s = (long)(time(NULL) - G.boot_time);
    out->rss_kb   = read_rss_kb();
}

/* ---------------------------------------------------------------- */
/* JSON serializer (no library)                                    */
/* ---------------------------------------------------------------- */
static int append_u16_array(char *buf, size_t cap, size_t pos,
                            const uint16_t *arr, int n)
{
    int w = 0;
    if (pos < cap) buf[pos++] = '[';
    for (int i = 0; i < n; i++) {
        char tmp[12];
        w = snprintf(tmp, sizeof(tmp), "%s%u",
                     i ? "," : "", (unsigned)arr[i]);
        if (pos + w >= cap) return -1;
        memcpy(buf + pos, tmp, w);
        pos += w;
    }
    if (pos < cap) buf[pos++] = ']';
    return (int)pos;
}

size_t stats_to_json(char *buf, size_t cap)
{
    if (!buf || cap < 256) return 0;
    struct stats_snapshot s;
    stats_get(&s);

    /* Top-level scalars + per-stream config & rates. The history
     * arrays we emit by hand because snprintf into a single
     * format string with 240 numbers is gross. */
    int n = snprintf(buf, cap,
        "{"
        "\"state\":\"%s\","
        "\"ssid\":\"%s\","
        "\"ip\":\"%s\","
        "\"configured\":%d,"
        "\"uptime_s\":%ld,"
        "\"rss_kb\":%ld,"
        "\"rtsp_clients\":%d,"
        "\"ir_mode\":%d,"
        "\"ir_level\":%d,"
        "\"ir_luma\":%u,"
        "\"streams\":[",
        s.state_name, s.ssid, s.ip, s.configured,
        s.uptime_s, s.rss_kb, s.rtsp_clients,
        s.ir_mode, s.ir_level, s.ir_luma);
    if (n < 0 || (size_t)n >= cap) return 0;
    size_t p = (size_t)n;

    for (int i = 0; i < 2; i++) {
        n = snprintf(buf + p, cap - p,
            "%s{"
            "\"enabled\":%d,"
            "\"codec\":\"%s\","
            "\"width\":%d,\"height\":%d,"
            "\"fps_target\":%d,\"kbps_target\":%d,"
            "\"fps_actual\":%.2f,\"kbps_actual\":%.1f,"
            "\"total_frames\":%u,"
            "\"total_keyframes\":%u,"
            "\"push_fails\":%u,"
            "\"max_frame_bytes\":%u,"
            "\"total_bytes\":%llu,"
            "\"fps_hist\":",
            i ? "," : "",
            s.streams[i].enabled,
            s.streams[i].codec ? s.streams[i].codec : "",
            s.streams[i].width, s.streams[i].height,
            s.streams[i].fps_target, s.streams[i].kbps_target,
            s.streams[i].fps_actual, s.streams[i].kbps_actual,
            s.streams[i].total_frames,
            s.streams[i].total_keyframes,
            s.streams[i].push_fails,
            s.streams[i].max_frame_bytes,
            (unsigned long long)s.streams[i].total_bytes);
        if (n < 0 || p + n >= cap) return 0;
        p += n;
        int q = append_u16_array(buf, cap, p, s.streams[i].fps_hist, 60);
        if (q < 0) return 0;
        p = (size_t)q;
        if (p + 16 >= cap) return 0;
        memcpy(buf + p, ",\"kbps_hist\":", 13); p += 13;
        q = append_u16_array(buf, cap, p, s.streams[i].kbps_hist, 60);
        if (q < 0) return 0;
        p = (size_t)q;
        if (p < cap) buf[p++] = '}';
    }
    if (p + 2 >= cap) return 0;
    buf[p++] = ']';
    buf[p++] = '}';
    if (p < cap) buf[p] = 0;
    return p;
}
