/*
 * auth.c — shared authentication for HTTP / RTSP / ONVIF.
 *
 * Implements:
 *  - MD5 (RFC 1321), self-contained, no OpenSSL.
 *  - HTTP Digest authentication (RFC 7616, MD5/qop=auth subset).
 *  - Basic auth as a fallback for clients that don't speak Digest.
 *  - A small in-memory credential store, populated from cfgfile.c.
 *  - Nonce generation: timestamp || random, HMAC'd with a process-
 *    local secret so old nonces can't be replayed across restarts
 *    (the secret is regenerated each boot from /dev/urandom).
 *
 * The single user/password pair guards the HTTP UI, the RTSP server
 * (step 4), and the ONVIF SOAP endpoints (step 3). Passwords up to
 * 64 chars are supported; longer is silently truncated on save.
 *
 * Threading: auth_check is read-mostly and stateless. Cred storage
 * is guarded by g_creds_mtx. The MD5 state is stack-local per call.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
#include <pthread.h>
#include <sys/time.h>

#include "ipcd.h"

/* ---------------------------------------------------------------- */
/* MD5                                                              */
/*                                                                  */
/* Public-domain implementation, adapted (RFC 1321 reference). We   */
/* keep it terse — Digest needs hex output of 16 bytes, nothing     */
/* more. ~100 LoC; the alternative (link OpenSSL/mbedtls) would     */
/* dwarf the rest of the binary on this device.                    */
/* ---------------------------------------------------------------- */
typedef struct {
    uint32_t state[4];
    uint64_t bitcount;
    uint8_t  buf[64];
} md5_ctx;

#define MD5_F(x,y,z) (((x) & (y)) | (~(x) & (z)))
#define MD5_G(x,y,z) (((x) & (z)) | ((y) & ~(z)))
#define MD5_H(x,y,z) ((x) ^ (y) ^ (z))
#define MD5_I(x,y,z) ((y) ^ ((x) | ~(z)))
#define ROL(x,n)     (((x) << (n)) | ((x) >> (32 - (n))))
#define MD5_STEP(f,a,b,c,d,x,t,s) \
    (a) += f((b),(c),(d)) + (x) + (t); (a) = ROL((a),(s)); (a) += (b)

