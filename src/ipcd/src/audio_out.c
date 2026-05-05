/*
 * audio_out.c — speaker output for two-way audio backchannel.
 *
 * Architecture:
 *
 *   HTTP POST /talkback (or eventually ONVIF Profile T backchannel)
 *      |
 *      v
 *   audio_out_push_g711(codec, buf, len)   — caller-provided codec bytes
 *   audio_out_push_pcm  (samples, n)       — caller-provided 16-bit PCM
 *      |
 *      v
 *   ring buffer (64 KiB, ~1 second @ 16 kHz mono 16-bit)
 *      |
 *      v
 *   speaker_thread — drains the ring buffer, calls SDK ak_ao_send_frame
 *      |
 *      v
 *   hardware DAC + amplifier (gpio-enabled at init time)
 *
 * G.711 decode:
 *   - µ-law (PT=0)  and A-law (PT=8) — both are 8 kHz, 8-bit, mono in
 *     standard RTP usage, but on this SoC the AO pipeline runs at
 *     16 kHz mono 16-bit, so we upsample 8k -> 16k by linear
 *     interpolation while decoding.
 *   - LUTs are 256 entries × int16, computed at init time per ITU-T
 *     G.711. Self-contained, no SDK dependency.
 *
 * Lifetime:
 *   audio_out_init() opens the AO channel and enables the amp GPIO.
 *   The speaker thread starts immediately and idles when the ring is
 *   empty. Close is performed by audio_out_shutdown().
 *
 *   The amp is left enabled for the lifetime of the module — the
 *   click on power-up is annoying if we toggle it per-burst. Power
 *   draw is small (~tens of mA on this class of camera).
 *
 * SDK speaker API:
 *   The Anyka SDK exports ak_ao_* in libplat_ao.so. Prototypes
 *   were reverse-engineered (Ghidra decompile + readelf) and the
 *   real signatures are now linked directly — see the SDK section
 *   below. The decoder side (libmpi_adec.so) is used for AAC; the
 *   G.711 path is pure software, no SDK dependency.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <sys/stat.h>

#include "ipcd.h"

/* ============================================================ */
/* Tunables                                                     */
/* ============================================================ */

/* Speaker hardware sample rate. The vendor configures AO at 16 kHz
 * (per the Debug_log "audioAoAttr.sampleRate = 16000"), so we
 * upsample 8 kHz G.711 to 16 kHz before sending. */
#define AO_SAMPLE_RATE     16000
#define AO_CHANNELS        1
#define AO_SAMPLE_BITS     16
#define AO_FRAME_MS        20         /* 20 ms per AO write */
#define AO_FRAME_SAMPLES   (AO_SAMPLE_RATE * AO_FRAME_MS / 1000)
#define AO_FRAME_BYTES     (AO_FRAME_SAMPLES * 2)   /* 16-bit mono */

/* Ring buffer: at 16 kHz mono 16-bit, 64 KiB holds ~2 seconds.
 * That's enough headroom for typical TCP bufferbloat; HTTP push
 * clients occasionally deliver in big bursts. */
#define RING_SIZE_BYTES    65536

/* GPIO controlling the amplifier enable. The vendor's hal_audio.c
 * logs "enable speaker 0 gpio 1 result [1]", suggesting GPIO #1 is
 * the amp enable. We expose the number as a build-time configurable
 * since other camera variants may differ. */
#ifndef AUDIO_AMP_GPIO
#define AUDIO_AMP_GPIO     1
#endif

/* Default speaker volume in dB. The SDK's ak_ao_set_volume accepts
 * dB in [-90..+20] (verified in libplat_ao.so decompile). 0 dB is
 * unattenuated — full DAC scale.
 *
 * On this hardware, 0 dB is described by the user as "bello forte"
 * (loud). For typical indoor use a -12 to -20 dB attenuation gives
 * conversational levels. We default to -12 as a less startling
 * out-of-box setting; the user can tune from there.
 *
 * Range bounds chosen tighter than SDK's: practical talkback
 * doesn't benefit from +20 dB (boost above DAC max = clipping)
 * and below ~-40 dB the speaker is essentially silent.
 */
