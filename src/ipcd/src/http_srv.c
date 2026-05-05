/*
 * http_srv.c — embedded HTTP/1.1 server.
 *
 * Endpoints:
 *   GET  /                    → web_get("index.html")
 *   GET  /stats               → web_get("stats.html")
 *   GET  /config              → web_get("config.html")
 *   GET  /api/status          → small JSON: state + ssid + ip + ir_*
 *   GET  /api/stats           → big JSON: stats_to_json()
 *   GET  /api/scan            → JSON list of nearby networks
 *   POST /api/save            → form-urlencoded ssid + psk → wifi.conf
 *   POST /api/ir              → form-urlencoded mode=auto|off|night
 *   GET  /api/config          → JSON of current capture config
 *   POST /api/config          → form-urlencoded fields → /etc/config/ipcd.conf
 *   GET  /favicon.ico         → 204 (avoid log spam)
 *
 * Captive-portal hooks redirect to /.
 *
 * Threading: one accept loop, one detached thread per connection.
 * Bodies are small (we cap at 4 KiB).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#include "ipcd.h"

/* ---------------------------------------------------------------- */
/* Capture restart helper                                           */
/*                                                                  */
/* capture_stop() joins the supervisor + RTSP threads, consuming   */
/* 20-30 KB of stack in sub-frames. Connection threads have only   */
/* 64 KB of stack, so we can't call it inline without risking a    */
/* stack overflow (Chrome shows ERR_CONNECTION_RESET). Instead we  */
/* dispatch the stop/start sequence to this detached thread, which */
/* runs on the default (full) stack. The HTTP response has already */
/* been sent before this thread touches anything. */
static void *capture_restart_thread(void *arg)
{
    struct capture_cfg *cfg = arg;
    fprintf(stderr, "[http] async capture restart starting\n");
    stats_sampler_stop();
    capture_stop();
    if (capture_start(cfg) == 0)
        stats_sampler_start();
    free(cfg);
    fprintf(stderr, "[http] async capture restart done\n");
    return NULL;
}

/* ---------------------------------------------------------------- */
/* HTTP helpers                                                     */
/* ---------------------------------------------------------------- */
static ssize_t writeall(int fd, const void *buf, size_t len)
{
    const char *p = buf;
    while (len) {
        ssize_t n = send(fd, p, len, MSG_NOSIGNAL);
        if (n < 0) { if (errno == EINTR) continue; return -1; }
        p += n; len -= (size_t)n;
    }
    return 0;
}

static void send_response(int fd, int code, const char *reason,
                          const char *ctype, const void *body, size_t blen,
                          const char *extra_headers)
{
    char hdr[384];
    int n = snprintf(hdr, sizeof(hdr),
        "HTTP/1.1 %d %s\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %zu\r\n"
        "Cache-Control: no-store\r\n"
        "Connection: close\r\n"
        "%s"
        "\r\n",
        code, reason, ctype, blen,
        extra_headers ? extra_headers : "");
    writeall(fd, hdr, (size_t)n);
    if (blen) writeall(fd, body, blen);
}

static void send_text(int fd, int code, const char *reason, const char *body)
{
    send_response(fd, code, reason, "text/plain; charset=utf-8",
                  body, strlen(body), NULL);
}

static void send_json(int fd, const char *json)
{
    send_response(fd, 200, "OK", "application/json",
                  json, strlen(json), NULL);
}

static void send_redirect(int fd, const char *location)
{
    char buf[256];
    int n = snprintf(buf, sizeof(buf),
        "HTTP/1.1 302 Found\r\n"
        "Location: %s\r\n"
        "Content-Length: 0\r\n"
        "Connection: close\r\n\r\n",
        location);
    writeall(fd, buf, (size_t)n);
}

static void send_204(int fd)
{
    const char resp[] =
        "HTTP/1.1 204 No Content\r\n"
        "Content-Length: 0\r\n"
        "Connection: close\r\n\r\n";
    writeall(fd, resp, sizeof(resp) - 1);
}

/* Pull a header value out of a raw request buffer. The caller passes
 * the start of the request (which still contains the request line +
 * all headers, NUL-terminated). Returns 0 if found, fills *out with
 * a heap-free trimmed copy. Returns -1 if not present.
 *
 * Case-insensitive on the name. We don't handle multi-line/folded
 * headers (RFC obsolete since 2014, browsers and curl don't do it). */
static int get_header(const char *req, const char *name,
                      char *out, size_t cap)
{
    if (!req || !name || !out || cap == 0) return -1;
    out[0] = 0;
    size_t nlen = strlen(name);
    const char *p = strstr(req, "\r\n");
    if (!p) return -1;
    p += 2; /* skip request line */

    while (*p && !(p[0] == '\r' && p[1] == '\n')) {
        const char *eol = strstr(p, "\r\n");
        if (!eol) break;
        if ((size_t)(eol - p) > nlen + 1 &&
            strncasecmp(p, name, nlen) == 0 && p[nlen] == ':') {
            const char *v = p + nlen + 1;
            while (*v == ' ' || *v == '\t') v++;
            size_t L = (size_t)(eol - v);
            if (L >= cap) L = cap - 1;
            memcpy(out, v, L);
            out[L] = 0;
            /* Trim trailing whitespace (some clients leave a space) */
            while (L > 0 && (out[L-1] == ' ' || out[L-1] == '\t'))
                out[--L] = 0;
            return 0;
        }
        p = eol + 2;
    }
    return -1;
}

