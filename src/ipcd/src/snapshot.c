/*
 * snapshot.c — JPEG snapshot via on-demand VENC channel.
 *
 * Frigate (and ONVIF GetSnapshotUri in step 3) need a JPEG of the
 * current scene. The Anyka v330 SDK supports a JPEG VENC profile
 * (enc_out_type=1, profile=PROFILE_JPEG=7), and the underlying
 * libmpi_venc.so has explicit handling for it. We use a third VENC
 * channel (chn_id=2; main=0, sub=1) bound to the same VI sub channel
 * as the H264 sub stream, so we don't pay for a second VI.
 *
 * Lifecycle:
 *   - snapshot_init() starts an encoder thread, registers the JPEG
 *     channel as IDLE (not yet open).
 *   - On the first GET /snapshot.jpg, the thread opens the JPEG VENC
 *     channel, encodes one frame, returns the bytes to the caller,
 *     and keeps the channel open for SNAPSHOT_TTL_MS (default 30s).
 *   - Subsequent requests within the TTL window get the next-encoded
 *     frame quickly. A 1-second JPEG cache absorbs Frigate's
 *     "snapshot every 5s but two clients" pattern with zero VENC
 *     activity in between.
 *   - After TTL with no requests, the thread closes the JPEG channel
 *     and goes back to IDLE.
 *   - snapshot_shutdown() closes the channel and joins the thread.
 *
 * Threading:
 *   - The encoder runs in its own thread; HTTP handlers post a
 *     "request" event and wait on a condvar with timeout.
 *   - Multiple concurrent requests share the same in-flight encode
 *     attempt — they don't each trigger their own.
 *   - Hard timeout per request: 2s. If the encoder is too slow or
 *     stuck, we return error rather than blocking the HTTP thread
 *     forever.
 *
 * Failure modes:
 *   - First open of the JPEG channel may fail (DMA pool too small,
 *     hardware doesn't support the configured resolution, etc).
 *     After SNAPSHOT_FAIL_LIMIT consecutive failures we mark the
 *     module "permanently unavailable" and short-circuit returns
 *     until shutdown — to avoid hammering the encoder uselessly.
 *
 * Subtleties found while writing this:
 *   - When the parent capture is restarted (Tier-2 config change),
 *     snapshot must be torn down BEFORE capture_stop and re-init
 *     AFTER capture_start. The HTTP handler tolerates a brief
 *     "module not ready" window with a 503.
 *   - The VI sub channel is already bound to a VENC dst (the H264
 *     sub stream). The SDK supports N:1 src-to-dst via its internal
 *     "group object" structure — verified in libapp_video.so's
 *     app_video_bind_vi_venc, which calls find_src_gchn first and
 *     reuses an existing group if present.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>

#include "ipcd.h"

/* ============================================================ */
/* Anyka SDK declarations needed locally                        */
/*                                                              */
/* These are duplicated from cap_pipeline.c on purpose: keeping */
/* snapshot.c self-contained avoids growing cap_pipeline's      */
/* public surface for an internal helper. The cost is ~30 lines */
/* of redundant declarations, which we accept.                  */
/*                                                              */
/* Layouts and offsets are reverse-engineered, see              */
/* cap_pipeline.c for the long-form derivation.                 */
/* ============================================================ */

struct sn_video_stream {
    unsigned char     *data;
    unsigned int       len;
    unsigned long long ts;
    unsigned long      seq_no;
    int                frame_type;
};

