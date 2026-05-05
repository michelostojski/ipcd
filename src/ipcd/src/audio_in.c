/*
 * audio_in.c — Microphone capture + AENC G.711 µ-law encoding
 *              with hardware AEC (echo cancellation).
 *
 * Architecture:
 *
 *   [mic HW]
 *      |
 *      v
 *   AI dev=0, 16 kHz mono 16-bit  +  AEC enabled (1024,1024,0)
 *      |
 *      | bind AI -> AENC via app_audio_bind_ai_aenc()
 *      v
 *   AENC type=18 (G.711 µ-law), 8 kHz mono 16-bit
 *      |
 *      | (SDK internally downsamples 16k -> 8k inside AENC)
 *      v
 *   ak_app_audio_aenc_get_stream()  -> encoded G.711 frames
 *      |
 *      v
 *   audio_in_get_frame(buf, *len)   <- public API
 *
 * AEC integration:
 *   The Anyka VQE engine ties AI (near-end) and AO (far-end)
 *   automatically when both are open. The far-end reference
 *   PCM is captured inside ak_ao_send_frame() (which calls
 *   ak_vqe_inner_send_far_pcm internally — verified in the AO
 *   decompile). When AI's AEC is enabled and configured with
 *   the right tap length and delay, the echo from the speaker
 *   is subtracted from the mic input transparently.
 *
 *   The aec_attr values are taken from the factory config:
 *     ai_aec = 1024, 1024, 0
 *   which presumably are filter_len, search_window, mode (the
 *   fields aren't fully documented; they go straight to
 *   ak_vqe_inner_set_ai_aec(). Vendor-tuned for this hardware.
 *
 * Channel types:
 *   The Anyka SDK uses a generic chn descriptor { type, chn_id }
 *   for source/dest binding. By analogy with the video pipeline
 *   (vi=7 source, venc=0xd dest) we use:
 *     AI source  type = 5
 *     AENC dest  type = 6
 *   These were inferred from the decompile of libapp_aenc_ex.so
 *   (CSWTCH_35 has 4 categories indexed by type-5; AI maps to
 *   category 0 = src, AENC to category 1 = dst). If the bind
 *   call returns "Chn param invalid", we'll need to revisit.
 *
 * Lifecycle:
 *   audio_in_init()   open AI (with AEC), open AENC, bind, start
 *   audio_in_get_frame()  pull one G.711 frame, returns bytes
 *   audio_in_shutdown()   stop, unbind, close
 *
 * Threading:
 *   Single mutex protects the whole module; the public API is
 *   thread-safe. The SDK's get_stream blocks up to a small
 *   timeout if no frame ready, so we drop the lock around it.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>

#include "ipcd.h"

/* ============================================================ */
/* SDK extern declarations — confirmed from libplat_ai.so,      */
/* libmpi_aenc.so, libapp_aenc_ex.so decompiles                 */
/* ============================================================ */

/* Same shape as ao_open_param: 4 ints. */
struct ai_open_param {
    int sample_rate;     /* 8000 / 12000 / 16000 / etc */
    int sample_bits;     /* must be 16 */
    int channel_num;     /* 1 or 2; mono only with dev_id=0 */
    int dev_id;          /* 0..3; mono only on 0 (the ADC) */
};

/* aec_attr is 0x18 = 24 bytes per the decompile (memcpy size).
 * Layout deduced from the factory cfg "ai_aec = 1024, 1024, 0":
 *   - 3 ints set (12 bytes)
 *   - 12 bytes of padding/reserved
 * The exact field names aren't documented but the values go
 * straight to ak_vqe_inner_set_ai_aec(); we trust the vendor's
 * factory tuning and don't second-guess. */
struct ai_aec_attr {
    int filter_len;     /* 1024 = ~64 ms tail length at 16 kHz */
    int search_window;  /* 1024 = far-end search range */
    int mode;           /* 0 = default mode */
    int reserved[3];    /* keep struct exactly 24 bytes */
};