#define AUDIO_VOLUME_DEFAULT_DB   (-12)
#define AUDIO_VOLUME_MIN_DB       (-40)
#define AUDIO_VOLUME_MAX_DB       (+10)

/* ============================================================ */
/* G.711 µ-law and A-law decode tables                          */
/*                                                              */
/* Built once at audio_out_init from the canonical ITU-T G.711  */
/* algorithms. Each table is 256 entries of int16 PCM samples.  */
/* ============================================================ */
static int16_t g_ulaw_lut[256];
static int16_t g_alaw_lut[256];

static int16_t ulaw_to_pcm(uint8_t u)
{
    /* µ-law decode per ITU-T G.711 Section 2.
     *
     * Sign convention: on-the-wire MSB=0 means NEGATIVE,
     * MSB=1 means POSITIVE. The customary first step `u = ~u`
     * inverts the byte; after the inversion, the sign bit reads
     * the opposite way. So in our inverted byte, MSB=1 means
     * the original MSB was 0 → NEGATIVE.
     *
     * Verified host-side against Python's audioop.ulaw2lin:
     *   ulaw 0x00 -> -32124    (max negative)
     *   ulaw 0x80 -> +32124    (max positive)
     *   ulaw 0x7F, 0xFF -> ~0  (silence)
     */
    u = ~u;
    int sign = (u & 0x80) ? -1 : 1;
    int exp  = (u >> 4) & 0x07;
    int mant = u & 0x0F;
    int magnitude = ((mant << 3) + 0x84) << exp;
    magnitude -= 0x84;
    return (int16_t)(sign * magnitude);
}

static int16_t alaw_to_pcm(uint8_t a)
{
    /* A-law decode: ITU-T G.711 Section 2.
     *
     * Sign convention same as µ-law: on-the-wire MSB=1 means
     * POSITIVE. After XOR-with-0x55 (the standard first step),
     * the sign bit reads as-is — but the sign mapping from there
     * varies by source. We verified by host-side test against
     * Python audioop:
     *   alaw_to_pcm(0xAA) must be max positive ~+32256
     *   alaw_to_pcm(0x2A) must be max negative ~-32256
     * which means after XOR, MSB=1 -> POSITIVE.
     */
    a ^= 0x55;
    int sign = (a & 0x80) ? 1 : -1;
    int exp  = (a >> 4) & 0x07;
    int mant = a & 0x0F;
    int magnitude;
    if (exp == 0) {
        magnitude = (mant << 4) + 8;
    } else {
        magnitude = ((mant << 4) + 0x108) << (exp - 1);
    }
    return (int16_t)(sign * magnitude);
}

static void g711_init_luts(void)
{
    for (int i = 0; i < 256; i++) {
        g_ulaw_lut[i] = ulaw_to_pcm((uint8_t)i);
        g_alaw_lut[i] = alaw_to_pcm((uint8_t)i);
    }
}

/* ============================================================ */
/* Ring buffer (single-producer single-consumer)                */
/*                                                              */
/* Pushers (HTTP threads) and the speaker thread synchronise on */
/* g_ring_mtx. This is simpler than a lock-free ring and the    */
/* throughput is 16 KB/s — locking overhead is negligible.     */
/* ============================================================ */
static uint8_t  g_ring[RING_SIZE_BYTES];
static size_t   g_ring_head;          /* write position */
static size_t   g_ring_tail;          /* read position  */
static size_t   g_ring_count;         /* bytes currently buffered */
static pthread_mutex_t g_ring_mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t  g_ring_cv  = PTHREAD_COND_INITIALIZER;

static size_t ring_free_locked(void)
{
    return RING_SIZE_BYTES - g_ring_count;
}

/* Push raw PCM into the ring. If the ring would overflow, we drop
 * the oldest data — speakers can't replay history, "now" is what
 * matters. */
