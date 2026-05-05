/*
 * rtsp_server.c — minimal RTSP/RTP server for embedded camera use
 *
 * SCAFFOLDING ONLY (turn 1 of 4):
 *   ✓ Public API (push_au, init, shutdown)
 *   ✓ Per-stream ring buffer (push side; consume side via streamer
 *     thread will use it from turn 3 onwards)
 *   ✓ Acceptor thread that accepts TCP connections on the listen port
 *   ✓ Parameter-set extraction from pushed AUs (VPS/SPS/PPS)
 *   ✓ Single-client guard: we accept one client at a time and 503 the rest
 *
 * NOT YET IMPLEMENTED (will be added in turns 2/3/4):
 *   ✗ RTSP request parser + state machine (turn 2)
 *   ✗ SDP generator (turn 2)
 *   ✗ RTP packetization (turn 3)
 *   ✗ Streamer thread (turn 3)
 *   ✗ HEVC SPS rewriter (turn 4)
 *
 * For now the acceptor closes any connecting client immediately after
 * sending a 501 response — just enough to verify the build, port, and
 * threading work end-to-end without breaking anything if you accidentally
 * point VLC at it.
 */

/* _GNU_SOURCE is set by the Makefile's -D_GNU_SOURCE. */
#include "ipcd.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <stdint.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

/* ====================================================================== */
/* Tunables                                                               */
/* ====================================================================== */

/* Ring buffer depth per stream. Must be >= 2x the largest expected GOP
 * so that a freshly-connected client always has at least one IDR
 * available. At 15fps + GOP=2s = 30 frames per GOP, 64 is generous. */
#define RING_DEPTH         64

/* Maximum size of a single NAL unit we'll accept in the ring. Bigger
 * NALs are dropped with a log message. The HEVC encoder on this SoC
 * caps frames at ~512KB (encoder stream buf), so 768KB is safe. */
#define MAX_NAL_BYTES      (768 * 1024)

/* Maximum size of a parameter set NAL (VPS/SPS/PPS). 256B is plenty
 * for HEVC; SPS at 1080p main profile is ~50B, VPS ~25B, PPS ~10B. */
#define MAX_PARAM_SET_LEN  256

/* ====================================================================== */
/* NAL type constants                                                     */
/* ====================================================================== */

/* H.264 NAL unit types we care about */
#define H264_NAL_IDR       5
#define H264_NAL_SPS       7
#define H264_NAL_PPS       8

/* HEVC NAL unit types we care about */
#define HEVC_NAL_VPS       32
#define HEVC_NAL_SPS       33
#define HEVC_NAL_PPS       34
#define HEVC_NAL_IDR_W_RADL 19
#define HEVC_NAL_IDR_N_LP   20

static int h264_nal_type(const uint8_t *nal) { return nal[0] & 0x1F; }
static int hevc_nal_type(const uint8_t *nal) { return (nal[0] >> 1) & 0x3F; }

/* ====================================================================== */
/* HEVC SPS rewriter — disables vui_timing_info_present_flag             */
/* ====================================================================== */
/*
 * Why this exists:
 *   The Anyka encoder embeds VUI timing info in the HEVC SPS that says
 *   "this stream is 15 fps". When the actual ingress framerate is lower
 *   (the camera ramps down to ~8 fps in low light due to auto-exposure),
 *   strict decoders like VLC's avcodec use the SPS-declared rate to set
 *   their "frame is late" threshold. Every received frame appears late
 *   by ~60 ms (1/15s vs 1/8s), and after a few seconds VLC drops to a
 *   "computer too slow" state that never recovers. ffplay uses the same
 *   lib but is more lenient.
 *
 * The fix: rewrite the SPS so vui_timing_info_present_flag = 0. The
 * decoder then trusts the RTP timestamps exclusively. Other VUI fields
 * (aspect ratio, video signal type, chroma loc) are preserved.
 *
 * On any parse error or unsupported feature (scaling lists, long-term
 * ref pics) we fall back to leaving the SPS unchanged — better safe.
 */

/* --- Bit reader --- */
struct bit_reader {
    const uint8_t *data;
    size_t         len;
    size_t         pos;     /* bit index, 0..len*8-1 */
    int            eof;
};

static void br_init(struct bit_reader *r, const uint8_t *data, size_t len) {
    r->data = data; r->len = len; r->pos = 0; r->eof = 0;
}
static int br_get1(struct bit_reader *r) {
    size_t bp = r->pos++;
    size_t bi = bp >> 3;
    if (bi >= r->len) { r->eof = 1; return 0; }
    return (r->data[bi] >> (7 - (bp & 7))) & 1;
}
static uint32_t br_get(struct bit_reader *r, int n) {
    uint32_t v = 0;
    for (int i = 0; i < n; i++) v = (v << 1) | br_get1(r);
    return v;
}
static uint32_t br_ue(struct bit_reader *r) {
    int zeros = 0;
    while (!r->eof && br_get1(r) == 0 && zeros < 32) zeros++;
    if (zeros == 0) return 0;
    return ((1u << zeros) | br_get(r, zeros)) - 1;
}

/* --- Bit writer --- */
struct bit_writer {
    uint8_t *data;
    size_t   cap;
    size_t   pos;     /* bit index where next write goes */
    int      err;
};

static void bw_init(struct bit_writer *w, uint8_t *buf, size_t cap) {
    w->data = buf; w->cap = cap; w->pos = 0; w->err = 0;
    if (cap > 0) memset(buf, 0, cap);
}
static void bw_put1(struct bit_writer *w, int bit) {
    size_t bp = w->pos++;
    size_t bi = bp >> 3;
    if (bi >= w->cap) { w->err = 1; return; }
    if (bit) w->data[bi] |= (uint8_t)(1 << (7 - (bp & 7)));
}
static void bw_put(struct bit_writer *w, uint32_t v, int n) {
    for (int i = n - 1; i >= 0; i--) bw_put1(w, (v >> i) & 1);
}
static void bw_put_ue(struct bit_writer *w, uint32_t v) {
    /* Exp-Golomb encode: write (n-1) zeros followed by 1+the n-bit
     * representation of (v+1). */
    uint32_t x = v + 1;
    int n = 0; uint32_t y = x;
    while (y) { n++; y >>= 1; }
    for (int i = 0; i < n - 1; i++) bw_put1(w, 0);
    bw_put(w, x, n);
}
/* Copy n bits from reader to writer verbatim. */
static void bw_copy_bits(struct bit_writer *w, struct bit_reader *r, int n) {
    for (int i = 0; i < n; i++) bw_put1(w, br_get1(r));
}
/* RBSP trailing bits: a 1 bit followed by zero padding to byte boundary. */
static void bw_trailing(struct bit_writer *w) {
    bw_put1(w, 1);
    while (w->pos & 7) bw_put1(w, 0);
}

/* --- Emulation prevention strip / add --- */
static size_t strip_ep(const uint8_t *in, size_t in_len, uint8_t *out) {
    size_t oi = 0;
    for (size_t i = 0; i < in_len; i++) {
        if (i + 2 < in_len && in[i] == 0 && in[i+1] == 0 && in[i+2] == 0x03) {
            out[oi++] = 0; out[oi++] = 0;
            i += 2;
        } else {
            out[oi++] = in[i];
        }
    }
    return oi;
}
static size_t add_ep(const uint8_t *in, size_t in_len, uint8_t *out) {
    size_t oi = 0;
    for (size_t i = 0; i < in_len; i++) {
        if (oi >= 2 && out[oi-1] == 0 && out[oi-2] == 0 && in[i] <= 0x03) {
            out[oi++] = 0x03;
        }
        out[oi++] = in[i];
    }
    return oi;
}

/* --- HEVC profile_tier_level — walk forward to know its bit length. */
static int hevc_skip_ptl(struct bit_reader *r,
                          int profile_present_flag,
                          int max_sub_layers_minus1)
{
    if (profile_present_flag) {
        br_get(r, 2);  /* profile_space */
        br_get1(r);    /* tier_flag */
        br_get(r, 5);  /* profile_idc */
        br_get(r, 32); /* profile_compatibility_flag[32] */
        br_get1(r); br_get1(r); br_get1(r); br_get1(r);  /* 4 source flags */
        /* 43 bits of constraint flags + 1 reserved/inbld bit */
        br_get(r, 32); br_get(r, 11); br_get1(r);
    }
    br_get(r, 8);  /* level_idc */
    int sl_profile[8] = {0}, sl_level[8] = {0};
    for (int i = 0; i < max_sub_layers_minus1; i++) {
        sl_profile[i] = br_get1(r);
        sl_level[i]   = br_get1(r);
    }
    if (max_sub_layers_minus1 > 0) {
        for (int i = max_sub_layers_minus1; i < 8; i++) br_get(r, 2);
    }
    for (int i = 0; i < max_sub_layers_minus1; i++) {
        if (sl_profile[i]) {
            br_get(r, 2); br_get1(r); br_get(r, 5); br_get(r, 32);
            br_get1(r); br_get1(r); br_get1(r); br_get1(r);
            br_get(r, 32); br_get(r, 11); br_get1(r);
        }
        if (sl_level[i]) br_get(r, 8);
    }
    return r->eof ? -1 : 0;
}

/* --- HEVC short-term ref pic set — parse one to advance the reader.
 * Records NumDeltaPocs in `prior_total_pocs[idx]` for later inter-ref. */
static int hevc_skip_strps(struct bit_reader *r, int idx, int n_total,
                            uint8_t *prior_total_pocs)
{
    int inter_pred = 0;
    if (idx != 0) inter_pred = br_get1(r);
    if (inter_pred) {
        int delta_idx_m1 = 0;
        if (idx == n_total) delta_idx_m1 = br_ue(r);
        int ref_rps_idx = idx - (delta_idx_m1 + 1);
        if (ref_rps_idx < 0 || ref_rps_idx >= idx) return -1;
        br_get1(r);  /* delta_rps_sign */
        br_ue(r);    /* abs_delta_rps_minus1 */
        int n_pocs = prior_total_pocs[ref_rps_idx];
        for (int i = 0; i <= n_pocs; i++) {
            int used = br_get1(r);
            if (!used) br_get1(r);  /* use_delta_flag */
        }
        prior_total_pocs[idx] = (uint8_t)n_pocs;  /* approx */
    } else {
        int n_neg = br_ue(r);
        int n_pos = br_ue(r);
        for (int i = 0; i < n_neg; i++) { br_ue(r); br_get1(r); }
        for (int i = 0; i < n_pos; i++) { br_ue(r); br_get1(r); }
        if (n_neg + n_pos > 64) return -1;  /* sanity */
        prior_total_pocs[idx] = (uint8_t)(n_neg + n_pos);
    }
    return r->eof ? -1 : 0;
}

/* The main rewriter. Returns the new SPS NAL length on success and writes
 * it into `out`. On any error or unsupported feature, returns 0 and the
 * caller should fall back to the original SPS. */