extern int ak_ai_open(const struct ai_open_param *param, int *handle_id);
extern int ak_ai_close(int handle_id);
extern int ak_ai_start_capture(int handle_id);
extern int ak_ai_stop_capture(int handle_id);
extern int ak_ai_enable_aec(unsigned int handle_id, unsigned int enable);
extern int ak_ai_set_aec_attr(unsigned int handle_id,
                              const struct ai_aec_attr *attr);
extern int ak_ai_set_volume(int handle_id, int db);
extern int ak_ai_set_gain(int handle_id, int gain);
extern int ak_ai_enable_nr(unsigned int handle_id, unsigned int enable);
extern int ak_ai_enable_agc(unsigned int handle_id, unsigned int enable);

/* PCM frame from ak_ai_get_frame.
 * Layout deduced from check_get_frame_param: data must be NULL on
 * input (SDK allocates), frame->data is set to the new buffer ptr,
 * length is param_2[1]. Same shape as video VI frames. */
struct ai_pcm_frame {
    void     *data;       /* [0] — NULL on input, set by SDK */
    uint32_t  len;        /* [1] — bytes of PCM */
    uint32_t  pts_lo;     /* [2] */
    uint32_t  pts_hi;     /* [3] */
    uint32_t  seq;        /* [4] */
    uint32_t  reserved[3];/* keep room — release_frame expects
                           * the same struct back */
};

extern int ak_ai_get_frame(unsigned int handle_id,
                           struct ai_pcm_frame *frame, int timeout);
extern int ak_ai_release_frame(unsigned int handle_id,
                                struct ai_pcm_frame *frame);

/* AENC */
struct aenc_open_param {
    int sample_rate;
    int sample_bits;
    int channel_num;
    int type;            /* 3=AMR, 4=AAC, 17=G.711A, 18=G.711U */
};

extern int ak_aenc_open(const struct aenc_open_param *param, int *handle_id);
extern int ak_aenc_close(int handle_id);

/* Send PCM to encoder. The frame is the same layout as ai_pcm_frame
 * (SDK passes the AI frame directly through). */
extern int ak_aenc_send_frame(unsigned int handle_id,
                              const struct ai_pcm_frame *frame,
                              unsigned int flags);

/* Get encoded stream. Layout deduced from ak_aenc_get_stream
 * decompile:
 *   stream->data    = SDK-alloc'd encoded bytes
 *   stream->len     = byte count
 *   stream->pts_lo, pts_hi
 *   stream->seq
 * Caller MUST call ak_aenc_release_stream to free the alloc. */
struct aenc_stream {
    void     *data;       /* [0] */
    uint32_t  len;        /* [1] */
    uint32_t  pts_lo;     /* [2] */
    uint32_t  pts_hi;     /* [3] */
    uint32_t  seq;        /* [4] */
    uint32_t  reserved;   /* total 24 bytes per memcpy size */
};

extern int ak_aenc_get_stream(unsigned int handle_id,
                              struct aenc_stream *stream,
                              unsigned int timeout_ms);
extern int ak_aenc_release_stream(unsigned int handle_id,
                                  struct aenc_stream *stream);

/* ============================================================ */
/* Configuration                                                */
/* ============================================================ */

/* AI sampling: 8 kHz mono to match AENC's G.711 output rate
 * directly. The vendor uses 16 kHz internally because they need
 * higher rate for AEC quality. We disable AEC by default for
 * CPU reasons, so 8 kHz is fine and halves the data rate.
 *
 * If you re-enable AEC and find it's not effective, switching
 * back to 16 kHz here is the first thing to try. */
#define AI_SAMPLE_RATE       8000
#define AI_SAMPLE_BITS       16
#define AI_CHANNELS          1
#define AI_DEV_ID            0

/* Output codec: G.711 µ-law. Standard RTP payload type 0,
 * 8 kHz clock, 64 kbps. Universally supported. */