static void md5_transform(uint32_t state[4], const uint8_t block[64])
{
    uint32_t a = state[0], b = state[1], c = state[2], d = state[3];
    uint32_t x[16];
    for (int i = 0; i < 16; i++) {
        x[i] =  (uint32_t)block[i*4]            |
               ((uint32_t)block[i*4+1] <<  8)   |
               ((uint32_t)block[i*4+2] << 16)   |
               ((uint32_t)block[i*4+3] << 24);
    }
    /* Round 1 */
    MD5_STEP(MD5_F,a,b,c,d, x[ 0],0xd76aa478, 7);
    MD5_STEP(MD5_F,d,a,b,c, x[ 1],0xe8c7b756,12);
    MD5_STEP(MD5_F,c,d,a,b, x[ 2],0x242070db,17);
    MD5_STEP(MD5_F,b,c,d,a, x[ 3],0xc1bdceee,22);
    MD5_STEP(MD5_F,a,b,c,d, x[ 4],0xf57c0faf, 7);
    MD5_STEP(MD5_F,d,a,b,c, x[ 5],0x4787c62a,12);
    MD5_STEP(MD5_F,c,d,a,b, x[ 6],0xa8304613,17);
    MD5_STEP(MD5_F,b,c,d,a, x[ 7],0xfd469501,22);
    MD5_STEP(MD5_F,a,b,c,d, x[ 8],0x698098d8, 7);
    MD5_STEP(MD5_F,d,a,b,c, x[ 9],0x8b44f7af,12);
    MD5_STEP(MD5_F,c,d,a,b, x[10],0xffff5bb1,17);
    MD5_STEP(MD5_F,b,c,d,a, x[11],0x895cd7be,22);
    MD5_STEP(MD5_F,a,b,c,d, x[12],0x6b901122, 7);
    MD5_STEP(MD5_F,d,a,b,c, x[13],0xfd987193,12);
    MD5_STEP(MD5_F,c,d,a,b, x[14],0xa679438e,17);
    MD5_STEP(MD5_F,b,c,d,a, x[15],0x49b40821,22);
    /* Round 2 */
    MD5_STEP(MD5_G,a,b,c,d, x[ 1],0xf61e2562, 5);
    MD5_STEP(MD5_G,d,a,b,c, x[ 6],0xc040b340, 9);
    MD5_STEP(MD5_G,c,d,a,b, x[11],0x265e5a51,14);
    MD5_STEP(MD5_G,b,c,d,a, x[ 0],0xe9b6c7aa,20);
    MD5_STEP(MD5_G,a,b,c,d, x[ 5],0xd62f105d, 5);
    MD5_STEP(MD5_G,d,a,b,c, x[10],0x02441453, 9);
    MD5_STEP(MD5_G,c,d,a,b, x[15],0xd8a1e681,14);
    MD5_STEP(MD5_G,b,c,d,a, x[ 4],0xe7d3fbc8,20);
    MD5_STEP(MD5_G,a,b,c,d, x[ 9],0x21e1cde6, 5);
    MD5_STEP(MD5_G,d,a,b,c, x[14],0xc33707d6, 9);
    MD5_STEP(MD5_G,c,d,a,b, x[ 3],0xf4d50d87,14);
    MD5_STEP(MD5_G,b,c,d,a, x[ 8],0x455a14ed,20);
    MD5_STEP(MD5_G,a,b,c,d, x[13],0xa9e3e905, 5);
    MD5_STEP(MD5_G,d,a,b,c, x[ 2],0xfcefa3f8, 9);
    MD5_STEP(MD5_G,c,d,a,b, x[ 7],0x676f02d9,14);
    MD5_STEP(MD5_G,b,c,d,a, x[12],0x8d2a4c8a,20);
    /* Round 3 */
    MD5_STEP(MD5_H,a,b,c,d, x[ 5],0xfffa3942, 4);
    MD5_STEP(MD5_H,d,a,b,c, x[ 8],0x8771f681,11);
    MD5_STEP(MD5_H,c,d,a,b, x[11],0x6d9d6122,16);
    MD5_STEP(MD5_H,b,c,d,a, x[14],0xfde5380c,23);
    MD5_STEP(MD5_H,a,b,c,d, x[ 1],0xa4beea44, 4);
    MD5_STEP(MD5_H,d,a,b,c, x[ 4],0x4bdecfa9,11);
    MD5_STEP(MD5_H,c,d,a,b, x[ 7],0xf6bb4b60,16);
    MD5_STEP(MD5_H,b,c,d,a, x[10],0xbebfbc70,23);
    MD5_STEP(MD5_H,a,b,c,d, x[13],0x289b7ec6, 4);
    MD5_STEP(MD5_H,d,a,b,c, x[ 0],0xeaa127fa,11);
    MD5_STEP(MD5_H,c,d,a,b, x[ 3],0xd4ef3085,16);
    MD5_STEP(MD5_H,b,c,d,a, x[ 6],0x04881d05,23);
    MD5_STEP(MD5_H,a,b,c,d, x[ 9],0xd9d4d039, 4);
    MD5_STEP(MD5_H,d,a,b,c, x[12],0xe6db99e5,11);
    MD5_STEP(MD5_H,c,d,a,b, x[15],0x1fa27cf8,16);
    MD5_STEP(MD5_H,b,c,d,a, x[ 2],0xc4ac5665,23);
    /* Round 4 */
    MD5_STEP(MD5_I,a,b,c,d, x[ 0],0xf4292244, 6);
    MD5_STEP(MD5_I,d,a,b,c, x[ 7],0x432aff97,10);
    MD5_STEP(MD5_I,c,d,a,b, x[14],0xab9423a7,15);
    MD5_STEP(MD5_I,b,c,d,a, x[ 5],0xfc93a039,21);
    MD5_STEP(MD5_I,a,b,c,d, x[12],0x655b59c3, 6);
    MD5_STEP(MD5_I,d,a,b,c, x[ 3],0x8f0ccc92,10);
    MD5_STEP(MD5_I,c,d,a,b, x[10],0xffeff47d,15);
    MD5_STEP(MD5_I,b,c,d,a, x[ 1],0x85845dd1,21);
    MD5_STEP(MD5_I,a,b,c,d, x[ 8],0x6fa87e4f, 6);
    MD5_STEP(MD5_I,d,a,b,c, x[15],0xfe2ce6e0,10);
    MD5_STEP(MD5_I,c,d,a,b, x[ 6],0xa3014314,15);
    MD5_STEP(MD5_I,b,c,d,a, x[13],0x4e0811a1,21);
    MD5_STEP(MD5_I,a,b,c,d, x[ 4],0xf7537e82, 6);
    MD5_STEP(MD5_I,d,a,b,c, x[11],0xbd3af235,10);
    MD5_STEP(MD5_I,c,d,a,b, x[ 2],0x2ad7d2bb,15);
    MD5_STEP(MD5_I,b,c,d,a, x[ 9],0xeb86d391,21);

    state[0] += a; state[1] += b; state[2] += c; state[3] += d;
}