/* Send 401 Unauthorized with a fresh Digest challenge. */
static void send_401(int fd)
{
    char chal[256];
    size_t cl = auth_make_challenge(chal, sizeof(chal));
    if (cl == 0) {
        send_text(fd, 500, "ERR", "auth challenge failed\n");
        return;
    }
    char extra[320];
    snprintf(extra, sizeof(extra), "WWW-Authenticate: %s\r\n", chal);
    const char body[] = "401 Unauthorized\n";
    send_response(fd, 401, "Unauthorized", "text/plain; charset=utf-8",
                  body, sizeof(body) - 1, extra);
}

/* Decide whether a given path needs auth in the current netmgr state.
 *
 * The captive-portal endpoints (/, /api/save, /api/scan, the
 * generate_204 family) must stay open while we're in AP_MODE — the
 * whole point of AP_MODE is letting an unconfigured user finish
 * the wifi setup, and we can't ask them for a password they haven't
 * set yet. Everything else gets the standard treatment. */
static int path_requires_auth(const char *method, const char *path)
{
    /* ONVIF endpoints carry their own WS-Security auth in the SOAP
     * body — they MUST NOT be gated by HTTP Digest, otherwise
     * clients that authenticate via UsernameToken get 401 before
     * their SOAP envelope is even parsed. The onvif dispatcher
     * runs onvif_check_ws_security() itself. */
    if (!strncmp(path, "/onvif/", 7)) return 0;

    /* favicon: always free, browser noise. */
    if (!strcmp(path, "/favicon.ico")) return 0;

    /* In AP mode, the wifi-setup flow is open. We allow the index
     * page, scan + save, and the captive-portal probes. */
    if (g_get_state() == PCS_AP_MODE) {
        if (!strcmp(path, "/") || !strncmp(path, "/?", 2)) return 0;
        if (!strcmp(path, "/api/scan")) return 0;
        if (!strcmp(path, "/api/save")) return 0;
        if (!strcmp(path, "/api/status")) return 0;
        if (strstr(path, "generate_204") || strstr(path, "gen_204") ||
            strstr(path, "hotspot-detect") || strstr(path, "ncsi.txt") ||
            strstr(path, "connecttest")) return 0;
    }

    /* /api/auth GET is open when no creds are set yet (otherwise
     * the user couldn't bootstrap auth from a fresh install). The
     * POST is *not* open in that case — we still want a plausible
     * actor to be the one setting it. We handle that nuance inside
     * the route itself, not here, so this returns 1 unconditionally
     * for /api/auth GET when creds *are* configured. */
    if (!strcmp(path, "/api/auth") && !strcmp(method, "GET") &&
        !auth_is_configured()) {
        return 0;
    }
    if (!strcmp(path, "/api/auth") && !strcmp(method, "POST") &&
        !auth_is_configured()) {
        /* First-time setup: anyone on the LAN can claim the camera.
         * Same trust model as a brand-new wifi router's admin
         * password — first one wins. We log it loudly. */
        return 0;
    }

    return 1;
}