static void ring_push_pcm_locked(const uint8_t *data, size_t len)
{
    if (len > RING_SIZE_BYTES) {
        /* Caller sent more than we can hold in one go; trim to the
         * tail, since again "newest is best". */
        data += len - RING_SIZE_BYTES;
        len   = RING_SIZE_BYTES;
    }
    if (len > ring_free_locked()) {
        /* Drop oldest to make room. */
        size_t need = len - ring_free_locked();
        g_ring_tail  = (g_ring_tail + need) % RING_SIZE_BYTES;
        g_ring_count -= need;
    }
    /* Copy in two segments if we wrap. */
    size_t first = RING_SIZE_BYTES - g_ring_head;
    if (first > len) first = len;
    memcpy(g_ring + g_ring_head, data, first);
    if (len > first)
        memcpy(g_ring, data + first, len - first);
    g_ring_head = (g_ring_head + len) % RING_SIZE_BYTES;
    g_ring_count += len;
}

/* Pop up to `len` bytes into `out`. Returns bytes actually popped. */
static size_t ring_pop_locked(uint8_t *out, size_t len)
{
    if (len > g_ring_count) len = g_ring_count;
    size_t first = RING_SIZE_BYTES - g_ring_tail;
    if (first > len) first = len;
    memcpy(out, g_ring + g_ring_tail, first);
    if (len > first)
        memcpy(out + first, g_ring, len - first);
    g_ring_tail  = (g_ring_tail + len) % RING_SIZE_BYTES;
    g_ring_count -= len;
    return len;
}

/* ============================================================ */
/* GPIO amp enable                                              */
/* ============================================================ */

/* Try to enable a GPIO via sysfs. The kernel exports the GPIO if
 * we write the number to /sys/class/gpio/export, then we set
 * direction=out and value=1. If the GPIO is already exported, the
 * export step returns EBUSY and we just continue.
 *
 * Returns 0 on success, -1 on failure. Failure is not fatal —
 * the speaker may still work if the amp is hardwired enabled. */