#define AENC_TYPE_G711U      18
#define AENC_SAMPLE_RATE     8000
#define AENC_SAMPLE_BITS     16
#define AENC_CHANNELS        1

/* Channel types for the bind. Verified in libapp_aenc_ex.so
 * decompile (app_audio_check_bind_chn_relation):
 *   AI    = 5      (audio source, mic)
 *   AO    = 6      (audio sink, speaker)
 *   AENC  = 15 (0xf)  (audio encoder dest)
 *   ADEC  = 16 (0x10) (audio decoder source)
 *
 * Valid bind tuples are:
 *   AI(5) -> AENC(15)    [our path: mic -> G.711 stream]
 *   AI(5) -> AO(6)       (loopback test)
 *   ADEC(16) -> AO(6)    [decode-to-speaker]
 *   ADEC(16) -> AENC(15) [re-encoding]
 *   AENC(15) -> ADEC(16) (transcoding loop, doesn't apply here)
 *
 * Earlier code used CHN_TYPE_AENC=6 by analogy with CHN_TYPE_AO=6
 * — wrong: that's AO, not AENC. The bind silently succeeded
 * because category-1 covers both, but get_stream specifically
 * checks type==0xf and would never find our (mistakenly bound)
 * dst. Result: 252 get_failures, 0 frames. */
#define CHN_TYPE_AI          5
#define CHN_TYPE_AENC        15
#define AI_CHN_ID            0
#define AENC_CHN_ID          0

/* AEC parameters from factory cfg ai_aec = 1024,1024,0.
 * Vendor-tuned for this exact hardware (mic-speaker geometry,
 * acoustic path). Don't change unless you're seeing residual
 * echo and have a way to measure improvement.
 *
 * AEC convolution at 1024 taps × 16 kHz is CPU-intensive on a
 * single-core ARMv7 SoC. If video fps suffers when audio is
 * active, set audio_aec_enable=0 in the config to bypass AEC.
 * Without AEC the mic still works but echo from the speaker
 * during talkback won't be cancelled. */
#define AEC_FILTER_LEN       1024
#define AEC_SEARCH_WINDOW    1024
#define AEC_MODE             0

/* Runtime toggle, settable via /api/config audio_aec_enable=0|1.
 * Default 0 (OFF) — AEC is expensive on this single-core SoC.
 * Enable only if echo from speaker is a problem (e.g., during
 * sustained talkback) and you accept lower video fps. */
static int g_aec_enabled = 0;

void audio_in_set_aec_enable(int enable)
{
    g_aec_enabled = enable ? 1 : 0;
    fprintf(stderr, "[audio_in] AEC %s (effective on next chain start)\n",
            g_aec_enabled ? "enabled" : "disabled");
}

int audio_in_get_aec_enable(void)
{
    return g_aec_enabled;
}

/* Mic input gain, dB. 0 = unattenuated. The vendor's Debug log
 * has gain=5; we match. Tune via /api/config later if needed. */
#define AI_GAIN_DEFAULT      5

/* ============================================================ */
/* State                                                        */
/* ============================================================ */
typedef struct {
    pthread_mutex_t  mtx;
    int              initialized;     /* module init done (no SDK yet) */

    /* SDK state — opened/closed on demand via acquire/release. */
    int              ai_handle;
    int              aenc_handle;
    int              ai_open;
    int              aenc_open;
    int              bound;
    int              capturing;
    int              streaming;        /* short-hand: full chain ready */

    /* Reference count: number of clients currently subscribed.
     * When refcount transitions 0->1 we open the SDK chain;
     * when it transitions 1->0 we close it. This avoids the
     * AEC + capture thread burning CPU (and starving VENC) when
     * no client is asking for mic audio. */
    int              refcount;

    /* Stats — useful for diagnosing dropouts. */
    unsigned long    frames_read;
    unsigned long    bytes_read;
    unsigned long    get_failures;
    long             last_frame_ms;
} audio_in_t;