static size_t fix_hevc_sps_remove_vui_timing(const uint8_t *in, size_t in_len,
                                              uint8_t *out, size_t out_cap)
{
    if (in_len < 4 || out_cap < 4) return 0;

    /* Step 1: strip emulation prevention from RBSP (skip 2-byte NAL hdr). */
    uint8_t rbsp[MAX_PARAM_SET_LEN];
    if (in_len > sizeof(rbsp)) return 0;
    size_t rbsp_len = strip_ep(in + 2, in_len - 2, rbsp);

    struct bit_reader r;
    br_init(&r, rbsp, rbsp_len);

    /* Step 2: parse + re-emit into a new RBSP. */
    uint8_t new_rbsp[MAX_PARAM_SET_LEN];
    struct bit_writer w;
    bw_init(&w, new_rbsp, sizeof(new_rbsp));

    /* sps_video_parameter_set_id u(4)
     * sps_max_sub_layers_minus1   u(3)
     * sps_temporal_id_nesting_flag u(1) */
    int sps_vps_id = br_get(&r, 4);            bw_put(&w, sps_vps_id, 4);
    int max_sub_layers_minus1 = br_get(&r, 3); bw_put(&w, max_sub_layers_minus1, 3);
    bw_put(&w, br_get1(&r), 1);

    /* profile_tier_level: walk to find length, then copy. */
    size_t ptl_start = r.pos;
    if (hevc_skip_ptl(&r, 1, max_sub_layers_minus1) < 0) return 0;
    size_t ptl_end = r.pos;
    {
        struct bit_reader r2;
        br_init(&r2, rbsp, rbsp_len);
        r2.pos = ptl_start;
        bw_copy_bits(&w, &r2, (int)(ptl_end - ptl_start));
    }

    /* sps_seq_parameter_set_id ue(v) */
    bw_put_ue(&w, br_ue(&r));
    /* chroma_format_idc ue(v) */
    int chroma_fmt = br_ue(&r); bw_put_ue(&w, chroma_fmt);
    if (chroma_fmt == 3) bw_put(&w, br_get1(&r), 1);
    /* pic_width / pic_height ue(v) */
    bw_put_ue(&w, br_ue(&r));
    bw_put_ue(&w, br_ue(&r));
    /* conformance_window_flag */
    int cwf = br_get1(&r); bw_put(&w, cwf, 1);
    if (cwf) for (int i = 0; i < 4; i++) bw_put_ue(&w, br_ue(&r));
    /* bit_depth_luma_minus8, bit_depth_chroma_minus8 */
    bw_put_ue(&w, br_ue(&r));
    bw_put_ue(&w, br_ue(&r));
    /* log2_max_pic_order_cnt_lsb_minus4 */
    bw_put_ue(&w, br_ue(&r));
    /* sps_sub_layer_ordering_info_present_flag */
    int slo = br_get1(&r); bw_put(&w, slo, 1);
    int loop_n = slo ? (max_sub_layers_minus1 + 1) : 1;
    for (int i = 0; i < loop_n; i++) {
        bw_put_ue(&w, br_ue(&r));
        bw_put_ue(&w, br_ue(&r));
        bw_put_ue(&w, br_ue(&r));
    }
    /* 4 ue(v) coding-block-size related */
    for (int i = 0; i < 4; i++) bw_put_ue(&w, br_ue(&r));
    /* max_transform_hierarchy_depth_inter, _intra */
    bw_put_ue(&w, br_ue(&r));
    bw_put_ue(&w, br_ue(&r));
    /* scaling_list_enabled_flag */
    int sle = br_get1(&r); bw_put(&w, sle, 1);
    if (sle) {
        int slr = br_get1(&r); bw_put(&w, slr, 1);
        if (slr) return 0;  /* scaling_list_data is too complex */
    }
    /* amp_enabled, sample_adaptive_offset, pcm_enabled */
    bw_put(&w, br_get1(&r), 1);
    bw_put(&w, br_get1(&r), 1);
    int pcm = br_get1(&r); bw_put(&w, pcm, 1);
    if (pcm) {
        bw_put(&w, br_get(&r, 4), 4);
        bw_put(&w, br_get(&r, 4), 4);
        bw_put_ue(&w, br_ue(&r));
        bw_put_ue(&w, br_ue(&r));
        bw_put(&w, br_get1(&r), 1);
    }
    /* num_short_term_ref_pic_sets and the structures */
    int nrps = br_ue(&r); bw_put_ue(&w, nrps);
    if (nrps > 64) return 0;
    size_t rps_start = r.pos;
    {
        uint8_t prior[64] = {0};
        for (int i = 0; i < nrps; i++) {
            if (hevc_skip_strps(&r, i, nrps, prior) < 0) return 0;
        }
    }
    size_t rps_end = r.pos;
    {
        struct bit_reader r2;
        br_init(&r2, rbsp, rbsp_len);
        r2.pos = rps_start;
        bw_copy_bits(&w, &r2, (int)(rps_end - rps_start));
    }
    /* long_term_ref_pics_present_flag */
    int ltrp = br_get1(&r); bw_put(&w, ltrp, 1);
    if (ltrp) return 0;  /* punt on long-term refs */
    /* sps_temporal_mvp_enabled_flag, strong_intra_smoothing_enabled_flag */
    bw_put(&w, br_get1(&r), 1);
    bw_put(&w, br_get1(&r), 1);

    /* vui_parameters_present_flag — THE IMPORTANT FIELD */
    int vui_present = br_get1(&r);
    if (!vui_present) return 0;  /* nothing to fix */
    bw_put(&w, 1, 1);

    /* --- vui_parameters() --- */
    int aspect_present = br_get1(&r); bw_put(&w, aspect_present, 1);
    if (aspect_present) {
        int ar_idc = br_get(&r, 8); bw_put(&w, ar_idc, 8);
        if (ar_idc == 255) {
            bw_put(&w, br_get(&r, 16), 16);
            bw_put(&w, br_get(&r, 16), 16);
        }
    }
    int overscan_present = br_get1(&r); bw_put(&w, overscan_present, 1);
    if (overscan_present) bw_put(&w, br_get1(&r), 1);
    int vsig_present = br_get1(&r); bw_put(&w, vsig_present, 1);
    if (vsig_present) {
        bw_put(&w, br_get(&r, 3), 3);
        bw_put(&w, br_get1(&r), 1);
        int cdesc_present = br_get1(&r); bw_put(&w, cdesc_present, 1);
        if (cdesc_present) {
            bw_put(&w, br_get(&r, 8), 8);
            bw_put(&w, br_get(&r, 8), 8);
            bw_put(&w, br_get(&r, 8), 8);
        }
    }
    int chloc_present = br_get1(&r); bw_put(&w, chloc_present, 1);
    if (chloc_present) {
        bw_put_ue(&w, br_ue(&r));
        bw_put_ue(&w, br_ue(&r));
    }
    bw_put(&w, br_get1(&r), 1);  /* neutral_chroma_indication_flag */
    bw_put(&w, br_get1(&r), 1);  /* field_seq_flag */
    bw_put(&w, br_get1(&r), 1);  /* frame_field_info_present_flag */
    int default_disp = br_get1(&r); bw_put(&w, default_disp, 1);
    if (default_disp) {
        for (int i = 0; i < 4; i++) bw_put_ue(&w, br_ue(&r));
    }

    /* === THE ACTUAL FIX ===
     * Read the original vui_timing_info_present_flag and its payload
     * to advance the reader, but write 0 to the output. We then end
     * the VUI block with bitstream_restriction_flag=0 and stop. */
    int orig_timing = br_get1(&r);
    if (orig_timing) {
        br_get(&r, 32);  /* num_units_in_tick */
        br_get(&r, 32);  /* time_scale */
        int poc_prop = br_get1(&r);
        if (poc_prop) br_ue(&r);
        /* hrd_parameters_present_flag — we don't bother decoding the
         * rest of VUI in the input; the output is complete. */
    }
    bw_put(&w, 0, 1);  /* vui_timing_info_present_flag = 0 */
    bw_put(&w, 0, 1);  /* bitstream_restriction_flag    = 0 */

    /* sps_extension_present_flag = 0 */
    bw_put(&w, 0, 1);

    /* RBSP trailing bits */
    bw_trailing(&w);

    if (w.err) return 0;
    size_t new_rbsp_len = w.pos / 8;

    /* Step 3: re-add emulation prevention + NAL header. */
    if (out_cap < 2 + new_rbsp_len * 2) return 0;
    out[0] = in[0];
    out[1] = in[1];
    size_t total = 2 + add_ep(new_rbsp, new_rbsp_len, out + 2);
    return total;
}


/* ====================================================================== */
/* Ring buffer                                                            */
/* ====================================================================== */

/* One Access Unit in the ring. We store all NALs of the AU as a
 * single flat buffer of length-prefixed NALs to keep the storage
 * layout simple (avoids per-NAL malloc on the hot path).
 *
 * Storage layout for `data`:
 *   [u32 LE len0] [nal0 bytes] [u32 LE len1] [nal1 bytes] ...
 *
 * (length is u32 little-endian for simplicity; total_data_bytes is
 *  the sum of all entries). The streamer thread will iterate this
 *  in turn 3 to packetize frames.
 */
struct au_entry {
    uint64_t ts_ms;
    uint64_t gseq;          /* monotonic sequence id, never wraps */
    int      kind;          /* RTSP_AU_IDR | RTSP_AU_NORMAL */
    uint8_t *data;          /* heap-allocated; freed when slot reused */
    size_t   data_len;      /* total bytes in `data` */
    int      nal_count;     /* number of NALs encoded in `data` */
};

struct ring {
    pthread_mutex_t mtx;
    pthread_cond_t  cond;       /* signaled when new AU pushed */
    struct au_entry slots[RING_DEPTH];
    int      head;              /* write index */
    int      count;             /* number of valid entries */
    uint64_t next_gseq;         /* next gseq to assign */

    /* Most recent parameter sets, copied verbatim from incoming AUs.
     * Used to build the SDP and to prepend at every IDR for the client
     * (helps recovery from packet loss / mid-stream join). */
    enum rtsp_codec codec;
    uint8_t  vps[MAX_PARAM_SET_LEN]; size_t vps_len;
    uint8_t  sps[MAX_PARAM_SET_LEN]; size_t sps_len;
    uint8_t  pps[MAX_PARAM_SET_LEN]; size_t pps_len;
    /* For HEVC we keep both the raw and the (eventually) VUI-fixed
     * SPS. In turn 4 the fixed copy gets populated by the rewriter
     * function; until then, sps_fixed mirrors sps. */
    uint8_t  sps_fixed[MAX_PARAM_SET_LEN]; size_t sps_fixed_len;
};

static struct ring g_rings[RTSP_MAX_STREAMS];

static void ring_init(struct ring *r, enum rtsp_codec codec)
{
    /* First-time init vs subsequent re-init: the static rings are
     * reused across capture restarts. We can't memset+pthread_init
     * blindly because that would overwrite an already-initialised
     * mutex. We track first-init with a sentinel bit in the codec
     * field (codec==RTSP_CODEC_NONE could mean either "uninit" or
     * "this stream is disabled" — so we use a separate flag). */
    static int initialized[RTSP_MAX_STREAMS] = {0};
    int idx = (int)(r - g_rings);
    if (idx >= 0 && idx < RTSP_MAX_STREAMS && initialized[idx]) {
        /* Re-init: zero only the data fields, leave mutex/cond alone. */
        pthread_mutex_lock(&r->mtx);
        for (int i = 0; i < RING_DEPTH; i++) {
            free(r->slots[i].data);
            r->slots[i].data = NULL;
            r->slots[i].data_len = 0;
        }
        r->head = 0;
        r->count = 0;
        r->next_gseq = 0;
        r->codec = codec;
        r->vps_len = r->sps_len = r->pps_len = r->sps_fixed_len = 0;
        pthread_mutex_unlock(&r->mtx);
        return;
    }
    /* First time: full memset + pthread_*_init. */
    memset(r, 0, sizeof(*r));
    pthread_mutex_init(&r->mtx, NULL);
    pthread_cond_init(&r->cond, NULL);
    r->codec = codec;
    if (idx >= 0 && idx < RTSP_MAX_STREAMS) initialized[idx] = 1;
}

static void ring_destroy(struct ring *r)
{
    /* NB: we deliberately do NOT pthread_mutex_destroy() / cond_destroy()
     * here. The rings are static globals reused across capture restarts
     * (see rtsp_server_init/shutdown). On uClibc, destroying a mutex and
     * then re-initing it with pthread_mutex_init can produce subtle
     * misbehaviour if any thread still holds a reference to the old
     * handle (e.g. a streamer_thread in flight). Just freeing the slot
     * payload is safe and idempotent — ring_init() resets the rest of
     * the struct via memset on the next round. */
    pthread_mutex_lock(&r->mtx);
    for (int i = 0; i < RING_DEPTH; i++) {
        free(r->slots[i].data);
        r->slots[i].data = NULL;
        r->slots[i].data_len = 0;
    }
    r->head = 0;
    r->count = 0;
    r->next_gseq = 0;
    pthread_mutex_unlock(&r->mtx);
}

/* Build the flat length-prefixed buffer from an array of NAL pointers.
 * Returns malloc'd buffer + length (caller takes ownership) or NULL. */
static uint8_t *pack_nals(const uint8_t * const *nals, const size_t *nal_lens,
                           int nal_count, size_t *out_total)
{
    /* Compute total size first. */
    size_t total = 0;
    for (int i = 0; i < nal_count; i++) {
        if (nal_lens[i] > MAX_NAL_BYTES) return NULL;  /* sanity */
        total += 4 + nal_lens[i];
    }
    if (total == 0) return NULL;
    uint8_t *buf = malloc(total);
    if (!buf) return NULL;
    size_t off = 0;
    for (int i = 0; i < nal_count; i++) {
        uint32_t L = (uint32_t)nal_lens[i];
        buf[off+0] = (uint8_t)(L      );
        buf[off+1] = (uint8_t)(L >>  8);
        buf[off+2] = (uint8_t)(L >> 16);
        buf[off+3] = (uint8_t)(L >> 24);
        off += 4;
        memcpy(buf + off, nals[i], nal_lens[i]);
        off += nal_lens[i];
    }
    *out_total = total;
    return buf;
}

/* Extract VPS/SPS/PPS from an AU and store in the ring's parameter-set
 * slots. Done while we're already iterating the NALs anyway. */
static void update_param_sets(struct ring *r,
                               const uint8_t * const *nals,
                               const size_t *nal_lens,
                               int nal_count)
{
    for (int i = 0; i < nal_count; i++) {
        if (nal_lens[i] < 2 || nal_lens[i] > MAX_PARAM_SET_LEN) continue;
        if (r->codec == RTSP_CODEC_H264) {
            int t = h264_nal_type(nals[i]);
            if (t == H264_NAL_SPS) {
                memcpy(r->sps, nals[i], nal_lens[i]); r->sps_len = nal_lens[i];
                /* For H.264 there's no VUI-rewriter step; the "fixed"
                 * copy is just the same. */
                memcpy(r->sps_fixed, nals[i], nal_lens[i]);
                r->sps_fixed_len = nal_lens[i];
            } else if (t == H264_NAL_PPS) {
                memcpy(r->pps, nals[i], nal_lens[i]); r->pps_len = nal_lens[i];
            }
        } else if (r->codec == RTSP_CODEC_H265) {
            int t = hevc_nal_type(nals[i]);
            if (t == HEVC_NAL_VPS) {
                memcpy(r->vps, nals[i], nal_lens[i]); r->vps_len = nal_lens[i];
            } else if (t == HEVC_NAL_SPS) {
                /* Only run the rewriter when the SPS actually changes
                 * (it normally arrives every IDR but is byte-identical).
                 * This avoids wasted CPU and noisy logs. */
                int sps_changed =
                    (r->sps_len != nal_lens[i] ||
                     memcmp(r->sps, nals[i], nal_lens[i]) != 0);
                memcpy(r->sps, nals[i], nal_lens[i]); r->sps_len = nal_lens[i];
                if (sps_changed) {
                    uint8_t fixed[MAX_PARAM_SET_LEN];
                    size_t fl = fix_hevc_sps_remove_vui_timing(
                        nals[i], nal_lens[i], fixed, sizeof(fixed));
                    if (fl > 0) {
                        memcpy(r->sps_fixed, fixed, fl);
                        r->sps_fixed_len = fl;
                        fprintf(stderr,
                            "[rtsp] HEVC SPS rewritten: VUI timing "
                            "disabled; in=%zuB out=%zuB\n",
                            nal_lens[i], fl);
                    } else {
                        /* Rewriter failed (or no VUI to fix) — fall back. */
                        memcpy(r->sps_fixed, nals[i], nal_lens[i]);
                        r->sps_fixed_len = nal_lens[i];
                        fprintf(stderr,
                            "[rtsp] HEVC SPS rewriter: passthrough "
                            "(no fix needed or unsupported feature)\n");
                    }
                }
            } else if (t == HEVC_NAL_PPS) {
                memcpy(r->pps, nals[i], nal_lens[i]); r->pps_len = nal_lens[i];
            }
        }
    }
}

/* Filter parameter-set NALs out of the AU before ring storage —
 * we'll re-emit them ourselves at IDR boundaries. */
static int is_param_set_nal(enum rtsp_codec codec, const uint8_t *nal,
                             size_t nal_len)
{
    if (nal_len < 1) return 0;
    if (codec == RTSP_CODEC_H264) {
        int t = h264_nal_type(nal);
        return (t == H264_NAL_SPS || t == H264_NAL_PPS);
    } else if (codec == RTSP_CODEC_H265) {
        int t = hevc_nal_type(nal);
        return (t == HEVC_NAL_VPS || t == HEVC_NAL_SPS || t == HEVC_NAL_PPS);
    }
    return 0;
}

/* ====================================================================== */
/* Public push API                                                        */
/* ====================================================================== */

