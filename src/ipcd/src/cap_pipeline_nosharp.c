/*
 * proxy_capture.c — embedded camera capture + RTSP server for Anyka AK39EV330.
 *
 * Replaces the stock anyka_ipc binary. Captures from VI (sc2331 sensor),
 * encodes via VENC (HEVC main + H264 sub), and serves both streams via
 * an embedded RTSP server (rtsp_server.c) on port 8554.
 *
 * Connect with: rtsp://<camera-ip>:8554/main  (1080p HEVC)
 *               rtsp://<camera-ip>:8554/sub   (360p H.264)
 *
 * v330 SDK API used (reverse-engineered from libapp_video.so / libplat_vi.so /
 * libmpi_venc.so / libplat_mem.so on the running camera firmware). The
 * function prototypes declared at the top come from Ghidra decompilation;
 * they are NOT in any official header.
 *
 * Build with the toolchain anyka_uclibc_gcc and link with the .so found
 * on the camera. See accompanying Makefile.
 *
 * Sequence (replicating the firmware's hal_video_init exactly, observed
 * from the original anyka_ipc debug log):
 *   1) ak_mem_init(0)
 *   2) ak_mem_dma_pool_create(0xd, ...)         // VENC pool
 *      ak_mem_dma_pool_create(0x07, ...)        // VI pool
 *   3) ak_mem_dma_pool_activate()              // -> "Get sys reserved memory"
 *   4) ak_vi_open(0)
 *   5) ak_vi_load_sensor_cfg(0, "/etc/config/isp_..._15fps.conf")
 *   6) ak_vi_get_sensor_resolution(0, &res)     // auto-detect sensor WxH
 *   7) ak_vi_set_dev_attr(0, &da)               // crop = sensor area
 *   8) ak_vi_set_chn_attr(0, ...) and (1, ...)
 *   9) ak_vi_enable_dev(0)                      // triggers vi_set_capture_on
 *  10) ak_vi_enable_chn(0) and (1)
 *  11) ak_venc_open(&encode_param, &venc_id)    // writes venc_id 0..7
 *  12) Build src_chn { type=7,  chn=<vi_chn_id> }
 *      Build dst_chn { type=13, chn=<venc_id>   }
 *      ak_app_video_bind_chn(&src, &dst, &bp)
 *      ak_app_video_set_dst_chn_active(&dst, 1)
 *  13) loop:
 *        ak_app_video_venc_get_stream(&dst, &vs)
 *        parse Annex-B → NAL list
 *        rtsp_server_push_au(stream_idx, ts_ms, nals, lens, count, kind)
 *        ak_venc_release_stream(venc_id, &vs)
 *
 * !!! IMPORTANT — DMA pool path !!!
 * We BYPASS the libapp_mem_ex.so high-level API
 * (ak_app_mem_ex_dma_pool_set_vi_policy, set_venc_policy, dma_pool_activate)
 * because that path pre-reserves a small fixed set of buffers via
 * ak_mem_dma_pool_create_reserved_obj — and the AKV encoder's runtime
 * DMA requests do not exact-match those reservations, causing
 * "No enough space in the pool" failures.
 *
 * Instead we use the low-level libplat_mem.so API directly, which is
 * what hal_video_init in the firmware actually does (no set_*_policy
 * lines appear in its debug log). The 20 MB pool is created as a
 * single free block, and AKV_Encoder_Open allocates from it naturally.
 */

/* _GNU_SOURCE is set by the Makefile's -D_GNU_SOURCE; defining it
 * here too triggers a redefinition warning on gcc. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>
#include <stdint.h>
#include <time.h>
#include <getopt.h>
#include <sys/ioctl.h>
#include <linux/watchdog.h>

#include "ipcd.h"

/* ====================================================================== */
/* Anyka SDK v330 — types & function prototypes (reverse-engineered)      */
/* ====================================================================== */

/* From ak_global.h (unchanged across versions): */
struct video_stream {
    unsigned char     *data;
    unsigned int       len;
    unsigned long long ts;
    unsigned long      seq_no;
    int                frame_type;   /* 0=P, 1=I, 2=B, 3=PI */
};

/* encode_param — 60 bytes (0x3c). Layout DEFINITIVELY confirmed by
 * decompiling venc_check_and_format_param in libmpi_venc.so.
 *
 * The decompiler reads param_1 as a (ushort *), so its indices are in
 * half-words. Conversion to byte offsets:
 *
 *   *param_1                  -> [0x00] width        (u16)
 *   param_1[1]                -> [0x02] height       (u16)
 *   param_1[2]                -> [0x04] fps          (u16)
 *   param_1[3]                -> [0x06] goplen       (u16)
 *   param_1[4]                -> [0x08] target_kbps  (u16)
 *   param_1[5]                -> [0x0a] max_kbps     (u16)
 *   *(uint *)(param_1 + 6)    -> [0x0c] profile      (u32)
 *   *(uint *)(param_1 + 8)    -> [0x10] br_mode      (u32)
 *   param_1[10]               -> [0x14] initial_qp   (u16)
 *   param_1[0xb]              -> [0x16] minqp        (u16)
 *   param_1[0xc]              -> [0x18] maxqp        (u16)
 *   *(uint *)(param_1 + 0xe)  -> [0x1c] jpeg_qlevel  (u32) ← validated <4 ALWAYS
 *   *(uint *)(param_1 + 0x10) -> [0x20] chroma_mode  (u32)
 *   *(uint *)(param_1 + 0x12) -> [0x24] enc_out_type (u32)
 *   *(uint *)(param_1 + 0x14) -> [0x28] reserved_0x28 (u32, copied to AKV)
 *   param_1[0x16]             -> [0x2c] enc_level    (u16) ← in [10..50]
 *   *(uint *)(param_1 + 0x18) -> [0x30] smart_mode   (u32)
 *   param_1[0x1a]             -> [0x34] smart_goplen
 *   param_1[0x1b]             -> [0x36] smart_quality
 *   param_1[0x1c]             -> [0x38] smart_static_value
 *
 * Earlier guesses had jpeg_qlevel (at 0x1c) labeled as enc_level, and
 * enc_level (at 0x2c) labeled as num_slices. The Ghidra decompile
 * corrected these. */
struct encode_param {
    uint16_t width;             /* 0x00 */
    uint16_t height;            /* 0x02 */
    uint16_t fps;               /* 0x04 */
    uint16_t goplen;            /* 0x06 */
    uint16_t target_kbps;       /* 0x08 */
    uint16_t max_kbps;          /* 0x0a */
    int32_t  profile;           /* 0x0c */
    int32_t  br_mode;           /* 0x10 — 0=CBR, 1=VBR (others rejected) */
    uint16_t initial_qp;        /* 0x14 — <= 100 and in [minqp..maxqp] */
    uint16_t minqp;             /* 0x16 */
    uint16_t maxqp;             /* 0x18 — non-jpeg: <= 51 */
    uint16_t _pad_1a;           /* 0x1a */
    int32_t  jpeg_qlevel;       /* 0x1c — must be < 4 even for non-JPEG! */
    int32_t  chroma_mode;       /* 0x20 — 0=MONO, 1=YUV420 (4:2:0),
                                   2=4:2:2. Validated <= 2. The firmware
                                   uses 1 (CHROMA_4_2_0) for color. */
    int32_t  enc_out_type;      /* 0x24 — 0=H264, 1=JPEG, 2=H265 */
    int32_t  _reserved_28;      /* 0x28 — copied verbatim to AKV[0xb] */
    uint16_t enc_level;         /* 0x2c — must be in [10..50] */
    uint16_t _pad_2e;           /* 0x2e */
    int32_t  smart_mode;        /* 0x30 — must be < 4 */
    uint16_t smart_goplen;      /* 0x34 — < 1001 */
    uint16_t smart_quality;     /* 0x36 — < 101 */
    uint16_t smart_static_value;/* 0x38 — < 769 */
    uint16_t _pad_3a;           /* 0x3a */
};
_Static_assert(sizeof(struct encode_param) == 0x3c,
               "encode_param must be exactly 60 bytes");

/* enum bitrate_ctrl_mode (encode_param.br_mode, validated <= 3) */
#define BR_MODE_CBR         0
#define BR_MODE_VBR         1
/* others reserved (2,3) */

/* encode_param.enc_out_type (validated <= 2) */
#define H264_ENC_TYPE       0
#define MJPEG_ENC_TYPE      1
#define HEVC_ENC_TYPE       2

/* encode_param.profile — simple integer in input.
 *
 * The function venc_check_and_format_param dispatches on this value via
 * a branch table at 0x2ea8 (for H264, range [0..3]) and translates each
 * one to a 32-bit tagged value internally. The mapping (RE'd from the
 * branch table) matches the v200 SDK header exactly:
 *
 *   For enc_out_type = H264:
 *     0 = PROFILE_MAIN        -> internal tag 0x0100004D
 *     1 = PROFILE_HIGH        -> internal tag 0x01000064
 *     2 = PROFILE_BASE        -> internal tag 0x01000042
 *     3 = PROFILE_CONSTRAINED -> internal tag 0x01000242
 *
 *   For enc_out_type = HEVC (range [4..6]):
 *     4 = HEVC_MAIN           -> internal tag 0x02000001
 *     5 = HEVC_MAIN_INTRA     -> internal tag 0x02000003
 *     6 = HEVC_MAIN_STILL     -> internal tag 0x02FA0004
 *
 *   For enc_out_type = JPEG (must be exactly 7):
 *     7 = JPEG                -> internal tag 0x04000000
 *
 * Pass the SHORT integer (0,1,2,3,4,5,6,7), NOT the tag. The earlier
 * attempt with tag-as-input failed with "profile error, not h264 profile"
 * because the input range check is `cmp r6, #3` -> bhi error. */