static audio_in_t g_ai;

/* Forward decl — used by audio_in_set_enable below. */
static void chain_stop_locked(void);

/* Master enable. Set to 0 via /api/config to disable mic entirely
 * (audio is then absent from the RTSP SDP — clients see video
 * only). Also useful for privacy. Default 1. */
static int g_audio_in_enable = 1;

void audio_in_set_enable(int enable)
{
    int prev = g_audio_in_enable;
    g_audio_in_enable = enable ? 1 : 0;
    fprintf(stderr, "[audio_in] master enable: %d -> %d\n", prev, g_audio_in_enable);

    /* If we just got disabled while a chain is running, tear it
     * down. The next acquire will re-fail. */
    if (prev && !g_audio_in_enable && g_ai.streaming) {
        pthread_mutex_lock(&g_ai.mtx);
        chain_stop_locked();
        pthread_mutex_unlock(&g_ai.mtx);
    }
}

int audio_in_get_enable(void)
{
    return g_audio_in_enable;
}

static long mono_ms(void)
{
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return (long)t.tv_sec * 1000 + t.tv_nsec / 1000000;
}

/* ============================================================ */
/* Init / shutdown                                              */
/* ============================================================ */

static int ai_open_locked(void)
{
    struct ai_open_param p = {
        .sample_rate = AI_SAMPLE_RATE,
        .sample_bits = AI_SAMPLE_BITS,
        .channel_num = AI_CHANNELS,
        .dev_id      = AI_DEV_ID,
    };
    int rc = ak_ai_open(&p, &g_ai.ai_handle);
    if (rc != 0) {
        fprintf(stderr, "[audio_in] ak_ai_open rc=0x%x\n", rc);
        return -1;
    }
    g_ai.ai_open = 1;
    fprintf(stderr, "[audio_in] AI opened (handle=%d, %d Hz, %d ch, dev=%d)\n",
            g_ai.ai_handle, AI_SAMPLE_RATE, AI_CHANNELS, AI_DEV_ID);

    /* Mic gain. The Debug log shows the vendor uses gain=5.
     * Non-fatal if the call rejects. */
    rc = ak_ai_set_gain(g_ai.ai_handle, AI_GAIN_DEFAULT);
    if (rc != 0) {
        fprintf(stderr, "[audio_in] set_gain(%d) rc=0x%x (non-fatal)\n",
                AI_GAIN_DEFAULT, rc);
    }

    /* AEC config + enable. Order matters: set_aec_attr before
     * enable_aec so the parameters are in place when the engine
     * starts processing. Skipped entirely if the user disabled
     * AEC via /api/config — useful when CPU is tight. */
    if (g_aec_enabled) {
        struct ai_aec_attr aec = {
            .filter_len    = AEC_FILTER_LEN,
            .search_window = AEC_SEARCH_WINDOW,
            .mode          = AEC_MODE,
            .reserved      = {0, 0, 0},
        };
        rc = ak_ai_set_aec_attr((unsigned)g_ai.ai_handle, &aec);
        if (rc != 0) {
            fprintf(stderr, "[audio_in] set_aec_attr rc=0x%x (non-fatal, AEC disabled)\n", rc);
        } else {
            rc = ak_ai_enable_aec((unsigned)g_ai.ai_handle, 1);
            if (rc != 0) {
                fprintf(stderr, "[audio_in] enable_aec rc=0x%x\n", rc);
            } else {
                fprintf(stderr, "[audio_in] AEC enabled (filter=%d, win=%d, mode=%d)\n",
                        AEC_FILTER_LEN, AEC_SEARCH_WINDOW, AEC_MODE);
            }
        }
    } else {
        fprintf(stderr, "[audio_in] AEC bypassed (config: audio_aec_enable=0)\n");
    }

    /* DSP filters: NR, AGC etc. all run as part of the VQE
     * pipeline and contribute significant CPU. We start with
     * them all OFF — the mic capture works without them, just
     * with raw audio quality. If you want noise reduction or
     * AGC, enable them via /api/config (TODO future) but expect
     * additional CPU cost.
     *
     * In particular, leaving NR off avoids running its filter
     * convolution every 20 ms at 16 kHz, which is what's been
     * causing the video fps to drop during streaming. */
    rc = ak_ai_enable_nr((unsigned)g_ai.ai_handle, 0);
    if (rc != 0) {
        fprintf(stderr, "[audio_in] enable_nr(0) rc=0x%x (non-fatal)\n", rc);
    }
    rc = ak_ai_enable_agc((unsigned)g_ai.ai_handle, 0);
    if (rc != 0) {
        fprintf(stderr, "[audio_in] enable_agc(0) rc=0x%x (non-fatal)\n", rc);
    }

    return 0;
}