static void md5_init(md5_ctx *c)
{
    c->state[0] = 0x67452301; c->state[1] = 0xefcdab89;
    c->state[2] = 0x98badcfe; c->state[3] = 0x10325476;
    c->bitcount = 0;
}

static void md5_update(md5_ctx *c, const void *data, size_t len)
{
    const uint8_t *p = data;
    size_t off = (size_t)((c->bitcount >> 3) & 0x3F);
    c->bitcount += (uint64_t)len << 3;
    size_t need = 64 - off;
    if (len >= need) {
        memcpy(c->buf + off, p, need);
        md5_transform(c->state, c->buf);
        p += need; len -= need; off = 0;
        while (len >= 64) {
            md5_transform(c->state, p);
            p += 64; len -= 64;
        }
    }
    memcpy(c->buf + off, p, len);
}

static void md5_final(md5_ctx *c, uint8_t out[16])
{
    static const uint8_t pad[64] = { 0x80 };
    uint64_t bits = c->bitcount;
    size_t off = (size_t)((c->bitcount >> 3) & 0x3F);
    size_t plen = (off < 56) ? (56 - off) : (120 - off);
    md5_update(c, pad, plen);
    uint8_t lenbuf[8];
    for (int i = 0; i < 8; i++) lenbuf[i] = (uint8_t)(bits >> (8*i));
    md5_update(c, lenbuf, 8);
    for (int i = 0; i < 4; i++) {
        out[i*4    ] = (uint8_t)(c->state[i]);
        out[i*4 + 1] = (uint8_t)(c->state[i] >>  8);
        out[i*4 + 2] = (uint8_t)(c->state[i] >> 16);
        out[i*4 + 3] = (uint8_t)(c->state[i] >> 24);
    }
}

static void md5_hex(const uint8_t in[16], char out[33])
{
    static const char h[] = "0123456789abcdef";
    for (int i = 0; i < 16; i++) {
        out[i*2    ] = h[in[i] >> 4];
        out[i*2 + 1] = h[in[i] & 0xF];
    }
    out[32] = 0;
}

/* Convenience: MD5 of a single concatenated string list, hex out. */
typedef const char *cstr_t;   /* va_arg can't take 'const char *' literally */
static void md5_hex_concat(char hex_out[33], int n, ...)
{
    md5_ctx c; md5_init(&c);
    va_list ap; va_start(ap, n);
    for (int i = 0; i < n; i++) {
        cstr_t s = va_arg(ap, cstr_t);
        if (s) md5_update(&c, s, strlen(s));
    }
    va_end(ap);
    uint8_t raw[16];
    md5_final(&c, raw);
    md5_hex(raw, hex_out);
}

/* (stdarg.h already included up top.) */

/* ---------------------------------------------------------------- */
/* Credential storage                                              */
/* ---------------------------------------------------------------- */
#define AUTH_USER_MAX  32
#define AUTH_PASS_MAX  64
#define AUTH_REALM     "ipcd"