#define PROFILE_MAIN        0
#define PROFILE_HIGH        1
#define PROFILE_BASE        2
#define PROFILE_CONSTRAINED 3
#define PROFILE_HEVC_MAIN       4
#define PROFILE_HEVC_MAIN_INTRA 5
#define PROFILE_HEVC_MAIN_STILL 6
#define PROFILE_JPEG            7

/* The "channel handle" used as src/dst in app_video API. */
struct ak_chn {
    int type;     /* 7=VI src, 0xd=VENC dst */
    int chn_id;   /* 0=main, 1=sub */
};

/* The bind_param / chn_attr struct (8 bytes), passed to bind_chn and
 * to set_chn_attr.
 *
 * !!! IMPORTANT layout !!! — verified from Ghidra decompilation of
 * libapp_video.so v1.0.07 (functions app_video_bind_vi_venc at
 * 0x2684 and app_video_vi_stream_do_venc at 0x11f94):
 *
 *   bind_vi_venc does:    memcpy(obj + 8, &bp, 8);
 *   stream_do_venc does:  rate     = obj[+0x08]   (4 bytes)
 *                         depth_lim= obj[+0x0c]   (4 bytes)
 *
 * Therefore the FIRST u32 in this struct must be frame_rate and the
 * SECOND u32 must be frame_depth — NOT the other way round. Earlier
 * the order was reversed which made app_video_vi_stream_do_venc
 * compute interval = 1000 / frame_depth — with frame_depth=8 that
 * gives 125 ms = 8 fps, which is exactly the rate cap we observed
 * even though the sensor was running at 15 fps. Swapping the fields
 * makes app_video read frame_rate from the first slot (=15) and
 * compute interval = 1000/15 = 66 ms = 15 fps.
 *
 * - frame_rate : 1..60 plain int, OR (num<<16)|den. The check is
 *                `if (rate < 1) skip; num = rate>>16; if(num==0) num=1;
 *                 interval_ms = num*1000 / (rate & 0xffff)`.
 *                Plain int N is decoded as num=1, den=N → 1000/N ms.
 * - frame_depth: max queued encoded frames before the source thread
 *                drops with "frame list reached frame_depth limit". */
struct ak_chn_attr {
    int frame_rate;
    int frame_depth;
};

/* libapp_mem_ex.so — DMA pool policy structs (RE'd).
 *
 * vi_policy is 48 bytes (memcpy size 0x30). The CORRECT layout has been
 * deduced from the Ghidra decompilation of:
 *   - ak_app_mem_ex_dma_pool_set_vi_policy: it only validates two
 *     fields, at offsets 0x10 and 0x1c, both required >= 2. The error
 *     messages call them "main_frame_depth" and "sub_frame_depth", but
 *     that labeling is misleading — see below.
 *   - ak_app_mem_ex_dma_pool_activate: this is what computes the actual
 *     pool size, and its arithmetic reveals the true layout:
 *
 *       iVar1 = pol[0x24/4] * pol[0x20/4];                 // raw_w * raw_h
 *       iVar8 = (pol[0]*pol[1]*3/2) * 5;                   // main: FIXED ×5
 *       ...
 *       total = pol[0x28/4]   * raw_size_capped              // [40] * raw
 *             + pol[0x1c/4]   * (sub_w*sub_h*3/2 + 0x800)    // [28] * sub
 *             + pol[0x10/4]   * (third_w*third_h*3/2+0x800)  // [16] * third
 *             + (main_size >> 2) + 0x40;
 *
 *     So the multipliers (frame depths) live at offsets 0x10, 0x1c, 0x28,
 *     and the dimensions immediately precede each one:
 *
 *       0x00,0x04: main_w, main_h          (multiplier is hard-coded ×5)
 *       0x08,0x0c: third_w, third_h
 *       0x10:      third_frame_depth       ← validated >= 2 (mislabeled
 *                                            "main_frame_depth" in error msg)
 *       0x14,0x18: sub_w, sub_h
 *       0x1c:      sub_frame_depth         ← validated >= 2
 *       0x20,0x24: raw_w, raw_h
 *       0x28:      raw_frame_depth
 *       0x2c:      (unused / reserved)
 *
 *     IMPORTANT: even if "third" channel is unused, third_frame_depth must
 *     still be >= 2, otherwise set_vi_policy returns 0x101. The cost is
 *     negligible: 2 * (0*0*3/2 + 0x800) = 0x1000 bytes.
 */
struct vi_policy {
    int main_w;             /* 0x00 */
    int main_h;             /* 0x04 */
    int third_w;            /* 0x08 */
    int third_h;            /* 0x0c */
    int third_frame_depth;  /* 0x10 — must be >= 2 (validated) */
    int sub_w;              /* 0x14 */
    int sub_h;              /* 0x18 */
    int sub_frame_depth;    /* 0x1c — must be >= 2 (validated) */
    int raw_w;              /* 0x20 */
    int raw_h;              /* 0x24 */
    int raw_frame_depth;    /* 0x28 */
    int reserved_2c;        /* 0x2c */
};

/* venc_policy is 28 bytes (7 words) read by set_venc_policy. */
struct venc_policy {
    int chn_id;             /* [0]  must be < 2 (0=main, 1=sub) */
    int width;              /* [1] */
    int height;             /* [2] */
    int type;               /* [3]  0=H264, 1=JPEG, 2=H265 (must be < 3) */
    int qp;                 /* [4]  qp/profile-related */
    int kbps;               /* [5] */
    int profile;            /* [6] */
};

/* ============================================================
 * DMA POOL — TWO ALTERNATIVE PATHS DISCOVERED VIA RE
 * ============================================================
 *
 * PATH A — high-level (libapp_mem_ex.so):
 *   set_vi_policy + set_venc_policy + dma_pool_activate
 *   Pre-reserves a fixed set of buffers via internal calls to
 *   AKV_Encoder_Get_Dma_Memory_Info + ak_mem_dma_pool_create_reserved_obj.
 *   Result: pool with N reserved obj, ZERO bytes in free list.
 *   Problem: AKV_Encoder_Open's runtime requests do not exact-match
 *   the pre-reservations, so allocations fail.
 *
 * PATH B — low-level (libplat_mem.so), which is what the FIRMWARE
 *   uses (per debug log: "open mem_dma_pool" → "Get sys reserved
 *   memory [0x1400000]" with NO intervening set_*_policy logs):
 *     ak_mem_dma_pool_create(mod_id, total_size)
 *     ak_mem_dma_pool_activate()
 *   No reserved obj. Pool has the FULL block in the free list.
 *   AKV_Encoder_Open allocates from the free pool directly.
 *
 * We use PATH B. */
extern int ak_app_mem_ex_dma_pool_set_vi_policy(const struct vi_policy *p);
extern int ak_app_mem_ex_dma_pool_set_venc_policy(const struct venc_policy *p);
extern int ak_app_mem_ex_dma_pool_activate(void);
extern int ak_app_mem_ex_dma_pool_exit(void);

/* libplat_mem.so — low-level DMA pool API (PATH B).
 *
 * Module IDs (RE'd from switch_mod_id in libplat_mem.so):
 *   0x07 = VI pool
 *   0x0d = VENC pool
 *   ... others
 *
 * ak_mem_dma_pool_create(mod_id, size_bytes):
 *   Registers a pool of `size_bytes` for module `mod_id`.
 *   Must be called BEFORE ak_mem_dma_pool_activate.
 *   Returns 0 on success.
 *
 * ak_mem_dma_pool_activate():
 *   Once all desired pools are registered via dma_pool_create,
 *   physically reserves the system memory and prints
 *   "Get sys reserved memory [0x%lx] bytes!" at level INFO.
 *   The total across all pools must fit in the reserved system
 *   region (the firmware budget appears to be 0x1400000 = 20MB).
 *
 * ak_mem_dma_pool_create_reserved_obj(mod_id, size, threshold):
 *   Carves a fixed-size buffer out of the pool. The allocator
 *   later uses these as exact-match candidates for requests.
 *   We DO NOT call this from PATH B — leaving the pool as one
 *   big free block lets AKV_Encoder_Open allocate naturally.
 *
 * ak_mem_init(0):
 *   Brings up the underlying allocator state. Required before any
 *   dma_pool_* call. */
extern int  ak_mem_init(int chip_variant);
extern void ak_mem_exit(void);
extern int  ak_mem_dma_pool_create(int mod_id, unsigned int size);
extern int  ak_mem_dma_pool_activate(void);
extern int  ak_mem_dma_pool_exit(void);
extern int  ak_mem_dma_pool_create_reserved_obj(int mod_id,
                                                 unsigned int size,
                                                 unsigned int threshold);

/* libplat_vi.so — VI device attribute (size 0x38 = 56 bytes). */
struct vi_dev_attr {
    unsigned int dev_id;       /* [0]  must equal first arg to set_dev_attr */
    unsigned int reserved1;    /* [1] */
    unsigned int reserved2;    /* [2] */
    unsigned int reserved3;    /* [3] */
    unsigned int reserved4;    /* [4] */
    int          crop_x;       /* [5]  offset 0x14 */
    int          crop_y;       /* [6]  offset 0x18 */
    int          crop_w;       /* [7]  offset 0x1c */
    int          crop_h;       /* [8]  offset 0x20 */
    unsigned int main_max_w;   /* [9]  offset 0x24 */
    unsigned int main_max_h;   /* [10] offset 0x28 */
    int          frame_rate;   /* [11] offset 0x2c — plain fps as int.
                                  Firmware passes 15 (not packed). The
                                  SDK reads it as num=fps, den=0. */
    unsigned int sub_max_w;    /* [12] offset 0x30 */
    unsigned int sub_max_h;    /* [13] offset 0x34 */
};

