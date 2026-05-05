/*
 * cfgfile.c — persistent capture config (/etc/config/ipcd.conf).
 *
 * Format: simple key = value INI, one pair per line. Comments
 * start with '#'. Whitespace around '=' and at line ends is
 * trimmed. Unknown keys are ignored (forward-compat).
 *
 * Example:
 *
 *   # ipcd capture config
 *   fps          = 15
 *   main_kbps    = 2000
 *   sub_kbps     = 300
 *   main_codec   = h264
 *   sub_codec    = h264
 *   enable_main  = 1
 *   enable_sub   = 1
 *   rtsp_port    = 8554
 *   ir_d2n_lum   = 8600
 *   ir_n2d_lum   = 1024
 *   sensor_cfg   = /etc/config/isp_sc2331_mipi_2lane_h3b_15fps.conf
 *
 * Atomic save: write to ipcd.conf.tmp then rename. A power-off
 * mid-write leaves either the previous good file or the new one,
 * never a partial.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <strings.h>
#include <sys/stat.h>

#include "ipcd.h"

/* ---------------------------------------------------------------- */
/* Helpers                                                          */
/* ---------------------------------------------------------------- */
static char *trim(char *s)
{
    while (*s == ' ' || *s == '\t' || *s == '\r' || *s == '\n') s++;
    char *e = s + strlen(s);
    while (e > s && (e[-1] == ' ' || e[-1] == '\t' ||
                     e[-1] == '\r' || e[-1] == '\n')) {
        *--e = 0;
    }
    return s;
}

static int parse_codec(const char *v, cap_codec_t *out)
{
    if (!strcasecmp(v, "h264") || !strcasecmp(v, "avc"))  {
        *out = CAP_CODEC_H264; return 0;
    }
    if (!strcasecmp(v, "h265") || !strcasecmp(v, "hevc")) {
        *out = CAP_CODEC_HEVC; return 0;
    }
    return -1;
}

static const char *codec_name(cap_codec_t c)
{
    return c == CAP_CODEC_HEVC ? "h265" : "h264";
}

/* sensor_cfg is a string we may need to strdup so the cfg owns it
 * across edits. We keep a single static buffer per cfg (i.e. once
 * loaded, the same buffer is reused on subsequent loads). */
static char g_sensor_path_buf[256];

/* ---------------------------------------------------------------- */
/* Auth credentials live alongside the capture cfg in the same      */
/* INI file — they're not part of struct capture_cfg because they   */
/* don't influence the pipeline, but the same load/save plumbing    */
/* is the path of least resistance.                                 */
/*                                                                  */
/* These are accessed by auth.c via the cfgfile_get_creds /         */
/* cfgfile_set_creds helpers; from auth.c's point of view they're   */
/* opaque storage. The actual values are kept in module-static      */
/* state below, populated by ipcd_cfg_load and persisted by         */
/* ipcd_cfg_save (which we update to also write the http_user/      */
/* http_pass keys).                                                 */
/* ---------------------------------------------------------------- */
#define AUTH_USER_BUF_MAX 33    /* match auth.c's AUTH_USER_MAX + NUL */
#define AUTH_PASS_BUF_MAX 65
static char g_http_user[AUTH_USER_BUF_MAX];
static char g_http_pass[AUTH_PASS_BUF_MAX];

int cfgfile_get_creds(char *user, size_t ulen, char *pass, size_t plen)
{
    if (user && ulen) snprintf(user, ulen, "%s", g_http_user);
    if (pass && plen) snprintf(pass, plen, "%s", g_http_pass);
    return 0;
}

int cfgfile_set_creds(const char *user, const char *pass)
{
    snprintf(g_http_user, sizeof(g_http_user), "%s", user ? user : "");
    snprintf(g_http_pass, sizeof(g_http_pass), "%s", pass ? pass : "");
    /* Persist by re-saving the whole config. We need a current
     * capture_cfg to do this — fetch via the global. */
    struct capture_cfg cur;
    capture_cfg_get(&cur);
    return ipcd_cfg_save(&cur);
}