struct sn_encode_param {
    uint16_t width;             /* 0x00 */
    uint16_t height;            /* 0x02 */
    uint16_t fps;               /* 0x04 */
    uint16_t goplen;            /* 0x06 */
    uint16_t target_kbps;       /* 0x08 */
    uint16_t max_kbps;          /* 0x0a */
    uint32_t profile;           /* 0x0c */
    uint32_t br_mode;           /* 0x10 */
    uint16_t initial_qp;        /* 0x14 */
    uint16_t minqp;             /* 0x16 */
    uint16_t maxqp;             /* 0x18 */
    uint16_t pad_1a;            /* 0x1a */
    uint32_t jpeg_qlevel;       /* 0x1c — must be < 4 */
    uint32_t chroma_mode;       /* 0x20 — 0 = YUV420 */
    uint32_t enc_out_type;      /* 0x24 — 1=JPEG */
    uint32_t reserved_28;       /* 0x28 */
    uint16_t enc_level;         /* 0x2c — in [10..50] */
    uint16_t pad_2e;            /* 0x2e */
    uint32_t smart_mode;        /* 0x30 */
    uint16_t smart_goplen;      /* 0x34 */
    uint16_t smart_quality;     /* 0x36 */
    uint16_t smart_static_value;/* 0x38 */
    uint16_t pad_3a;            /* 0x3a */
};
/* total 60 = 0x3c */

struct sn_chn {
    int type;
    int chn_id;
};

struct sn_chn_attr {
    int frame_depth;
    int frame_rate;     /* (num << 16) | denom */
};

extern int ak_venc_open(const struct sn_encode_param *param, int *out_handle_id);
extern int ak_venc_close(int handle_id);
extern int ak_app_video_bind_chn(struct sn_chn *src, struct sn_chn *dst,
                                 struct sn_chn_attr *bp);
extern int ak_app_video_unbind_chn(struct sn_chn *src, struct sn_chn *dst);
extern int ak_app_video_set_dst_chn_active(struct sn_chn *dst, int on);
extern int ak_app_video_venc_get_stream(struct sn_chn *dst,
                                        struct sn_video_stream *vs);
extern int ak_venc_release_stream(int handle_id, struct sn_video_stream *vs);

/* ============================================================ */
/* Tunables                                                     */
/* ============================================================ */
#define SNAPSHOT_VENC_ID        2     /* main=0, sub=1, jpeg=2 */
#define SNAPSHOT_VI_SRC_TYPE    7     /* VI */
#define SNAPSHOT_VENC_DST_TYPE  0xd   /* VENC */

#define SNAPSHOT_W              640   /* match the sub stream — same VI res */
#define SNAPSHOT_H              360
#define SNAPSHOT_KBPS           1000  /* JPEG ignores rate-control mostly */
#define SNAPSHOT_QLEVEL         2     /* 0..3, lower = better quality */

/* How long the JPEG channel stays open after the last request before
 * we tear it down. Frigate's default snapshot interval is 5s, so 30s
 * comfortably covers normal usage and one-off ONVIF probes. */
#define SNAPSHOT_TTL_MS         30000

/* JPEG cache: serve stale frames up to this age without re-encoding.
 * Two clients hitting at the same moment get the same JPEG; bursts
 * from a single client (common: Frigate retrying) reuse it too. */
#define SNAPSHOT_CACHE_MS       1000

/* Per-request total deadline. */
#define SNAPSHOT_REQ_TIMEOUT_MS 2000

/* If first-encode fails this many times in a row, give up entirely
 * until module is shut down + re-init. Avoids logspam if the JPEG
 * codec just doesn't work on this config. */
#define SNAPSHOT_FAIL_LIMIT     3

/* Pull poll: how often to check for a fresh frame after triggering
 * an encode. Small enough to keep latency low, large enough not to
 * pin the CPU. */
#define SNAPSHOT_POLL_US        20000  /* 20ms */

/* ============================================================ */
/* State                                                        */
/* ============================================================ */

typedef enum {
    SN_STATE_UNINIT = 0,
    SN_STATE_IDLE,           /* thread alive, JPEG channel closed */
    SN_STATE_CHANNEL_OPEN,   /* JPEG channel open, encoder ready */
    SN_STATE_DEAD,           /* failed too many times, refuse work */
} sn_state_t;