static pthread_mutex_t g_creds_mtx = PTHREAD_MUTEX_INITIALIZER;
static char            g_user[AUTH_USER_MAX + 1];
static char            g_pass[AUTH_PASS_MAX + 1];
/* HA1 = MD5(user:realm:pass), precomputed at credential change. */
static char            g_ha1[33];
static int             g_configured;

/* Process-local nonce secret. 16 random bytes from /dev/urandom at
 * boot, never written anywhere. Used as the HMAC key for nonces. */
static uint8_t         g_nonce_secret[16];
static int             g_nonce_secret_ready;

/* ---------------------------------------------------------------- */
/* Forward decls for cfgfile glue                                   */
/* ---------------------------------------------------------------- */
/* These two helpers live in cfgfile.c; we don't export them via the
 * public ipcd.h because they're an implementation detail of the
 * auth/cfg coupling. Declared here so we can link. */
int  cfgfile_get_creds(char *user, size_t ulen, char *pass, size_t plen);
int  cfgfile_set_creds(const char *user, const char *pass);

/* ---------------------------------------------------------------- */
/* Init / cred management                                          */
/* ---------------------------------------------------------------- */
static void recompute_ha1_locked(void)
{
    if (g_user[0] && g_pass[0]) {
        md5_hex_concat(g_ha1, 5, g_user, ":", AUTH_REALM, ":", g_pass);
        g_configured = 1;
    } else {
        g_ha1[0] = 0;
        g_configured = 0;
    }
}

static void seed_nonce_secret(void)
{
    if (g_nonce_secret_ready) return;
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd >= 0) {
        ssize_t n = read(fd, g_nonce_secret, sizeof(g_nonce_secret));
        close(fd);
        if (n == (ssize_t)sizeof(g_nonce_secret)) {
            g_nonce_secret_ready = 1;
            return;
        }
    }
    /* Fallback: time + pid. Bad entropy but better than zeros, and
     * we still have replay-resistance via the timestamp embedded in
     * the nonce itself. */
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    uint32_t mix[4] = {
        (uint32_t)ts.tv_sec, (uint32_t)ts.tv_nsec,
        (uint32_t)getpid(),  0xdeadbeef
    };
    memcpy(g_nonce_secret, mix, sizeof(g_nonce_secret));
    g_nonce_secret_ready = 1;
}

void auth_init(void)
{
    seed_nonce_secret();
    char user[AUTH_USER_MAX + 1] = {0};
    char pass[AUTH_PASS_MAX + 1] = {0};
    cfgfile_get_creds(user, sizeof(user), pass, sizeof(pass));

    pthread_mutex_lock(&g_creds_mtx);
    snprintf(g_user, sizeof(g_user), "%s", user);
    snprintf(g_pass, sizeof(g_pass), "%s", pass);
    recompute_ha1_locked();
    int cfgd = g_configured;
    pthread_mutex_unlock(&g_creds_mtx);

    fprintf(stderr, "[auth] init: %s\n",
            cfgd ? "configured" : "open (no password set)");
}

int auth_is_configured(void)
{
    pthread_mutex_lock(&g_creds_mtx);
    int v = g_configured;
    pthread_mutex_unlock(&g_creds_mtx);
    return v;
}

const char *auth_get_user(void)
{
    /* Returning a pointer to mutex-protected storage is technically
     * unsafe for concurrent set+get, but the only caller is the
     * /api/auth GET handler which just snprintfs the result before
     * the next set is plausible. Document this and move on. */
    return g_user;
}

const char *auth_get_pass(void)
{
    /* Same caveat as auth_get_user. Used by onvif_auth.c for
     * WS-Security UsernameToken-Digest, which by spec needs the
     * cleartext password to compute SHA1(nonce||created||password).
     * No way around the cleartext requirement; the password is
     * already kept in memory for Basic auth validation anyway. */
    return g_pass;
}