/* libplat_vi.so — VI channel attribute (size 0x14 = 20 bytes). */
struct vi_chn_attr {
    unsigned int chn_id;       /* [0]  must equal first arg to set_chn_attr */
    int          frame_rate;   /* [1]  plain fps as int (e.g. 15). The
                                  SDK reads it as num=fps, den=0. */
    unsigned int width;        /* [2] */
    unsigned int height;       /* [3] */
    unsigned int frame_depth;  /* [4]  must be 2, 3, or 4 */
};

/* libplat_vi.so prototypes */
extern int   ak_vi_load_sensor_cfg(unsigned int dev_id, const char *path);
extern int   ak_vi_open(unsigned int dev_id);
extern int   ak_vi_close(unsigned int dev_id);
extern int   ak_vi_enable_dev(unsigned int dev_id);
extern int   ak_vi_disable_dev(unsigned int dev_id);
extern int   ak_vi_enable_chn(unsigned int chn_id);
extern int   ak_vi_disable_chn(unsigned int chn_id);
extern int   ak_vi_get_dev_attr(unsigned int dev_id, struct vi_dev_attr *attr);
extern int   ak_vi_set_dev_attr(unsigned int dev_id, const struct vi_dev_attr *attr);

/* ak_vi_get_sensor_resolution(dev_id, &res[2])
 *
 * Pure getter — queries the sensor for its native capture resolution
 * via VIDIOC_CROPCAP, no state change. Internally calls
 * vi_dev_get_sensor_crop which logs "vi_dev_get_sensor_crop %d, ret:%d,
 * w:%u, h:%u" (visible in the firmware debug log).
 *
 * Decompiled signature (Ghidra):
 *   int ak_vi_get_sensor_resolution(uint dev_id, uint *res);
 *     res[0] = native sensor width
 *     res[1] = native sensor height
 * Returns 0 on success, 0x101 if res is NULL, 0x7000000 if dev_id >= 2,
 * 0x7000001 if device not opened. */
extern int   ak_vi_get_sensor_resolution(unsigned int dev_id, unsigned int res[2]);
extern int   ak_vi_get_chn_attr(unsigned int chn_id, struct vi_chn_attr *attr);
extern int   ak_vi_set_chn_attr(unsigned int chn_id, const struct vi_chn_attr *attr);
extern int   ak_print_set_level(int level, unsigned int param_2);
extern int   ak_print_set_syslog_level(unsigned int param_1,int param_2);
extern int   ak_print(int param_1,char *param_2,...);

/* libplat_vpss.so — fps-level / exposure-cap control.
 *
 * The ISP keeps a "fps configuration table" with up to 3 light levels
 * (high / mid / low). Each level has a fps and a max_exp_time. When
 * the AE algorithm decides current scene gain crosses a threshold,
 * the ISP calls change_sensor_fps to drop to the next level — and
 * if max_exp_time on the current level exceeds 1/fps in sensor lines
 * the sensor extends VTS to fit, dropping fps.
 *
 * On our camera the config file ships max_exp_time=4676 with fps=15.
 * 4676 sensor lines × ~28us = ~131ms = 7.5 fps, so the sensor sits
 * at ~8 fps in normal lighting because AE always exhausts the budget.
 *
 * ak_vpss_get_fps_level / ak_vpss_set_fps_level read/write that table
 * in-memory (NOT the .conf file — runtime only). Layout (9 u32):
 *   [0] high_light_fps
 *   [1] high_light_max_exp_time   ← cap me to force fps stable
 *   [2] lower_light_gain (threshold: drop level if gain >= this)
 *   [3] mid_light_fps             (0 if 2-level config)
 *   [4] mid_light_max_exp_time    (0 if 2-level config)
 *   [5] mid_to_low_gain           (0 if 2-level config)
 *   [6] low_light_fps
 *   [7] low_light_max_exp_time    ← cap me too
 *   [8] higher_light_gain (threshold: raise level if gain <= this)
 *
 * Decompiled signatures (libplat_vpss.so v1.3.07):
 *   int ak_vpss_get_fps_level(int dev_id, uint32_t table[9]);
 *   int ak_vpss_set_fps_level(int dev_id, const uint32_t table[9]);
 * Both return 0 on success. */
extern int   ak_vpss_get_fps_level(int dev_id, uint32_t table[9]);
extern int   ak_vpss_set_fps_level(int dev_id, const uint32_t table[9]);

/* libplat_isp_sdk.so — direct sensor framerate control.
 *
 * The ISP SDK exposes Ak_ISP_Set_Sensor_Fps which forwards the new
 * fps value to the kernel sensor driver via I2C, telling it to
 * adjust VTS so the sensor outputs the requested rate.
 *
 * Why we need it: ak_vi_load_sensor_cfg loads the ISP parameters
 * but DOES NOT call set_sensor_fps. The original firmware's debug
 * log shows three explicit "[isp_set_sensor_fps:2633] set sensor
 * fps: 15" calls during startup which we don't trigger. Without
 * them the sensor sits at whatever its driver default is — on this
 * SC2331 module it's apparently ~8 fps, not the 15 the cfg file
 * declares. (vpss has ak_vpss_change_sensor_fps but it returns
 * early when current == target, so it can't be used to push a
 * fresh value.)
 *
 * Decompiled signature (libplat_isp_sdk v7.0.01):
 *   int Ak_ISP_Set_Sensor_Fps(int dev_id, int *fps);
 * Returns 0 on success. */
extern int   Ak_ISP_Set_Sensor_Fps(int dev_id, int *fps);
extern int   Ak_ISP_Get_Sensor_Fps(int dev_id, int *fps);
struct isp_flip_mirror_info { int flip_en; int mirror_en; };
extern int   isp_set_flip_mirror(struct isp_flip_mirror_info *info);
extern int   ak_vpss_get_sensor_fps(int dev_id, int *fps);

/* libmpi_venc.so */
extern int   ak_venc_open(const struct encode_param *param, int *out_handle_id);
extern int   ak_venc_get_attr(int handle_id, struct encode_param *param);
extern int   ak_venc_set_attr(int handle_id, const struct encode_param *param);

/* libapp_video.so */
extern int   ak_app_video_bind_chn(struct ak_chn *src, struct ak_chn *dst,
                                    const struct ak_chn_attr *bp);
extern int   ak_app_video_unbind_chn(struct ak_chn *src, struct ak_chn *dst);
extern int   ak_app_video_set_chn_attr(struct ak_chn *dst,
                                        const struct ak_chn_attr *attr);
extern int   ak_app_video_set_dst_chn_active(struct ak_chn *dst,
                                              unsigned int active);
extern int   ak_app_video_venc_get_stream(struct ak_chn *dst,
                                           struct video_stream *vs);

/* ====================================================================== */
/* Configuration                                                          */
/* ====================================================================== */

#define DEFAULT_SENSOR_CONFIG  "/etc/config/isp_f37p_mipi_1lane_h3b.conf"
#define DEFAULT_FPS              15
/* GOP length in seconds. We use 1 second (= one IDR every ~8 frames at
 * effective framerate) instead of the original 2 seconds, because VLC
 * has known issues with HEVC streams at low framerates ("buffer
 * deadlock prevented" + "More than 11 late frames"). More frequent
 * IDRs give VLC more sync points to recover from drift, shorten the
 * P-frame dependency chains, and let it resync faster when packets
 * are lost. Costs ~25-40% extra bandwidth (I-frames >> P-frames) but
 * at 8 fps that's still well under our configured kbps cap. */
#define DEFAULT_GOP_SEC           1
#define DEFAULT_MIN_QP           20
#define DEFAULT_MAX_QP           42

#define DEFAULT_MAIN_W         1920
#define DEFAULT_MAIN_H         1080
#define DEFAULT_MAIN_KBPS      2000

#define DEFAULT_SUB_W           640
#define DEFAULT_SUB_H           360
#define DEFAULT_SUB_KBPS        300

#define DEFAULT_FRAME_DEPTH       8

#define WDT_DEVICE             "/dev/watchdog"

#define DEFAULT_RTSP_PORT      8554

/* ====================================================================== */
/* Globals                                                                */
/* ====================================================================== */

/* Codec choice for each stream — same values as in rtsp_server.h
 * (RTSP_CODEC_H264 / RTSP_CODEC_H265) but kept local to avoid leaking
 * the rtsp header into our config layer. */
enum codec_kind {
    CODEC_H264 = 1,
    CODEC_H265 = 2,
};

struct cfg {
    const char     *sensor_config;
    int             rtsp_port;
    int             enable_main;
    int             enable_sub;
    int             feed_watchdog;
    enum codec_kind main_codec;
    enum codec_kind sub_codec;
    /* Cap the maximum exposure time (in sensor lines) on every fps
     * level of the ISP fps_cfg table. The ISP defaults this to 4676
     * lines (~131ms) on our SC2331 sensor + isp_..._15fps.conf, which
     * makes the sensor extend VTS and run at ~8 fps even in bright
     * light. Capping to 2152 lines (~60ms) keeps the sensor at 15 fps
     * stable; AE compensates with more analog gain (slightly noisier
     * picture in low light). 0 = leave the table as the ISP cfg
     * file set it. */
    unsigned int    max_exp_lines;
};

static struct cfg G_cfg = {
    .sensor_config = DEFAULT_SENSOR_CONFIG,
    .rtsp_port     = DEFAULT_RTSP_PORT,
    .enable_main   = 1,
    .enable_sub    = 1,
    .feed_watchdog = 1,
    /* Default to H.264 on both streams. HEVC is supported on main but
     * is opt-in via --main-codec h265 because VLC has known bugs
     * playing back HEVC RTSP streams from embedded cameras (see the
     * comment in stream_worker). H.264 works in every client we've
     * tested. */
    .main_codec    = CODEC_H265,
    .sub_codec     = CODEC_H264,
    .max_exp_lines = 2152,
};