static int gpio_set(int n, int high)
{
    char buf[64];
    int  fd;

    /* Export. EBUSY = already exported, fine. */
    fd = open("/sys/class/gpio/export", O_WRONLY);
    if (fd >= 0) {
        snprintf(buf, sizeof(buf), "%d", n);
        if (write(fd, buf, strlen(buf)) < 0) {
            if (errno != EBUSY) {
                fprintf(stderr, "[audio_out] gpio %d export: %s\n",
                        n, strerror(errno));
            }
        }
        close(fd);
    }

    /* direction=out */
    snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/direction", n);
    fd = open(buf, O_WRONLY);
    if (fd < 0) {
        fprintf(stderr, "[audio_out] gpio %d direction: %s\n",
                n, strerror(errno));
        return -1;
    }
    if (write(fd, "out", 3) < 0) {
        fprintf(stderr, "[audio_out] gpio %d set out: %s\n",
                n, strerror(errno));
        close(fd);
        return -1;
    }
    close(fd);

    /* value */
    snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/value", n);
    fd = open(buf, O_WRONLY);
    if (fd < 0) {
        fprintf(stderr, "[audio_out] gpio %d value: %s\n",
                n, strerror(errno));
        return -1;
    }
    if (write(fd, high ? "1" : "0", 1) < 0) {
        fprintf(stderr, "[audio_out] gpio %d set value: %s\n",
                n, strerror(errno));
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

/* ============================================================ */
/* SDK AO API — confirmed prototypes from libplat_ao.so          */
/* (ELF symbols + decompile via Ghidra, see                      */
/*  /mnt/project/libplat_ao.so.c reverse-engineered files).      */
/*                                                               */
/* Earlier versions of this module used dlsym() because the      */
/* signatures weren't known yet. We now link against the real    */
/* symbols directly — fewer moving parts, simpler error paths.   */
/* ============================================================ */

/* AO open parameter struct — 4 ints in this order.
 *
 * From the decompile of ak_ao_open's check_open_param:
 *   param_1[0] sample_rate (8000, 12000, 16000, 22050, 24000,
 *              32000, 44100, 48000, 96000)
 *   param_1[1] sample_bits (must equal 0x10 = 16)
 *   param_1[2] channel_num (1 or 2)
 *   param_1[3] dev_id (0..3; dev_id=1 + channel=1 not allowed) */
struct ao_open_param {
    int sample_rate;
    int sample_bits;
    int channel_num;
    int dev_id;
};

extern int ak_ao_open(const struct ao_open_param *param,
                      unsigned int *handle_id);
extern int ak_ao_close(unsigned int handle_id);

/* ak_ao_send_frame(handle, data, len, &out_param)
 *
 * Length limits — confirmed against the decompile:
 *   - Mono at any sample_rate <= 48 kHz: max 0x1000 = 4096 bytes
 *   - Stereo at <= 48 kHz:               max 0x2000 = 8192 bytes
 *   - Any channels at >  48 kHz:         max 0x4000 = 16384 bytes
 *   - Absolute outer cap (checked first): 0x6400 = 25600 bytes
 *
 * `len` MUST be a multiple of 2 for mono, 4 for stereo (sample
 * alignment). Anything else returns 0x101.
 *
 * The 4th argument is read in the SDK but its value is ignored on
 * the success path; we pass &dummy to avoid passing literal NULL
 * which the SDK might (or might not) check. */
extern int ak_ao_send_frame(unsigned int handle_id,
                            const void *data, unsigned int len,
                            int *out_param);

/* ak_ao_set_speaker(dev_id, enable) — toggles the amplifier
 * enable line (board-specific GPIO; on this hardware
 * Debug_log says "enable speaker 0 gpio 1"). */
extern int ak_ao_set_speaker(unsigned int dev_id, unsigned int enable);

extern int ak_ao_set_volume(unsigned int handle_id, int volume);
extern int ak_ao_wait_play_finish(unsigned int handle_id);

/* ============================================================ */
/* AO channel state                                              */
/* ============================================================ */
static int          g_ao_open;
static unsigned int g_ao_handle;

/* Current volume in dB. Single-word reads/writes are atomic on
 * ARM, mirror of motion_set_threshold pattern. The setter applies
 * the new value to the live AO handle if open; otherwise the
 * value is saved and applied at the next ak_ao_open. */
static int g_ao_volume_db = AUDIO_VOLUME_DEFAULT_DB;

void audio_out_set_volume_db(int db)
{
    if (db < AUDIO_VOLUME_MIN_DB) db = AUDIO_VOLUME_MIN_DB;
    if (db > AUDIO_VOLUME_MAX_DB) db = AUDIO_VOLUME_MAX_DB;
    g_ao_volume_db = db;

    if (g_ao_open) {
        int rc = ak_ao_set_volume(g_ao_handle, db);
        if (rc != 0) {
            fprintf(stderr,
                "[audio_out] set_volume(%d dB) rc=0x%x\n", db, rc);
            return;
        }
    }
    fprintf(stderr, "[audio_out] volume = %d dB\n", db);
}

int audio_out_get_volume_db(void)
{
    return g_ao_volume_db;
}

static int sdk_resolve(void)
{
    /* Nothing to do — we link against the symbols directly. The
     * function is kept (as a no-op) to preserve call sites and
     * make a future move back to dlsym easier if some camera
     * variant lacks one of these symbols. */
    return 0;
}

static int sdk_speaker_open(void)
{
    struct ao_open_param p = {
        .sample_rate = AO_SAMPLE_RATE,
        .sample_bits = AO_SAMPLE_BITS,
        .channel_num = AO_CHANNELS,
        .dev_id      = 0,
    };
    int rc = ak_ao_open(&p, &g_ao_handle);
    if (rc != 0) {
        fprintf(stderr, "[audio_out] ak_ao_open rc=0x%x — speaker disabled\n", rc);
        return -1;
    }
    g_ao_open = 1;
    fprintf(stderr, "[audio_out] AO opened "
                    "(handle=%u, %d Hz, %d ch, %d bit)\n",
            g_ao_handle, AO_SAMPLE_RATE, AO_CHANNELS, AO_SAMPLE_BITS);

    /* Volume — applied from g_ao_volume_db (settable runtime via
     * audio_out_set_volume_db). Default is AUDIO_VOLUME_DEFAULT_DB
     * unless cfgfile loaded a different audio_volume_db before
     * audio_out_init runs. */
    rc = ak_ao_set_volume(g_ao_handle, g_ao_volume_db);
    if (rc != 0) {
        fprintf(stderr, "[audio_out] set_volume(%d dB) rc=0x%x (non-fatal)\n",
                g_ao_volume_db, rc);
    } else {
        fprintf(stderr, "[audio_out] volume = %d dB\n", g_ao_volume_db);
    }

    /* Enable the amp via the SDK's set_speaker. This is what the
     * vendor's hal_audio_enable_speaker maps to internally; the
     * sysfs GPIO fallback below is kept for cameras whose SDK
     * doesn't toggle the GPIO for us. */
    rc = ak_ao_set_speaker(0, 1);
    if (rc != 0) {
        fprintf(stderr, "[audio_out] set_speaker rc=0x%x — "
                        "trying sysfs GPIO%d fallback\n",
                rc, AUDIO_AMP_GPIO);
        if (gpio_set(AUDIO_AMP_GPIO, 1) != 0) {
            fprintf(stderr, "[audio_out] amp enable failed both ways — "
                            "speaker may be silent\n");
            /* Not fatal: the AO channel is still open and writes
             * succeed; only the audible result is missing. */
        }
    }
    return 0;
}

static void sdk_speaker_close(void)
{
    if (!g_ao_open) return;
    /* Drain the SDK's internal buffer before disabling. */
    ak_ao_wait_play_finish(g_ao_handle);
    ak_ao_set_speaker(0, 0);
    ak_ao_close(g_ao_handle);
    g_ao_open = 0;
}

static int sdk_speaker_send(const void *pcm, size_t bytes)
{
    if (!g_ao_open) return -1;

    /* Chunk to AO_FRAME_BYTES (~640 bytes / 20 ms @ 16 kHz).
     * The SDK's send_frame caps at 25600 bytes per call but
     * smaller chunks reduce blocking time and let the watchdog
     * kick in promptly if the AO ever stalls. */
    const uint8_t *p = pcm;
    size_t rem = bytes;
    while (rem > 0) {
        size_t n = rem > AO_FRAME_BYTES ? AO_FRAME_BYTES : rem;
        int dummy = 0;
        int rc = ak_ao_send_frame(g_ao_handle, p, (unsigned)n, &dummy);
        if (rc != 0) {
            fprintf(stderr, "[audio_out] ak_ao_send_frame rc=0x%x "
                            "(len=%zu)\n", rc, n);
            return -1;
        }
        p   += n;
        rem -= n;
    }
    return 0;
}

/* ============================================================ */
/* Speaker thread                                               */
/*                                                              */
/* Drains the ring into the SDK speaker. Sleeps when empty, no   */
/* polling. Wakes via the ring condvar.                         */
/* ============================================================ */
static pthread_t g_spk_tid;
static int       g_spk_run;

static void *speaker_thread(void *arg)
{
    (void)arg;
    uint8_t frame[AO_FRAME_BYTES];

    pthread_mutex_lock(&g_ring_mtx);
    while (g_spk_run) {
        if (g_ring_count < AO_FRAME_BYTES) {
            /* Wait for more data, or for shutdown. We don't try to
             * partially drain — the SDK prefers fixed-size frames
             * and the latency cost of waiting one more frame is
             * <= 20 ms. */
            pthread_cond_wait(&g_ring_cv, &g_ring_mtx);
            continue;
        }
        ring_pop_locked(frame, AO_FRAME_BYTES);
        pthread_mutex_unlock(&g_ring_mtx);

        sdk_speaker_send(frame, AO_FRAME_BYTES);

        pthread_mutex_lock(&g_ring_mtx);
    }
    pthread_mutex_unlock(&g_ring_mtx);
    return NULL;
}

/* ============================================================ */
/* Public API                                                   */
/* ============================================================ */

static int g_initialized;

/* Time of the last push (in monotonic ms). Used by the pop
 * suppression in audio_out_push_pcm to decide whether to
 * prepend silence + fade-in. 0 = never pushed yet. */
static long g_last_push_ms;

static long mono_ms(void)
{
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return (long)t.tv_sec * 1000 + t.tv_nsec / 1000000;
}

int audio_out_init(void)
{
    fprintf(stderr, "[audio_out] init: entering\n");
    if (g_initialized) {
        fprintf(stderr, "[audio_out] init: already initialized\n");
        return 0;
    }

    g711_init_luts();
    fprintf(stderr, "[audio_out] init: G.711 LUTs ready\n");

    /* Order is significant: open AO first, then enable amp via
     * SDK's set_speaker. This mirrors the vendor's hal_audio
     * sequence in the Debug log:
     *   audioAoAttr.sampleRate = 16000   <- ao_open_param
     *   ...
     *   enable speaker 0 gpio 1 result [1]   <- set_speaker(0,1)
     * sdk_speaker_open does both. */
    if (sdk_resolve() != 0) {
        fprintf(stderr, "[audio_out] init: sdk_resolve failed\n");
        return -1;
    }
    fprintf(stderr, "[audio_out] init: about to call ak_ao_open\n");
    if (sdk_speaker_open() != 0) {
        fprintf(stderr, "[audio_out] init: sdk_speaker_open failed\n");
        return -1;
    }
    fprintf(stderr, "[audio_out] init: ak_ao_open succeeded\n");

    g_spk_run = 1;
    if (pthread_create(&g_spk_tid, NULL, speaker_thread, NULL) != 0) {
        fprintf(stderr, "[audio_out] init: pthread_create failed\n");
        sdk_speaker_close();
        return -1;
    }

    g_initialized = 1;
    fprintf(stderr, "[audio_out] init OK\n");
    return 0;
}

void audio_out_shutdown(void)
{
    if (!g_initialized) return;

    pthread_mutex_lock(&g_ring_mtx);
    g_spk_run = 0;
    pthread_cond_broadcast(&g_ring_cv);
    pthread_mutex_unlock(&g_ring_mtx);
    pthread_join(g_spk_tid, NULL);

    /* sdk_speaker_close handles wait_play_finish, set_speaker(0)
     * and ak_ao_close in the right order. */
    sdk_speaker_close();

    /* Reset ring */
    pthread_mutex_lock(&g_ring_mtx);
    g_ring_head = g_ring_tail = g_ring_count = 0;
    pthread_mutex_unlock(&g_ring_mtx);

    g_initialized = 0;
    fprintf(stderr, "[audio_out] shutdown done\n");
}

int audio_out_is_available(void)
{
    return g_initialized;
}

/* Push raw 16-bit signed mono PCM at AO_SAMPLE_RATE.
 * `samples` is the number of int16 samples (not bytes).
 *
 * Pop-suppression: if more than POP_GUARD_MS have elapsed since
 * the last push, we prepend ~50 ms of silence and apply a brief
 * linear fade-in to the first frame. Reasoning: when the DAC is
 * idle for a while, the amp sits in a high-impedance "quiet"
 * state. The first sample of new audio causes a sudden current
 * step in the speaker coil — audible as a click/pop, regardless
 * of whether the audio itself starts at silence-level or not.
 *
 * Pre-roll silence lets the DAC ramp up its output before the
 * real signal arrives, and the linear fade ensures the very
 * first non-silent sample doesn't appear as a step from 0. */
#define POP_GUARD_MS         500   /* idle threshold to retrigger guard */
#define POP_PREROLL_MS       50    /* zero PCM before first real audio */
#define POP_FADEIN_MS        20    /* linear fade-in length */

int audio_out_push_pcm(const int16_t *samples, size_t n_samples)
{
    if (!g_initialized) return -1;
    pthread_mutex_lock(&g_ring_mtx);

    /* Decide whether we need pop suppression. We track the time
     * of the last push; if too long ago, the amp has gone idle
     * and a transient is likely. */
    long now = mono_ms();
    int need_guard = (g_last_push_ms == 0) ||
                     (now - g_last_push_ms > POP_GUARD_MS);
    g_last_push_ms = now;

    if (need_guard && n_samples > 0) {
        /* Pre-roll: PCM zero (true silence). The amp settles
         * into normal-output mode before the real signal hits. */
        size_t preroll = AO_SAMPLE_RATE * POP_PREROLL_MS / 1000;
        int16_t zero = 0;
        for (size_t i = 0; i < preroll; i++) {
            ring_push_pcm_locked((const uint8_t *)&zero, 2);
        }

        /* Linear fade-in on the first POP_FADEIN_MS of real audio.
         * sample[i] *= i / fade_len  for i in [0..fade_len) */
        size_t fade_len = AO_SAMPLE_RATE * POP_FADEIN_MS / 1000;
        if (fade_len > n_samples) fade_len = n_samples;
        for (size_t i = 0; i < fade_len; i++) {
            int32_t v = (int32_t)samples[i] * (int32_t)i / (int32_t)fade_len;
            int16_t s = (int16_t)v;
            ring_push_pcm_locked((const uint8_t *)&s, 2);
        }
        /* Remainder unchanged. */
        if (fade_len < n_samples) {
            ring_push_pcm_locked((const uint8_t *)(samples + fade_len),
                                 (n_samples - fade_len) * 2);
        }
    } else {
        ring_push_pcm_locked((const uint8_t *)samples, n_samples * 2);
    }

    pthread_cond_signal(&g_ring_cv);
    pthread_mutex_unlock(&g_ring_mtx);
    return 0;
}

/* Flush the ring: any tail of less than AO_FRAME_BYTES is sent
 * out anyway, padded with silence if needed to match the SDK's
 * mono alignment requirement (multiple of 2 bytes).
 *
 * Useful at the end of an HTTP /talkback so the last few hundred
 * bytes don't sit in the ring forever. The cost is at most one
 * AO_FRAME_BYTES of trailing silence, ~20 ms — inaudible. */
void audio_out_flush(void)
{
    if (!g_initialized) return;

    uint8_t frame[AO_FRAME_BYTES];
    pthread_mutex_lock(&g_ring_mtx);
    if (g_ring_count == 0) {
        pthread_mutex_unlock(&g_ring_mtx);
        return;
    }
    /* Drain up to one AO_FRAME_BYTES, padded with zero (silence)
     * if shorter. Multiple incomplete frames are unlikely (callers
     * usually flush once per stream); we do one at most. */
    size_t got = ring_pop_locked(frame, AO_FRAME_BYTES);
    pthread_mutex_unlock(&g_ring_mtx);

    if (got > 0) {
        if (got < AO_FRAME_BYTES) {
            memset(frame + got, 0, AO_FRAME_BYTES - got);
        }
        sdk_speaker_send(frame, AO_FRAME_BYTES);
    }
}

/* Decode + upsample G.711 8 kHz mono into 16 kHz mono PCM.
 *
 *   codec: AUDIO_CODEC_G711U or AUDIO_CODEC_G711A
 *   buf:   raw G.711 bytes (one byte per 8 kHz sample)
 *   len:   buffer length in bytes / number of input samples
 *
 * Output: 2× the input samples (8k -> 16k upsample by linear
 * interpolation).
 */
int audio_out_push_g711(int codec, const uint8_t *buf, size_t len)
{
    if (!g_initialized) return -1;
    if (len == 0) return 0;

    const int16_t *lut;
    if      (codec == AUDIO_CODEC_G711U) lut = g_ulaw_lut;
    else if (codec == AUDIO_CODEC_G711A) lut = g_alaw_lut;
    else return -1;

    /* We allocate a stack buffer for up to ~20ms at 16 kHz
     * (320 samples = 640 bytes). For longer inputs, we loop in
     * chunks. */
    enum { CHUNK_IN = 160 };  /* 20 ms @ 8 kHz */
    int16_t pcm16k[CHUNK_IN * 2];

    /* The previous sample carries across chunks for proper
     * linear-interpolation continuity. Static is fine here because
     * push is single-threaded per stream, and even if multiple
     * concurrent streams pushed (we don't support that yet),
     * tiny click is the worst outcome. */
    static int16_t prev = 0;

    size_t off = 0;
    while (off < len) {
        size_t n_in = len - off;
        if (n_in > CHUNK_IN) n_in = CHUNK_IN;

        /* Decode + linear upsample 8k -> 16k. For each input sample
         *   y_2k   = (prev + cur) / 2     (interpolated midpoint)
         *   y_2k+1 = cur                   (current sample)
         */
        for (size_t i = 0; i < n_in; i++) {
            int16_t cur = lut[buf[off + i]];
            pcm16k[i * 2]     = (int16_t)(((int)prev + (int)cur) / 2);
            pcm16k[i * 2 + 1] = cur;
            prev = cur;
        }
        audio_out_push_pcm(pcm16k, n_in * 2);
        off += n_in;
    }
    return 0;
}