static int aenc_open_locked(void)
{
    struct aenc_open_param p = {
        .sample_rate = AENC_SAMPLE_RATE,
        .sample_bits = AENC_SAMPLE_BITS,
        .channel_num = AENC_CHANNELS,
        .type        = AENC_TYPE_G711U,
    };
    int rc = ak_aenc_open(&p, &g_ai.aenc_handle);
    if (rc != 0) {
        fprintf(stderr, "[audio_in] ak_aenc_open(G711U) rc=0x%x\n", rc);
        return -1;
    }
    g_ai.aenc_open = 1;
    fprintf(stderr, "[audio_in] AENC opened (handle=%d, type=G.711µ, %d Hz)\n",
            g_ai.aenc_handle, AENC_SAMPLE_RATE);
    return 0;
}

/* Open + start the AI->AENC chain manually (no app-level bind).
 *
 * The app_audio_bind_ai_aenc + set_dst_chn_active path turned
 * out to NOT actually pump PCM into the AENC encoder — the
 * internal stream_behavior loop allocates a stub buffer and calls
 * ak_aenc_send_frame, but the buffer it stores is empty (just a
 * memset-zero of 32 bytes). Result: 0 bytes of encoded data.
 *
 * Instead we pump manually in audio_in_get_frame():
 *   1. ak_ai_get_frame()      — pull PCM from mic
 *   2. ak_aenc_send_frame()   — push PCM into encoder
 *   3. ak_ai_release_frame()  — return mic buffer
 *   4. ak_aenc_get_stream()   — pull encoded G.711
 *   5. ak_aenc_release_stream — return encoded buffer
 *
 * Caller must hold g_ai.mtx. Idempotent. */
static int chain_start_locked(void)
{
    if (g_ai.streaming) return 0;
    if (ai_open_locked() != 0) goto fail;
    if (aenc_open_locked() != 0) goto fail;

    int rc = ak_ai_start_capture(g_ai.ai_handle);
    if (rc != 0) {
        fprintf(stderr, "[audio_in] start_capture rc=0x%x\n", rc);
        goto fail;
    }
    g_ai.capturing = 1;
    g_ai.streaming = 1;
    fprintf(stderr, "[audio_in] chain started "
            "(manual AI->AENC pump, G.711µ @ 8 kHz)\n");
    return 0;

fail:
    if (g_ai.aenc_open) { ak_aenc_close(g_ai.aenc_handle); g_ai.aenc_open = 0; }
    if (g_ai.ai_open)   { ak_ai_close(g_ai.ai_handle);     g_ai.ai_open   = 0; }
    return -1;
}

/* Stop + close. Caller must hold g_ai.mtx. */
static void chain_stop_locked(void)
{
    if (!g_ai.streaming) return;
    if (g_ai.capturing) {
        ak_ai_stop_capture(g_ai.ai_handle);
        g_ai.capturing = 0;
    }
    if (g_ai.aenc_open) { ak_aenc_close(g_ai.aenc_handle); g_ai.aenc_open = 0; }
    if (g_ai.ai_open)   { ak_ai_close(g_ai.ai_handle);     g_ai.ai_open   = 0; }
    g_ai.streaming = 0;
    fprintf(stderr, "[audio_in] chain stopped\n");
}