/* Renamed from g_run to cap_run when integrating into ipcd:
 * netmgr (main.c) owns the global g_run, this module needs its own
 * cancellation flag that capture_stop() flips. */
static volatile sig_atomic_t cap_run = 1;

struct stream_ctx {
    int                idx;          /* 0=main, 1=sub: our wire index */
    int                vi_chn_id;    /* VI channel id (typically 0=main, 1=sub) */
    int                venc_id;      /* assigned by ak_venc_open() */
    struct ak_chn      src;          /* { type=7, chn_id=vi_chn_id } */
    struct ak_chn      dst;          /* { type=13, chn_id=venc_id } */
    int                width, height;
    int                fps, gop_sec;
    int                kbps;
    enum codec_kind    codec;        /* CODEC_H264 or CODEC_H265 */
    int                bound;
    int                active;
    pthread_t          tid;
    int                started;
};

static struct stream_ctx g_streams[2];

/* ====================================================================== */
/* Signals                                                                */
/* ====================================================================== */

/* Note: install_signals() and on_signal() were removed when this
 * module was integrated into ipcd. netmgr (main.c) owns SIGTERM /
 * SIGINT and flips cap_run via capture_stop(). */

/* ====================================================================== */
/* Watchdog feeder                                                        */
/* ====================================================================== */

static int       g_wdt_fd      = -1;
static pthread_t g_wdt_tid;
static int       g_wdt_started = 0;

static void *wdt_thread(void *arg)
{
    (void)arg;
    int timeout = 30;
    if (ioctl(g_wdt_fd, WDIOC_GETTIMEOUT, &timeout) < 0) timeout = 30;
    int interval = timeout / 3;
    if (interval < 1) interval = 1;
    fprintf(stderr, "[wdt] feeding every %ds (timeout %ds)\n", interval, timeout);
    while (cap_run) {
        if (ioctl(g_wdt_fd, WDIOC_KEEPALIVE, 0) < 0)
            fprintf(stderr, "[wdt] keepalive: %s\n", strerror(errno));
        for (int i = 0; i < interval && cap_run; i++) sleep(1);
    }
    if (write(g_wdt_fd, "V", 1) != 1)
        fprintf(stderr, "[wdt] magic close write failed: %s\n", strerror(errno));
    close(g_wdt_fd);
    g_wdt_fd = -1;
    return NULL;
}

static void wdt_start(void)
{
    if (!G_cfg.feed_watchdog) return;
    g_wdt_fd = open(WDT_DEVICE, O_WRONLY);
    if (g_wdt_fd < 0) {
        fprintf(stderr, "[wdt] open(%s): %s — continuing without\n",
                WDT_DEVICE, strerror(errno));
        return;
    }
    if (pthread_create(&g_wdt_tid, NULL, wdt_thread, NULL) != 0) {
        close(g_wdt_fd);
        g_wdt_fd = -1;
        return;
    }
    g_wdt_started = 1;
}


/* ====================================================================== */
/* Stream worker                                                          */
/* ====================================================================== */

static void *stream_worker(void *arg)
{
    struct stream_ctx *s = (struct stream_ctx *)arg;
    fprintf(stderr, "[s%d] start (%dx%d, %dfps, gop=%ds, %dkbps, vi_chn=%d)\n",
            s->idx, s->width, s->height, s->fps, s->gop_sec, s->kbps, s->vi_chn_id);

    /* 1) Open VENC channel.
     *
     *    !!! IMPORTANT — DMA pool sizing !!!
     *    The AKV encoder computes its DMA buffer requirements at
     *    runtime using a formula involving (encoder_type, w, h, kbps,
     *    minqp, maxqp). We must pass values that match the policy in
     *    mem_pool_init() so that the runtime requests match the
     *    reserved-object thresholds exactly.
     *
     *    Concretely, the firmware (whose DMA layout we matched)
     *    uses these exact values for its main encoder:
     *      HEVC main 1920x1080 @ 500 kbps, qp=25..50, initial_qp=37
     *      H264 sub  640x360   @ 500 kbps, qp=25..50, initial_qp=37
     *    Any deviation from these triggers "No enough space in pool". */
    struct encode_param ep;
    memset(&ep, 0, sizeof(ep));
    ep.width        = (uint16_t)s->width;
    ep.height       = (uint16_t)s->height;
    ep.fps          = (uint16_t)s->fps;
    ep.goplen       = (uint16_t)(s->fps * s->gop_sec);
    /* Bitrate & QP — these are now driven by --main-kbps / --sub-kbps.
     *
     * Historical note: in earlier iterations we used libapp_mem_ex.so's
     * pre-reserved DMA pool path, which required encode_param values to
     * EXACTLY match the policy registered in mem_pool_init() — any
     * deviation triggered "No enough space in pool" failures. We now
     * use the low-level libplat_mem.so API with a single big free pool,
     * so AKV_Encoder_Open allocates dynamically and we are free to use
     * any sensible bitrate / QP combination. */
    ep.target_kbps  = (uint16_t)s->kbps;
    ep.max_kbps     = (uint16_t)s->kbps;       /* CBR: target == max */
    ep.br_mode      = BR_MODE_CBR;
    /* QP range — must be tight enough that the rate controller can
     * actually hit the target bitrate. With minqp too low (e.g. 10),
     * "easy" scenes generate huge frames that ignore target_kbps,
     * blowing the bitrate by 10x+ on I-frames.
     *
     * Values from __factory_cfg.ini, which the firmware uses in
     * production: main qp [38..49], sub qp [30..45]. */
    if (s->idx == 0) {
        ep.initial_qp = 40;
        ep.minqp      = 38;
        ep.maxqp      = 49;
    } else {
        ep.initial_qp = 35;
        ep.minqp      = 30;
        ep.maxqp      = 45;
    }
    ep.jpeg_qlevel  = 0;                      /* validated < 4 ALWAYS */
    ep.chroma_mode  = 1;                      /* CHROMA_4_2_0 (YUV420 color).
                                                 0 produces MONO (B/W) output! */
    ep.enc_level    = 30;                     /* must be in [10..50] */
    ep.smart_mode   = 0;                      /* DISABLE */
    ep.smart_goplen = 100;
    ep.smart_quality= 50;
    ep.smart_static_value = 0;

    /* Encoder type & profile based on the codec configured for this
     * stream. Defaults via CLI to H.264 for both streams; HEVC can be
     * enabled on main with --main-codec h265.
     *
     * NOTE: VLC has known bugs handling HEVC RTSP streams from
     * embedded cameras (manifest: "buffer deadlock prevented" +
     * "More than 11 late frames" → "more than 5 seconds of late
     * video"). The bug persists with both UDP and TCP transport,
     * with HW decoding disabled, and with VUI timing stripped from
     * the SPS. The only client-side workaround is
     * --network-caching=3000. ffplay/ffmpeg/mpv have no such issue.
     *
     * H.264 is the safe default. HEVC is ~25-30% more efficient but
     * pay attention to which client(s) you use. */
    if (s->codec == CODEC_H265) {
        ep.enc_out_type = HEVC_ENC_TYPE;       /* 2 */
        ep.profile      = PROFILE_HEVC_MAIN;   /* 4 = HEVC main */
    } else {
        ep.enc_out_type = H264_ENC_TYPE;       /* 0 */
        ep.profile      = PROFILE_MAIN;        /* 0 = H.264 main */
    }

    int rc = ak_venc_open(&ep, &s->venc_id);
    if (rc != 0) {
        fprintf(stderr, "[s%d] ak_venc_open failed: 0x%x\n", s->idx, rc);
        return NULL;
    }
    fprintf(stderr, "[s%d] ak_venc_open OK -> venc_id=%d\n", s->idx, s->venc_id);

    /* 2) Build channel handles */
    s->src.type   = 7;            /* VI */
    s->src.chn_id = s->vi_chn_id;
    s->dst.type   = 0xd;          /* VENC */
    s->dst.chn_id = s->venc_id;

    /* 3) Bind src (VI) -> dst (VENC).
     *
     * frame_rate: the firmware passes a plain integer (visible in the
     * debug log as "frame_rate[15] frame_num[15], frame_den[0],
     * interval[66]") — i.e. 15 not 0xF0001. The packed (num<<16)|den
     * form makes app_video compute interval=125ms = 8 fps; plain int
     * matches what set_chn_attr / set_dev_attr already use and gives
     * interval=66ms = 15 fps. */
    struct ak_chn_attr bp = {
        .frame_depth = DEFAULT_FRAME_DEPTH,
        .frame_rate  = s->fps
    };
    rc = ak_app_video_bind_chn(&s->src, &s->dst, &bp);
    if (rc != 0) {
        fprintf(stderr, "[s%d] ak_app_video_bind_chn failed: 0x%x\n", s->idx, rc);
        ak_venc_close(s->venc_id);
        return NULL;
    }
    s->bound = 1;
    fprintf(stderr, "[s%d] bind OK\n", s->idx);

    /* 4) Activate */
    rc = ak_app_video_set_dst_chn_active(&s->dst, 1);
    if (rc != 0) {
        fprintf(stderr, "[s%d] set_dst_chn_active(1) failed: 0x%x\n", s->idx, rc);
        ak_app_video_unbind_chn(&s->src, &s->dst);
        ak_venc_close(s->venc_id);
        return NULL;
    }
    s->active = 1;
    fprintf(stderr, "[s%d] active, capturing\n", s->idx);

    /* 5) Pull loop. The encoder produces Annex-B framed bitstream
     *    (i.e. NAL units separated by start codes 00 00 00 01 or
     *    00 00 01). We parse each VENC output buffer into a list of
     *    NAL pointers + lengths, then push that as one Access Unit
     *    into the RTSP server's per-stream ring buffer.
     *
     *    Telemetry kept minimal — RTSP server has its own client-side
     *    metrics. We log throughput every 5s. */
    uint64_t total_bytes   = 0;
    uint32_t total_frames  = 0;
    uint32_t keyframes     = 0;
    uint32_t push_fails    = 0;
    uint32_t empty_polls   = 0;
    uint32_t max_empty     = 0;
    uint32_t max_frame_len = 0;
    time_t   stat_t = time(NULL);

    /* Buffers reused per-iteration to avoid alloc/free in the hot loop.
     * 16 NALs per AU is plenty: typical AKV output is 1 SPS + 1 PPS +
     * (1 VPS for HEVC) + 1 VCL = 3-4 NALs per IDR, 1 NAL per P. */
    const uint8_t *nal_ptrs[16];
    size_t         nal_lens[16];

    while (cap_run) {
        struct video_stream vs;
        memset(&vs, 0, sizeof(vs));

        rc = ak_app_video_venc_get_stream(&s->dst, &vs);
        if (rc == 0 && vs.data && vs.len > 0) {
            empty_polls = 0;

            /* --- Parse Annex-B into NAL list ---
             *
             * Walk vs.data looking for start codes (00 00 00 01 or
             * 00 00 01). NAL bodies are everything between consecutive
             * start codes (or between the last start code and end of
             * buffer). We just store pointers into vs.data — no copy
             * here; rtsp_server_push_au() will copy. */
            int nal_count = 0;
            size_t i = 0, n = vs.len;
            const uint8_t *buf = vs.data;
            const uint8_t *cur_nal_start = NULL;
            while (i + 3 < n) {
                int sc_len = 0;
                if (buf[i] == 0 && buf[i+1] == 0) {
                    if (buf[i+2] == 1) sc_len = 3;
                    else if (buf[i+2] == 0 && buf[i+3] == 1) sc_len = 4;
                }
                if (sc_len > 0) {
                    if (cur_nal_start) {
                        size_t L = (buf + i) - cur_nal_start;
                        if (L > 0 && nal_count < 16) {
                            nal_ptrs[nal_count] = cur_nal_start;
                            nal_lens[nal_count] = L;
                            nal_count++;
                        }
                    }
                    i += sc_len;
                    cur_nal_start = buf + i;
                } else {
                    i++;
                }
            }
            /* Last NAL: from cur_nal_start to end of buffer. */
            if (cur_nal_start && nal_count < 16) {
                size_t L = (buf + n) - cur_nal_start;
                if (L > 0) {
                    nal_ptrs[nal_count] = cur_nal_start;
                    nal_lens[nal_count] = L;
                    nal_count++;
                }
            }

            if (nal_count > 0) {
                /* Frame type 1 = I (H264) or 3 = PI (HEVC IDR per
                 * ak_global.h enum) — both are IDR boundaries. */
                enum rtsp_au_kind kind =
                    (vs.frame_type == 1 || vs.frame_type == 3)
                    ? RTSP_AU_IDR : RTSP_AU_NORMAL;

                int pr = rtsp_server_push_au(s->idx,
                                              vs.ts,
                                              nal_ptrs, nal_lens,
                                              nal_count, kind);
                if (pr != 0) push_fails++;

                /* Stats: one entry per frame (AU). is_keyframe drives
                 * the GOP-cadence sparkline coloring on the UI. */
                stats_record_frame(s->idx, (uint32_t)vs.len,
                                   kind == RTSP_AU_IDR,
                                   pr != 0);
            }

            total_bytes  += vs.len;
            total_frames += 1;
            if (vs.frame_type == 1 || vs.frame_type == 3) keyframes++;
            if (vs.len > max_frame_len) max_frame_len = vs.len;
            ak_venc_release_stream(s->venc_id, &vs);
        } else {
            /* No frame ready. */
            empty_polls++;
            if (empty_polls > max_empty) max_empty = empty_polls;
            usleep(10 * 1000);
        }

        /* periodic stats every 5s */
        time_t now = time(NULL);
        if (now - stat_t >= 5) {
            fprintf(stderr,
                "[s%d] %us: %u f (%u key), %llu KB, "
                "max_frame=%uB, push_fails=%u, max_empty=%u\n",
                s->idx, (unsigned)(now - stat_t),
                total_frames, keyframes,
                (unsigned long long)(total_bytes / 1024),
                max_frame_len, push_fails, max_empty);
            total_bytes  = 0;
            total_frames = 0;
            keyframes    = 0;
            push_fails   = 0;
            max_empty    = 0;
            max_frame_len = 0;
            stat_t = now;
        }
    }

    /* Shutdown */
    fprintf(stderr, "[s%d] shutting down\n", s->idx);
    ak_app_video_set_dst_chn_active(&s->dst, 0);
    s->active = 0;
    ak_app_video_unbind_chn(&s->src, &s->dst);
    s->bound = 0;
    ak_venc_close(s->venc_id);
    return NULL;
}