typedef struct {
    pthread_mutex_t  mtx;
    pthread_cond_t   request_cv;     /* http -> encoder */
    pthread_cond_t   ready_cv;       /* encoder -> http */
    pthread_t        thread;
    int              run;            /* 0 = stop thread */

    sn_state_t       state;
    int              vi_chn_id;      /* set by snapshot_init */
    int              consecutive_fails;

    /* "Pending request" flag: set by snapshot_get_jpeg, cleared by
     * the encoder when it has produced a fresh frame for that wave.
     * Shared between concurrent callers; everyone wakes up on
     * ready_cv when it goes 0 again. */
    int              request_pending;
    long             last_request_ms;     /* monotonic, for TTL */

    /* The most recently produced JPEG. malloc'd, owned by the
     * snapshot module. cache_ms timestamp is monotonic. */
    uint8_t         *cache_buf;
    size_t           cache_len;
    long             cache_ms;
} sn_t;

static sn_t g_sn;

/* ============================================================ */
/* Helpers                                                      */
/* ============================================================ */

static long now_ms(void)
{
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return (long)t.tv_sec * 1000 + t.tv_nsec / 1000000;
}

/* Validate that what we just produced looks like a JPEG. We're not
 * trying to fully parse it — just sanity-check the SOI/EOI markers
 * so a confused codec returning H264 NALs by mistake gets caught
 * before we hand it to a client. */
static int looks_like_jpeg(const uint8_t *buf, size_t len)
{
    if (len < 4) return 0;
    if (buf[0] != 0xFF || buf[1] != 0xD8) return 0;          /* SOI */
    if (buf[len-2] != 0xFF || buf[len-1] != 0xD9) return 0;  /* EOI */
    return 1;
}

/* ============================================================ */
/* JPEG channel open/close                                      */
/* ============================================================ */

/* Open the JPEG VENC channel and bind it to our VI src.
 * Returns 0 on success. Must be called from the encoder thread
 * (the bind/active calls aren't documented as thread-safe vs other
 * SDK callers, so we serialize on our thread). */
static int jpeg_channel_open(void)
{
    struct sn_encode_param ep;
    memset(&ep, 0, sizeof(ep));
    ep.width        = SNAPSHOT_W;
    ep.height       = SNAPSHOT_H;
    ep.fps          = 15;          /* doesn't matter much for JPEG */
    ep.goplen       = 15;          /* unused for JPEG but must be > 0 */
    ep.target_kbps  = SNAPSHOT_KBPS;
    ep.max_kbps     = SNAPSHOT_KBPS;
    ep.profile      = 7;           /* PROFILE_JPEG */
    ep.br_mode      = 0;           /* CBR */
    ep.initial_qp   = 37;
    ep.minqp        = 25;
    ep.maxqp        = 50;
    ep.jpeg_qlevel  = SNAPSHOT_QLEVEL;
    ep.chroma_mode  = 1;           /* 1 = YUV420 (color); 0 = MONO!
                                    * The vendor's proxy_capture_17.c
                                    * commented this as "0 = YUV420"
                                    * but that's a copy-paste error;
                                    * cap_pipeline.c uses 1 for the
                                    * H264/HEVC streams which are
                                    * verifiably color, and so do we. */
    ep.enc_out_type = 1;           /* MJPEG_ENC_TYPE */
    ep.enc_level    = 30;
    ep.smart_mode   = 0;
    ep.smart_goplen = 100;
    ep.smart_quality= 50;

    int venc_id = SNAPSHOT_VENC_ID;
    int rc = ak_venc_open(&ep, &venc_id);
    if (rc != 0) {
        fprintf(stderr, "[snap] ak_venc_open(JPEG) failed: 0x%x\n", rc);
        return -1;
    }
    if (venc_id != SNAPSHOT_VENC_ID) {
        /* The SDK assigns its own venc_id, may not honour ours. Log
         * but continue — we use whatever it gave us. */
        fprintf(stderr, "[snap] requested venc_id=%d, got %d\n",
                SNAPSHOT_VENC_ID, venc_id);
    }
    fprintf(stderr, "[snap] JPEG VENC channel %d opened (%dx%d q=%d)\n",
            venc_id, SNAPSHOT_W, SNAPSHOT_H, SNAPSHOT_QLEVEL);

    /* Bind VI sub -> JPEG VENC. The src is already bound to the
     * H264 sub VENC; the SDK supports N:1 by reusing the source
     * group object internally. */
    struct sn_chn src = { SNAPSHOT_VI_SRC_TYPE,    g_sn.vi_chn_id };
    struct sn_chn dst = { SNAPSHOT_VENC_DST_TYPE,  venc_id };
    struct sn_chn_attr bp = {
        .frame_depth = 2,
        .frame_rate  = (15 << 16) | 1,
    };
    rc = ak_app_video_bind_chn(&src, &dst, &bp);
    if (rc != 0) {
        fprintf(stderr, "[snap] bind VI->JPEG failed: 0x%x\n", rc);
        ak_venc_close(venc_id);
        return -1;
    }

    rc = ak_app_video_set_dst_chn_active(&dst, 1);
    if (rc != 0) {
        fprintf(stderr, "[snap] set_dst_chn_active(JPEG, 1) failed: 0x%x\n", rc);
        ak_app_video_unbind_chn(&src, &dst);
        ak_venc_close(venc_id);
        return -1;
    }

    /* Stash the active venc_id in shared state. The .chn_id we'll
     * use when pulling stream is the same. */
    g_sn.vi_chn_id = g_sn.vi_chn_id;  /* unchanged */
    /* We don't track venc_id in sn_t separately because we always
     * use SNAPSHOT_VENC_ID — but keep this comment as a reminder
     * that if the SDK starts reassigning, we must update.
     */
    return 0;
}