/* Public: register a "user" of the audio stream. The first user
 * triggers SDK open + capture start; subsequent users just bump
 * the refcount.
 *
 * Returns 0 if audio is now available, -1 if open failed. */
int audio_in_acquire(void)
{
    if (!g_ai.initialized) return -1;
    if (!g_audio_in_enable) return -1;
    pthread_mutex_lock(&g_ai.mtx);
    if (g_ai.refcount == 0) {
        if (chain_start_locked() != 0) {
            pthread_mutex_unlock(&g_ai.mtx);
            return -1;
        }
    }
    g_ai.refcount++;
    fprintf(stderr, "[audio_in] acquire (refcount=%d)\n", g_ai.refcount);
    pthread_mutex_unlock(&g_ai.mtx);
    return 0;
}

/* Public: release a previously-acquired user slot. When refcount
 * reaches 0, the SDK chain is torn down to save CPU. */
void audio_in_release(void)
{
    if (!g_ai.initialized) return;
    pthread_mutex_lock(&g_ai.mtx);
    if (g_ai.refcount > 0) g_ai.refcount--;
    fprintf(stderr, "[audio_in] release (refcount=%d)\n", g_ai.refcount);
    if (g_ai.refcount == 0) {
        chain_stop_locked();
    }
    pthread_mutex_unlock(&g_ai.mtx);
}

int audio_in_init(void)
{
    fprintf(stderr, "[audio_in] init: entering\n");

    if (g_ai.initialized) {
        fprintf(stderr, "[audio_in] init: already initialized\n");
        return 0;
    }
    memset(&g_ai, 0, sizeof(g_ai));
    pthread_mutex_init(&g_ai.mtx, NULL);

    /* Module is initialized but the SDK chain stays closed until
     * the first acquire(). This keeps the AEC engine + 16 kHz
     * capture thread out of the system when no client is using
     * audio — important on this single-core SoC where the AEC
     * convolution + VENC video can starve each other. */
    g_ai.initialized = 1;
    fprintf(stderr, "[audio_in] init OK (lazy: chain opens on first use)\n");
    return 0;
}

void audio_in_shutdown(void)
{
    if (!g_ai.initialized) return;
    pthread_mutex_lock(&g_ai.mtx);
    chain_stop_locked();
    g_ai.refcount = 0;
    g_ai.initialized = 0;
    pthread_mutex_unlock(&g_ai.mtx);
    pthread_mutex_destroy(&g_ai.mtx);
    fprintf(stderr, "[audio_in] shutdown done "
                    "(stats: frames=%lu bytes=%lu get_fails=%lu)\n",
            g_ai.frames_read, g_ai.bytes_read, g_ai.get_failures);
}

int audio_in_is_available(void)
{
    /* Available means: module init done AND master-enable is on.
     * This drives the SDP advertisement: when master-enable is
     * off, we don't include audio in the SDP and clients see
     * video only.
     *
     * The actual SDK chain may not be open yet; acquire() opens
     * it on demand if available returns true. */
    return g_ai.initialized && g_audio_in_enable;
}

/* ============================================================ */
/* Public — get one encoded frame                               */
/* ============================================================ */

/* Pull one G.711 µ-law frame. On success, copies up to *len
 * bytes into out, sets *len to the actual byte count.
 *
 * G.711 frame size = 160 bytes (20 ms @ 8 kHz, 1 byte/sample).
 * The SDK may deliver larger or smaller packs depending on its
 * internal buffering — we just copy what we get.
 *
 * Returns:
 *    0 on success
 *   -1 on transient failure (no frame ready, etc.)
 *   -2 on permanent failure (module not initialized)
 */