/* ---------------------------------------------------------------- */
/* Load                                                             */
/* ---------------------------------------------------------------- */
int ipcd_cfg_load(struct capture_cfg *cfg)
{
    if (!cfg) return -1;

    FILE *f = fopen(IPCD_CONF_PATH, "r");
    if (!f) return -1;

    char line[512];
    int  applied = 0;

    while (fgets(line, sizeof(line), f)) {
        /* Strip comments */
        char *hash = strchr(line, '#');
        if (hash) *hash = 0;

        char *p = trim(line);
        if (!*p) continue;

        char *eq = strchr(p, '=');
        if (!eq) continue;
        *eq = 0;
        char *k = trim(p);
        char *v = trim(eq + 1);
        if (!*k || !*v) continue;

        if      (!strcmp(k, "fps"))          cfg->fps          = atoi(v);
        else if (!strcmp(k, "gop_sec"))      cfg->gop_sec      = atoi(v);
        else if (!strcmp(k, "main_kbps"))    cfg->main_kbps    = atoi(v);
        else if (!strcmp(k, "sub_kbps"))     cfg->sub_kbps     = atoi(v);
        else if (!strcmp(k, "rtsp_port"))    cfg->rtsp_port    = atoi(v);
        else if (!strcmp(k, "enable_main"))  cfg->enable_main  = atoi(v) ? 1 : 0;
        else if (!strcmp(k, "enable_sub"))   cfg->enable_sub   = atoi(v) ? 1 : 0;
        else if (!strcmp(k, "feed_watchdog"))cfg->feed_watchdog= atoi(v) ? 1 : 0;
        else if (!strcmp(k, "ir_enable"))    cfg->ir_enable    = atoi(v) ? 1 : 0;
        else if (!strcmp(k, "main_codec")) {
            cap_codec_t c; if (parse_codec(v, &c) == 0) cfg->main_codec = c;
        }
        else if (!strcmp(k, "sub_codec")) {
            cap_codec_t c; if (parse_codec(v, &c) == 0) cfg->sub_codec  = c;
        }
        else if (!strcmp(k, "sensor_cfg")) {
            snprintf(g_sensor_path_buf, sizeof(g_sensor_path_buf),
                     "%s", v);
            cfg->sensor_cfg_path = g_sensor_path_buf;
        }
        /* Note: ir_d2n_lum / ir_n2d_lum aren't part of capture_cfg.
         * They live in ir.c's static state. We expose them as a
         * separate API call; see ir_set_thresholds(). For now we
         * just parse and forward. */
        else if (!strcmp(k, "ir_d2n_lum") || !strcmp(k, "ir_n2d_lum")) {
            unsigned int u = (unsigned)strtoul(v, NULL, 10);
            ir_set_threshold(k[3] == 'd' /* 'd2n' */, u);
        }
        else if (!strcmp(k, "md_threshold")) {
            /* Same pattern as ir_*_lum: not part of capture_cfg,
             * forwarded directly to the motion detector module. */
            motion_set_threshold(atoi(v));
        }
        else if (!strcmp(k, "audio_volume_db")) {
            /* Speaker volume in dB. Same pattern: lives in
             * audio_out.c's static state, not in capture_cfg.
             * Setter clamps to a safe range. Note: if ipcd is
             * loading config before audio_out_init, the value is
             * just remembered and applied at AO open time. */
            audio_out_set_volume_db(atoi(v));
        }
        else if (!strcmp(k, "audio_in_enable")) {
            audio_in_set_enable(atoi(v));
        }
        else if (!strcmp(k, "audio_aec_enable")) {
            audio_in_set_aec_enable(atoi(v));
        }
        else if (!strcmp(k, "http_user")) {
            snprintf(g_http_user, sizeof(g_http_user), "%s", v);
        }
        else if (!strcmp(k, "http_pass")) {
            /* Stored as plaintext. The whole config dir is mode 0600
             * on the camera, so this is no worse than what every
             * other firmware does. We still don't echo it through
             * /api/config or any other endpoint. */
            snprintf(g_http_pass, sizeof(g_http_pass), "%s", v);
        }
        else continue;   /* unknown key -> ignore */

        applied++;
    }

    fclose(f);
    fprintf(stderr, "[cfg] loaded %d keys from %s\n",
            applied, IPCD_CONF_PATH);
    return 0;
}