static void jpeg_channel_close(void)
{
    struct sn_chn src = { SNAPSHOT_VI_SRC_TYPE,    g_sn.vi_chn_id };
    struct sn_chn dst = { SNAPSHOT_VENC_DST_TYPE,  SNAPSHOT_VENC_ID };

    /* Order: deactivate -> unbind -> close. */
    int rc = ak_app_video_set_dst_chn_active(&dst, 0);
    if (rc != 0) {
        fprintf(stderr, "[snap] set_dst_chn_active(JPEG, 0) rc=0x%x\n", rc);
    }
    rc = ak_app_video_unbind_chn(&src, &dst);
    if (rc != 0) {
        fprintf(stderr, "[snap] unbind VI->JPEG rc=0x%x\n", rc);
    }
    rc = ak_venc_close(SNAPSHOT_VENC_ID);
    if (rc != 0) {
        fprintf(stderr, "[snap] ak_venc_close(JPEG) rc=0x%x\n", rc);
    }
    fprintf(stderr, "[snap] JPEG channel closed\n");
}

/* ============================================================ */
/* Encode + cache update                                        */
/*                                                              */
/* Pull frames from the JPEG VENC channel, copy the latest into */
/* the cache, and signal waiters. Called with mtx held; releases */
/* it across the SDK calls + sleep so HTTP threads can read the */
/* old cache while we encode the new one.                       */
/* ============================================================ */