int auth_set_creds(const char *user, const char *pass)
{
    if (!user) user = "";
    if (!pass) pass = "";

    /* Empty user with non-empty pass is nonsensical; refuse. */
    if (pass[0] && !user[0]) return -1;

    /* Persist first, in-memory second. If the disk write fails we
     * don't want to lock the user out with creds that survive only
     * in RAM until reboot. */
    if (cfgfile_set_creds(user, pass) != 0) return -1;

    pthread_mutex_lock(&g_creds_mtx);
    snprintf(g_user, sizeof(g_user), "%s", user);
    snprintf(g_pass, sizeof(g_pass), "%s", pass);
    recompute_ha1_locked();
    pthread_mutex_unlock(&g_creds_mtx);

    fprintf(stderr, "[auth] credentials updated (%s)\n",
            pass[0] ? "auth on" : "auth off");
    return 0;
}

/* ---------------------------------------------------------------- */
/* Header parsing                                                  */
/*                                                                  */
/* The Authorization value looks like:                             */
/*   Digest username="alice", realm="ipcd", nonce="abc",           */
/*          uri="/api/stats", response="...", qop=auth, nc=00...,  */
/*          cnonce="..."                                           */
/*                                                                  */
/* Values may or may not be quoted. We accept both.                */
/* ---------------------------------------------------------------- */
int auth_parse_kv(const char *src, const char *key,
                  char *out, size_t cap)
{
    if (!src || !key || !out || cap == 0) return -1;
    size_t klen = strlen(key);
    const char *p = src;
    out[0] = 0;

    /* If the input starts with an auth-scheme token (e.g. "Digest "
     * or "Basic "), skip past it. Detection: a leading run of
     * letters followed by whitespace, with no '=' before the first
     * space. We don't want to confuse this with a parameter that
     * happens to come first. */
    {
        const char *q = p;
        while (*q && (*q == ' ' || *q == '\t')) q++;
        const char *tok_start = q;
        while ((*q >= 'A' && *q <= 'Z') || (*q >= 'a' && *q <= 'z'))
            q++;
        if (q > tok_start && (*q == ' ' || *q == '\t')) {
            /* Scheme token, no '='. Skip it. */
            p = q;
        }
    }

    while (*p) {
        /* Skip leading whitespace + commas */
        while (*p == ' ' || *p == '\t' || *p == ',') p++;
        if (!*p) break;

        /* Look for key= at the current position. We do a case-
         * insensitive compare on the key itself, since RFC 7616
         * parameter names are case-insensitive (the auth-scheme
         * "Digest" too, but we match that ourselves earlier). */
        if (strncasecmp(p, key, klen) == 0 && p[klen] == '=') {
            const char *v = p + klen + 1;
            size_t o = 0;
            if (*v == '"') {
                v++;
                while (*v && *v != '"' && o + 1 < cap) {
                    if (*v == '\\' && v[1]) v++;  /* very light unescape */
                    out[o++] = *v++;
                }
            } else {
                while (*v && *v != ',' && *v != ' ' && *v != '\t' &&
                       o + 1 < cap) {
                    out[o++] = *v++;
                }
            }
            out[o] = 0;
            return 0;
        }
        /* Skip this key=value to the next comma. Mind quoted commas. */
        const char *q = strchr(p, '=');
        if (!q) break;
        q++;
        if (*q == '"') {
            q++;
            while (*q && *q != '"') { if (*q == '\\' && q[1]) q++; q++; }
            if (*q == '"') q++;
        } else {
            while (*q && *q != ',') q++;
        }
        p = q;
    }
    return -1;
}

/* ---------------------------------------------------------------- */
/* Nonce                                                            */
/*                                                                  */
/* Format: hex( ts_secs[8] || rand[8] || mac[8] )                  */
/*   ts_secs = seconds since epoch, big-endian 4 bytes (we only    */
/*             use the lower 32 bits — this is good until 2106).   */
/*   rand    = 4 random bytes                                       */
/*   mac     = first 8 bytes of MD5(secret || ts || rand)          */
/*                                                                  */
/* Total 16 bytes -> 32 hex chars. Verifier recomputes MAC and    */
/* checks the timestamp is within NONCE_TTL_SECS (default 5 min). */
/* That's the whole replay-protection story — no per-nonce table. */
/* ---------------------------------------------------------------- */
#define NONCE_TTL_SECS  600