int rtsp_server_push_au(int stream_idx,
                        uint64_t ts_ms,
                        const uint8_t * const *nals,
                        const size_t *nal_lens,
                        int nal_count,
                        enum rtsp_au_kind kind)
{
    if (stream_idx < 0 || stream_idx >= RTSP_MAX_STREAMS) return -1;
    if (nal_count <= 0 || !nals || !nal_lens) return -1;

    struct ring *r = &g_rings[stream_idx];
    if (r->codec == RTSP_CODEC_NONE) return -1;  /* not registered */

    /* Update parameter-set cache (this also peeks at the NALs but
     * doesn't mutate them). */
    pthread_mutex_lock(&r->mtx);
    update_param_sets(r, nals, nal_lens, nal_count);
    pthread_mutex_unlock(&r->mtx);

    /* Build a filtered NAL list excluding parameter sets. Most AUs
     * have all 4-5 NALs being VCL; param sets only appear at IDR. */
    const uint8_t *body_nals[16];
    size_t         body_lens[16];
    int            body_count = 0;
    for (int i = 0; i < nal_count && body_count < 16; i++) {
        if (is_param_set_nal(r->codec, nals[i], nal_lens[i])) continue;
        body_nals[body_count] = nals[i];
        body_lens[body_count] = nal_lens[i];
        body_count++;
    }
    if (body_count == 0) {
        /* AU contained only parameter sets (rare but possible at
         * stream start). Nothing to enqueue, but param-set update
         * already done. */
        return 0;
    }

    size_t total = 0;
    uint8_t *buf = pack_nals(body_nals, body_lens, body_count, &total);
    if (!buf) {
        fprintf(stderr, "[rtsp] pack_nals failed for stream %d\n", stream_idx);
        return -1;
    }

    pthread_mutex_lock(&r->mtx);
    /* If full, drop the oldest entry to make room. For live streaming
     * this is the right policy — newest data wins. */
    if (r->count == RING_DEPTH) {
        int oldest = (r->head - r->count + RING_DEPTH) % RING_DEPTH;
        free(r->slots[oldest].data);
        r->slots[oldest].data = NULL;
        r->count--;
    }
    int wi = r->head;
    r->slots[wi].ts_ms     = ts_ms;
    r->slots[wi].gseq      = ++r->next_gseq;
    r->slots[wi].kind      = kind;
    r->slots[wi].data      = buf;
    r->slots[wi].data_len  = total;
    r->slots[wi].nal_count = body_count;
    r->head = (r->head + 1) % RING_DEPTH;
    r->count++;
    pthread_cond_broadcast(&r->cond);
    pthread_mutex_unlock(&r->mtx);
    return 0;
}

/* ====================================================================== */
/* RTSP request parsing                                                   */
/* ====================================================================== */

/* Forward decl — defined together with the listen socket below. */
static volatile int g_shutdown;

/*
 * RTSP messages are textual, looking very much like HTTP/1.1:
 *
 *     METHOD url RTSP/1.0\r\n
 *     Header-Name: value\r\n
 *     Header-Name: value\r\n
 *     \r\n
 *     [optional body — only used by SET_PARAMETER which we don't support]
 *
 * Header names are case-insensitive (RFC 7826 §5.2). We store them
 * lowercased to make lookup easy.
 */

#define RTSP_MAX_HEADERS    16
#define RTSP_MAX_HEADER_LEN 256
#define RTSP_REQ_BUF_LEN    8192

struct rtsp_request {
    char method[16];                     /* e.g. "DESCRIBE", uppercased */
    char url[512];                       /* full URL or path           */
    char path[64];                       /* extracted path: "/main"    */
    int  n_hdrs;
    char hdr_name [RTSP_MAX_HEADERS][32];   /* lowercased */
    char hdr_value[RTSP_MAX_HEADERS][RTSP_MAX_HEADER_LEN];
};

/* Lowercase in-place (ASCII). */
static void str_lower(char *s) {
    for (; *s; s++)
        if (*s >= 'A' && *s <= 'Z') *s += 32;
}

/* Strip leading + trailing whitespace in-place. Returns pointer to
 * the (possibly shifted) start. */
static char *str_strip(char *s) {
    while (*s == ' ' || *s == '\t') s++;
    char *e = s + strlen(s);
    while (e > s && (e[-1] == ' ' || e[-1] == '\t' ||
                     e[-1] == '\r' || e[-1] == '\n')) {
        e--;
    }
    *e = 0;
    return s;
}

static const char *rtsp_get_header(const struct rtsp_request *r,
                                    const char *name)
{
    /* `name` should be lowercase. */
    for (int i = 0; i < r->n_hdrs; i++) {
        if (strcmp(r->hdr_name[i], name) == 0)
            return r->hdr_value[i];
    }
    return NULL;
}

/* Extract just the path part of the URL ("/main" from
 * "rtsp://host:port/main/main"). Strips any trailing /control suffix.
 * For SETUP requests the URL is typically rtsp://host/main/main —
 * we want the leading "/main". */
static void extract_path(const char *url, char *out_path, size_t out_len)
{
    out_path[0] = 0;
    /* Skip rtsp://host:port — find first '/' after "rtsp://". */
    const char *p = url;
    if (strncmp(p, "rtsp://", 7) == 0) {
        p += 7;
        const char *slash = strchr(p, '/');
        p = slash ? slash : "";
    }
    if (*p != '/') {
        snprintf(out_path, out_len, "/%s", p);
    } else {
        snprintf(out_path, out_len, "%s", p);
    }
    /* Reduce "/main/something" to "/main" — match against our known
     * stream prefixes. This treats both "rtsp://h/main" (DESCRIBE)
     * and "rtsp://h/main/main" (SETUP — second "main" is the
     * stream control attribute) as the same /main. */
    if (strncmp(out_path, "/main", 5) == 0) {
        out_path[5] = 0;
    } else if (strncmp(out_path, "/sub", 4) == 0) {
        out_path[4] = 0;
    }
    /* Strip trailing slashes. */
    size_t L = strlen(out_path);
    while (L > 1 && out_path[L-1] == '/') {
        out_path[--L] = 0;
    }
}

/* Parse one RTSP request from `buf` of `len` bytes. Returns:
 *   > 0  success, returns number of bytes consumed (incl. trailing \r\n)
 *   == 0 incomplete — need more bytes
 *   < 0  malformed
 */
static int rtsp_parse(const char *buf, size_t len, struct rtsp_request *out)
{
    /* Find the end of headers — \r\n\r\n. We don't support pipelined
     * bodies (no SET_PARAMETER with content). */
    const char *eoh = NULL;
    for (size_t i = 0; i + 3 < len; i++) {
        if (buf[i]   == '\r' && buf[i+1] == '\n' &&
            buf[i+2] == '\r' && buf[i+3] == '\n') {
            eoh = buf + i;
            break;
        }
    }
    if (!eoh) return 0;
    size_t total = (eoh - buf) + 4;

    /* Make a mutable copy so we can tokenize in place. */
    char tmp[RTSP_REQ_BUF_LEN];
    if (total + 1 > sizeof(tmp)) return -1;
    memcpy(tmp, buf, total);
    tmp[total] = 0;

    memset(out, 0, sizeof(*out));

    /* --- Request line: "METHOD URL RTSP/1.0\r\n" --- */
    char *line_end = strstr(tmp, "\r\n");
    if (!line_end) return -1;
    *line_end = 0;
    char *line = tmp;
    char *sp1 = strchr(line, ' ');
    if (!sp1) return -1;
    *sp1 = 0;
    char *sp2 = strchr(sp1 + 1, ' ');
    if (!sp2) return -1;
    *sp2 = 0;
    snprintf(out->method, sizeof(out->method), "%s", line);
    /* Method to uppercase (RTSP methods are uppercase-only really). */
    for (char *m = out->method; *m; m++)
        if (*m >= 'a' && *m <= 'z') *m -= 32;
    snprintf(out->url, sizeof(out->url), "%s", sp1 + 1);
    extract_path(out->url, out->path, sizeof(out->path));
    /* sp2+1 .. line_end is "RTSP/1.0" — we don't bother validating. */

    /* --- Headers loop --- */
    char *cur = line_end + 2;
    while (*cur && (cur < tmp + total - 4)) {
        char *next = strstr(cur, "\r\n");
        if (!next) break;
        if (next == cur) { /* empty line — end of headers */
            break;
        }
        *next = 0;
        char *colon = strchr(cur, ':');
        if (colon) {
            *colon = 0;
            char *name  = str_strip(cur);
            char *value = str_strip(colon + 1);
            if (out->n_hdrs < RTSP_MAX_HEADERS) {
                snprintf(out->hdr_name[out->n_hdrs],
                         sizeof(out->hdr_name[0]), "%s", name);
                str_lower(out->hdr_name[out->n_hdrs]);
                snprintf(out->hdr_value[out->n_hdrs],
                         sizeof(out->hdr_value[0]), "%s", value);
                out->n_hdrs++;
            }
        }
        cur = next + 2;
    }

    return (int)total;
}

/* ====================================================================== */
/* Base64 (used for SDP sprop-* parameters)                               */
/* ====================================================================== */