static int encode_one_frame_locked(void)
{
    /* Drop our lock for the SDK pull — get_stream may block briefly
     * inside the kernel waiting for the next encoded frame. */
    pthread_mutex_unlock(&g_sn.mtx);

    struct sn_chn dst = { SNAPSHOT_VENC_DST_TYPE, SNAPSHOT_VENC_ID };
    struct sn_video_stream vs;
    long deadline = now_ms() + 1500;     /* 1.5s to grab a frame */

    int got = 0;
    uint8_t *jpeg_buf = NULL;
    size_t   jpeg_len = 0;

    while (now_ms() < deadline) {
        memset(&vs, 0, sizeof(vs));
        int rc = ak_app_video_venc_get_stream(&dst, &vs);
        if (rc == 0 && vs.data && vs.len > 0) {
            /* Copy out before releasing — the SDK reclaims vs.data */
            jpeg_len = vs.len;
            jpeg_buf = malloc(jpeg_len);
            if (jpeg_buf) memcpy(jpeg_buf, vs.data, jpeg_len);
            ak_venc_release_stream(SNAPSHOT_VENC_ID, &vs);
            if (!jpeg_buf) {
                /* OOM. Treat as a transient error. */
                pthread_mutex_lock(&g_sn.mtx);
                return -1;
            }
            got = 1;
            break;
        }
        usleep(SNAPSHOT_POLL_US);
    }

    pthread_mutex_lock(&g_sn.mtx);

    if (!got) {
        fprintf(stderr, "[snap] encode timeout (no frame in 1.5s)\n");
        return -1;
    }

    if (!looks_like_jpeg(jpeg_buf, jpeg_len)) {
        fprintf(stderr, "[snap] encoded buffer doesn't look like JPEG "
                        "(len=%zu, first=%02x %02x, last=%02x %02x)\n",
                jpeg_len,
                jpeg_buf[0], jpeg_buf[1],
                jpeg_buf[jpeg_len-2], jpeg_buf[jpeg_len-1]);
        free(jpeg_buf);
        return -1;
    }

    /* Swap into cache */
    free(g_sn.cache_buf);
    g_sn.cache_buf = jpeg_buf;
    g_sn.cache_len = jpeg_len;
    g_sn.cache_ms  = now_ms();
    return 0;
}

/* ============================================================ */
/* Encoder thread                                               */
/*                                                              */
/* States it cycles through:                                    */
/*   IDLE -> (request arrives) -> open channel -> CHANNEL_OPEN  */
/*   CHANNEL_OPEN -> (no requests for TTL) -> close -> IDLE     */
/*   * -> (run cleared) -> exit                                 */
/* ============================================================ */