/* ====================================================================== */
/* VI init/deinit (device-level)                                          */
/* ====================================================================== */

static int g_vi_dev_opened  = 0;
static int g_vi_dev_enabled  = 0;
static int g_vi_chn_main_enabled = 0;
static int g_vi_chn_sub_enabled  = 0;

static int mem_pool_init(void)
{
    int rc;

    /* The firmware's hal_video_init produces just two memory log lines:
     *   "open mem_dma_pool"
     *   "[MEMORY] Get sys reserved memory [0x1400000] bytes!"
     * No set_vi_policy, no set_venc_policy, no reserved obj logs.
     *
     * That means the firmware uses the LOW-LEVEL libplat_mem.so API
     * directly, registering one big VENC pool (0x1400000 = 20MB) and
     * activating it. AKV_Encoder_Open then allocates from this pool's
     * free list — no exact-match-threshold dance.
     *
     * We do the same. */
    fprintf(stderr, "[mem] ak_mem_init(0)\n");
    rc = ak_mem_init(0);
    if (rc != 0) {
        fprintf(stderr, "[mem] ak_mem_init failed: 0x%x\n", rc);
        return -1;
    }

    /* Register VENC pool (mod_id 0xd).
     *
     * Total system DMA budget = 0x1400000 = 20 MB
     * (firmware log: "Get sys reserved memory [0x1400000]"). We split
     * it between VENC and VI pools:
     *   VENC: 0x900000 =  9 MB — covers HEVC 1080p ref frames
     *                            (~3.4 MB ×2 ≈ 7 MB) + stream buffers
     *                            (512 KB main, 86 KB sub) + scratch.
     *   VI:   0xB00000 = 11 MB — covers 3DNR (~3.7 MB) + main capture
     *                            buffers (3 MB ×2 = 6 MB, with
     *                            frame_depth=2) + sub buffers (~700 KB).
     *   ---
     *   total: 0x1400000 = 20 MB. */
    fprintf(stderr, "[mem] ak_mem_dma_pool_create(0xd, 0x900000)    # 9MB VENC pool\n");
    rc = ak_mem_dma_pool_create(0xd, 0x900000);
    if (rc != 0) {
        fprintf(stderr, "[mem] ak_mem_dma_pool_create(VENC) failed: 0x%x\n", rc);
        return -1;
    }

    /* Register VI pool (mod_id 0x07).
     *
     * The VI subsystem (libplat_vi.so) allocates DMA buffers for:
     *   - ISP 3D-NR working memory: 3,888,064 bytes ≈ 3.7 MB
     *     (size visible from "Alloc DMA memory, not enough system
     *     memory size:3888064" log line in earlier failure)
     *   - Capture buffers per channel:
     *       chn 0 (main 1920x1080 YUV420): 3,110,400 B ≈ 3 MB each
     *       chn 1 (sub  640x360  YUV420):    345,600 B ≈ 350 KB each
     *     With frame_depth=2 (matching firmware): 2 buffers per channel.
     *
     * Total estimate: 3.7 + 6 + 0.7 = 10.4 MB → 11 MB pool. */
    fprintf(stderr, "[mem] ak_mem_dma_pool_create(0x07, 0xB00000)   # 11MB VI pool\n");
    rc = ak_mem_dma_pool_create(0x07, 0xB00000);
    if (rc != 0) {
        fprintf(stderr, "[mem] ak_mem_dma_pool_create(VI) failed: 0x%x\n", rc);
        return -1;
    }

    fprintf(stderr, "[mem] ak_mem_dma_pool_activate()\n");
    rc = ak_mem_dma_pool_activate();
    if (rc != 0) {
        fprintf(stderr, "[mem] ak_mem_dma_pool_activate failed: 0x%x\n", rc);
        return -1;
    }
    fprintf(stderr, "[mem] dma pool ready (free)\n");

    return 0;
}