static const char b64_chars[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/* Encode `len` bytes from `data` into `out`. Caller must ensure
 * out has at least 4*((len+2)/3) + 1 bytes. */
static void b64_encode(const uint8_t *data, size_t len, char *out)
{
    size_t i, j = 0;
    for (i = 0; i + 2 < len; i += 3) {
        uint32_t v = (data[i] << 16) | (data[i+1] << 8) | data[i+2];
        out[j++] = b64_chars[(v >> 18) & 0x3f];
        out[j++] = b64_chars[(v >> 12) & 0x3f];
        out[j++] = b64_chars[(v >>  6) & 0x3f];
        out[j++] = b64_chars[(v      ) & 0x3f];
    }
    if (i < len) {
        uint32_t v = data[i] << 16;
        if (i + 1 < len) v |= data[i+1] << 8;
        out[j++] = b64_chars[(v >> 18) & 0x3f];
        out[j++] = b64_chars[(v >> 12) & 0x3f];
        out[j++] = (i + 1 < len) ? b64_chars[(v >> 6) & 0x3f] : '=';
        out[j++] = '=';
    }
    out[j] = 0;
}

/* ====================================================================== */
/* SDP generator                                                          */
/* ====================================================================== */

/* Build an SDP describing the requested stream. Returns # bytes written
 * to `out`, or -1 on overflow / no stream. */
static int build_sdp(int stream_idx, const char *server_ip,
                      char *out, size_t out_len)
{
    if (stream_idx < 0 || stream_idx >= RTSP_MAX_STREAMS) return -1;
    struct ring *r = &g_rings[stream_idx];

    pthread_mutex_lock(&r->mtx);
    if (r->codec == RTSP_CODEC_NONE ||
        r->sps_fixed_len == 0 || r->pps_len == 0 ||
        (r->codec == RTSP_CODEC_H265 && r->vps_len == 0)) {
        pthread_mutex_unlock(&r->mtx);
        /* Parameter sets not yet captured — caller should retry or
         * return 503 to the client. */
        return -1;
    }

    /* Encode parameter sets in base64. */
    char sps_b64[MAX_PARAM_SET_LEN * 2];
    char pps_b64[MAX_PARAM_SET_LEN * 2];
    char vps_b64[MAX_PARAM_SET_LEN * 2];
    b64_encode(r->sps_fixed, r->sps_fixed_len, sps_b64);
    b64_encode(r->pps,       r->pps_len,       pps_b64);
    if (r->codec == RTSP_CODEC_H265)
        b64_encode(r->vps, r->vps_len, vps_b64);
    else
        vps_b64[0] = 0;

    /* For H.264, profile-level-id is taken from SPS bytes 1-3. */
    char h264_plid[8] = "";
    if (r->codec == RTSP_CODEC_H264 && r->sps_fixed_len >= 4) {
        snprintf(h264_plid, sizeof(h264_plid), "%02X%02X%02X",
                 r->sps_fixed[1], r->sps_fixed[2], r->sps_fixed[3]);
    }

    enum rtsp_codec codec = r->codec;
    pthread_mutex_unlock(&r->mtx);

    /* The control attribute used to be the path component
     * (`a=control:main` or `a=control:sub`). With multi-track
     * (audio + video) we use trackID-based control URLs so each
     * track has a unique control selector that the client appends
     * to the base URL: e.g. SETUP rtsp://cam:8554/main/trackID=0.
     *
     * The audio track is included only if audio_in is up — if the
     * mic capture failed at startup, we serve a video-only SDP
     * exactly as before, so older clients that never asked for
     * audio see no behavior change. */
    int audio_avail = audio_in_is_available();
    int n;
    if (codec == RTSP_CODEC_H264) {
        n = snprintf(out, out_len,
            "v=0\r\n"
            "o=- 0 0 IN IP4 %s\r\n"
            "s=anyka_camera\r\n"
            "c=IN IP4 0.0.0.0\r\n"
            "t=0 0\r\n"
            "a=tool:proxy_capture\r\n"
            "m=video 0 RTP/AVP 96\r\n"
            "a=rtpmap:96 H264/90000\r\n"
            "a=fmtp:96 packetization-mode=1;profile-level-id=%s;"
                "sprop-parameter-sets=%s,%s\r\n"
            "a=control:trackID=0\r\n",
            server_ip, h264_plid, sps_b64, pps_b64);
    } else {
        n = snprintf(out, out_len,
            "v=0\r\n"
            "o=- 0 0 IN IP4 %s\r\n"
            "s=anyka_camera\r\n"
            "c=IN IP4 0.0.0.0\r\n"
            "t=0 0\r\n"
            "a=tool:proxy_capture\r\n"
            "m=video 0 RTP/AVP 96\r\n"
            "a=rtpmap:96 H265/90000\r\n"
            "a=fmtp:96 sprop-vps=%s;sprop-sps=%s;sprop-pps=%s\r\n"
            "a=control:trackID=0\r\n",
            server_ip, vps_b64, sps_b64, pps_b64);
    }
    if (n < 0 || (size_t)n >= out_len) return -1;

    /* Append audio m-line if mic capture is available. PT=0 is
     * the static RTP payload type for G.711 µ-law (PCMU), 8 kHz
     * mono. No fmtp needed for static PT. */
    if (audio_avail) {
        int n2 = snprintf(out + n, out_len - n,
            "m=audio 0 RTP/AVP 0\r\n"
            "a=rtpmap:0 PCMU/8000/1\r\n"
            "a=control:trackID=1\r\n");
        if (n2 < 0 || (size_t)n2 >= out_len - n) return -1;
        n += n2;
    }
    return n;
}

/* ====================================================================== */
/* Per-client state and helpers                                           */
/* ====================================================================== */

enum client_state {
    CS_INIT = 0,    /* connected, no SETUP yet            */
    CS_READY,       /* SETUP received, waiting for PLAY   */
    CS_PLAYING,     /* PLAY in progress                   */
};

/* Transport types negotiated in SETUP. */
enum xport_type {
    XPORT_NONE = 0,
    XPORT_TCP,      /* RTP over TCP, interleaved on the RTSP socket */
    XPORT_UDP,      /* RTP over UDP, separate sockets               */
};

struct client_ctx {
    int               conn_fd;          /* RTSP TCP socket */
    char              peer_str[64];

    enum client_state state;
    char              session_id[16];   /* generated at SETUP */
    int               stream_idx;       /* 0 = /main, 1 = /sub */

    /* Track 0 = video (existing path; field names unchanged for
     * minimal diff). Track 1 = audio (new — see audio_* below). */

    /* === VIDEO TRACK === */
    enum xport_type   xport;
    int               iv_rtp_chan;      /* e.g. 0 — interleaved RTP */
    int               iv_rtcp_chan;     /* e.g. 1 — interleaved RTCP */
    int               udp_rtp_fd;
    int               udp_rtcp_fd;
    struct sockaddr_in udp_rtp_addr;
    struct sockaddr_in udp_rtcp_addr;
    uint32_t          rtp_ts_base;
    uint16_t          initial_seq;
    uint32_t          ssrc;

    /* === AUDIO TRACK === (parallel set; only used if client
     * SETUPs trackID=1. If audio_setup_done==0, the streamer
     * skips audio entirely.) */
    int                  audio_setup_done;
    enum xport_type      audio_xport;
    int                  audio_iv_rtp_chan;     /* e.g. 2 */
    int                  audio_iv_rtcp_chan;    /* e.g. 3 */
    int                  audio_udp_rtp_fd;
    int                  audio_udp_rtcp_fd;
    struct sockaddr_in   audio_udp_rtp_addr;
    struct sockaddr_in   audio_udp_rtcp_addr;
    uint32_t             audio_rtp_ts_base;     /* 8 kHz clock */
    uint16_t             audio_initial_seq;
    uint32_t             audio_ssrc;
    /* Audio runtime: incremented on every RTP packet sent. */
    uint16_t             audio_seq;
    uint32_t             audio_ts;              /* current RTP TS */

    /* Serializes writes on conn_fd. The streamer thread (RTP send,
     * interleaved-TCP only) and the main serve_client loop (RTSP
     * keepalive responses) can both write to the socket. */
    pthread_mutex_t   write_mtx;

    /* RTSP read buffer (accumulates partial requests). */
    char   rxbuf[RTSP_REQ_BUF_LEN];
    size_t rxlen;

    /* Track if we've spawned a streamer thread for PLAY. */
    pthread_t streamer_tid;
    int       streamer_started;
    pthread_t audio_streamer_tid;
    int       audio_streamer_started;
};

/* Serialize a response and send. The buffer is sized to fit a generous
 * SDP (the biggest response we generate). */
static int send_response(struct client_ctx *c,
                          const char *status,        /* e.g. "200 OK" */
                          const char *cseq,
                          const char *extra_hdrs,    /* may be NULL    */
                          const char *body,          /* may be NULL    */
                          const char *content_type)  /* may be NULL    */
{
    char hdr[1024];
    int  blen = body ? (int)strlen(body) : 0;
    int  n;
    if (body && content_type) {
        n = snprintf(hdr, sizeof(hdr),
            "RTSP/1.0 %s\r\n"
            "CSeq: %s\r\n"
            "Server: anyka_proxy/0.1\r\n"
            "%s"
            "Content-Type: %s\r\n"
            "Content-Length: %d\r\n"
            "\r\n",
            status, cseq, extra_hdrs ? extra_hdrs : "",
            content_type, blen);
    } else {
        n = snprintf(hdr, sizeof(hdr),
            "RTSP/1.0 %s\r\n"
            "CSeq: %s\r\n"
            "Server: anyka_proxy/0.1\r\n"
            "%s"
            "\r\n",
            status, cseq, extra_hdrs ? extra_hdrs : "");
    }
    if (n < 0 || (size_t)n >= sizeof(hdr)) return -1;
    if (send(c->conn_fd, hdr, n, MSG_NOSIGNAL) != n) return -1;
    if (body && blen > 0) {
        if (send(c->conn_fd, body, blen, MSG_NOSIGNAL) != blen) return -1;
    }
    return 0;
}

/* Map URL path to stream index. Returns -1 if no match. */
static int path_to_stream_idx(const char *path)
{
    if (strcmp(path, "/main") == 0) return 0;
    if (strcmp(path, "/sub")  == 0) return 1;
    return -1;
}

/* Generate a session ID by reading some entropy from /dev/urandom or
 * just using time + pid as fallback. We only need it unique per
 * client session, not cryptographically random. */
static void gen_session_id(char *buf, size_t len)
{
    uint32_t v = (uint32_t)(time(NULL)) ^ (uint32_t)(uintptr_t)buf;
    snprintf(buf, len, "%08x", v);
}

/* ====================================================================== */
/* RTSP method handlers                                                   */
/* ====================================================================== */

static void handle_options(struct client_ctx *c, const struct rtsp_request *req,
                            const char *cseq)
{
    (void)req;
    send_response(c, "200 OK", cseq,
        "Public: OPTIONS, DESCRIBE, SETUP, PLAY, PAUSE, TEARDOWN, "
        "GET_PARAMETER\r\n",
        NULL, NULL);
}

static void handle_describe(struct client_ctx *c, const struct rtsp_request *req,
                              const char *cseq)
{
    int idx = path_to_stream_idx(req->path);
    if (idx < 0) {
        send_response(c, "404 Not Found", cseq, NULL, NULL, NULL);
        return;
    }
    /* If the stream slot exists but the codec is NONE, this stream
     * was disabled in the running config (enable_main=0 / enable_sub=0).
     * It's *permanently* not available, not temporarily — so 404,
     * not 503. Returning 503 with Retry-After made VLC poll forever
     * on the dead URL, blocking the single-client slot for other
     * sessions. */
    pthread_mutex_lock(&g_rings[idx].mtx);
    int disabled = (g_rings[idx].codec == RTSP_CODEC_NONE);
    pthread_mutex_unlock(&g_rings[idx].mtx);
    if (disabled) {
        send_response(c, "404 Not Found", cseq,
                      NULL,
                      "Stream disabled in capture config\n",
                      "text/plain");
        return;
    }

    /* Use the local IP we're bound to for the SDP origin field.
     * We figure it out from the connected socket. Falls back to
     * "0.0.0.0" if anything goes wrong. */
    char host_ip[INET_ADDRSTRLEN] = "0.0.0.0";
    struct sockaddr_in sa;
    socklen_t sl = sizeof(sa);
    if (getsockname(c->conn_fd, (struct sockaddr *)&sa, &sl) == 0) {
        inet_ntop(AF_INET, &sa.sin_addr, host_ip, sizeof(host_ip));
    }

    char sdp[2048];
    int  n = build_sdp(idx, host_ip, sdp, sizeof(sdp));
    if (n < 0) {
        /* Parameter sets not yet available — ask client to retry. */
        send_response(c, "503 Service Unavailable", cseq,
                      "Retry-After: 1\r\n", NULL, NULL);
        return;
    }

    char extra[256];
    snprintf(extra, sizeof(extra),
             "Content-Base: %s/\r\n", req->url);

    send_response(c, "200 OK", cseq, extra, sdp, "application/sdp");
}

/* Parse the Transport: header. Examples we accept:
 *    RTP/AVP/TCP;unicast;interleaved=0-1
 *    RTP/AVP;unicast;client_port=51000-51001
 *
 * Sets c->xport, c->iv_rtp_chan/iv_rtcp_chan or c->udp_rtp_addr port. */
static int parse_transport(struct client_ctx *c, const char *transport)
{
    if (!transport) return -1;

    if (strstr(transport, "RTP/AVP/TCP") != NULL) {
        c->xport = XPORT_TCP;
        c->iv_rtp_chan  = 0;
        c->iv_rtcp_chan = 1;
        const char *iv = strstr(transport, "interleaved=");
        if (iv) {
            int a, b;
            if (sscanf(iv + 12, "%d-%d", &a, &b) == 2) {
                c->iv_rtp_chan  = a;
                c->iv_rtcp_chan = b;
            } else if (sscanf(iv + 12, "%d", &a) == 1) {
                c->iv_rtp_chan  = a;
                c->iv_rtcp_chan = a + 1;
            }
        }
        return 0;
    } else if (strstr(transport, "RTP/AVP") != NULL) {
        c->xport = XPORT_UDP;
        const char *cp = strstr(transport, "client_port=");
        if (!cp) return -1;
        int a, b;
        if (sscanf(cp + 12, "%d-%d", &a, &b) != 2) {
            if (sscanf(cp + 12, "%d", &a) == 1) {
                b = a + 1;
            } else {
                return -1;
            }
        }
        /* Address comes from the connected RTSP peer; only the port
         * part is in the Transport header. */
        struct sockaddr_in peer;
        socklen_t pl = sizeof(peer);
        if (getpeername(c->conn_fd, (struct sockaddr *)&peer, &pl) != 0)
            return -1;
        c->udp_rtp_addr  = peer; c->udp_rtp_addr.sin_port  = htons((uint16_t)a);
        c->udp_rtcp_addr = peer; c->udp_rtcp_addr.sin_port = htons((uint16_t)b);
        return 0;
    }
    return -1;
}

/* Determine which track the client is SETUPing.
 *   trackID=0 (or absent) -> video
 *   trackID=1            -> audio
 * Returns 0=video, 1=audio.
 *
 * Older clients (and our pre-audio SDP) used "/main/main" or
 * "/main/sub" without trackID syntax. We treat those as video. */
static int extract_track_id(const char *url)
{
    const char *t = strstr(url, "trackID=");
    if (!t) return 0;
    t += 8;
    return atoi(t);
}

static void handle_setup(struct client_ctx *c, const struct rtsp_request *req,
                          const char *cseq)
{
    if (c->state != CS_INIT && c->state != CS_READY) {
        send_response(c, "455 Method Not Valid In This State", cseq,
                      NULL, NULL, NULL);
        return;
    }
    int idx = path_to_stream_idx(req->path);
    if (idx < 0) {
        send_response(c, "404 Not Found", cseq, NULL, NULL, NULL);
        return;
    }
    int track = extract_track_id(req->url);
    if (track == 1 && !audio_in_is_available()) {
        /* Client asked for audio track but mic isn't up. Fail
         * gracefully — the client will continue with video only. */
        send_response(c, "404 Not Found", cseq, NULL, NULL, NULL);
        return;
    }

    const char *transport = rtsp_get_header(req, "transport");

    /* parse_transport currently writes into the video fields
     * (c->xport, c->iv_rtp_chan, c->udp_rtp_addr, etc.). For an
     * audio SETUP we don't want to overwrite the video transport
     * we already negotiated — we copy the result over to the
     * audio_* fields and reset the video fields if they hadn't
     * already been set. We do this by capturing pre-state and
     * post-state and routing to the right struct. */
    enum xport_type pre_xport = c->xport;
    int  pre_iv_rtp = c->iv_rtp_chan;
    int  pre_iv_rtcp = c->iv_rtcp_chan;
    int  pre_udp_rtp_fd = c->udp_rtp_fd;
    int  pre_udp_rtcp_fd = c->udp_rtcp_fd;
    struct sockaddr_in pre_udp_rtp_addr  = c->udp_rtp_addr;
    struct sockaddr_in pre_udp_rtcp_addr = c->udp_rtcp_addr;
    int video_was_setup = (pre_xport != XPORT_NONE);

    if (parse_transport(c, transport) < 0) {
        send_response(c, "461 Unsupported Transport", cseq, NULL, NULL, NULL);
        return;
    }

    if (track == 1) {
        /* Move newly-parsed transport to audio_* fields. */
        c->audio_xport         = c->xport;
        c->audio_iv_rtp_chan   = c->iv_rtp_chan;
        c->audio_iv_rtcp_chan  = c->iv_rtcp_chan;
        c->audio_udp_rtp_fd    = c->udp_rtp_fd;
        c->audio_udp_rtcp_fd   = c->udp_rtcp_fd;
        c->audio_udp_rtp_addr  = c->udp_rtp_addr;
        c->audio_udp_rtcp_addr = c->udp_rtcp_addr;
        c->audio_setup_done    = 1;

        /* Restore video fields if they had been set by an earlier
         * SETUP (typical sequence: SETUP video then SETUP audio). */
        if (video_was_setup) {
            c->xport         = pre_xport;
            c->iv_rtp_chan   = pre_iv_rtp;
            c->iv_rtcp_chan  = pre_iv_rtcp;
            c->udp_rtp_fd    = pre_udp_rtp_fd;
            c->udp_rtcp_fd   = pre_udp_rtcp_fd;
            c->udp_rtp_addr  = pre_udp_rtp_addr;
            c->udp_rtcp_addr = pre_udp_rtcp_addr;
        }
    }
    /* track == 0: parse_transport already wrote into the video
     * fields, which is exactly what we want. */

    c->stream_idx = idx;
    if (c->session_id[0] == 0) {
        gen_session_id(c->session_id, sizeof(c->session_id));
    }
    c->state = CS_READY;

    /* Build Transport response. */
    char xhdr[256];
    enum xport_type tx = (track == 1) ? c->audio_xport : c->xport;
    int iv_rtp  = (track == 1) ? c->audio_iv_rtp_chan  : c->iv_rtp_chan;
    int iv_rtcp = (track == 1) ? c->audio_iv_rtcp_chan : c->iv_rtcp_chan;
    struct sockaddr_in *udp_rtp  = (track == 1)
        ? &c->audio_udp_rtp_addr  : &c->udp_rtp_addr;
    struct sockaddr_in *udp_rtcp = (track == 1)
        ? &c->audio_udp_rtcp_addr : &c->udp_rtcp_addr;

    if (tx == XPORT_TCP) {
        snprintf(xhdr, sizeof(xhdr),
            "Session: %s;timeout=60\r\n"
            "Transport: RTP/AVP/TCP;unicast;interleaved=%d-%d\r\n",
            c->session_id, iv_rtp, iv_rtcp);
    } else {
        snprintf(xhdr, sizeof(xhdr),
            "Session: %s;timeout=60\r\n"
            "Transport: RTP/AVP;unicast;client_port=%u-%u;"
                "server_port=6970-6971\r\n",
            c->session_id,
            ntohs(udp_rtp->sin_port),
            ntohs(udp_rtcp->sin_port));
    }
    send_response(c, "200 OK", cseq, xhdr, NULL, NULL);
    fprintf(stderr, "[rtsp] %s SETUP /%s trackID=%d — xport=%s, session=%s\n",
            c->peer_str, idx == 0 ? "main" : "sub", track,
            tx == XPORT_TCP ? "TCP-interleaved" : "UDP",
            c->session_id);
}

/* Forward declaration — implementation comes later in the file. */
static void *streamer_thread(void *arg);
static void *audio_streamer_thread(void *arg);

static void handle_play(struct client_ctx *c, const struct rtsp_request *req,
                          const char *cseq)
{
    (void)req;
    if (c->state != CS_READY) {
        send_response(c, "455 Method Not Valid In This State", cseq,
                      NULL, NULL, NULL);
        return;
    }

    /* Decide initial RTP state NOW so we can announce it via RTP-Info
     * and the streamer thread uses the same values.
     *
     * Why rtp_ts_base = monotonic × 90 kHz instead of just 0:
     *   VLC opens a ~1000ms jitter buffer at PLAY. While buffering, it
     *   accumulates frames whose PTS we control. When buffering ends
     *   and rendering begins, VLC compares each frame's PTS to its
     *   internal wall clock. If we sent PTS starting at 0, the first
     *   frame's PTS is "in the past" relative to the wall clock VLC
     *   reached during buffering, and VLC reports
     *     "picture is too late to be displayed (missing 1000+ ms)"
     *   then drops everything.
     *
     *   Setting rtp_ts_base to a monotonic-clock-derived value means
     *   the first frame's PTS roughly matches the actual moment VLC
     *   should render it, and successive PTS values track wall clock.
     *   ffplay was tolerant to PTS=0; VLC's avcodec wrapper is not.
     */
    struct timespec ts0;
    clock_gettime(CLOCK_MONOTONIC, &ts0);
    uint64_t now90 = (uint64_t)ts0.tv_sec * 90000ULL +
                     (uint64_t)ts0.tv_nsec * 90ULL / 1000000ULL;
    c->rtp_ts_base  = (uint32_t)now90;
    c->initial_seq  = (uint16_t)(ts0.tv_nsec & 0xffff);
    c->ssrc         = (uint32_t)(ts0.tv_nsec ^ (uintptr_t)c);

    /* Audio track RTP state (if SETUP'd a trackID=1). 8 kHz clock
     * for G.711, separate ssrc and seq from video. The audio
     * timestamp advances by 160 per packet (20 ms × 8 kHz). */
    if (c->audio_setup_done) {
        uint64_t now8 = (uint64_t)ts0.tv_sec * 8000ULL +
                        (uint64_t)ts0.tv_nsec * 8ULL / 1000000ULL;
        c->audio_rtp_ts_base = (uint32_t)now8;
        c->audio_initial_seq = (uint16_t)((ts0.tv_nsec >> 8) & 0xffff);
        c->audio_ssrc        = (uint32_t)((ts0.tv_nsec << 1) ^
                                          (uintptr_t)c) ^ 0xa5a5a5a5;
        c->audio_seq         = c->audio_initial_seq;
        c->audio_ts          = c->audio_rtp_ts_base;
    }

    char extra[256];
    snprintf(extra, sizeof(extra),
             "Session: %s\r\n"
             "RTP-Info: url=%s;seq=%u;rtptime=%u\r\n",
             c->session_id, req->url,
             (unsigned)c->initial_seq,
             (unsigned)c->rtp_ts_base);
    send_response(c, "200 OK", cseq, extra, NULL, NULL);

    c->state = CS_PLAYING;
    fprintf(stderr, "[rtsp] %s PLAY /%s — entering streaming state "
            "(seq=%u, rtptime=%u)\n",
            c->peer_str, c->stream_idx == 0 ? "main" : "sub",
            (unsigned)c->initial_seq, (unsigned)c->rtp_ts_base);

    if (pthread_create(&c->streamer_tid, NULL, streamer_thread, c) == 0) {
        c->streamer_started = 1;
    } else {
        fprintf(stderr, "[rtsp] %s failed to start streamer thread\n",
                c->peer_str);
    }

    /* Spawn the audio streamer if the client SETUP'd trackID=1 and
     * mic capture is up. The audio thread is independent — video
     * works fine without it (and vice versa). */
    if (c->audio_setup_done && audio_in_is_available()) {
        if (pthread_create(&c->audio_streamer_tid, NULL,
                           audio_streamer_thread, c) == 0) {
            c->audio_streamer_started = 1;
        } else {
            fprintf(stderr,
                "[rtsp] %s failed to start audio streamer thread\n",
                c->peer_str);
        }
    }
}

static void handle_pause(struct client_ctx *c, const struct rtsp_request *req,
                          const char *cseq)
{
    (void)req;
    char extra[64];
    snprintf(extra, sizeof(extra), "Session: %s\r\n", c->session_id);
    send_response(c, "200 OK", cseq, extra, NULL, NULL);
    c->state = CS_READY;
}

static void handle_teardown(struct client_ctx *c, const struct rtsp_request *req,
                             const char *cseq)
{
    (void)req;
    char extra[64];
    if (c->session_id[0]) {
        snprintf(extra, sizeof(extra), "Session: %s\r\n", c->session_id);
    } else {
        extra[0] = 0;
    }
    send_response(c, "200 OK", cseq, extra, NULL, NULL);
    c->state = CS_INIT;
    /* The serve_client loop checks state and will exit. */
}

static void handle_get_parameter(struct client_ctx *c,
                                   const struct rtsp_request *req,
                                   const char *cseq)
{
    (void)req;
    /* GET_PARAMETER is most commonly used as a keepalive. We just
     * acknowledge with 200 OK. */
    char extra[64];
    if (c->session_id[0]) {
        snprintf(extra, sizeof(extra), "Session: %s\r\n", c->session_id);
        send_response(c, "200 OK", cseq, extra, NULL, NULL);
    } else {
        send_response(c, "200 OK", cseq, NULL, NULL, NULL);
    }
}

/* ====================================================================== */
/* RTP packetization                                                       */
/* ====================================================================== */

/* RTP packet payload type for dynamic codec assignment (matches SDP). */
#define RTP_PT_VIDEO    96    /* dynamic PT for H.264/H.265 */
#define RTP_PT_PCMU      0    /* static PT for G.711 µ-law (RFC 3551) */

/* MTU minus IP/UDP/RTP overhead for fragmentation. 1400 is conservative
 * (works on Ethernet 1500-MTU networks even with various tunneling). */
#define RTP_MAX_PAYLOAD 1400

/* RTP common header is 12 bytes. */
#define RTP_HDR_LEN     12

/* RTSP interleaved framing: '$' <chan u8> <len u16> = 4 bytes. */
#define IV_HDR_LEN      4

/* Build the 12-byte RTP header into `out`. The video path passes
 * RTP_PT_VIDEO; the audio path passes RTP_PT_PCMU. */
static void rtp_build_hdr_pt(uint8_t *out, int marker, uint16_t seq,
                              uint32_t ts, uint32_t ssrc, uint8_t pt)
{
    out[0]  = 0x80;                                  /* V=2, P=0, X=0, CC=0 */
    out[1]  = (marker ? 0x80 : 0x00) | (pt & 0x7f);
    out[2]  = (uint8_t)(seq >> 8);
    out[3]  = (uint8_t)(seq     );
    out[4]  = (uint8_t)(ts >> 24);
    out[5]  = (uint8_t)(ts >> 16);
    out[6]  = (uint8_t)(ts >>  8);
    out[7]  = (uint8_t)(ts      );
    out[8]  = (uint8_t)(ssrc >> 24);
    out[9]  = (uint8_t)(ssrc >> 16);
    out[10] = (uint8_t)(ssrc >>  8);
    out[11] = (uint8_t)(ssrc      );
}

/* Original video-path entry point — compatibility wrapper. */
static void rtp_build_hdr(uint8_t *out, int marker, uint16_t seq,
                            uint32_t ts, uint32_t ssrc)
{
    rtp_build_hdr_pt(out, marker, seq, ts, ssrc, RTP_PT_VIDEO);
}

/* Append one RTP packet (with optional interleave prefix) to a growing
 * output buffer. We batch all RTP packets for an Access Unit into one
 * buffer and send with a single write(), which dramatically reduces
 * syscall overhead and makes I-frame transmission atomic from the
 * kernel TCP-send perspective. */
struct outbuf {
    uint8_t *data;
    size_t   len;
    size_t   cap;
};

static int outbuf_reserve(struct outbuf *b, size_t need)
{
    if (b->len + need <= b->cap) return 0;
    size_t newcap = b->cap ? b->cap * 2 : 4096;
    while (newcap < b->len + need) newcap *= 2;
    uint8_t *p = realloc(b->data, newcap);
    if (!p) return -1;
    b->data = p;
    b->cap  = newcap;
    return 0;
}

/* Append one RTP packet whose payload has already been built in
 * `payload[0..payload_len)`. If `iv_chan >= 0` we prepend the
 * interleaved framing header. */
static int outbuf_append_rtp(struct outbuf *b, int iv_chan,
                              uint8_t marker, uint16_t seq, uint32_t ts,
                              uint32_t ssrc, const uint8_t *payload,
                              size_t payload_len)
{
    size_t total_rtp = RTP_HDR_LEN + payload_len;
    size_t needed = (iv_chan >= 0 ? IV_HDR_LEN : 0) + total_rtp;
    if (outbuf_reserve(b, needed) < 0) return -1;

    if (iv_chan >= 0) {
        b->data[b->len + 0] = '$';
        b->data[b->len + 1] = (uint8_t)iv_chan;
        b->data[b->len + 2] = (uint8_t)(total_rtp >> 8);
        b->data[b->len + 3] = (uint8_t)(total_rtp     );
        b->len += IV_HDR_LEN;
    }
    rtp_build_hdr(b->data + b->len, marker, seq, ts, ssrc);
    memcpy(b->data + b->len + RTP_HDR_LEN, payload, payload_len);
    b->len += total_rtp;
    return 0;
}

/* Packetize one AU's worth of NALs into RTP packets in `out`.
 *
 * Strategy: each NAL becomes either a single RTP packet (if it fits
 * in MTU) or a chain of FU fragments. The marker bit is set on the
 * very last packet of the AU only.
 *
 * Returns the next sequence number to use, or 0 on alloc failure. */
static uint16_t packetize_h264_au(struct outbuf *out, int iv_chan,
                                    const uint8_t * const *nals,
                                    const size_t *nal_lens, int n_nals,
                                    uint32_t rtp_ts, uint16_t seq,
                                    uint32_t ssrc)
{
    for (int i = 0; i < n_nals; i++) {
        const uint8_t *nal = nals[i];
        size_t len = nal_lens[i];
        int last_nal = (i == n_nals - 1);
        if (len <= RTP_MAX_PAYLOAD) {
            uint8_t marker = (uint8_t)(last_nal ? 1 : 0);
            if (outbuf_append_rtp(out, iv_chan, marker, seq,
                                   rtp_ts, ssrc, nal, len) < 0) return 0;
            seq++;
        } else {
            /* FU-A fragmentation. Strip NAL header byte, replace with
             * indicator byte (NRI | 28) + FU header (S/E/R | type). */
            uint8_t nri  = nal[0] & 0x60;
            uint8_t typ  = nal[0] & 0x1f;
            const uint8_t *body = nal + 1;
            size_t body_left = len - 1;
            const size_t chunk_max = RTP_MAX_PAYLOAD - 2;  /* 2 bytes FU hdr */
            int first = 1;
            while (body_left > 0) {
                size_t take = body_left > chunk_max ? chunk_max : body_left;
                int last_frag = (take == body_left);
                uint8_t fu_pkt[RTP_MAX_PAYLOAD];
                fu_pkt[0] = nri | 28;
                fu_pkt[1] = (first ? 0x80 : 0) | (last_frag ? 0x40 : 0) | typ;
                memcpy(fu_pkt + 2, body, take);
                uint8_t marker = (uint8_t)((last_nal && last_frag) ? 1 : 0);
                if (outbuf_append_rtp(out, iv_chan, marker, seq,
                                       rtp_ts, ssrc, fu_pkt, take + 2) < 0)
                    return 0;
                seq++;
                body     += take;
                body_left -= take;
                first = 0;
            }
        }
    }
    return seq;
}

static uint16_t packetize_h265_au(struct outbuf *out, int iv_chan,
                                    const uint8_t * const *nals,
                                    const size_t *nal_lens, int n_nals,
                                    uint32_t rtp_ts, uint16_t seq,
                                    uint32_t ssrc)
{
    for (int i = 0; i < n_nals; i++) {
        const uint8_t *nal = nals[i];
        size_t len = nal_lens[i];
        int last_nal = (i == n_nals - 1);
        if (len <= RTP_MAX_PAYLOAD) {
            uint8_t marker = (uint8_t)(last_nal ? 1 : 0);
            if (outbuf_append_rtp(out, iv_chan, marker, seq,
                                   rtp_ts, ssrc, nal, len) < 0) return 0;
            seq++;
        } else {
            /* HEVC FU fragmentation. NAL header is 2 bytes:
             *   b0 = [F(1)][type(6)][layer_high(1)]
             *   b1 = [layer_low(5)][TID(3)]
             * For FU, we replace the 6-bit type with 49 (FU type), keep
             * F + layer + TID. Then 1-byte FU header carries S/E + the
             * original type. */
            uint8_t b0 = nal[0];
            uint8_t b1 = nal[1];
            uint8_t typ = (b0 >> 1) & 0x3f;
            uint8_t pl_hdr_b0 = (b0 & 0x81) | (49 << 1);
            uint8_t pl_hdr_b1 = b1;
            const uint8_t *body = nal + 2;
            size_t body_left = len - 2;
            const size_t chunk_max = RTP_MAX_PAYLOAD - 3;  /* 3 bytes FU hdr */
            int first = 1;
            while (body_left > 0) {
                size_t take = body_left > chunk_max ? chunk_max : body_left;
                int last_frag = (take == body_left);
                uint8_t fu_pkt[RTP_MAX_PAYLOAD];
                fu_pkt[0] = pl_hdr_b0;
                fu_pkt[1] = pl_hdr_b1;
                fu_pkt[2] = (first ? 0x80 : 0) | (last_frag ? 0x40 : 0) | typ;
                memcpy(fu_pkt + 3, body, take);
                uint8_t marker = (uint8_t)((last_nal && last_frag) ? 1 : 0);
                if (outbuf_append_rtp(out, iv_chan, marker, seq,
                                       rtp_ts, ssrc, fu_pkt, take + 3) < 0)
                    return 0;
                seq++;
                body     += take;
                body_left -= take;
                first = 0;
            }
        }
    }
    return seq;
}

/* Send the entire batched outbuf, atomically per AU. For TCP we hold
 * the write lock to serialize against other threads writing to the
 * same socket (eg keepalive responses). For UDP we send each RTP
 * packet individually (UDP sends are limited to one datagram per
 * sendto), but we don't need a lock since UDP sends are independent. */
static int outbuf_send_tcp(struct client_ctx *c, const struct outbuf *b)
{
    pthread_mutex_lock(&c->write_mtx);
    size_t off = 0;
    while (off < b->len) {
        ssize_t n = send(c->conn_fd, b->data + off, b->len - off,
                         MSG_NOSIGNAL);
        if (n < 0) {
            if (errno == EINTR) continue;
            pthread_mutex_unlock(&c->write_mtx);
            return -1;
        }
        off += (size_t)n;
    }
    pthread_mutex_unlock(&c->write_mtx);
    return 0;
}

/* For UDP: send a single RTP packet directly via sendto. Used by the
 * UDP-mode packetizer below. */
static int udp_send_one(struct client_ctx *c, int marker,
                         uint16_t seq, uint32_t ts, uint32_t ssrc,
                         const uint8_t *payload, size_t payload_len)
{
    uint8_t pkt[RTP_HDR_LEN + RTP_MAX_PAYLOAD];
    if (payload_len > RTP_MAX_PAYLOAD) return -1;
    rtp_build_hdr(pkt, marker, seq, ts, ssrc);
    memcpy(pkt + RTP_HDR_LEN, payload, payload_len);
    ssize_t n = sendto(c->udp_rtp_fd, pkt, RTP_HDR_LEN + payload_len, 0,
                       (struct sockaddr *)&c->udp_rtp_addr,
                       sizeof(c->udp_rtp_addr));
    return (n == (ssize_t)(RTP_HDR_LEN + payload_len)) ? 0 : -1;
}

/* Packetize and immediately UDP-send an entire AU. Sets the marker bit
 * correctly only on the very last packet (last fragment of last NAL). */
static uint16_t packetize_au_udp(struct client_ctx *c,
                                   enum rtsp_codec codec,
                                   const uint8_t * const *nals,
                                   const size_t *nal_lens, int n_nals,
                                   uint32_t rtp_ts, uint16_t seq,
                                   uint32_t ssrc, int *out_failed)
{
    *out_failed = 0;
    for (int i = 0; i < n_nals; i++) {
        const uint8_t *nal = nals[i];
        size_t len = nal_lens[i];
        int last_nal = (i == n_nals - 1);

        if (len <= RTP_MAX_PAYLOAD) {
            int marker = last_nal ? 1 : 0;
            if (udp_send_one(c, marker, seq, rtp_ts, ssrc, nal, len) < 0) {
                *out_failed = 1; return seq;
            }
            seq++;
        } else if (codec == RTSP_CODEC_H264) {
            uint8_t nri = nal[0] & 0x60;
            uint8_t typ = nal[0] & 0x1f;
            const uint8_t *body = nal + 1;
            size_t left = len - 1;
            const size_t chunk_max = RTP_MAX_PAYLOAD - 2;
            int first = 1;
            while (left > 0) {
                size_t take = left > chunk_max ? chunk_max : left;
                int last_frag = (take == left);
                uint8_t fu[RTP_MAX_PAYLOAD];
                fu[0] = nri | 28;
                fu[1] = (first ? 0x80 : 0) | (last_frag ? 0x40 : 0) | typ;
                memcpy(fu + 2, body, take);
                int marker = (last_nal && last_frag) ? 1 : 0;
                if (udp_send_one(c, marker, seq, rtp_ts, ssrc,
                                  fu, take + 2) < 0) {
                    *out_failed = 1; return seq;
                }
                seq++;
                body += take; left -= take; first = 0;
            }
        } else { /* H.265 */
            uint8_t b0 = nal[0], b1 = nal[1];
            uint8_t typ = (b0 >> 1) & 0x3f;
            uint8_t pl_b0 = (b0 & 0x81) | (49 << 1);
            uint8_t pl_b1 = b1;
            const uint8_t *body = nal + 2;
            size_t left = len - 2;
            const size_t chunk_max = RTP_MAX_PAYLOAD - 3;
            int first = 1;
            while (left > 0) {
                size_t take = left > chunk_max ? chunk_max : left;
                int last_frag = (take == left);
                uint8_t fu[RTP_MAX_PAYLOAD];
                fu[0] = pl_b0; fu[1] = pl_b1;
                fu[2] = (first ? 0x80 : 0) | (last_frag ? 0x40 : 0) | typ;
                memcpy(fu + 3, body, take);
                int marker = (last_nal && last_frag) ? 1 : 0;
                if (udp_send_one(c, marker, seq, rtp_ts, ssrc,
                                  fu, take + 3) < 0) {
                    *out_failed = 1; return seq;
                }
                seq++;
                body += take; left -= take; first = 0;
            }
        }
    }
    return seq;
}

/* ====================================================================== */
/* Streamer thread                                                         */
/* ====================================================================== */

/* Walk a length-prefixed flat NAL buffer (as stored in au_entry::data)
 * and fill out NAL pointer + length arrays. Returns NAL count. */
static int unpack_nals(const uint8_t *buf, size_t buf_len,
                        const uint8_t **out_nals, size_t *out_lens,
                        int max_nals)
{
    int n = 0;
    size_t off = 0;
    while (off + 4 <= buf_len && n < max_nals) {
        uint32_t L = (uint32_t)buf[off]        |
                     ((uint32_t)buf[off+1] <<  8) |
                     ((uint32_t)buf[off+2] << 16) |
                     ((uint32_t)buf[off+3] << 24);
        off += 4;
        if (off + L > buf_len) break;  /* corrupt */
        out_nals[n] = buf + off;
        out_lens[n] = L;
        off += L;
        n++;
    }
    return n;
}

/* Pace this AU against wall-clock vs camera ts_ms. On entry the caller
 * should have already established (t_emit_start, ts_camera_base) on
 * the first AU. We sleep if ahead, resync if more than 1s behind.
 *
 * IMPORTANT — pre-roll burst:
 *   When a client first connects, RTSP players (VLC, ffmpeg) need to
 *   accumulate ~1 second of frames in their jitter buffer before they
 *   start rendering. If we strictly pace from frame 1 at the real
 *   ingest rate (~8 fps), filling that buffer takes ~1 wall-clock
 *   second — by which time the player's internal clock has advanced
 *   1 second and the first frame's PTS=0 is "1000 ms in the past",
 *   producing the "picture is too late to be displayed" warnings and
 *   eventually causing avcodec to give up with "computer too slow".
 *
 *   Fix: for the first PRE_ROLL_MS of camera-time frames, skip the
 *   sleep entirely. Frames are sent as fast as the network allows.
 *   The player's buffer fills in ~50ms instead of ~1s, the wall-clock
 *   skew at start-of-render is small, and pacing kicks in cleanly
 *   once the buffer is full.
 *
 *   Without this fix, the workaround on the client side is
 *   `--network-caching=3000` (i.e. 3-second buffer), which is the
 *   "smoking gun" that confirmed the diagnosis.
 */
#define PRE_ROLL_MS  1500

static void pace_au(uint64_t ts_camera_ms,
                     uint64_t *ts_camera_base,
                     struct timespec *t_emit_start)
{
    if (t_emit_start->tv_sec == 0 && t_emit_start->tv_nsec == 0) {
        clock_gettime(CLOCK_MONOTONIC, t_emit_start);
        *ts_camera_base = ts_camera_ms;
        return;
    }

    /* Pre-roll burst: don't sleep for the first PRE_ROLL_MS of
     * camera-time frames. The PTS values themselves stay correct
     * (RTP timestamps still derive from camera_ts_ms), so once we
     * exit pre-roll the player's buffer is full and timestamps
     * align with its wall clock. */
    if (ts_camera_ms - *ts_camera_base < PRE_ROLL_MS) {
        return;  /* burst — don't sleep */
    }

    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    int64_t target_ns = (int64_t)(ts_camera_ms - *ts_camera_base) * 1000000LL;
    int64_t actual_ns = (int64_t)(now.tv_sec  - t_emit_start->tv_sec) * 1000000000LL
                      + (now.tv_nsec - t_emit_start->tv_nsec);
    int64_t delta = target_ns - actual_ns;

    /* When we transition out of pre-roll, the wall-clock has only
     * advanced by ~50ms but `target_ns` is already at ~PRE_ROLL_MS.
     * That means `delta > 0` and we'd sleep until target catches up.
     * That's exactly what we want: we burst the first 1.5s, then
     * pause until the wall clock has caught up to camera-time. After
     * this single big sleep, normal pacing resumes. */
    if (delta > 0 && delta < 5000000000LL) {  /* up to 5s ahead */
        struct timespec ts = {
            .tv_sec  = delta / 1000000000LL,
            .tv_nsec = delta % 1000000000LL,
        };
        nanosleep(&ts, NULL);
    } else if (-delta > 1000000000LL) {  /* more than 1s behind */
        /* Resync: pretend this AU is "now" and continue from here. */
        *t_emit_start = now;
        *ts_camera_base = ts_camera_ms;
    }
    /* else: within 1s of target — fine, just go */
}

/* Build a snapshot of the 3 (or 4) parameter-set NALs to prepend at
 * IDR boundaries. Returns NAL count. Pointers reference internal
 * storage in the ring (caller must hold no lock when using — but
 * the parameter sets are stable enough between updates that racing
 * is fine). For safety we copy them out under the lock. */
static int snapshot_param_sets(int stream_idx,
                                 uint8_t *vps_buf, size_t *vps_len,
                                 uint8_t *sps_buf, size_t *sps_len,
                                 uint8_t *pps_buf, size_t *pps_len)
{
    struct ring *r = &g_rings[stream_idx];
    pthread_mutex_lock(&r->mtx);
    int has_vps = (r->codec == RTSP_CODEC_H265 && r->vps_len > 0);
    int has_sps = (r->sps_fixed_len > 0);
    int has_pps = (r->pps_len > 0);
    if (has_vps) { memcpy(vps_buf, r->vps, r->vps_len); *vps_len = r->vps_len; }
    else *vps_len = 0;
    if (has_sps) { memcpy(sps_buf, r->sps_fixed, r->sps_fixed_len); *sps_len = r->sps_fixed_len; }
    else *sps_len = 0;
    if (has_pps) { memcpy(pps_buf, r->pps, r->pps_len); *pps_len = r->pps_len; }
    else *pps_len = 0;
    int codec = r->codec;
    pthread_mutex_unlock(&r->mtx);
    int n = 0;
    if (codec == RTSP_CODEC_H265 && *vps_len > 0) n++;
    if (*sps_len > 0) n++;
    if (*pps_len > 0) n++;
    return n;
}

/* Setup UDP send sockets. We bind to 6970/6971 (the server_port we
 * announced in SETUP response). Returns 0 on success. */
static int udp_setup_sockets(struct client_ctx *c)
{
    c->udp_rtp_fd  = socket(AF_INET, SOCK_DGRAM, 0);
    c->udp_rtcp_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (c->udp_rtp_fd < 0 || c->udp_rtcp_fd < 0) return -1;
    struct sockaddr_in la = {0};
    la.sin_family      = AF_INET;
    la.sin_addr.s_addr = htonl(INADDR_ANY);
    la.sin_port        = htons(6970);
    if (bind(c->udp_rtp_fd, (struct sockaddr *)&la, sizeof(la)) < 0) {
        /* Already in use? Try ephemeral. We don't actually care — the
         * client only knows about our port via server_port=N-N+1 in
         * SETUP, which it usually ignores anyway. */
    }
    la.sin_port = htons(6971);
    (void)bind(c->udp_rtcp_fd, (struct sockaddr *)&la, sizeof(la));
    return 0;
}

/* ====================================================================== */
/* Audio streamer — pulls G.711 µ-law frames from audio_in and pushes    */
/* them as RTP packets to the client. Independent from the video         */
/* streamer; runs only if the client SETUP'd trackID=1.                   */
/*                                                                        */
/* Audio is much simpler than video: each G.711 frame from the SDK is   */
/* already small enough to fit in a single RTP packet (typically 160     */
/* bytes = 20 ms). No fragmentation. No keyframe/IDR semantics. Just    */
/* timed delivery at 8000 samples/sec.                                   */
/* ====================================================================== */
static void *audio_streamer_thread(void *arg)
{
    struct client_ctx *c = (struct client_ctx *)arg;

    if (!c->audio_setup_done || !audio_in_is_available()) {
        return NULL;
    }

    /* Open the SDK chain if not already (refcount-based). The
     * matching release() runs before we exit. */
    if (audio_in_acquire() != 0) {
        fprintf(stderr, "[rtsp] %s audio_in_acquire failed — exiting\n",
                c->peer_str);
        return NULL;
    }

    /* For UDP the audio sender just needs a socket bound to the
     * source; we don't reuse the video send socket because the
     * destination port is different. SOCK_DGRAM, no bind needed
     * (kernel auto-assigns ephemeral source port). */
    if (c->audio_xport == XPORT_UDP && c->audio_udp_rtp_fd <= 0) {
        c->audio_udp_rtp_fd = socket(AF_INET, SOCK_DGRAM, 0);
        if (c->audio_udp_rtp_fd < 0) {
            fprintf(stderr, "[rtsp] %s audio UDP socket: %s\n",
                    c->peer_str, strerror(errno));
            audio_in_release();
            return NULL;
        }
    }

    fprintf(stderr, "[rtsp] %s audio streamer started "
            "(seq=%u, ssrc=0x%08x, ts0=%u)\n",
            c->peer_str,
            (unsigned)c->audio_initial_seq,
            (unsigned)c->audio_ssrc,
            (unsigned)c->audio_rtp_ts_base);

    uint8_t pcm_frame[2048];
    uint8_t rtp_pkt[RTP_HDR_LEN + 2048];
    uint8_t iv_pkt[IV_HDR_LEN + RTP_HDR_LEN + 2048];

    /* Backoff: when get_frame returns no data, sleep — but ramp
     * up the sleep duration if many consecutive failures. The SDK
     * fills the queue at the encoder's natural rate (one G.711
     * frame every 20 ms). If we're polling too aggressively, we
     * burn CPU; if too slowly, we add latency. The ramp avoids
     * tight-looping when the chain is slow to start producing. */
    int empty_streak = 0;

    while (!g_shutdown && c->state == CS_PLAYING) {
        size_t got = sizeof(pcm_frame);
        int rc = audio_in_get_frame(pcm_frame, &got);
        if (rc != 0 || got == 0) {
            empty_streak++;
            if (empty_streak < 5) {
                usleep(5 * 1000);     /* 5 ms — fresh start */
            } else if (empty_streak < 50) {
                usleep(20 * 1000);    /* 20 ms — normal pacing */
            } else {
                usleep(100 * 1000);   /* 100 ms — chain not producing */
            }
            continue;
        }
        empty_streak = 0;

        /* Build RTP packet with audio PT=0 (PCMU). Marker bit
         * stays 0 for continuous audio (set on first packet only
         * if you want, ffplay/VLC don't care). */
        rtp_build_hdr_pt(rtp_pkt, 0,
                         c->audio_seq, c->audio_ts, c->audio_ssrc,
                         RTP_PT_PCMU);
        memcpy(rtp_pkt + RTP_HDR_LEN, pcm_frame, got);
        size_t total = RTP_HDR_LEN + got;

        if (c->audio_xport == XPORT_TCP) {
            iv_pkt[0] = '$';
            iv_pkt[1] = (uint8_t)c->audio_iv_rtp_chan;
            iv_pkt[2] = (uint8_t)((total >> 8) & 0xff);
            iv_pkt[3] = (uint8_t)(total & 0xff);
            memcpy(iv_pkt + IV_HDR_LEN, rtp_pkt, total);
            pthread_mutex_lock(&c->write_mtx);
            ssize_t s = send(c->conn_fd, iv_pkt, IV_HDR_LEN + total,
                             MSG_NOSIGNAL);
            pthread_mutex_unlock(&c->write_mtx);
            if (s != (ssize_t)(IV_HDR_LEN + total)) break;
        } else {
            ssize_t s = sendto(c->audio_udp_rtp_fd, rtp_pkt, total, 0,
                               (struct sockaddr *)&c->audio_udp_rtp_addr,
                               sizeof(c->audio_udp_rtp_addr));
            if (s != (ssize_t)total) break;
        }

        /* Advance RTP state: 1 sample per byte for G.711, so
         * timestamp advances by the byte count of payload. */
        c->audio_seq++;
        c->audio_ts += (uint32_t)got;
    }

    audio_in_release();
    fprintf(stderr, "[rtsp] %s audio streamer exit\n", c->peer_str);
    return NULL;
}

/* ====================================================================== */
/* Video streamer — main RTSP streaming loop.                             */
/* ====================================================================== */
static void *streamer_thread(void *arg)
{
    struct client_ctx *c = (struct client_ctx *)arg;
    struct ring *r = &g_rings[c->stream_idx];
    enum rtsp_codec codec = r->codec;

    /* Setup UDP sockets if needed. */
    if (c->xport == XPORT_UDP) {
        if (udp_setup_sockets(c) < 0) {
            fprintf(stderr, "[rtsp] %s UDP socket setup failed\n", c->peer_str);
            return NULL;
        }
    }

    /* RTP session identifiers. */
    uint32_t ssrc;
    {
        struct timespec t;
        clock_gettime(CLOCK_MONOTONIC, &t);
        ssrc = (uint32_t)(t.tv_nsec ^ (uintptr_t)c);
    }
    uint16_t seq = (uint16_t)(ssrc & 0xffff);   /* random initial seq */

    /* Pacing state. */
    struct timespec t_emit_start = {0, 0};
    uint64_t ts_camera_base = 0;

    /* Don't start from an IDR already in the buffer (that's stale data
     * up to ~8s old at our framerate). Wait for the next IDR that
     * arrives AFTER the client connected. We capture cutoff = highest
     * gseq currently in the ring; the entry-point IDR must be > cutoff. */
    uint64_t cutoff_gseq;
    pthread_mutex_lock(&r->mtx);
    int newest = (r->head - 1 + RING_DEPTH) % RING_DEPTH;
    cutoff_gseq = r->count > 0 ? r->slots[newest].gseq : 0;
    pthread_mutex_unlock(&r->mtx);

    fprintf(stderr, "[rtsp] %s streamer waiting for next IDR after gseq=%llu\n",
            c->peer_str, (unsigned long long)cutoff_gseq);

    uint64_t last_emit_gseq = 0;
    {
        /* Wait up to 10s for a fresh IDR. */
        struct timespec deadline;
        clock_gettime(CLOCK_REALTIME, &deadline);
        deadline.tv_sec += 10;
        pthread_mutex_lock(&r->mtx);
        while (!g_shutdown && c->state == CS_PLAYING) {
            uint64_t found = 0;
            for (int i = 0; i < r->count; i++) {
                int idx = (r->head - r->count + i + RING_DEPTH) % RING_DEPTH;
                if (r->slots[idx].gseq > cutoff_gseq &&
                    r->slots[idx].kind == RTSP_AU_IDR) {
                    found = r->slots[idx].gseq;
                    break;
                }
            }
            if (found) {
                last_emit_gseq = found - 1;
                break;
            }
            int rc = pthread_cond_timedwait(&r->cond, &r->mtx, &deadline);
            if (rc == ETIMEDOUT) {
                /* Fall back to latest IDR in buffer. */
                for (int i = r->count - 1; i >= 0; i--) {
                    int idx = (r->head - r->count + i + RING_DEPTH) % RING_DEPTH;
                    if (r->slots[idx].kind == RTSP_AU_IDR) {
                        last_emit_gseq = r->slots[idx].gseq - 1;
                        break;
                    }
                }
                fprintf(stderr, "[rtsp] %s no fresh IDR after 10s, "
                        "falling back to latest in buffer\n", c->peer_str);
                break;
            }
        }
        pthread_mutex_unlock(&r->mtx);
    }

    if (last_emit_gseq == 0) {
        fprintf(stderr, "[rtsp] %s no IDR available, exiting\n", c->peer_str);
        return NULL;
    }

    fprintf(stderr, "[rtsp] %s starting playout from gseq=%llu (codec=%s, xport=%s)\n",
            c->peer_str, (unsigned long long)(last_emit_gseq + 1),
            codec == RTSP_CODEC_H265 ? "h265" : "h264",
            c->xport == XPORT_TCP ? "tcp-iv" : "udp");

    struct outbuf ob = {0};
    int iv_chan = (c->xport == XPORT_TCP) ? c->iv_rtp_chan : -1;

    /* Statistics. */
    uint32_t emitted_frames = 0;
    uint64_t emitted_bytes  = 0;
    time_t   stat_t = time(NULL);

    while (!g_shutdown && c->state == CS_PLAYING) {
        /* --- Wait for next AU to emit --- */
        uint64_t next_ts_ms;
        int      next_kind;
        uint64_t next_gseq;
        uint8_t *next_data = NULL;
        size_t   next_data_len = 0;

        pthread_mutex_lock(&r->mtx);
        while (!g_shutdown && c->state == CS_PLAYING) {
            /* Live catch-up: if we're more than 30 AUs behind the
             * latest in the ring, jump to the next IDR. */
            int found_next = -1;
            uint64_t latest_gseq = 0;
            int newest_idx = (r->head - 1 + RING_DEPTH) % RING_DEPTH;
            if (r->count > 0) latest_gseq = r->slots[newest_idx].gseq;

            if (latest_gseq > last_emit_gseq + 30) {
                /* Skip to next IDR > last_emit_gseq. */
                for (int i = 0; i < r->count; i++) {
                    int idx = (r->head - r->count + i + RING_DEPTH) % RING_DEPTH;
                    if (r->slots[idx].gseq > last_emit_gseq &&
                        r->slots[idx].kind == RTSP_AU_IDR) {
                        last_emit_gseq = r->slots[idx].gseq - 1;
                        /* Reset pacing baseline. */
                        t_emit_start.tv_sec = 0;
                        t_emit_start.tv_nsec = 0;
                        fprintf(stderr, "[rtsp] %s live catch-up: "
                                "skip to gseq=%llu\n", c->peer_str,
                                (unsigned long long)r->slots[idx].gseq);
                        break;
                    }
                }
            }
            /* Find next AU > last_emit_gseq. */
            for (int i = 0; i < r->count; i++) {
                int idx = (r->head - r->count + i + RING_DEPTH) % RING_DEPTH;
                if (r->slots[idx].gseq > last_emit_gseq) {
                    found_next = idx;
                    break;
                }
            }
            if (found_next >= 0) {
                /* Steal a copy of the data so we can release the lock
                 * before doing network I/O. The data buffer itself is
                 * stable (slot.data isn't freed until the slot is
                 * overwritten), but copying is safer against ring
                 * wraparound during pacing sleeps. */
                struct au_entry *e = &r->slots[found_next];
                next_data = malloc(e->data_len);
                if (!next_data) {
                    pthread_mutex_unlock(&r->mtx);
                    goto cleanup;
                }
                memcpy(next_data, e->data, e->data_len);
                next_data_len = e->data_len;
                next_ts_ms    = e->ts_ms;
                next_kind     = e->kind;
                next_gseq     = e->gseq;
                break;
            }
            /* Wait for new data. */
            struct timespec dl;
            clock_gettime(CLOCK_REALTIME, &dl);
            dl.tv_sec += 5;
            pthread_cond_timedwait(&r->cond, &r->mtx, &dl);
        }
        pthread_mutex_unlock(&r->mtx);

        if (!next_data) break;  /* shutdown / state change */

        /* --- Pace --- */
        pace_au(next_ts_ms, &ts_camera_base, &t_emit_start);

        /* --- Build NAL list, prepending param sets at IDR boundaries --- */
        const uint8_t *all_nals[24];
        size_t         all_lens[24];
        int            n_all = 0;

        uint8_t vps_buf[MAX_PARAM_SET_LEN];
        uint8_t sps_buf[MAX_PARAM_SET_LEN];
        uint8_t pps_buf[MAX_PARAM_SET_LEN];
        size_t  vps_l = 0, sps_l = 0, pps_l = 0;

        if (next_kind == RTSP_AU_IDR) {
            (void)snapshot_param_sets(c->stream_idx,
                                       vps_buf, &vps_l,
                                       sps_buf, &sps_l,
                                       pps_buf, &pps_l);
            if (codec == RTSP_CODEC_H265 && vps_l > 0) {
                all_nals[n_all] = vps_buf; all_lens[n_all] = vps_l; n_all++;
            }
            if (sps_l > 0) {
                all_nals[n_all] = sps_buf; all_lens[n_all] = sps_l; n_all++;
            }
            if (pps_l > 0) {
                all_nals[n_all] = pps_buf; all_lens[n_all] = pps_l; n_all++;
            }
        }
        const uint8_t *body_nals[16];
        size_t         body_lens[16];
        int n_body = unpack_nals(next_data, next_data_len,
                                  body_nals, body_lens, 16);
        for (int i = 0; i < n_body && n_all < 24; i++) {
            all_nals[n_all] = body_nals[i];
            all_lens[n_all] = body_lens[i];
            n_all++;
        }

        if (n_all == 0) {
            free(next_data);
            last_emit_gseq = next_gseq;
            continue;
        }

        /* --- Build RTP timestamp from the relative camera ts ---
         * 90kHz clock, so each ms = 90 ticks. The RTP ts wraps at 32
         * bits naturally. */
        uint32_t rtp_ts = (uint32_t)((next_ts_ms - ts_camera_base) * 90ULL);

        /* --- Packetize and send --- */
        int send_failed = 0;
        if (c->xport == XPORT_TCP) {
            ob.len = 0;  /* reset */
            uint16_t new_seq = (codec == RTSP_CODEC_H265)
                ? packetize_h265_au(&ob, iv_chan, all_nals, all_lens, n_all,
                                     rtp_ts, seq, ssrc)
                : packetize_h264_au(&ob, iv_chan, all_nals, all_lens, n_all,
                                     rtp_ts, seq, ssrc);
            if (new_seq == 0 || outbuf_send_tcp(c, &ob) < 0) {
                send_failed = 1;
            }
            seq = new_seq;
        } else {
            /* UDP: send each RTP packet directly with sendto, no
             * buffering. Marker bit is handled correctly by
             * packetize_au_udp. */
            seq = packetize_au_udp(c, codec, all_nals, all_lens, n_all,
                                    rtp_ts, seq, ssrc, &send_failed);
        }

        free(next_data);

        if (send_failed) {
            fprintf(stderr, "[rtsp] %s send failed, ending session\n",
                    c->peer_str);
            break;
        }

        last_emit_gseq = next_gseq;
        emitted_frames++;
        /* For TCP-interleaved we have ob.len (which includes the iv
         * framing overhead). For UDP we estimate from NAL bytes. Both
         * are approximations. */
        size_t this_au_bytes = 0;
        if (c->xport == XPORT_TCP) {
            this_au_bytes = ob.len;
        } else {
            for (int i = 0; i < n_all; i++) this_au_bytes += all_lens[i];
        }
        emitted_bytes += this_au_bytes;

        /* --- Periodic stats --- */
        time_t now = time(NULL);
        if (now - stat_t >= 5) {
            fprintf(stderr, "[rtsp] %s %us: %u f, %llu KB out\n",
                    c->peer_str, (unsigned)(now - stat_t),
                    emitted_frames,
                    (unsigned long long)(emitted_bytes / 1024));
            emitted_frames = 0;
            emitted_bytes = 0;
            stat_t = now;
        }
    }

cleanup:
    free(ob.data);
    fprintf(stderr, "[rtsp] %s streamer thread exit\n", c->peer_str);
    return NULL;
}

/* ====================================================================== */
/* Per-client serve loop                                                  */
/* ====================================================================== */

/* ---------------------------------------------------------------- */
/* Auth gate                                                        */
/*                                                                  */
/* RFC 2326 leaves the choice of which methods require auth to the */
/* server. We require auth on everything except OPTIONS and        */
/* TEARDOWN — OPTIONS is the discovery probe (must work to learn   */
/* what auth is needed), TEARDOWN must always succeed so a client  */
/* can clean up even after creds have been rotated.                */
/*                                                                  */
/* Most clients (VLC, ffmpeg, GStreamer) attempt the request       */
/* unauthenticated, get a 401 with WWW-Authenticate, then retry    */
/* with the matching Authorization header. They cache the digest   */
/* state for the rest of the session. On the camera side we don't  */
/* keep per-session auth state — every request is verified         */
/* independently. That's fine: the digest itself contains a nonce  */
/* with TTL, so re-verifying isn't a security regression, just a   */
/* tiny CPU cost.                                                   */
/*                                                                  */
/* The URI in the digest is what the client sent in Authorization, */
/* not the request URL — RFC 7616. We pass req->url as the URI     */
/* hint; auth.c's verify_digest extracts the actual uri="..."      */
/* parameter from the Authorization header itself.                 */
/* ---------------------------------------------------------------- */
static int rtsp_auth_gate(struct client_ctx *c,
                          const struct rtsp_request *req,
                          const char *cseq)
{
    /* OPTIONS and TEARDOWN bypass auth entirely. */
    if (strcmp(req->method, "OPTIONS")  == 0) return 0;
    if (strcmp(req->method, "TEARDOWN") == 0) return 0;

    if (!auth_is_configured()) return 0;   /* open mode */

    const char *authz = rtsp_get_header(req, "authorization");
    auth_result_t r = auth_rtsp_check(authz, req->method, req->url);
    if (r == AUTH_OK) return 0;

    /* Build the WWW-Authenticate header. We offer Digest only —
     * Basic over plaintext RTSP would leak the password, and any
     * client that supports RTSP also supports Digest (introduced
     * in RTSP 1.0 itself). */
    char chal_body[256];
    if (auth_make_challenge(chal_body, sizeof(chal_body)) == 0) {
        /* Should not happen — fall back to a generic 401. */
        send_response(c, "401 Unauthorized", cseq, NULL, NULL, NULL);
        return -1;
    }

    char extra[320];
    snprintf(extra, sizeof(extra),
             "WWW-Authenticate: %s\r\n", chal_body);
    send_response(c, "401 Unauthorized", cseq, extra, NULL, NULL);
    return -1;
}

/* Process one RTSP request. Returns 0 on success, -1 on connection
 * close requested. */
static int handle_request(struct client_ctx *c, const struct rtsp_request *req)
{
    const char *cseq = rtsp_get_header(req, "cseq");
    if (!cseq) cseq = "0";

    if (rtsp_auth_gate(c, req, cseq) != 0) return 0;

    if      (strcmp(req->method, "OPTIONS")       == 0) handle_options(c, req, cseq);
    else if (strcmp(req->method, "DESCRIBE")      == 0) handle_describe(c, req, cseq);
    else if (strcmp(req->method, "SETUP")         == 0) handle_setup(c, req, cseq);
    else if (strcmp(req->method, "PLAY")          == 0) handle_play(c, req, cseq);
    else if (strcmp(req->method, "PAUSE")         == 0) handle_pause(c, req, cseq);
    else if (strcmp(req->method, "TEARDOWN")      == 0) {
        handle_teardown(c, req, cseq);
        return -1;
    }
    else if (strcmp(req->method, "GET_PARAMETER") == 0) handle_get_parameter(c, req, cseq);
    else if (strcmp(req->method, "SET_PARAMETER") == 0) {
        /* We don't really support SET_PARAMETER. Acknowledge to keep
         * clients happy but ignore the body (which we haven't read). */
        send_response(c, "200 OK", cseq, NULL, NULL, NULL);
    } else {
        send_response(c, "501 Not Implemented", cseq, NULL, NULL, NULL);
    }
    return 0;
}

/* Main per-client loop. Reads requests, dispatches handlers, exits on
 * connection close, TEARDOWN, or shutdown. */
static void serve_client(int conn_fd, const char *peer_str)
{
    struct client_ctx c;
    memset(&c, 0, sizeof(c));
    c.conn_fd = conn_fd;
    c.udp_rtp_fd  = -1;
    c.udp_rtcp_fd = -1;
    pthread_mutex_init(&c.write_mtx, NULL);
    snprintf(c.peer_str, sizeof(c.peer_str), "%s", peer_str);

    /* Reasonable IO timeouts so a misbehaving client can't hold us
     * forever. RTSP doesn't have a fixed message rate but a 10s
     * recv timeout matches typical keepalive intervals. */
    struct timeval tv = { .tv_sec = 60, .tv_usec = 0 };
    setsockopt(conn_fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    tv.tv_sec = 10;
    setsockopt(conn_fd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));

    while (!g_shutdown) {
        /* If state went back to CS_INIT (TEARDOWN), close. */
        if (c.state == CS_INIT && c.session_id[0]) break;

        ssize_t got = recv(conn_fd,
                           c.rxbuf + c.rxlen,
                           sizeof(c.rxbuf) - c.rxlen - 1, 0);
        if (got <= 0) {
            if (got < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
                continue;
            }
            break;  /* peer closed or error */
        }
        c.rxlen += (size_t)got;
        c.rxbuf[c.rxlen] = 0;

        /* Parse as many full requests as we have buffered. */
        while (c.rxlen > 0) {
            struct rtsp_request req;
            int consumed = rtsp_parse(c.rxbuf, c.rxlen, &req);
            if (consumed == 0) break;          /* need more bytes */
            if (consumed < 0) {                /* malformed */
                fprintf(stderr, "[rtsp] %s bad request\n", c.peer_str);
                goto done;
            }
            int hr = handle_request(&c, &req);
            /* Slide remaining bytes down. */
            size_t left = c.rxlen - (size_t)consumed;
            memmove(c.rxbuf, c.rxbuf + consumed, left);
            c.rxlen = left;
            if (hr < 0) goto done;
        }
    }

done:
    if (c.streamer_started) {
        c.state = CS_INIT;
        pthread_join(c.streamer_tid, NULL);
    }
    if (c.audio_streamer_started) {
        c.state = CS_INIT;
        pthread_join(c.audio_streamer_tid, NULL);
    }
    if (c.udp_rtp_fd  >= 0) close(c.udp_rtp_fd);
    if (c.udp_rtcp_fd >= 0) close(c.udp_rtcp_fd);
    if (c.audio_udp_rtp_fd  > 0) close(c.audio_udp_rtp_fd);
    if (c.audio_udp_rtcp_fd > 0) close(c.audio_udp_rtcp_fd);
    close(conn_fd);
    pthread_mutex_destroy(&c.write_mtx);
    fprintf(stderr, "[rtsp] %s disconnected\n", peer_str);
}

/* ====================================================================== */
/* Acceptor                                                               */
/* ====================================================================== */

static int             g_listen_fd  = -1;
static pthread_t       g_accept_tid;
static int             g_client_count = 0;     /* atomic via g_client_mtx */
static pthread_mutex_t g_client_mtx = PTHREAD_MUTEX_INITIALIZER;

/* Per-client thread: takes ownership of the connection fd and the
 * peer-string, bumps the client counter, runs serve_client, and
 * decrements on the way out. We deliberately don't cap concurrency
 * — the realistic load on this camera is 1-2 viewers + maybe a
 * background recorder, and serve_client is mostly I/O-bound. The
 * RTSP ring buffer is shared across all clients, so memory cost is
 * O(streams), not O(clients). */
struct client_arg {
    int  conn_fd;
    char peer_str[64];
};

static void *client_thread(void *arg)
{
    struct client_arg *ca = arg;
    pthread_mutex_lock(&g_client_mtx);
    g_client_count++;
    pthread_mutex_unlock(&g_client_mtx);

    serve_client(ca->conn_fd, ca->peer_str);

    pthread_mutex_lock(&g_client_mtx);
    if (g_client_count > 0) g_client_count--;
    pthread_mutex_unlock(&g_client_mtx);
    free(ca);
    return NULL;
}

static void *accept_loop(void *arg)
{
    (void)arg;
    fprintf(stderr, "[rtsp] acceptor running\n");

    while (!g_shutdown) {
        struct sockaddr_in cli;
        socklen_t cli_len = sizeof(cli);
        int conn = accept(g_listen_fd, (struct sockaddr *)&cli, &cli_len);
        if (conn < 0) {
            if (errno == EINTR) continue;
            if (g_shutdown) break;
            fprintf(stderr, "[rtsp] accept: %s\n", strerror(errno));
            usleep(100 * 1000);
            continue;
        }
        char peer_str[64];
        snprintf(peer_str, sizeof(peer_str), "%s:%u",
                 inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));

        /* Set TCP_NODELAY so RTSP responses are sent immediately
         * (no Nagle buffering). VLC/ffmpeg otherwise see ~40ms gaps
         * which can break PLAY ack timing. */
        int one = 1;
        setsockopt(conn, IPPROTO_TCP, TCP_NODELAY, &one, sizeof(one));

        /* Hand off to a per-client thread so the acceptor stays
         * responsive. The thread is detached: no join needed, it
         * cleans up by itself on exit. */
        struct client_arg *ca = malloc(sizeof(*ca));
        if (!ca) {
            close(conn);
            continue;
        }
        ca->conn_fd = conn;
        snprintf(ca->peer_str, sizeof(ca->peer_str), "%s", peer_str);

        pthread_t tid;
        pthread_attr_t at;
        pthread_attr_init(&at);
        pthread_attr_setdetachstate(&at, PTHREAD_CREATE_DETACHED);
        if (pthread_create(&tid, &at, client_thread, ca) != 0) {
            fprintf(stderr,
                "[rtsp] %s pthread_create failed, dropping\n", peer_str);
            close(conn);
            free(ca);
        } else {
            fprintf(stderr, "[rtsp] %s connected\n", peer_str);
        }
        pthread_attr_destroy(&at);
    }

    fprintf(stderr, "[rtsp] acceptor exit\n");
    return NULL;
}

