/*
 * web_assets.c — central registry of embedded HTML/CSS/JS blobs.
 *
 * Build-time: files in web/ (and a few shared JS/CSS blobs) are
 * converted to C arrays by `xxd -i` (run from the Makefile) and
 * dropped into web_blobs/. We include them all here.
 *
 * Runtime: if env IPCD_WEB_RUNTIME=1, web_get() first tries to
 * read the file from $WEB_RUNTIME_DIR (default /mnt/ipcd/web) so
 * you can iterate on the UI without recompiling. Failure to read
 * silently falls through to the embedded blob.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "ipcd.h"

/* ---------------------------------------------------------------- */
/* Embedded blobs                                                   */
/* ---------------------------------------------------------------- */
#include "web_blobs/index_html.h"
#include "web_blobs/stats_html.h"
#include "web_blobs/config_html.h"
#include "web_blobs/auth_html.h"

/* xxd -i emits arrays named after the input filename, with hyphens
 * mapped to underscores. We define expected symbols here for clarity
 * and in case the user runs xxd manually with different names. */
#ifndef WEB_HAVE_INDEX
extern unsigned char index_html[];
extern unsigned int  index_html_len;
#endif
#ifndef WEB_HAVE_STATS
extern unsigned char stats_html[];
extern unsigned int  stats_html_len;
#endif
#ifndef WEB_HAVE_CONFIG
extern unsigned char config_html[];
extern unsigned int  config_html_len;
#endif
#ifndef WEB_HAVE_AUTH
extern unsigned char auth_html[];
extern unsigned int  auth_html_len;
#endif

/* Registry: name -> blob */
static const struct {
    const char         *name;
    const char         *ctype;
    unsigned char      *data;
    unsigned int       *len;
} REG[] = {
    { "index.html",  "text/html; charset=utf-8", index_html,  &index_html_len },
    { "stats.html",  "text/html; charset=utf-8", stats_html,  &stats_html_len },
    { "config.html", "text/html; charset=utf-8", config_html, &config_html_len },
    { "auth.html",   "text/html; charset=utf-8", auth_html,   &auth_html_len },
};
static const int REG_N = sizeof(REG) / sizeof(REG[0]);

/* ---------------------------------------------------------------- */
/* Runtime override                                                 */
/* ---------------------------------------------------------------- */
static int g_runtime_enabled = 0;
static char g_runtime_dir[128] = WEB_RUNTIME_DIR;

void web_init(void)
{
    const char *e = getenv("IPCD_WEB_RUNTIME");
    if (e && (e[0] == '1' || e[0] == 'y' || e[0] == 'Y')) {
        g_runtime_enabled = 1;
        const char *d = getenv("IPCD_WEB_DIR");
        if (d && d[0]) {
            snprintf(g_runtime_dir, sizeof(g_runtime_dir), "%s", d);
        }
        fprintf(stderr,
            "[web] runtime mode ON, serving from %s (fallback to embedded)\n",
            g_runtime_dir);
    }
}

/* ctype-from-name (only what we serve). */
static const char *ctype_for(const char *name)
{
    const char *dot = strrchr(name, '.');
    if (!dot) return "application/octet-stream";
    if (!strcmp(dot, ".html")) return "text/html; charset=utf-8";
    if (!strcmp(dot, ".css"))  return "text/css; charset=utf-8";
    if (!strcmp(dot, ".js"))   return "application/javascript; charset=utf-8";
    if (!strcmp(dot, ".json")) return "application/json";
    if (!strcmp(dot, ".svg"))  return "image/svg+xml";
    if (!strcmp(dot, ".ico"))  return "image/x-icon";
    if (!strcmp(dot, ".png"))  return "image/png";
    if (!strcmp(dot, ".jpg") || !strcmp(dot, ".jpeg")) return "image/jpeg";
    return "application/octet-stream";
}

/* Try to load a runtime file. Returns 0 if loaded. */
static int try_runtime(const char *name, struct web_asset_buf *out)
{
    if (!g_runtime_enabled) return -1;
    /* Reject path traversal: no '/', no '..' */
    if (strchr(name, '/') || strstr(name, "..")) return -1;

    char path[256];
    snprintf(path, sizeof(path), "%s/%s", g_runtime_dir, name);

    int fd = open(path, O_RDONLY);
    if (fd < 0) return -1;

    struct stat st;
    if (fstat(fd, &st) != 0 || st.st_size <= 0 || st.st_size > 512 * 1024) {
        close(fd); return -1;
    }
    unsigned char *buf = malloc((size_t)st.st_size);
    if (!buf) { close(fd); return -1; }

    size_t got = 0;
    while (got < (size_t)st.st_size) {
        ssize_t n = read(fd, buf + got, (size_t)st.st_size - got);
        if (n <= 0) { free(buf); close(fd); return -1; }
        got += n;
    }
    close(fd);

    out->data  = buf;
    out->len   = got;
    out->owns  = 1;
    out->ctype = ctype_for(name);
    return 0;
}

/* ---------------------------------------------------------------- */
/* web_get / web_release                                            */
/* ---------------------------------------------------------------- */
int web_get(const char *name, struct web_asset_buf *out)
{
    if (!name || !out) return -1;
    memset(out, 0, sizeof(*out));

    /* Runtime override takes precedence. */
    if (try_runtime(name, out) == 0) return 0;

    /* Embedded */
    for (int i = 0; i < REG_N; i++) {
        if (!strcmp(REG[i].name, name)) {
            out->data  = REG[i].data;
            out->len   = *REG[i].len;
            out->ctype = REG[i].ctype;
            out->owns  = 0;
            return 0;
        }
    }
    return -1;
}

void web_release(struct web_asset_buf *buf)
{
    if (!buf) return;
    if (buf->owns && buf->data) {
        free(buf->data);
    }
    memset(buf, 0, sizeof(*buf));
}