static int vi_init(void)
{
    int rc;
	
    /* 1) Open VI device 0 */
    fprintf(stderr, "[vi] ak_vi_open(0)\n");
    rc = ak_vi_open(0);
    if (rc != 0) {
        fprintf(stderr, "[vi] ak_vi_open(0) failed: 0x%x\n", rc);
        return -1;
    }
    g_vi_dev_opened = 1;

    /* 2) Load sensor cfg (sensor I2C init + ISP params) */
    fprintf(stderr, "[vi] load_sensor_cfg(0, %s)\n", G_cfg.sensor_config);
    rc = ak_vi_load_sensor_cfg(0, G_cfg.sensor_config);
    if (rc != 0) {
        fprintf(stderr, "[vi] load_sensor_cfg failed: 0x%x\n", rc);
        return -1;
    }

    /* 2.5) Cap max_exp_time on every fps level so the sensor doesn't
     * extend VTS and drop fps below the configured rate. Same block
     * also bumps the fps levels in the ISP fps_table if the user
     * requested a higher fps than the cfg file declared (e.g. the
     * shipped isp_..._15fps.conf maxes out at 15 but the SC2331
     * sensor is natively 30 fps, so --fps 30 should work too).
     *
     * See the extern declaration of ak_vpss_set_fps_level above for
     * the full background. Skip if max_exp_lines == 0 (--no-fps-cap). */
    if (G_cfg.max_exp_lines > 0) {
        uint32_t fps_table[9] = {0};
        rc = ak_vpss_get_fps_level(0, fps_table);
        if (rc != 0) {
            fprintf(stderr, "[isp] get_fps_level failed: 0x%x — "
                    "skipping fps/exposure setup\n", rc);
        } else {
            fprintf(stderr,
                "[isp] fps table before: hi=%u/%u mid=%u/%u low=%u/%u "
                "(fps/max_exp_lines)\n",
                fps_table[0], fps_table[1],
                fps_table[3], fps_table[4],
                fps_table[6], fps_table[7]);

            /* Auto-shrink max_exp_lines if it wouldn't fit in 1/fps:
             * at line_time ≈ 28us, exposure must be < 1000ms / fps
             * lines for the sensor not to extend VTS. Allow ~93%
             * margin. Without this clamp, if user sets --fps 30 with
             * default --max-exp 2152 (≈60 ms), the sensor still slows
             * to ~16 fps because 60 ms > 1/30s = 33 ms. */
            int target_fps = g_streams[0].fps;
            uint32_t safe_max_exp_lines =
                (uint32_t)(33000 / target_fps);  /* lines ≈ 1000/fps × 33 */
            if (G_cfg.max_exp_lines > safe_max_exp_lines) {
                fprintf(stderr,
                    "[isp] auto-tightening max_exp_lines from %u to %u "
                    "to fit %d fps target\n",
                    G_cfg.max_exp_lines, safe_max_exp_lines, target_fps);
                G_cfg.max_exp_lines = safe_max_exp_lines;
            }

            int changed = 0;

            /* Bump fps levels if user requested higher than ISP default */
            if (fps_table[0] < (uint32_t)target_fps) {
                fps_table[0] = target_fps; changed = 1;
            }
            if (fps_table[6] < (uint32_t)target_fps) {
                fps_table[6] = target_fps; changed = 1;
            }
            /* mid level: only touch if it was actually configured */
            if (fps_table[3] > 0 &&
                fps_table[3] < (uint32_t)target_fps) {
                fps_table[3] = target_fps; changed = 1;
            }

            /* Cap max_exp_time on each level */
            if (fps_table[1] > G_cfg.max_exp_lines) {
                fps_table[1] = G_cfg.max_exp_lines; changed = 1;
            }
            if (fps_table[4] > 0 &&
                fps_table[4] > G_cfg.max_exp_lines) {
                fps_table[4] = G_cfg.max_exp_lines; changed = 1;
            }
            if (fps_table[7] > G_cfg.max_exp_lines) {
                fps_table[7] = G_cfg.max_exp_lines; changed = 1;
            }

            if (changed) {
                rc = ak_vpss_set_fps_level(0, fps_table);
                if (rc != 0) {
                    fprintf(stderr, "[isp] set_fps_level failed: 0x%x\n",
                            rc);
                } else {
                    fprintf(stderr,
                        "[isp] fps table after:  hi=%u/%u mid=%u/%u "
                        "low=%u/%u (fps/max_exp_lines)\n",
                        fps_table[0], fps_table[1],
                        fps_table[3], fps_table[4],
                        fps_table[6], fps_table[7]);
                }
            } else {
                fprintf(stderr, "[isp] fps table already correct, "
                        "nothing to do\n");
            }
        }
    }

    /* 2.6) Force the sensor framerate explicitly.
     *
     * ak_vi_load_sensor_cfg loads ISP parameters but does NOT push a
     * sensor framerate down to the kernel driver — the firmware does
     * this separately as visible in its debug log:
     *   [isp_set_sensor_fps:2633] set sensor fps: 15
     *   [set_fps:236] set dev:0 fps:15 ok
     * Without this call the sensor sits at its driver default (which
     * on the SC2331 module here is ~8 fps despite the cfg saying 15).
     * We fix that by calling Ak_ISP_Set_Sensor_Fps directly with the
     * configured target framerate. */
    {
        int requested_fps = g_streams[0].fps;
        int current_fps = -1;
        Ak_ISP_Get_Sensor_Fps(0, &current_fps);
        fprintf(stderr, "[isp] sensor fps before: %d (target %d)\n",
                current_fps, requested_fps);
        rc = Ak_ISP_Set_Sensor_Fps(0, &requested_fps);
        if (rc != 0) {
            fprintf(stderr, "[isp] Ak_ISP_Set_Sensor_Fps(%d) failed: "
                    "0x%x — sensor will stay at default rate\n",
                    requested_fps, rc);
        } else {
            int verify = -1;
            Ak_ISP_Get_Sensor_Fps(0, &verify);
            fprintf(stderr, "[isp] sensor fps after:  %d (verify=%d)\n",
                    requested_fps, verify);
        }
    }

    /* 3) Auto-detect sensor's native resolution.
     *
     *    The firmware does this right after load_sensor_cfg (visible
     *    in the debug log as "vi_dev_get_sensor_crop ... w:1920, h:1080").
     *    Doing this lets the program adapt automatically to whatever
     *    sensor is on the board (sc2331 = 1920x1080, sc2335 = 1920x1080,
     *    imx323 = 1920x1080, etc., but with different ISP files).
     *
     *    We then use the sensor's native resolution as the upper bound
     *    for crop_w/h and main_max_w/h, clamping the user's requested
     *    values to what's actually achievable. */
    unsigned int sensor_res[2] = { 0, 0 };
    rc = ak_vi_get_sensor_resolution(0, sensor_res);
    if (rc != 0 || sensor_res[0] == 0 || sensor_res[1] == 0) {
        fprintf(stderr,
            "[vi] get_sensor_resolution failed: 0x%x — falling back to 1920x1080\n",
            rc);
        sensor_res[0] = 1920;
        sensor_res[1] = 1080;
    }
    fprintf(stderr, "[vi] sensor native resolution: %ux%u\n",
            sensor_res[0], sensor_res[1]);

    /* Adjust user-requested main resolution to sensor capability.
     * Round main width down to multiple of 32 and height to multiple of
     * 8, matching the SDK's internal alignment. */
    //if (G_cfg.enable_main) 
	{
        if ((unsigned)g_streams[0].width  > sensor_res[0]) {
            fprintf(stderr,
                "[vi] main width %d > sensor %u, clamping\n",
                g_streams[0].width, sensor_res[0]);
            g_streams[0].width  = (int)sensor_res[0];
        }
        if ((unsigned)g_streams[0].height > sensor_res[1]) {
            fprintf(stderr,
                "[vi] main height %d > sensor %u, clamping\n",
                g_streams[0].height, sensor_res[1]);
            g_streams[0].height = (int)sensor_res[1];
        }
        g_streams[0].width  &= ~31;   /* align to 32 */
        g_streams[0].height &= ~7;    /* align to 8 */
    }
    //if (G_cfg.enable_sub) 
	{
        /* Sub is normally a downscaled version. Cap to sensor too just
         * in case, and align. */
        if ((unsigned)g_streams[1].width  > sensor_res[0])
            g_streams[1].width  = (int)sensor_res[0];
        if ((unsigned)g_streams[1].height > sensor_res[1])
            g_streams[1].height = (int)sensor_res[1];
        g_streams[1].width  &= ~31;
        g_streams[1].height &= ~7;
    }

    /* 4) Set device attributes.
     *
     *    REQUIRED: ak_vi_set_chn_attr internally validates the requested
     *    channel width/height against device->main_max_w/h (or
     *    sub_max_w/h for chn 1). These maxes are populated ONLY by
     *    ak_vi_set_dev_attr — they are NOT set by ak_vi_open or
     *    ak_vi_load_sensor_cfg. If we skip this call, every set_chn_attr
     *    fails with 0x101 ("the channel resolution param w/h is invalid")
     *    because dev->main_max_w == 0 and any width > 0 is rejected.
     *
     *    Constraints (from RE of ak_vi_set_dev_attr at 0x8ea0):
     *      - main_max_w/h   in [0x12 .. 0xa20] = [18 .. 2592]
     *      - sub_max_w/h    in [0x12 .. 0x500] = [18 .. 1280]
     *      - main_max_w  must be aligned to 32 (SDK aligns internally)
     *      - main_max_h  must be aligned to 8
     *      - sub_max_w   must be aligned to 32
     *      - sub_max_h   must be aligned to 8
     *      - attr->dev_id (offset 0) must equal first arg
     */
    struct vi_dev_attr da;
    memset(&da, 0, sizeof(da));
    da.dev_id     = 0;
    /* crop is the full sensor area we capture from. Use the sensor's
     * native resolution (auto-detected above) so the ISP processes the
     * full frame and the channels can independently downscale. */
    da.crop_x     = 0;
    da.crop_y     = 0;
    da.crop_w     = (int)sensor_res[0];
    da.crop_h     = (int)sensor_res[1];
    /* main_max defines the largest size chn 0 can request — the sensor
     * native resolution is the natural choice. */
    da.main_max_w = sensor_res[0];
    da.main_max_h = sensor_res[1];
    da.frame_rate = g_streams[0].fps;  /* firmware passes fps as a plain
                                          int, not packed; SDK reads it
                                          as num=fps, den=0 internally */
    /* sub_max defines the largest size chn 1 can request. We size it to
     * the user's requested sub resolution (already sensor-clamped). */
    //da.sub_max_w  = G_cfg.enable_sub ? (unsigned)g_streams[1].width  : 320;
    //da.sub_max_h  = G_cfg.enable_sub ? (unsigned)g_streams[1].height : 240;
    da.sub_max_w  = (unsigned)g_streams[1].width;
    da.sub_max_h  = (unsigned)g_streams[1].height;

    /* clamp to SDK-allowed ranges */
    if (da.main_max_w > 0xa20) da.main_max_w = 0xa20;
    if (da.main_max_h > 0xa20) da.main_max_h = 0xa20;
    if (da.sub_max_w  > 0x500) da.sub_max_w  = 0x500;
    if (da.sub_max_h  > 0x500) da.sub_max_h  = 0x500;
    if (da.main_max_w < 0x12)  da.main_max_w = 0x12;
    if (da.main_max_h < 0x12)  da.main_max_h = 0x12;
    if (da.sub_max_w  < 0x12)  da.sub_max_w  = 0x12;
    if (da.sub_max_h  < 0x12)  da.sub_max_h  = 0x12;

    fprintf(stderr,
        "[vi] set_dev_attr: crop=[%d,%d %dx%d] main_max=%ux%u sub_max=%ux%u fps=%d\n",
        da.crop_x, da.crop_y, da.crop_w, da.crop_h,
        da.main_max_w, da.main_max_h,
        da.sub_max_w,  da.sub_max_h,
        da.frame_rate);

    rc = ak_vi_set_dev_attr(0, &da);
    if (rc != 0) {
        fprintf(stderr, "[vi] set_dev_attr failed: 0x%x\n", rc);
        return -1;
    }
    fprintf(stderr, "[vi] set_dev_attr OK\n");

    /* 5) Register/configure VI channels via set_chn_attr. set_chn_attr
     *    (RE'd at 0x3dd4 in libplat_vi.so) requires:
     *      - attr->chn_id == first arg, else returns 0x0700000d
     *      - width and height align UP to 32 and 8 respectively, then
     *        the aligned values must satisfy:
     *           aligned_w  >= 0x12 (18)
     *           aligned_w  <= dev->main_max_w (set above)
     *           aligned_h  >= 0x12 (18)
     *           aligned_h  <= dev->main_max_h (set above)
     *      - frame_depth in [2..4]
     *      - frame_rate has high 16 bits != 0 (numerator) */
    //if (G_cfg.enable_main) 
	{
        struct vi_chn_attr ca = {
            .chn_id      = 0,
            .frame_rate  = g_streams[0].fps,  /* plain fps, not packed */
            .width       = (unsigned)g_streams[0].width,
            .height      = (unsigned)g_streams[0].height,
            .frame_depth = 2,   /* matches firmware: 2 capture buffers/chn */
        };
        fprintf(stderr, "[vi] set_chn_attr(0, %ux%u depth=%u fps=%d)\n",
                ca.width, ca.height, ca.frame_depth, ca.frame_rate);
        rc = ak_vi_set_chn_attr(0, &ca);
        if (rc != 0) {
            fprintf(stderr, "[vi] set_chn_attr(0) failed: 0x%x\n", rc);
            return -1;
        }
    }
    //if (G_cfg.enable_sub) 
	{
        struct vi_chn_attr ca = {
            .chn_id      = 1,
            .frame_rate  = g_streams[1].fps,  /* plain fps, not packed */
            .width       = (unsigned)g_streams[1].width,
            .height      = (unsigned)g_streams[1].height,
            .frame_depth = 2,   /* matches firmware: 2 capture buffers/chn */
        };
        fprintf(stderr, "[vi] set_chn_attr(1, %ux%u depth=%u fps=%d)\n",
                ca.width, ca.height, ca.frame_depth, ca.frame_rate);
        rc = ak_vi_set_chn_attr(1, &ca);
        if (rc != 0) {
            fprintf(stderr, "[vi] set_chn_attr(1) failed: 0x%x — disabling sub\n", rc);
            G_cfg.enable_sub = 0;
        }
    }

    /* 6) Enable the VI device.
     *
     *    Empirical RE finding: the firmware DOES call ak_vi_enable_dev,
     *    even though its name doesn't appear in the debug log. Evidence:
     *    the firmware log shows "vi_set_capture_on:1173 vi channel [N]
     *    is started!" lines BEFORE the ak_vi_enable_chn lines, and
     *    vi_set_capture_on (an internal symbol at 0x28b8 in libplat_vi)
     *    is only called from ak_vi_enable_dev (0x4650). It is NOT
     *    called from ak_vi_enable_chn or anywhere else.
     *
     *    Furthermore, the "device enabled" flag at offset 0 of the
     *    vi_device struct (which is checked by ak_vi_get_frame_ex with
     *    "vi device should be enable first!" if 0) is ONLY set to 1
     *    by ak_vi_enable_dev. Without that call, every get_frame_ex
     *    returns "device should be enable first!" — exactly the
     *    failure mode we observed when we initially skipped it.
     *
     *    ak_vi_enable_dev iterates over all registered channels of the
     *    given device, calls vi_set_capture_on for each, sets the
     *    device_enabled flag, then calls "viN=enabled" through a
     *    callback (presumably to notify other modules like VENC). */
    fprintf(stderr, "[vi] ak_vi_enable_dev(0)\n");
    rc = ak_vi_enable_dev(0);
    if (rc != 0) {
        fprintf(stderr, "[vi] ak_vi_enable_dev(0) failed: 0x%x\n", rc);
        return -1;
    }
    g_vi_dev_enabled = 1;
    fprintf(stderr, "[vi] dev enabled\n");
    {
        struct isp_flip_mirror_info fm;
        fm.flip_en = 0;
        fm.mirror_en = 0;
        fprintf(stderr, "[isp] isp_set_flip_mirror flip=%d mirror=%d\n", fm.flip_en, fm.mirror_en);
        isp_set_flip_mirror(&fm);
    }
    /* 7) Enable the channels (logs "set channel [N] capture on"). */
    if (G_cfg.enable_main) {
        rc = ak_vi_enable_chn(0);
        if (rc != 0) {
            fprintf(stderr, "[vi] enable_chn(0) failed: 0x%x\n", rc);
            return -1;
        }
        g_vi_chn_main_enabled = 1;
    }
    if (G_cfg.enable_sub) {
        rc = ak_vi_enable_chn(1);
        if (rc != 0) {
            fprintf(stderr, "[vi] enable_chn(1) failed: 0x%x — disabling sub\n", rc);
            G_cfg.enable_sub = 0;
        } else {
            g_vi_chn_sub_enabled = 1;
        }
    }

    fprintf(stderr, "[vi] ready (main=%d sub=%d)\n",
            g_vi_chn_main_enabled, g_vi_chn_sub_enabled);
    return 0;
}