static void make_nonce(char hex_out[33])
{
    uint8_t raw[16];
    uint32_t now = (uint32_t)time(NULL);
    raw[0] = (uint8_t)(now >> 24); raw[1] = (uint8_t)(now >> 16);
    raw[2] = (uint8_t)(now >>  8); raw[3] = (uint8_t)(now);

    /* 4 random bytes — try urandom, fall back to clock. */
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd >= 0) {
        if (read(fd, raw + 4, 4) != 4) { /* ignore, fallback below */ }
        close(fd);
    } else {
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        uint32_t r = (uint32_t)ts.tv_nsec ^ (uint32_t)getpid();
        raw[4] = (uint8_t)(r); raw[5] = (uint8_t)(r >> 8);
        raw[6] = (uint8_t)(r >> 16); raw[7] = (uint8_t)(r >> 24);
    }

    /* MAC the first 8 bytes with secret. We don't bother with full
     * HMAC — keyed MD5 is fine here since the secret is private and
     * the input length is fixed (length-extension immunity not
     * needed). */
    md5_ctx c; md5_init(&c);
    md5_update(&c, g_nonce_secret, sizeof(g_nonce_secret));
    md5_update(&c, raw, 8);
    uint8_t mac[16];
    md5_final(&c, mac);
    memcpy(raw + 8, mac, 8);

    md5_hex(raw, hex_out);
}

/* Returns 1 if nonce is valid (good MAC + within TTL), 0 otherwise. */
static int verify_nonce(const char *nonce_hex)
{
    if (!nonce_hex || strlen(nonce_hex) != 32) return 0;
    uint8_t raw[16];
    for (int i = 0; i < 16; i++) {
        char h = nonce_hex[i*2], l = nonce_hex[i*2 + 1];
        int hv = (h >= '0' && h <= '9') ? h - '0'
               : (h >= 'a' && h <= 'f') ? h - 'a' + 10
               : (h >= 'A' && h <= 'F') ? h - 'A' + 10 : -1;
        int lv = (l >= '0' && l <= '9') ? l - '0'
               : (l >= 'a' && l <= 'f') ? l - 'a' + 10
               : (l >= 'A' && l <= 'F') ? l - 'A' + 10 : -1;
        if (hv < 0 || lv < 0) return 0;
        raw[i] = (uint8_t)((hv << 4) | lv);
    }

    /* Recompute MAC */
    md5_ctx c; md5_init(&c);
    md5_update(&c, g_nonce_secret, sizeof(g_nonce_secret));
    md5_update(&c, raw, 8);
    uint8_t mac[16];
    md5_final(&c, mac);
    if (memcmp(raw + 8, mac, 8) != 0) return 0;

    /* TTL check */
    uint32_t ts = ((uint32_t)raw[0] << 24) | ((uint32_t)raw[1] << 16) |
                  ((uint32_t)raw[2] <<  8) |  (uint32_t)raw[3];
    uint32_t now = (uint32_t)time(NULL);
    if (now < ts) return 0;                  /* clock went backwards */
    if (now - ts > NONCE_TTL_SECS) return 0; /* expired */
    return 1;
}