/* Pull one G.711 µ-law frame.
 *
 * Pipeline (manual, doesn't use app_audio_bind_ai_aenc):
 *
 *   1. ak_aenc_get_stream()   — drain any pending encoded output FIRST
 *                                (so the encoder's output queue has
 *                                 room for what we're about to push)
 *   2. ak_ai_get_frame()      — pull PCM from mic
 *   3. ak_aenc_send_frame()   — push PCM into encoder
 *   4. ak_ai_release_frame()  — return mic buffer to SDK pool
 *   5. If we got encoded output in step 1, return it; else
 *      retry get_stream once now (the just-pushed PCM may have
 *      produced output immediately).
 *
 * Why drain first: ak_aenc_send_frame returns 0x10000007 ("list
 * count too many, please get stream") if the encoder has > 0x32
 * (50) unread output frames. The SDK encoded our PCM successfully
 * but is now blocking us until we read.
 *
 * Mutex held for the whole cycle.
 *
 * Returns:
 *    0 on success — *len = bytes written
 *   -1 on transient (no PCM ready, no encoded output yet)
 *   -2 on permanent (module not initialized)
 */
int audio_in_get_frame(uint8_t *out, size_t *len)
{
    if (!out || !len || *len == 0) return -2;
    if (!g_ai.initialized) return -2;

    pthread_mutex_lock(&g_ai.mtx);
    if (!g_ai.streaming) {
        pthread_mutex_unlock(&g_ai.mtx);
        *len = 0;
        return -1;
    }

    /* Step 1: drain any pending encoded output. Use 0 timeout —
     * we don't want to block, just take whatever's ready. The
     * encoder accumulates output until we read; if its queue
     * fills, send_frame fails with 0x10000007. */
    struct aenc_stream enc;
    memset(&enc, 0, sizeof(enc));
    int got_stream = 0;
    int rc = ak_aenc_get_stream((unsigned)g_ai.aenc_handle, &enc, 0);
    if (rc == 0 && enc.data && enc.len > 0) {
        got_stream = 1;
    }

    /* Step 2: pull PCM from mic. Short timeout to avoid blocking
     * forever if mic has stalled. */
    struct ai_pcm_frame pcm;
    memset(&pcm, 0, sizeof(pcm));
    int ai_rc = ak_ai_get_frame((unsigned)g_ai.ai_handle, &pcm, 10);
    if (ai_rc == 0) {
        /* Step 3: feed encoder. */
        int send_rc = ak_aenc_send_frame((unsigned)g_ai.aenc_handle, &pcm, 0);
        if (send_rc != 0 && send_rc != 0x10000007) {
            /* 0x10000007 = output queue full; that's fine, we'll
             * drain on the next call. Other errors are real. */
            fprintf(stderr, "[audio_in] aenc_send_frame rc=0x%x (pcm_len=%u)\n",
                    send_rc, pcm.len);
        }
        /* Step 4: return PCM buffer to pool. */
        ak_ai_release_frame((unsigned)g_ai.ai_handle, &pcm);
    }

    /* Step 5: if we didn't already get an encoded frame in step 1,
     * try once more now (the PCM we just pushed may have produced
     * output instantly for G.711). */
    if (!got_stream) {
        memset(&enc, 0, sizeof(enc));
        rc = ak_aenc_get_stream((unsigned)g_ai.aenc_handle, &enc, 5);
        if (rc == 0 && enc.data && enc.len > 0) {
            got_stream = 1;
        }
    }

    if (!got_stream) {
        g_ai.get_failures++;
        pthread_mutex_unlock(&g_ai.mtx);
        *len = 0;
        return -1;
    }

    /* Copy out, release. */
    size_t copy = enc.len;
    if (copy > *len) copy = *len;
    if (enc.data && copy > 0) memcpy(out, enc.data, copy);
    ak_aenc_release_stream((unsigned)g_ai.aenc_handle, &enc);

    *len = copy;
    g_ai.frames_read++;
    g_ai.bytes_read += copy;
    g_ai.last_frame_ms = mono_ms();
    pthread_mutex_unlock(&g_ai.mtx);
    return 0;
}