/* ---------------------------------------------------------------- */
/* Save                                                             */
/* ---------------------------------------------------------------- */
int ipcd_cfg_save(const struct capture_cfg *cfg)
{
    if (!cfg) return -1;

    char tmp[sizeof(IPCD_CONF_PATH) + 8];
    snprintf(tmp, sizeof(tmp), "%s.tmp", IPCD_CONF_PATH);

    FILE *f = fopen(tmp, "w");
    if (!f) {
        fprintf(stderr, "[cfg] cannot open %s for write: %s\n",
                tmp, strerror(errno));
        return -1;
    }

    /* Resolve current IR thresholds at save time. */
    unsigned int d2n = ir_get_threshold(1);
    unsigned int n2d = ir_get_threshold(0);
    int md_thr = motion_get_threshold();
    int vol_db = audio_out_get_volume_db();
    int audio_in_en = audio_in_get_enable();
    int audio_aec_en = audio_in_get_aec_enable();

    fprintf(f,
        "# ipcd capture config — auto-generated, edits preserved\n"
        "fps           = %d\n"
        "gop_sec       = %d\n"
        "main_kbps     = %d\n"
        "sub_kbps      = %d\n"
        "rtsp_port     = %d\n"
        "enable_main   = %d\n"
        "enable_sub    = %d\n"
        "feed_watchdog = %d\n"
        "ir_enable     = %d\n"
        "main_codec    = %s\n"
        "sub_codec     = %s\n"
        "ir_d2n_lum    = %u\n"
        "ir_n2d_lum    = %u\n"
        "md_threshold  = %d\n"
        "audio_volume_db = %d\n"
        "audio_in_enable = %d\n"
        "audio_aec_enable = %d\n",
        cfg->fps, cfg->gop_sec,
        cfg->main_kbps, cfg->sub_kbps,
        cfg->rtsp_port,
        cfg->enable_main, cfg->enable_sub,
        cfg->feed_watchdog, cfg->ir_enable,
        codec_name(cfg->main_codec), codec_name(cfg->sub_codec),
        d2n, n2d, md_thr, vol_db, audio_in_en, audio_aec_en);

    if (cfg->sensor_cfg_path && cfg->sensor_cfg_path[0]) {
        fprintf(f, "sensor_cfg    = %s\n", cfg->sensor_cfg_path);
    }

    /* Auth credentials: we only emit the keys when set, so an
     * upgrade on a camera that never enabled auth doesn't introduce
     * stray empty keys (and the file format stays parseable by
     * older ipcd binaries that don't know about these keys yet). */
    if (g_http_user[0]) {
        fprintf(f, "http_user     = %s\n", g_http_user);
    }
    if (g_http_pass[0]) {
        fprintf(f, "http_pass     = %s\n", g_http_pass);
    }

    /* fsync + close so the bytes are on disk before rename. */
    fflush(f);
    int fd = fileno(f);
    if (fd >= 0) fsync(fd);
    fclose(f);

    if (rename(tmp, IPCD_CONF_PATH) != 0) {
        fprintf(stderr, "[cfg] rename %s -> %s failed: %s\n",
                tmp, IPCD_CONF_PATH, strerror(errno));
        unlink(tmp);
        return -1;
    }
    fprintf(stderr, "[cfg] saved to %s\n", IPCD_CONF_PATH);
    return 0;
}

/* ---------------------------------------------------------------- */
/* JSON for /api/config                                            */
/* ---------------------------------------------------------------- */
size_t ipcd_cfg_to_json(const struct capture_cfg *cfg, char *out, size_t cap)
{
    if (!cfg || !out || cap < 256) return 0;
    unsigned int d2n = ir_get_threshold(1);
    unsigned int n2d = ir_get_threshold(0);
    int md_thr = motion_get_threshold();
    int vol_db = audio_out_get_volume_db();
    int audio_in_en = audio_in_get_enable();
    int audio_aec_en = audio_in_get_aec_enable();

    int n = snprintf(out, cap,
        "{"
        "\"fps\":%d,"
        "\"gop_sec\":%d,"
        "\"main_kbps\":%d,"
        "\"sub_kbps\":%d,"
        "\"rtsp_port\":%d,"
        "\"enable_main\":%d,"
        "\"enable_sub\":%d,"
        "\"feed_watchdog\":%d,"
        "\"ir_enable\":%d,"
        "\"main_codec\":\"%s\","
        "\"sub_codec\":\"%s\","
        "\"ir_d2n_lum\":%u,"
        "\"ir_n2d_lum\":%u,"
        "\"md_threshold\":%d,"
        "\"audio_volume_db\":%d,"
        "\"audio_in_enable\":%d,"
        "\"audio_aec_enable\":%d,"
        "\"sensor_cfg\":\"%s\""
        "}",
        cfg->fps, cfg->gop_sec,
        cfg->main_kbps, cfg->sub_kbps,
        cfg->rtsp_port,
        cfg->enable_main, cfg->enable_sub,
        cfg->feed_watchdog, cfg->ir_enable,
        codec_name(cfg->main_codec), codec_name(cfg->sub_codec),
        d2n, n2d, md_thr, vol_db, audio_in_en, audio_aec_en,
        cfg->sensor_cfg_path ? cfg->sensor_cfg_path : "");
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}