/* ---------------------------------------------------------------- */
/* form-urlencoded parser                                           */
/* ---------------------------------------------------------------- */
static int hexv(int c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

static void urldecode(const char *in, char *out, size_t cap)
{
    size_t o = 0;
    for (size_t i = 0; in[i] && o + 1 < cap; ) {
        if (in[i] == '+') { out[o++] = ' '; i++; }
        else if (in[i] == '%' && in[i+1] && in[i+2]) {
            int h = hexv(in[i+1]), l = hexv(in[i+2]);
            if (h >= 0 && l >= 0) { out[o++] = (char)((h << 4) | l); i += 3; }
            else { out[o++] = in[i++]; }
        }
        else out[o++] = in[i++];
    }
    out[o] = 0;
}

static int form_get(const char *body, const char *key, char *out, size_t cap)
{
    size_t kl = strlen(key);
    const char *p = body;
    while (*p) {
        if (!strncmp(p, key, kl) && p[kl] == '=') {
            const char *v = p + kl + 1;
            const char *amp = strchr(v, '&');
            size_t L = amp ? (size_t)(amp - v) : strlen(v);
            char raw[256];
            if (L >= sizeof(raw)) L = sizeof(raw) - 1;
            memcpy(raw, v, L); raw[L] = 0;
            urldecode(raw, out, cap);
            return 0;
        }
        const char *amp = strchr(p, '&');
        if (!amp) break;
        p = amp + 1;
    }
    out[0] = 0;
    return -1;
}

/* ---------------------------------------------------------------- */
/* Serve a web asset (HTML/CSS/JS) by name                          */
/* ---------------------------------------------------------------- */
static void serve_asset(int fd, const char *name)
{
    struct web_asset_buf buf;
    if (web_get(name, &buf) != 0) {
        send_text(fd, 404, "Not Found", "asset not found\n");
        return;
    }
    send_response(fd, 200, "OK", buf.ctype, buf.data, buf.len, NULL);
    web_release(&buf);
}

/* ---------------------------------------------------------------- */
/* Talkback: streaming body handler                                 */
/*                                                                  */
/* Audio backchannel POSTs can send megabytes per minute; we can't  */
/* buffer the whole body in RAM. This function reads body bytes     */
/* in chunks straight from the socket and pushes them to            */
/* audio_out as they arrive.                                        */
/*                                                                  */
/* The codec is selected from the URL query (?codec=g711u|g711a|    */
/* pcm) — defaults to g711u, which is the most common choice for    */
/* low-bandwidth talkback. Content-Type is informational, we trust  */
/* the codec parameter.                                             */
/*                                                                  */
/* The function consumes content_len bytes from the socket          */
/* (anything pre-buffered in `prebuf` first), then sends a 200 OK   */
/* once done. If the client closes early, we send 200 too — partial */
/* audio is fine.                                                   */
/* ---------------------------------------------------------------- */
static void handle_talkback(int fd, const char *path,
                            const uint8_t *prebuf, size_t prebuf_len,
                            long content_len)
{
    /* Parse codec from query string. */
    int codec = AUDIO_CODEC_G711U;
    const char *q = strchr(path, '?');
    if (q) {
        q++;
        if (strstr(q, "codec=g711a"))   codec = AUDIO_CODEC_G711A;
        else if (strstr(q, "codec=g711u")) codec = AUDIO_CODEC_G711U;
        else if (strstr(q, "codec=pcm"))   codec = AUDIO_CODEC_PCM;
    }

    if (!audio_out_is_available()) {
        send_text(fd, 503, "Service Unavailable",
            "speaker not available\n");
        return;
    }

    /* Push the prebuffered tail of the request that we already
     * read while accumulating headers. */
    size_t pushed = 0;
    if (prebuf_len > 0) {
        if (codec == AUDIO_CODEC_PCM) {
            /* Caller-provided PCM is assumed to already be at our
             * AO sample rate (16 kHz mono 16-bit). If they push
             * 8 kHz they'll just play at half speed — caveat
             * emptor; we don't resample arbitrary PCM. */
            audio_out_push_pcm((const int16_t *)prebuf,
                               prebuf_len / 2);
        } else {
            audio_out_push_g711(codec, prebuf, prebuf_len);
        }
        pushed = prebuf_len;
    }

    /* Read remaining body in chunks. We use a small buffer to keep
     * memory usage tight, and because the audio decode loop is fine
     * with frequent small calls. Content-Length may be 0 (chunked
     * encoding — not supported here, treated as "read until close"). */
    uint8_t chunk[1024];
    size_t  remaining = (content_len > 0)
                          ? (size_t)content_len - pushed
                          : SIZE_MAX;

    /* Bump the recv timeout for the duration of the talkback —
     * the client may pace audio in real time, so blocking 30s on
     * a quiet stretch is fine. */
    struct timeval tv = { .tv_sec = 30, .tv_usec = 0 };
    setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    while (remaining > 0) {
        size_t want = remaining > sizeof(chunk) ? sizeof(chunk) : remaining;
        ssize_t n = recv(fd, chunk, want, 0);
        if (n <= 0) break;
        if (codec == AUDIO_CODEC_PCM) {
            /* Round to even byte count (16-bit samples). Drop the
             * odd byte if any — a desync of half a sample is
             * inaudible. */
            audio_out_push_pcm((const int16_t *)chunk, (size_t)n / 2);
        } else {
            audio_out_push_g711(codec, chunk, (size_t)n);
        }
        if (content_len > 0) remaining -= (size_t)n;
    }

    /* Flush the ring tail so the last <20 ms of audio actually
     * reaches the speaker instead of waiting for an unrelated
     * future push to fill out a frame. */
    audio_out_flush();

    send_text(fd, 200, "OK", "talkback ended\n");
}

/* ---------------------------------------------------------------- */
/* Connection handler                                               */
/* ---------------------------------------------------------------- */
static void handle_conn(int fd)
{
    /* Buffer is sized for the largest single request we expect to
     * service in one go: ONVIF SOAP envelopes with a WS-Security
     * UsernameToken can run 1.5–2 KB; 8 KB is comfortable headroom.
     * Browser requests are far smaller. */
    char buf[8192];
    size_t total = 0;
    int header_done = 0;
    size_t header_len = 0;
    long content_len = 0;

    /* recv timeout: if the browser opens a TCP connection but
     * doesn't send anything (e.g. speculative preconnect that the
     * tab never used), we don't want this thread to sit on the
     * socket for 5+ seconds. 2s is plenty for a real request to
     * finish arriving over wifi. */
    struct timeval tv = { .tv_sec = 2, .tv_usec = 0 };
    setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    /* Phase 1: read until end-of-headers, regardless of body size. */
    while (total < sizeof(buf) - 1) {
        ssize_t n = recv(fd, buf + total, sizeof(buf) - 1 - total, 0);
        if (n <= 0) goto done;
        total += (size_t)n;
        buf[total] = 0;

        char *eoh = strstr(buf, "\r\n\r\n");
        if (eoh) {
            header_done = 1;
            header_len = (size_t)(eoh - buf) + 4;
            char *cl = strcasestr(buf, "Content-Length:");
            if (cl) content_len = strtol(cl + 15, NULL, 10);
            break;
        }
    }
    if (!header_done) goto done;

    /* Extract method + path before we decide whether to keep
     * accumulating the body or hand off to a streaming handler. */
    char method[8] = {0}, path[256] = {0};
    sscanf(buf, "%7s %255s", method, path);

    /* /talkback is special: body can be megabytes. We hand off to
     * a streaming handler that reads from the socket directly,
     * after re-checking auth.
     *
     * (Auth re-check below is done before the handoff, so the
     * streaming handler doesn't have to redo the digest dance.) */
    int is_talkback = (!strcmp(method, "POST") &&
                       !strncmp(path, "/talkback", 9) &&
                       (path[9] == 0 || path[9] == '?'));

    /* For non-talkback requests, finish reading the body into
     * `buf` if we haven't already. */
    if (!is_talkback) {
        if (content_len > (long)(sizeof(buf) - 512)) goto done;
        while (total < header_len + (size_t)content_len) {
            ssize_t n = recv(fd, buf + total,
                             sizeof(buf) - 1 - total, 0);
            if (n <= 0) goto done;
            total += (size_t)n;
            buf[total] = 0;
        }
    }

    /* ---- auth gate ----
     * If a password has been set, every "interesting" endpoint
     * requires a valid Digest Authorization header. The exemption
     * list (captive portal, AP-mode setup, favicon) is handled by
     * path_requires_auth. */
    if (path_requires_auth(method, path)) {
        char authz[768];
        int have = (get_header(buf, "Authorization", authz, sizeof(authz)) == 0);
        auth_result_t ar = auth_http_check(have ? authz : NULL, method, path);
        if (ar != AUTH_OK) {
            send_401(fd);
            goto done;
        }
    }

    /* /talkback handoff: at this point we have headers + auth
     * passed, plus possibly some body bytes pre-buffered after
     * the headers. Forward the prebuf and then stream the rest. */
    if (is_talkback) {
        size_t prebuf_len = total - header_len;
        handle_talkback(fd, path,
                        (const uint8_t *)(buf + header_len),
                        prebuf_len, content_len);
        goto done;
    }

    /* ---- routing ---- */
    int is_get  = !strcmp(method, "GET");
    int is_post = !strcmp(method, "POST");

    if (is_get && (!strcmp(path, "/") || !strncmp(path, "/?", 2))) {
        serve_asset(fd, "index.html");
    }
    else if (is_get && (!strcmp(path, "/stats") || !strcmp(path, "/stats.html"))) {
        serve_asset(fd, "stats.html");
    }
    else if (is_get && (!strcmp(path, "/config") || !strcmp(path, "/config.html"))) {
        serve_asset(fd, "config.html");
    }
    else if (is_get && (!strcmp(path, "/auth") || !strcmp(path, "/auth.html"))) {
        serve_asset(fd, "auth.html");
    }
    else if (is_post && !strncmp(path, "/onvif/", 7)) {
        const char *body = buf + header_len;
        char host_hdr[80];
        if (get_header(buf, "Host", host_hdr, sizeof(host_hdr)) != 0) {
            host_hdr[0] = 0;
        }

        /* Use a heap buffer for the response — some ONVIF responses
         * (GetCapabilities, GetProfiles with both streams) are 4-6 KB.
         * 16 KB gives us plenty of headroom. */
        char *resp = malloc(16384);
        if (!resp) {
            send_text(fd, 500, "ERR", "out of memory\n");
            goto done;
        }
        size_t rlen = 0;

        /* Split path into path_only + query. Events subscriptions
         * encode the subscription token as ?token=... in the URL,
         * which we forward to the dispatcher. */
        char path_only[128];
        snprintf(path_only, sizeof(path_only), "%s", path);
        const char *query = "";
        char *q = strchr(path_only, '?');
        if (q) {
            *q = 0;
            query = q + 1;
        }

        if (onvif_dispatch(path_only, query, body, host_hdr,
                           resp, 16384, &rlen) != 0 || rlen == 0) {
            free(resp);
            send_text(fd, 500, "ERR", "onvif dispatch failed\n");
            goto done;
        }

        send_response(fd, 200, "OK",
                      "application/soap+xml; charset=utf-8",
                      resp, rlen, NULL);
        free(resp);
    }
    else if (is_get && !strcmp(path, "/snapshot.jpg")) {
        if (!snapshot_is_available()) {
            /* Capture is starting up, restarting, or sub stream is
             * disabled. Frigate's HTTP retry logic handles 503 with
             * Retry-After cleanly. */
            send_response(fd, 503, "Service Unavailable",
                          "text/plain; charset=utf-8",
                          "snapshot module not ready\n", 26,
                          "Retry-After: 2\r\n");
        } else {
            uint8_t *buf = NULL;
            size_t   len = 0;
            if (snapshot_get_jpeg(&buf, &len) == 0 && buf && len > 0) {
                send_response(fd, 200, "OK", "image/jpeg",
                              buf, len, NULL);
                free(buf);
            } else {
                send_text(fd, 503, "Service Unavailable",
                          "snapshot encode failed\n");
            }
        }
    }
    else if (is_get && !strcmp(path, "/api/auth")) {
        char json[128];
        snprintf(json, sizeof(json),
            "{\"configured\":%s,\"user\":\"%s\"}",
            auth_is_configured() ? "true" : "false",
            auth_get_user());
        send_json(fd, json);
    }
    else if (is_post && !strcmp(path, "/api/auth")) {
        const char *body = buf + header_len;
        char user[40], pass[80];
        if (form_get(body, "user", user, sizeof(user)) != 0) user[0] = 0;
        if (form_get(body, "pass", pass, sizeof(pass)) != 0) pass[0] = 0;

        /* Empty pass + non-empty user = "disable auth". Empty user +
         * empty pass = "disable auth" too. Anything else: user is
         * mandatory. */
        if (pass[0] && !user[0]) {
            send_text(fd, 400, "Bad Request",
                "username required when password is set\n");
            goto done;
        }

        if (auth_set_creds(user, pass) != 0) {
            send_text(fd, 500, "ERR", "save failed\n");
            goto done;
        }

        /* The browser is still using the *old* session credentials in
         * its cached Authorization header. After this response the
         * next request will get a 401 with a fresh challenge under
         * the new realm/nonce, prompting the browser to re-ask. We
         * intentionally don't try to log the user in synchronously —
         * the round-trip would race the browser's cache anyway. */
        char resp[80];
        snprintf(resp, sizeof(resp),
            "{\"ok\":true,\"configured\":%s}",
            pass[0] ? "true" : "false");
        send_json(fd, resp);
    }
    else if (is_get && (strstr(path, "generate_204") || strstr(path, "gen_204") ||
              strstr(path, "hotspot-detect") || strstr(path, "ncsi.txt") ||
              strstr(path, "connecttest"))) {
        send_redirect(fd, "http://" AP_LOCAL_IP "/");
    }
    else if (is_get && !strcmp(path, "/favicon.ico")) {
        send_204(fd);
    }
    else if (is_get && !strcmp(path, "/api/status")) {
        char ip[16] = "";
        wifi_sta_has_ip(ip);
        pthread_mutex_lock(&G.mtx);
        char json[512];
        snprintf(json, sizeof(json),
            "{\"state\":\"%s\",\"ssid\":\"%s\",\"ip\":\"%s\","
            "\"configured\":%d,"
            "\"ir_mode\":%d,\"ir_level\":%d}",
            pc_state_name(G.st),
            G.cfg.ssid,
            ip,
            G.cfg.configured,
            (int)ir_get_mode(),
            ir_get_level());
        pthread_mutex_unlock(&G.mtx);
        send_json(fd, json);
    }
    else if (is_get && !strcmp(path, "/api/stats")) {
        /* Big JSON — up to ~3 KiB with both stream sparkline arrays. */
        char *json = malloc(8 * 1024);
        if (!json) { send_text(fd, 500, "ERR", "oom"); goto done; }
        size_t L = stats_to_json(json, 8 * 1024);
        if (L == 0) {
            free(json);
            send_text(fd, 500, "ERR", "stats serialization failed\n");
        } else {
            send_response(fd, 200, "OK", "application/json", json, L, NULL);
            free(json);
        }
    }
    else if (is_get && !strcmp(path, "/api/scan")) {
        char *json = malloc(16 * 1024);
        if (!json) { send_text(fd, 500, "ERR", "oom"); goto done; }
        wifi_sta_scan(json, 16 * 1024);
        send_json(fd, json);
        free(json);
    }
    else if (is_post && !strcmp(path, "/api/save")) {
        const char *body = buf + header_len;
        struct wifi_cfg cfg;
        memset(&cfg, 0, sizeof(cfg));
        if (form_get(body, "ssid", cfg.ssid, sizeof(cfg.ssid)) != 0 ||
            cfg.ssid[0] == 0) {
            send_text(fd, 400, "Bad Request", "missing ssid");
            goto done;
        }
        form_get(body, "psk", cfg.psk, sizeof(cfg.psk));
        cfg.configured = 1;

        if (wifi_cfg_save(&cfg) != 0) {
            send_text(fd, 500, "ERR", "save failed");
            goto done;
        }

        pthread_mutex_lock(&G.mtx);
        G.cfg = cfg;
        G.cfg_pending = 1;
        pthread_cond_signal(&G.cfg_pending_cv);
        pthread_mutex_unlock(&G.mtx);

        send_json(fd, "{\"ok\":true}");
    }
    else if (is_post && !strcmp(path, "/api/ir")) {
        const char *body = buf + header_len;
        char modev[16];
        if (form_get(body, "mode", modev, sizeof(modev)) != 0) {
            send_text(fd, 400, "Bad Request", "missing mode\n");
            goto done;
        }
        ir_mode_t m;
        if      (!strcmp(modev, "auto"))  m = IR_MODE_AUTO;
        else if (!strcmp(modev, "off"))   m = IR_MODE_OFF;
        else if (!strcmp(modev, "night")) m = IR_MODE_FORCE_NIGHT;
        else { send_text(fd, 400, "Bad Request", "bad mode\n"); goto done; }
        ir_set_mode(m);
        send_json(fd, "{\"ok\":true}");
    }
    else if (is_get && !strcmp(path, "/api/config")) {
        struct capture_cfg cfg;
        capture_cfg_get(&cfg);
        char json[1024];
        size_t L = ipcd_cfg_to_json(&cfg, json, sizeof(json));
        if (L == 0) {
            send_text(fd, 500, "ERR", "config serialization failed\n");
        } else {
            send_response(fd, 200, "OK", "application/json",
                          json, L, NULL);
        }
    }
    else if (is_post && !strcmp(path, "/api/config")) {
        /* Body is application/x-www-form-urlencoded with arbitrary
         * subset of keys. We start from the current config, overlay
         * only fields that the form actually carries, then decide
         * whether to persist + restart. */
        const char *body = buf + header_len;
        struct capture_cfg cur, next;
        capture_cfg_get(&cur);
        next = cur;

        char v[64];
        if (form_get(body, "fps", v, sizeof(v)) == 0 && v[0]) {
            int n = atoi(v);
            if (n > 0 && n <= 60) next.fps = n;
        }
        if (form_get(body, "gop_sec", v, sizeof(v)) == 0 && v[0]) {
            int n = atoi(v);
            if (n > 0 && n <= 10) next.gop_sec = n;
        }
        if (form_get(body, "main_kbps", v, sizeof(v)) == 0 && v[0]) {
            int n = atoi(v);
            if (n >= 64 && n <= 8000) next.main_kbps = n;
        }
        if (form_get(body, "sub_kbps", v, sizeof(v)) == 0 && v[0]) {
            int n = atoi(v);
            if (n >= 32 && n <= 2000) next.sub_kbps = n;
        }
        if (form_get(body, "rtsp_port", v, sizeof(v)) == 0 && v[0]) {
            int n = atoi(v);
            if (n > 0 && n <= 65535) next.rtsp_port = n;
        }
        if (form_get(body, "enable_main", v, sizeof(v)) == 0 && v[0]) {
            next.enable_main = atoi(v) ? 1 : 0;
        }
        if (form_get(body, "enable_sub", v, sizeof(v)) == 0 && v[0]) {
            next.enable_sub = atoi(v) ? 1 : 0;
        }
        if (form_get(body, "ir_enable", v, sizeof(v)) == 0 && v[0]) {
            next.ir_enable = atoi(v) ? 1 : 0;
        }
        if (form_get(body, "main_codec", v, sizeof(v)) == 0 && v[0]) {
            if (!strcmp(v, "h264"))      next.main_codec = CAP_CODEC_H264;
            else if (!strcmp(v, "h265")) next.main_codec = CAP_CODEC_HEVC;
        }
        if (form_get(body, "sub_codec", v, sizeof(v)) == 0 && v[0]) {
            if (!strcmp(v, "h264"))      next.sub_codec = CAP_CODEC_H264;
            else if (!strcmp(v, "h265")) next.sub_codec = CAP_CODEC_HEVC;
        }
        /* IR thresholds — these are runtime-applied, not part of
         * capture_cfg, but get persisted alongside it. */
        int ir_changed = 0;
        if (form_get(body, "ir_d2n_lum", v, sizeof(v)) == 0 && v[0]) {
            unsigned u = (unsigned)strtoul(v, NULL, 10);
            if (u > 0) { ir_set_threshold(1, u); ir_changed = 1; }
        }
        if (form_get(body, "ir_n2d_lum", v, sizeof(v)) == 0 && v[0]) {
            unsigned u = (unsigned)strtoul(v, NULL, 10);
            if (u > 0) { ir_set_threshold(0, u); ir_changed = 1; }
        }
        /* Motion threshold — also runtime-applied, also persisted. */
        if (form_get(body, "md_threshold", v, sizeof(v)) == 0 && v[0]) {
            int t = atoi(v);
            if (t > 0) { motion_set_threshold(t); ir_changed = 1; }
            /* Reusing ir_changed here is sloppy naming but the
             * effect we need (don't trigger a capture restart for
             * threshold-only edits) is identical. Rename later. */
        }
        /* Speaker volume in dB. Also runtime-applied. Range
         * checking is done by the setter; we accept any int and
         * let the setter clamp. atoi("") returns 0 which is a
         * legitimate value, so we explicitly check the field
         * is present and non-empty. */
        if (form_get(body, "audio_volume_db", v, sizeof(v)) == 0 && v[0]) {
            audio_out_set_volume_db(atoi(v));
            ir_changed = 1;
        }
        if (form_get(body, "audio_in_enable", v, sizeof(v)) == 0 && v[0]) {
            audio_in_set_enable(atoi(v));
            ir_changed = 1;
        }
        if (form_get(body, "audio_aec_enable", v, sizeof(v)) == 0 && v[0]) {
            audio_in_set_aec_enable(atoi(v));
            ir_changed = 1;
        }

        /* enable_main && enable_sub both 0 would leave nothing to
         * capture — refuse the change. */
        if (!next.enable_main && !next.enable_sub) {
            send_text(fd, 400, "Bad Request",
                "at least one of main/sub must be enabled\n");
            goto done;
        }

        /* Decide if anything that requires a capture restart
         * actually changed. Bitrate alone does not (would once we
         * implement live ak_venc_set_attr); for now any encode-
         * affecting field triggers a restart. */
        int needs_restart =
            next.fps          != cur.fps          ||
            next.gop_sec      != cur.gop_sec      ||
            next.main_kbps    != cur.main_kbps    ||
            next.sub_kbps     != cur.sub_kbps     ||
            next.rtsp_port    != cur.rtsp_port    ||
            next.enable_main  != cur.enable_main  ||
            next.enable_sub   != cur.enable_sub   ||
            next.main_codec   != cur.main_codec   ||
            next.sub_codec    != cur.sub_codec    ||
            next.ir_enable    != cur.ir_enable;

        /* Persist and update the in-memory copy. */
        if (capture_cfg_set(&next) != 0) {
            send_text(fd, 500, "ERR", "save failed\n");
            goto done;
        }

        /* If only IR thresholds changed, we're done — they're live. */
        if (needs_restart) {
            /* capture_stop() blocks while joining the supervisor and
             * RTSP threads, which can easily consume 20-30 KB of
             * stack with their sub-frames.  This HTTP handler runs
             * on a connection thread with only 64 KB of stack, so
             * doing the stop/start inline causes a stack overflow
             * (seen as ERR_CONNECTION_RESET in Chrome's devtools).
             *
             * Fix: copy next into a heap-allocated struct and hand
             * it to a detached thread with the default stack size
             * (uClibc default: 2 MB, more than enough). The HTTP
             * response is sent *before* the restart so the browser
             * gets a clean 200 instead of a reset. */
            struct capture_cfg *heap = malloc(sizeof(*heap));
            if (heap) {
                *heap = next;
                pthread_t rtid;
                pthread_attr_t rattr;
                pthread_attr_init(&rattr);
                pthread_attr_setdetachstate(&rattr, PTHREAD_CREATE_DETACHED);
                /* Default stack — do NOT call setstacksize here. */
                if (pthread_create(&rtid, &rattr,
                        capture_restart_thread, heap) != 0) {
                    free(heap);
                    /* Fall back to inline restart (may RST the conn,
                     * but at least the config is saved). */
                    fprintf(stderr,
                        "[http] restart thread spawn failed, "
                        "falling back to inline restart\n");
                    stats_sampler_stop();
                    capture_stop();
                    if (capture_start(&next) == 0) stats_sampler_start();
                }
                pthread_attr_destroy(&rattr);
            }
        }

        char resp[96];
        snprintf(resp, sizeof(resp),
            "{\"ok\":true,\"restarted\":%d,\"ir_updated\":%d}",
            needs_restart ? 1 : 0, ir_changed);
        send_json(fd, resp);
    }
    else {
        send_text(fd, 404, "Not Found", "nope\n");
    }

done:
    shutdown(fd, SHUT_RDWR);
    close(fd);
}

static void *conn_thread(void *arg)
{
    int fd = (int)(intptr_t)arg;
    handle_conn(fd);
    return NULL;
}

/* ---------------------------------------------------------------- */
/* accept loop                                                      */
/* ---------------------------------------------------------------- */
static int g_listen_fd = -1;
static pthread_t g_accept_tid;
static int       g_accept_started = 0;

static void *accept_loop(void *arg)
{
    (void)arg;
    for (;;) {
        struct sockaddr_in sa;
        socklen_t sl = sizeof(sa);
        int cfd = accept(g_listen_fd, (struct sockaddr *)&sa, &sl);
        if (cfd < 0) {
            if (errno == EINTR) continue;
            if (g_listen_fd < 0) break;
            usleep(50 * 1000);
            continue;
        }
        /* TCP_NODELAY: avoid Nagle delays on small responses (most
         * of our responses fit in one segment, but the browser's
         * subsequent requests on the same flow benefit from
         * immediate ACKs). */
        int one = 1;
        setsockopt(cfd, IPPROTO_TCP, TCP_NODELAY, &one, sizeof(one));

        /* The listening socket has SO_LINGER(on, 0) to skip TIME_WAIT
         * on restart, but accepted sockets on some kernels/uClibc
         * inherit that option.  An inherited linger=0 means close()
         * sends RST immediately, truncating large responses (e.g.
         * config.html at 16 KB) before the client has ACKed all the
         * data — Chrome shows ERR_CONNECTION_RESET.
         * Reset linger on every accepted socket to get normal FIN. */
        struct linger cl = { .l_onoff = 0, .l_linger = 0 };
        setsockopt(cfd, SOL_SOCKET, SO_LINGER, &cl, sizeof(cl));

        pthread_t tid;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
        /* Smaller stack: each thread does a single short request,
         * 64 KiB is plenty. uClibc default is often 2 MiB which
         * makes us run out of address space when the user spam-
         * clicks the nav and 20+ threads are in flight. */
        pthread_attr_setstacksize(&attr, 64 * 1024);
        int rc = pthread_create(&tid, &attr, conn_thread,
                                (void *)(intptr_t)cfd);
        pthread_attr_destroy(&attr);
        if (rc != 0) {
            /* Thread creation failed (typically EAGAIN under load).
             * Send a 503 so the browser shows an error instead of
             * a blank page from "connection closed mid-handshake".
             * Then close and move on; the next request will likely
             * succeed once previous threads have drained. */
            const char resp[] =
                "HTTP/1.1 503 Service Unavailable\r\n"
                "Content-Length: 21\r\n"
                "Content-Type: text/plain\r\n"
                "Connection: close\r\n"
                "\r\n"
                "Server busy, retry.\n";
            (void)send(cfd, resp, sizeof(resp) - 1, MSG_NOSIGNAL);
            shutdown(cfd, SHUT_RDWR);
            close(cfd);
            fprintf(stderr, "[http] thread spawn failed (%s), 503\n",
                    strerror(rc));
        }
    }
    return NULL;
}

int http_server_start(int port)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) return -1;
    int one = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    /* SO_LINGER (onoff=1, linger=0) makes close() send RST instead
     * of FIN, skipping TIME_WAIT entirely. Without this, restarting
     * ipcd within ~60 s of a client connection sometimes hits
     * EADDRINUSE on bind() — even with SO_REUSEADDR — because the
     * kernel keeps the previous endpoint alive in TIME_WAIT and
     * REUSEADDR is finicky on uClibc/older kernels.
     *
     * Trade-off: clients that were mid-request when we shutdown
     * see a connection reset rather than a clean half-close. For
     * an HTTP control-plane that's perfectly fine. */
    struct linger lg = { .l_onoff = 1, .l_linger = 0 };
    setsockopt(fd, SOL_SOCKET, SO_LINGER, &lg, sizeof(lg));

    struct sockaddr_in sa = {0};
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = htonl(INADDR_ANY);
    sa.sin_port = htons(port);
    if (bind(fd, (struct sockaddr *)&sa, sizeof(sa)) != 0) {
        fprintf(stderr,
            "[http] bind :%d failed: %s "
            "(stale TIME_WAIT? kill any other ipcd with `killall -9 ipcd`)\n",
            port, strerror(errno));
        close(fd); return -1;
    }
    if (listen(fd, 8) != 0) { close(fd); return -1; }

    g_listen_fd = fd;
    if (pthread_create(&g_accept_tid, NULL, accept_loop, NULL) != 0) {
        close(fd); g_listen_fd = -1; return -1;
    }
    g_accept_started = 1;
    fprintf(stderr, "[http] listening on :%d\n", port);
    return 0;
}

void http_server_stop(void)
{
    int fd = g_listen_fd;
    g_listen_fd = -1;
    if (fd >= 0) {
        /* shutdown() unblocks the accept() syscall on most kernels;
         * close() alone does not on some uClibc/kernel pairs. We
         * call both: shutdown to wake the thread, close to release
         * the descriptor + port. */
        shutdown(fd, SHUT_RDWR);
        close(fd);
    }
    if (g_accept_started) {
        /* Wait for the accept loop to actually return, otherwise
         * subsequent http_server_start() can race on g_listen_fd. */
        pthread_join(g_accept_tid, NULL);
        g_accept_started = 0;
    }
    fprintf(stderr, "[http] stopped\n");
}