static void vi_deinit(void)
{
    if (g_vi_chn_sub_enabled)  ak_vi_disable_chn(1);
    if (g_vi_chn_main_enabled) ak_vi_disable_chn(0);
    if (g_vi_dev_enabled)      ak_vi_disable_dev(0);
    if (g_vi_dev_opened)       ak_vi_close(0);
    g_vi_chn_sub_enabled = g_vi_chn_main_enabled = 0;
    g_vi_dev_enabled = 0;
    g_vi_dev_opened = 0;
}

/* ====================================================================== */
/* Public capture API — used by netmgr (main.c)                           */
/* ====================================================================== */

/* Single supervisor thread runs the equivalent of the old main(). It
 * blocks until cap_run goes 0, then tears down. capture_stop() flips
 * cap_run and joins; if the supervisor wedged in some lib call, we
 * don't kill -9 it (would corrupt the SDK), we wait. */
static pthread_t   g_cap_super_tid;
static int         g_cap_super_started = 0;
static int         g_cap_super_failed  = 0;

void capture_cfg_defaults(struct capture_cfg *cfg)
{
    if (!cfg) return;
    memset(cfg, 0, sizeof(*cfg));
    cfg->rtsp_port      = DEFAULT_RTSP_PORT;
    cfg->sensor_cfg_path= NULL;             /* uses DEFAULT_SENSOR_CONFIG */
    cfg->enable_main    = 1;
    cfg->enable_sub     = 1;
    cfg->main_w         = DEFAULT_MAIN_W;
    cfg->main_h         = DEFAULT_MAIN_H;
    cfg->main_kbps      = DEFAULT_MAIN_KBPS;
    cfg->sub_w          = DEFAULT_SUB_W;
    cfg->sub_h          = DEFAULT_SUB_H;
    cfg->sub_kbps       = DEFAULT_SUB_KBPS;
    cfg->fps            = DEFAULT_FPS;
    cfg->gop_sec        = DEFAULT_GOP_SEC;
    cfg->main_codec     = CAP_CODEC_H264;   /* compat-friendly default */
    cfg->sub_codec      = CAP_CODEC_H264;
    cfg->max_exp_lines  = 2152;
    cfg->feed_watchdog  = 1;
    cfg->ir_enable      = 1;
    cfg->ir_initial_mode= IR_MODE_AUTO;
}

int capture_is_running(void)
{
    return g_cap_super_started && !g_cap_super_failed;
}

/* Translate the public capture_cfg into the module-local G_cfg/g_streams
 * before kicking the pipeline up. Caller holds nothing. */