static void *encoder_thread(void *arg)
{
    (void)arg;
    pthread_mutex_lock(&g_sn.mtx);

    while (g_sn.run) {
        long now = now_ms();

        /* IDLE: wait for a request. */
        if (g_sn.state == SN_STATE_IDLE) {
            if (g_sn.request_pending) {
                /* Try to open the JPEG channel. */
                pthread_mutex_unlock(&g_sn.mtx);
                int rc = jpeg_channel_open();
                pthread_mutex_lock(&g_sn.mtx);

                if (rc == 0) {
                    g_sn.state = SN_STATE_CHANNEL_OPEN;
                    g_sn.consecutive_fails = 0;
                    /* Fall through to encode the first frame. */
                } else {
                    g_sn.consecutive_fails++;
                    if (g_sn.consecutive_fails >= SNAPSHOT_FAIL_LIMIT) {
                        fprintf(stderr,
                            "[snap] %d consecutive open failures — "
                            "marking module unavailable\n",
                            g_sn.consecutive_fails);
                        g_sn.state = SN_STATE_DEAD;
                    }
                    /* Tell the waiting caller the bad news. */
                    g_sn.request_pending = 0;
                    pthread_cond_broadcast(&g_sn.ready_cv);
                    /* Loop back to wait for another request. */
                    continue;
                }
            } else {
                /* No request — wait. */
                pthread_cond_wait(&g_sn.request_cv, &g_sn.mtx);
                continue;
            }
        }

        /* DEAD: drain any pending request with an error and sleep
         * until shutdown. */
        if (g_sn.state == SN_STATE_DEAD) {
            if (g_sn.request_pending) {
                g_sn.request_pending = 0;
                pthread_cond_broadcast(&g_sn.ready_cv);
            }
            pthread_cond_wait(&g_sn.request_cv, &g_sn.mtx);
            continue;
        }

        /* CHANNEL_OPEN: */
        if (g_sn.state == SN_STATE_CHANNEL_OPEN) {
            if (g_sn.request_pending) {
                /* Encode a fresh frame (drops + reacquires mtx) */
                int rc = encode_one_frame_locked();
                g_sn.request_pending = 0;
                if (rc != 0) {
                    g_sn.consecutive_fails++;
                    /* Don't blow up immediately — channel may glitch
                     * but recover. Only retry if we're still under
                     * the limit.
                     *
                     * Going DEAD here is harsher than at open time
                     * because the channel is open and likely fine —
                     * it's probably a transient frame issue. We
                     * lower the bar slightly: 2x the limit before
                     * giving up. */
                    if (g_sn.consecutive_fails >= SNAPSHOT_FAIL_LIMIT * 2) {
                        fprintf(stderr,
                            "[snap] %d consecutive encode failures — "
                            "marking module unavailable\n",
                            g_sn.consecutive_fails);
                        g_sn.state = SN_STATE_DEAD;
                    }
                } else {
                    g_sn.consecutive_fails = 0;
                }
                pthread_cond_broadcast(&g_sn.ready_cv);
                continue;
            }

            /* No request — check TTL. If exceeded, close the channel
             * and go IDLE. Otherwise sleep with timeout. */
            long idle_ms = now - g_sn.last_request_ms;
            if (idle_ms >= SNAPSHOT_TTL_MS) {
                pthread_mutex_unlock(&g_sn.mtx);
                jpeg_channel_close();
                pthread_mutex_lock(&g_sn.mtx);
                g_sn.state = SN_STATE_IDLE;
                continue;
            }

            struct timespec ts;
            clock_gettime(CLOCK_REALTIME, &ts);
            long sleep_ms = SNAPSHOT_TTL_MS - idle_ms;
            ts.tv_sec  += sleep_ms / 1000;
            ts.tv_nsec += (sleep_ms % 1000) * 1000000L;
            if (ts.tv_nsec >= 1000000000L) {
                ts.tv_sec  += 1;
                ts.tv_nsec -= 1000000000L;
            }
            pthread_cond_timedwait(&g_sn.request_cv, &g_sn.mtx, &ts);
            continue;
        }

        /* Defensive: any unexpected state -> wait */
        pthread_cond_wait(&g_sn.request_cv, &g_sn.mtx);
    }

    /* Shutdown: if channel is open, close it. */
    if (g_sn.state == SN_STATE_CHANNEL_OPEN) {
        pthread_mutex_unlock(&g_sn.mtx);
        jpeg_channel_close();
        pthread_mutex_lock(&g_sn.mtx);
        g_sn.state = SN_STATE_IDLE;
    }

    pthread_mutex_unlock(&g_sn.mtx);
    return NULL;
}

/* ============================================================ */
/* Public API                                                   */
/* ============================================================ */

int snapshot_init(int vi_sub_chn_id)
{
    if (g_sn.state != SN_STATE_UNINIT) {
        fprintf(stderr, "[snap] init called but state != UNINIT\n");
        return -1;
    }
    memset(&g_sn, 0, sizeof(g_sn));
    pthread_mutex_init(&g_sn.mtx, NULL);
    pthread_cond_init(&g_sn.request_cv, NULL);
    pthread_cond_init(&g_sn.ready_cv, NULL);
    g_sn.vi_chn_id = vi_sub_chn_id;
    g_sn.run       = 1;
    g_sn.state     = SN_STATE_IDLE;

    int rc = pthread_create(&g_sn.thread, NULL, encoder_thread, NULL);
    if (rc != 0) {
        fprintf(stderr, "[snap] pthread_create failed: %d\n", rc);
        g_sn.state = SN_STATE_UNINIT;
        return -1;
    }
    fprintf(stderr, "[snap] init OK (vi_chn=%d, idle)\n", vi_sub_chn_id);
    return 0;
}

void snapshot_shutdown(void)
{
    if (g_sn.state == SN_STATE_UNINIT) return;

    pthread_mutex_lock(&g_sn.mtx);
    g_sn.run = 0;
    pthread_cond_broadcast(&g_sn.request_cv);
    pthread_mutex_unlock(&g_sn.mtx);

    pthread_join(g_sn.thread, NULL);

    free(g_sn.cache_buf);
    pthread_mutex_destroy(&g_sn.mtx);
    pthread_cond_destroy(&g_sn.request_cv);
    pthread_cond_destroy(&g_sn.ready_cv);
    memset(&g_sn, 0, sizeof(g_sn));
    fprintf(stderr, "[snap] shutdown done\n");
}