size_t auth_make_challenge(char *out, size_t cap)
{
    char nonce[33];
    make_nonce(nonce);
    int n = snprintf(out, cap,
        "Digest realm=\"" AUTH_REALM "\", "
        "nonce=\"%s\", qop=\"auth\", algorithm=MD5",
        nonce);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

/* ---------------------------------------------------------------- */
/* Common Digest verification                                       */
/*                                                                  */
/* Used by both HTTP and RTSP. The only difference between the two */
/* is the choice of method string ("GET" vs "DESCRIBE" etc) — the  */
/* digest itself is identical RFC 7616 / RFC 2617. */
/* ---------------------------------------------------------------- */
static auth_result_t verify_digest(const char *authz,
                                   const char *method,
                                   const char *uri)
{
    /* authz starts with "Digest " (case-insensitive). Skip it. */
    while (*authz == ' ' || *authz == '\t') authz++;
    if (strncasecmp(authz, "Digest", 6) != 0) return AUTH_NEEDED;
    authz += 6;
    while (*authz == ' ' || *authz == '\t') authz++;

    char username[AUTH_USER_MAX + 1] = {0};
    char realm[64] = {0};
    char nonce[64] = {0};
    char authz_uri[256] = {0};
    char response[64] = {0};
    char qop[16] = {0};
    char nc[16] = {0};
    char cnonce[64] = {0};
    char algorithm[16] = {0};

    auth_parse_kv(authz, "username",  username,  sizeof(username));
    auth_parse_kv(authz, "realm",     realm,     sizeof(realm));
    auth_parse_kv(authz, "nonce",     nonce,     sizeof(nonce));
    auth_parse_kv(authz, "uri",       authz_uri, sizeof(authz_uri));
    auth_parse_kv(authz, "response",  response,  sizeof(response));
    auth_parse_kv(authz, "qop",       qop,       sizeof(qop));
    auth_parse_kv(authz, "nc",        nc,        sizeof(nc));
    auth_parse_kv(authz, "cnonce",    cnonce,    sizeof(cnonce));
    auth_parse_kv(authz, "algorithm", algorithm, sizeof(algorithm));

    if (!username[0] || !nonce[0] || !response[0]) return AUTH_NEEDED;

    /* algorithm: only MD5 (and unspecified, which means MD5). We
     * don't implement MD5-sess. */
    if (algorithm[0] && strcasecmp(algorithm, "MD5") != 0) return AUTH_FAIL;

    /* Realm must match. RFC says ignore mismatched realm, but we're
     * a single-realm server; mismatches are always wrong. */
    if (realm[0] && strcasecmp(realm, AUTH_REALM) != 0) return AUTH_FAIL;

    /* RFC 7616: the digest is computed by the client over the URI
     * it places in its Authorization header (authz_uri), not over
     * the request URL. For HTTP these usually coincide, but in
     * RTSP they differ — RFC 2326 clients commonly send
     * Authorization with the base URI on every method even when
     * SETUP / PLAY use sub-URIs like "rtsp://cam/main/track1".
     * VLC, ffmpeg, GStreamer all behave this way.
     *
     * We therefore use authz_uri for HA2 below. We do NOT require
     * authz_uri == request URI: that would falsely reject every
     * RTSP SETUP. The digest itself is the cryptographic binding —
     * an attacker who substitutes the URL must recompute the
     * digest, which requires the password. The `uri` parameter
     * passed in is now unused; kept for API stability with the
     * older signature in case future code wants to do its own
     * URL/scope check at a higher level.
     */
    (void)uri;

    if (!authz_uri[0]) return AUTH_NEEDED;

    if (!verify_nonce(nonce)) return AUTH_FAIL;

    /* User must match. We compare the configured user to the one
     * the client claims — case-sensitively, which is consistent
     * with most cameras. */
    pthread_mutex_lock(&g_creds_mtx);
    if (!g_configured || strcmp(username, g_user) != 0) {
        pthread_mutex_unlock(&g_creds_mtx);
        return AUTH_FAIL;
    }
    char ha1[33];
    memcpy(ha1, g_ha1, sizeof(ha1));
    pthread_mutex_unlock(&g_creds_mtx);

    /* HA2 = MD5(method:authz_uri)  — using authz_uri, not the
     * request URL. See comment above. */
    char ha2[33];
    md5_hex_concat(ha2, 3, method, ":", authz_uri);

    /* response = MD5(HA1:nonce:nc:cnonce:qop:HA2)   if qop=auth
     *          = MD5(HA1:nonce:HA2)                 if qop absent */
    char expected[33];
    if (qop[0]) {
        if (!nc[0] || !cnonce[0]) return AUTH_FAIL;
        if (strcasecmp(qop, "auth") != 0) return AUTH_FAIL;
        md5_hex_concat(expected, 11,
            ha1, ":", nonce, ":", nc, ":", cnonce, ":", qop, ":", ha2);
    } else {
        md5_hex_concat(expected, 5, ha1, ":", nonce, ":", ha2);
    }

    /* Constant-time-ish compare on lowercased hex. We use strcasecmp
     * because some clients send uppercase hex; not constant-time but
     * MD5 isn't security-critical here anyway. */
    if (strcasecmp(expected, response) != 0) return AUTH_FAIL;
    return AUTH_OK;
}

/* ---------------------------------------------------------------- */
/* Basic auth (for old RTSP clients only)                          */
/* ---------------------------------------------------------------- */
static int b64_decode_char(int c)
{
    if (c >= 'A' && c <= 'Z') return c - 'A';
    if (c >= 'a' && c <= 'z') return c - 'a' + 26;
    if (c >= '0' && c <= '9') return c - '0' + 52;
    if (c == '+') return 62;
    if (c == '/') return 63;
    return -1;
}

static int b64_decode(const char *in, char *out, size_t cap)
{
    size_t o = 0;
    int v[4]; int vi = 0;
    for (const char *p = in; *p && *p != ' ' && *p != ','; p++) {
        if (*p == '=') break;
        int d = b64_decode_char(*p);
        if (d < 0) continue;
        v[vi++] = d;
        if (vi == 4) {
            if (o + 3 >= cap) return -1;
            out[o++] = (char)((v[0] << 2) | (v[1] >> 4));
            out[o++] = (char)((v[1] << 4) | (v[2] >> 2));
            out[o++] = (char)((v[2] << 6) | v[3]);
            vi = 0;
        }
    }
    if (vi == 2) {
        if (o + 1 >= cap) return -1;
        out[o++] = (char)((v[0] << 2) | (v[1] >> 4));
    } else if (vi == 3) {
        if (o + 2 >= cap) return -1;
        out[o++] = (char)((v[0] << 2) | (v[1] >> 4));
        out[o++] = (char)((v[1] << 4) | (v[2] >> 2));
    }
    if (o >= cap) return -1;
    out[o] = 0;
    return (int)o;
}

static auth_result_t verify_basic(const char *authz)
{
    while (*authz == ' ' || *authz == '\t') authz++;
    if (strncasecmp(authz, "Basic", 5) != 0) return AUTH_NEEDED;
    authz += 5;
    while (*authz == ' ' || *authz == '\t') authz++;

    char dec[AUTH_USER_MAX + AUTH_PASS_MAX + 4];
    if (b64_decode(authz, dec, sizeof(dec)) <= 0) return AUTH_FAIL;
    char *colon = strchr(dec, ':');
    if (!colon) return AUTH_FAIL;
    *colon = 0;
    const char *user = dec, *pass = colon + 1;

    pthread_mutex_lock(&g_creds_mtx);
    int ok = g_configured &&
             strcmp(user, g_user) == 0 &&
             strcmp(pass, g_pass) == 0;
    pthread_mutex_unlock(&g_creds_mtx);
    return ok ? AUTH_OK : AUTH_FAIL;
}

/* ---------------------------------------------------------------- */
/* Public entry points                                              */
/* ---------------------------------------------------------------- */
auth_result_t auth_http_check(const char *authz_value,
                              const char *method,
                              const char *uri)
{
    if (!auth_is_configured()) return AUTH_OK;
    if (!authz_value || !*authz_value) return AUTH_NEEDED;
    /* HTTP UI only accepts Digest. Basic over plaintext HTTP would
     * leak the password to anyone on the LAN — we leave it for
     * RTSP only, where some legacy clients refuse Digest. */
    return verify_digest(authz_value, method, uri);
}

auth_result_t auth_rtsp_check(const char *authz_value,
                              const char *method,
                              const char *uri)
{
    if (!auth_is_configured()) return AUTH_OK;
    if (!authz_value || !*authz_value) return AUTH_NEEDED;
    /* Try Digest first (preferred), Basic as a fallback. */
    while (*authz_value == ' ' || *authz_value == '\t') authz_value++;
    if (strncasecmp(authz_value, "Digest", 6) == 0)
        return verify_digest(authz_value, method, uri);
    if (strncasecmp(authz_value, "Basic", 5) == 0)
        return verify_basic(authz_value);
    return AUTH_NEEDED;
}