/* ====================================================================== */
/* Public init / shutdown                                                 */
/* ====================================================================== */

int rtsp_server_init(int listen_port,
                     const enum rtsp_codec stream_codecs[RTSP_MAX_STREAMS])
{
    /* Reset transient state in case we're being re-initialised
     * after a previous rtsp_server_shutdown() (e.g. capture restart
     * via /api/config). Without this, the previous shutdown left
     * g_shutdown=1 and the new accept_loop would exit immediately. */
    g_shutdown = 0;
    pthread_mutex_lock(&g_client_mtx);
    g_client_count = 0;
    pthread_mutex_unlock(&g_client_mtx);

    /* Initialize per-stream rings with their codec. */
    for (int i = 0; i < RTSP_MAX_STREAMS; i++)
        ring_init(&g_rings[i], stream_codecs[i]);

    /* Open listen socket. */
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        fprintf(stderr, "[rtsp] socket: %s\n", strerror(errno));
        return -1;
    }
    int one = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    /* Same TIME_WAIT-evading trick as http_srv: linger=0 makes
     * close() send RST instead of FIN, so a subsequent
     * rtsp_server_init() (e.g. after a capture restart from the
     * /api/config endpoint) doesn't hit EADDRINUSE. */
    struct linger lg = { .l_onoff = 1, .l_linger = 0 };
    setsockopt(fd, SOL_SOCKET, SO_LINGER, &lg, sizeof(lg));

    struct sockaddr_in addr = {0};
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port        = htons((uint16_t)listen_port);
    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        fprintf(stderr, "[rtsp] bind(%d): %s\n", listen_port, strerror(errno));
        close(fd);
        return -1;
    }
    if (listen(fd, 4) < 0) {
        fprintf(stderr, "[rtsp] listen: %s\n", strerror(errno));
        close(fd);
        return -1;
    }
    g_listen_fd = fd;

    if (pthread_create(&g_accept_tid, NULL, accept_loop, NULL) != 0) {
        fprintf(stderr, "[rtsp] cannot start acceptor thread\n");
        close(fd);
        g_listen_fd = -1;
        return -1;
    }

    fprintf(stderr, "[rtsp] listening on tcp/%d "
                    "(streams: main=%s, sub=%s)\n",
            listen_port,
            stream_codecs[0] == RTSP_CODEC_H264 ? "h264" :
            stream_codecs[0] == RTSP_CODEC_H265 ? "h265" : "none",
            stream_codecs[1] == RTSP_CODEC_H264 ? "h264" :
            stream_codecs[1] == RTSP_CODEC_H265 ? "h265" : "none");
    return 0;
}