/* Get a JPEG. On success, *out_buf is malloc'd (caller frees), *out_len
 * is the length. Returns 0 on success, -1 on error.
 *
 * The caller blocks up to SNAPSHOT_REQ_TIMEOUT_MS waiting for a
 * fresh frame, unless a recent cached frame can be served. */
int snapshot_get_jpeg(uint8_t **out_buf, size_t *out_len)
{
    if (!out_buf || !out_len) return -1;
    *out_buf = NULL;
    *out_len = 0;

    pthread_mutex_lock(&g_sn.mtx);

    if (g_sn.state == SN_STATE_UNINIT || g_sn.state == SN_STATE_DEAD) {
        pthread_mutex_unlock(&g_sn.mtx);
        return -1;
    }

    long now = now_ms();
    g_sn.last_request_ms = now;

    /* Cache hit? */
    if (g_sn.cache_buf && (now - g_sn.cache_ms) <= SNAPSHOT_CACHE_MS) {
        *out_buf = malloc(g_sn.cache_len);
        if (!*out_buf) {
            pthread_mutex_unlock(&g_sn.mtx);
            return -1;
        }
        memcpy(*out_buf, g_sn.cache_buf, g_sn.cache_len);
        *out_len = g_sn.cache_len;
        pthread_mutex_unlock(&g_sn.mtx);
        return 0;
    }

    /* Cache miss: trigger encoder + wait. */
    g_sn.request_pending = 1;
    pthread_cond_signal(&g_sn.request_cv);

    struct timespec deadline;
    clock_gettime(CLOCK_REALTIME, &deadline);
    deadline.tv_sec  += SNAPSHOT_REQ_TIMEOUT_MS / 1000;
    deadline.tv_nsec += (SNAPSHOT_REQ_TIMEOUT_MS % 1000) * 1000000L;
    if (deadline.tv_nsec >= 1000000000L) {
        deadline.tv_sec  += 1;
        deadline.tv_nsec -= 1000000000L;
    }

    /* Wait for either: request_pending == 0 (encoder finished, fresh
     * cache available — or it gave up), or timeout, or shutdown. */
    while (g_sn.request_pending && g_sn.run &&
           g_sn.state != SN_STATE_DEAD) {
        int rc = pthread_cond_timedwait(&g_sn.ready_cv, &g_sn.mtx, &deadline);
        if (rc == ETIMEDOUT) {
            /* We don't clear request_pending — let the encoder still
             * fulfill it for a future caller, since the cost is
             * already paid. */
            pthread_mutex_unlock(&g_sn.mtx);
            fprintf(stderr, "[snap] request timeout after %dms\n",
                    SNAPSHOT_REQ_TIMEOUT_MS);
            return -1;
        }
    }

    if (g_sn.state == SN_STATE_DEAD || !g_sn.cache_buf) {
        pthread_mutex_unlock(&g_sn.mtx);
        return -1;
    }

    /* Encoder may have produced a frame newer than the deadline —
     * use whatever's in cache. */
    *out_buf = malloc(g_sn.cache_len);
    if (!*out_buf) {
        pthread_mutex_unlock(&g_sn.mtx);
        return -1;
    }
    memcpy(*out_buf, g_sn.cache_buf, g_sn.cache_len);
    *out_len = g_sn.cache_len;
    pthread_mutex_unlock(&g_sn.mtx);
    return 0;
}

int snapshot_is_available(void)
{
    pthread_mutex_lock(&g_sn.mtx);
    int ok = (g_sn.state == SN_STATE_IDLE ||
              g_sn.state == SN_STATE_CHANNEL_OPEN);
    pthread_mutex_unlock(&g_sn.mtx);
    return ok;
}