static void apply_cfg(const struct capture_cfg *cfg)
{
    G_cfg.sensor_config = cfg->sensor_cfg_path ? cfg->sensor_cfg_path
                                               : DEFAULT_SENSOR_CONFIG;
    G_cfg.rtsp_port     = cfg->rtsp_port > 0 ? cfg->rtsp_port : DEFAULT_RTSP_PORT;
    G_cfg.enable_main   = cfg->enable_main;
    G_cfg.enable_sub    = cfg->enable_sub;
    G_cfg.feed_watchdog = cfg->feed_watchdog;
    G_cfg.main_codec    = (cfg->main_codec == CAP_CODEC_HEVC) ? CODEC_H265 : CODEC_H264;
    G_cfg.sub_codec     = (cfg->sub_codec  == CAP_CODEC_HEVC) ? CODEC_H265 : CODEC_H264;
    G_cfg.max_exp_lines = cfg->max_exp_lines;

    g_streams[0].idx       = 0;
    g_streams[0].vi_chn_id = 0;
    g_streams[0].width     = cfg->main_w   > 0 ? cfg->main_w   : DEFAULT_MAIN_W;
    g_streams[0].height    = cfg->main_h   > 0 ? cfg->main_h   : DEFAULT_MAIN_H;
    g_streams[0].fps       = cfg->fps      > 0 ? cfg->fps      : DEFAULT_FPS;
    g_streams[0].gop_sec   = cfg->gop_sec  > 0 ? cfg->gop_sec  : DEFAULT_GOP_SEC;
    g_streams[0].kbps      = cfg->main_kbps> 0 ? cfg->main_kbps: DEFAULT_MAIN_KBPS;
    g_streams[0].codec     = G_cfg.main_codec;

    g_streams[1].idx       = 1;
    g_streams[1].vi_chn_id = 1;
    g_streams[1].width     = cfg->sub_w    > 0 ? cfg->sub_w    : DEFAULT_SUB_W;
    g_streams[1].height    = cfg->sub_h    > 0 ? cfg->sub_h    : DEFAULT_SUB_H;
    g_streams[1].fps       = cfg->fps      > 0 ? cfg->fps      : DEFAULT_FPS;
    g_streams[1].gop_sec   = cfg->gop_sec  > 0 ? cfg->gop_sec  : DEFAULT_GOP_SEC;
    g_streams[1].kbps      = cfg->sub_kbps > 0 ? cfg->sub_kbps : DEFAULT_SUB_KBPS;
    g_streams[1].codec     = G_cfg.sub_codec;

    /* Wire stats: tell the stats module what each stream is configured
     * for so /api/stats can render the target alongside the actual. */
    stats_set_stream_cfg(0, G_cfg.enable_main,
                         g_streams[0].width, g_streams[0].height,
                         g_streams[0].fps, g_streams[0].kbps,
                         cfg->main_codec);
    stats_set_stream_cfg(1, G_cfg.enable_sub,
                         g_streams[1].width, g_streams[1].height,
                         g_streams[1].fps, g_streams[1].kbps,
                         cfg->sub_codec);
}

static void *cap_supervisor(void *arg)
{
    struct capture_cfg cfg;
    memcpy(&cfg, arg, sizeof(cfg));
    free(arg);

    apply_cfg(&cfg);

    /* No signal trapping: netmgr owns SIGTERM/SIGINT. We rely on
     * cap_run being flipped externally via capture_stop(). The
     * legacy install_signals() is intentionally not called here. */
    cap_run = 1;

    fprintf(stderr, "[cap] starting, RTSP port=%d, main=%s, sub=%s\n",
            G_cfg.rtsp_port,
            cfg.main_codec == CAP_CODEC_HEVC ? "h265" : "h264",
            cfg.sub_codec  == CAP_CODEC_HEVC ? "h265" : "h264");

    wdt_start();

    if (mem_pool_init() < 0) {
        fprintf(stderr, "[cap] mem_pool_init failed\n");
        g_cap_super_failed = 1;
        if (g_wdt_started) { cap_run = 0; pthread_join(g_wdt_tid, NULL); }
        return NULL;
    }
    if (vi_init() < 0) {
        fprintf(stderr, "[cap] vi_init failed\n");
        g_cap_super_failed = 1;
        if (g_wdt_started) { cap_run = 0; pthread_join(g_wdt_tid, NULL); }
        ak_mem_dma_pool_exit();
        ak_mem_exit();
        return NULL;
    }

    enum rtsp_codec codecs[RTSP_MAX_STREAMS] = {
        G_cfg.enable_main
            ? (G_cfg.main_codec == CODEC_H265 ? RTSP_CODEC_H265 : RTSP_CODEC_H264)
            : RTSP_CODEC_NONE,
        G_cfg.enable_sub
            ? (G_cfg.sub_codec  == CODEC_H265 ? RTSP_CODEC_H265 : RTSP_CODEC_H264)
            : RTSP_CODEC_NONE,
    };
    if (rtsp_server_init(G_cfg.rtsp_port, codecs) < 0) {
        fprintf(stderr, "[cap] rtsp_server_init failed\n");
        goto cleanup;
    }

    /* IR-cut + IR-LED day/night automatic switching.
     * Runs as an SDK-side state machine; see ir.c. We init AFTER
     * vi_init so the ISP statistics (luma) are flowing before the
     * SDK starts polling them. */
    if (cfg.ir_enable) {
        if (ir_init() == 0 && cfg.ir_initial_mode != IR_MODE_AUTO) {
            ir_set_mode(cfg.ir_initial_mode);
        }
    }

    int n = 0;
    if (G_cfg.enable_main) {
        if (pthread_create(&g_streams[0].tid, NULL,
                           stream_worker, &g_streams[0]) != 0) {
            fprintf(stderr, "[cap] cannot start main worker\n");
            goto cleanup;
        }
        g_streams[0].started = 1; n++;
    }
    if (G_cfg.enable_sub) {
        if (pthread_create(&g_streams[1].tid, NULL,
                           stream_worker, &g_streams[1]) != 0) {
            fprintf(stderr, "[cap] cannot start sub worker\n");
            goto cleanup;
        }
        g_streams[1].started = 1; n++;
    }
    fprintf(stderr, "[cap] %d worker(s) running\n", n);

    /* Bring up the JPEG snapshot module. It piggy-backs on the VI
     * sub channel (chn 1), so it's only meaningful if the sub
     * stream is enabled. If sub is disabled, snapshot is too —
     * users can re-enable sub from the Settings page. */
    if (G_cfg.enable_sub) {
        if (snapshot_init(1) != 0) {
            fprintf(stderr,
                "[cap] snapshot_init failed — /snapshot.jpg "
                "will return 503\n");
            /* Non-fatal: capture still works without snapshots. */
        }
    } else {
        fprintf(stderr,
            "[cap] sub stream disabled — snapshots also disabled\n");
    }

    /* Block until capture_stop() flips cap_run. */
    while (cap_run) sleep(1);

cleanup:
    fprintf(stderr, "[cap] shutdown\n");
    cap_run = 0;

    /* Snapshot must be torn down before we destroy the VI sub
     * channel, otherwise its in-flight encode would dereference a
     * dead VI source. */
    snapshot_shutdown();

    rtsp_server_shutdown();
    ir_shutdown();

    if (g_vi_chn_sub_enabled)  { ak_vi_disable_chn(1); g_vi_chn_sub_enabled = 0; }
    if (g_vi_chn_main_enabled) { ak_vi_disable_chn(0); g_vi_chn_main_enabled = 0; }

    for (int i = 0; i < 2; i++) {
        if (g_streams[i].started) {
            pthread_join(g_streams[i].tid, NULL);
            g_streams[i].started = 0;
        }
    }
    vi_deinit();
    ak_mem_dma_pool_exit();
    ak_mem_exit();
    if (g_wdt_started) { pthread_join(g_wdt_tid, NULL); g_wdt_started = 0; }

    fprintf(stderr, "[cap] bye\n");
    g_cap_super_failed = 0;
    return NULL;
}

int capture_start(const struct capture_cfg *cfg_in)
{
    if (g_cap_super_started) return 0;

    struct capture_cfg *heap = malloc(sizeof(*heap));
    if (!heap) return -1;
    if (cfg_in) *heap = *cfg_in;
    else        capture_cfg_defaults(heap);

    g_cap_super_failed = 0;
    if (pthread_create(&g_cap_super_tid, NULL, cap_supervisor, heap) != 0) {
        free(heap);
        return -1;
    }
    g_cap_super_started = 1;
    return 0;
}
/* Switch encoder chroma: color=1 (day/YUV420), color=0 (night/mono).
 * Matches stock anyka_ipc set_encoder_chroma_mode - fixes IR night tint. */
void cap_set_chroma(int color)
{
    for (int i = 0; i < 2; i++) {
        if (g_streams[i].venc_id < 0) continue;
        struct encode_param ep;
        memset(&ep, 0, sizeof(ep));
        if (ak_venc_get_attr(g_streams[i].venc_id, &ep) == 0) {
            ep.chroma_mode = color ? 1 : 0;
            ak_venc_set_attr(g_streams[i].venc_id, &ep);
        }
    }
    fprintf(stderr, "[cap] chroma -> %s\n", color ? "color" : "mono");
}
void capture_stop(void)
{
    if (!g_cap_super_started) return;
    cap_run = 0;
    pthread_join(g_cap_super_tid, NULL);
    g_cap_super_started = 0;
}

/* Re-apply only the live-tunable parameters of cfg.
 *
 * Currently a placeholder: the VENC SDK exposes ak_venc_set_attr()
 * which can in theory change bitrate on the fly, but on this
 * firmware ISP we've seen instability at 30fps — until that's
 * understood it's safer to require a capture restart for any
 * encode-affecting change. So this function logs the requested
 * change and returns 0 without touching the live VENC. The caller
 * (http_srv POST /api/config) will perform a capture_stop +
 * capture_start when needed instead.
 *
 * What IS live-applied here: the IR thresholds, since those don't
 * touch the encoder at all. */
int capture_apply_runtime(const struct capture_cfg *cfg)
{
    if (!cfg) return -1;
    /* IR thresholds aren't in capture_cfg; the caller already
     * applied them via ir_set_threshold(). Nothing else to do
     * for now — bitrate hot-swap requires more soak time. */
    fprintf(stderr,
        "[cap] runtime apply: no fields are hot-swappable yet "
        "(use capture_stop/start for kbps/codec/fps changes)\n");
    return 0;
}