void rtsp_server_shutdown(void)
{
    g_shutdown = 1;
    if (g_listen_fd >= 0) {
        /* Close the listen socket to wake accept(). */
        shutdown(g_listen_fd, SHUT_RDWR);
        close(g_listen_fd);
        g_listen_fd = -1;
    }
    pthread_join(g_accept_tid, NULL);

    /* Now wait (briefly) for any in-flight client_thread to drain.
     * They observe g_shutdown via the streamer loop's
     * `while (!g_shutdown && c->state == CS_PLAYING)` and exit
     * promptly. We poll the counter; if a client is wedged in a
     * blocking syscall after grace_ms we move on anyway — the
     * thread will harmlessly run to completion later (it's
     * detached) but ring_destroy below may pull the rug out from
     * under it. In practice this never happens because all
     * blocking I/O in serve_client uses short timeouts. */
    int grace_ms = 2000;
    while (grace_ms > 0) {
        pthread_mutex_lock(&g_client_mtx);
        int n = g_client_count;
        pthread_mutex_unlock(&g_client_mtx);
        if (n == 0) break;
        usleep(50 * 1000);
        grace_ms -= 50;
    }
    if (grace_ms <= 0) {
        pthread_mutex_lock(&g_client_mtx);
        int n = g_client_count;
        pthread_mutex_unlock(&g_client_mtx);
        if (n > 0) {
            fprintf(stderr,
                "[rtsp] shutdown: %d client(s) still active after grace, "
                "forcing\n", n);
        }
    }

    for (int i = 0; i < RTSP_MAX_STREAMS; i++)
        ring_destroy(&g_rings[i]);
    fprintf(stderr, "[rtsp] shutdown complete\n");
}

/* ====================================================================== */
/* Public stats accessor used by the HTTP /api/stats endpoint.            */
/* Single-client policy means this is 0 or 1, but exposing it as a count */
/* keeps the API future-proof for when we lift that limit.               */
/* ====================================================================== */
int rtsp_server_active_clients(void)
{
    int n;
    pthread_mutex_lock(&g_client_mtx);
    n = g_client_count;
    pthread_mutex_unlock(&g_client_mtx);
    return n;
}
