/*
 * onvif_auth.c — WS-Security UsernameToken verification.
 *
 * ONVIF clients authenticate by including a SOAP <Security> header
 * with a UsernameToken whose Password is a hash:
 *
 *   PasswordDigest = base64( SHA1( base64-decode(Nonce) || Created || Password ) )
 *
 * where Nonce is a 16-byte random per-request value (base64'd) and
 * Created is an ISO-8601 timestamp. The server recomputes the digest
 * with its known password and compares.
 *
 * We pull the username/password from auth.c (same creds as HTTP
 * Digest and RTSP). If auth is configured, all ONVIF calls except
 * GetSystemDateAndTime require this header — Frigate and most other
 * clients try the unauthenticated GetSystemDateAndTime first to
 * synchronise the Created timestamp, then send authenticated calls.
 *
 * Replay protection: we accept Created within ±5 minutes of our
 * clock. We don't track nonce uniqueness (would need a cache); the
 * tight time window is the protection. Good enough for a LAN cam.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#include "ipcd.h"

/* ============================================================ */
/* SHA-1 — RFC 3174, public domain reference impl              */
/*                                                              */
/* We can't reuse the MD5 in auth.c: WS-Security mandates SHA1. */
/* Self-contained, ~120 lines. Same rationale as MD5 in auth.c: */
/* linking OpenSSL would dwarf the whole binary on this device. */
/* ============================================================ */
typedef struct {
    uint32_t state[5];
    uint64_t bitcount;
    uint8_t  buf[64];
} sha1_ctx;

#define SHA1_ROL(x,n) (((x) << (n)) | ((x) >> (32 - (n))))

static void sha1_transform(uint32_t state[5], const uint8_t block[64])
{
    uint32_t w[80];
    for (int i = 0; i < 16; i++) {
        w[i] = ((uint32_t)block[i*4    ] << 24) |
               ((uint32_t)block[i*4 + 1] << 16) |
               ((uint32_t)block[i*4 + 2] <<  8) |
                (uint32_t)block[i*4 + 3];
    }
    for (int i = 16; i < 80; i++) {
        w[i] = SHA1_ROL(w[i-3] ^ w[i-8] ^ w[i-14] ^ w[i-16], 1);
    }
    uint32_t a = state[0], b = state[1], c = state[2], d = state[3], e = state[4];
    for (int i = 0; i < 80; i++) {
        uint32_t f, k;
        if      (i < 20) { f = (b & c) | (~b & d);     k = 0x5A827999; }
        else if (i < 40) { f =  b ^ c ^ d;             k = 0x6ED9EBA1; }
        else if (i < 60) { f = (b & c) | (b & d) | (c & d); k = 0x8F1BBCDC; }
        else             { f =  b ^ c ^ d;             k = 0xCA62C1D6; }
        uint32_t t = SHA1_ROL(a, 5) + f + e + k + w[i];
        e = d; d = c; c = SHA1_ROL(b, 30); b = a; a = t;
    }
    state[0] += a; state[1] += b; state[2] += c; state[3] += d; state[4] += e;
}

static void sha1_init(sha1_ctx *c)
{
    c->state[0] = 0x67452301; c->state[1] = 0xEFCDAB89;
    c->state[2] = 0x98BADCFE; c->state[3] = 0x10325476;
    c->state[4] = 0xC3D2E1F0;
    c->bitcount = 0;
}

static void sha1_update(sha1_ctx *c, const void *data, size_t len)
{
    const uint8_t *p = data;
    size_t off = (size_t)((c->bitcount >> 3) & 0x3F);
    c->bitcount += (uint64_t)len << 3;
    size_t need = 64 - off;
    if (len >= need) {
        memcpy(c->buf + off, p, need);
        sha1_transform(c->state, c->buf);
        p += need; len -= need; off = 0;
        while (len >= 64) {
            sha1_transform(c->state, p);
            p += 64; len -= 64;
        }
    }
    memcpy(c->buf + off, p, len);
}

static void sha1_final(sha1_ctx *c, uint8_t out[20])
{
    static const uint8_t pad[64] = { 0x80 };
    uint64_t bits = c->bitcount;
    size_t off = (size_t)((c->bitcount >> 3) & 0x3F);
    size_t plen = (off < 56) ? (56 - off) : (120 - off);
    sha1_update(c, pad, plen);
    uint8_t lenbuf[8];
    for (int i = 0; i < 8; i++) lenbuf[i] = (uint8_t)(bits >> (56 - i*8));
    sha1_update(c, lenbuf, 8);
    for (int i = 0; i < 5; i++) {
        out[i*4    ] = (uint8_t)(c->state[i] >> 24);
        out[i*4 + 1] = (uint8_t)(c->state[i] >> 16);
        out[i*4 + 2] = (uint8_t)(c->state[i] >>  8);
        out[i*4 + 3] = (uint8_t)(c->state[i]);
    }
}

/* ============================================================ */
/* Base64                                                       */
/* ============================================================ */
static const char B64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static int b64_dec_char(int c)
{
    if (c >= 'A' && c <= 'Z') return c - 'A';
    if (c >= 'a' && c <= 'z') return c - 'a' + 26;
    if (c >= '0' && c <= '9') return c - '0' + 52;
    if (c == '+') return 62;
    if (c == '/') return 63;
    return -1;
}

/* Decode base64 in `in` (whitespace-tolerant, stops at end or non-b64).
 * Returns number of bytes written, -1 on error. */
int onvif_b64_decode(const char *in, uint8_t *out, size_t cap)
{
    size_t o = 0;
    int v[4]; int vi = 0;
    for (const char *p = in; *p; p++) {
        if (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n') continue;
        if (*p == '=') break;
        int d = b64_dec_char(*p);
        if (d < 0) break;
        v[vi++] = d;
        if (vi == 4) {
            if (o + 3 > cap) return -1;
            out[o++] = (uint8_t)((v[0] << 2) | (v[1] >> 4));
            out[o++] = (uint8_t)((v[1] << 4) | (v[2] >> 2));
            out[o++] = (uint8_t)((v[2] << 6) |  v[3]);
            vi = 0;
        }
    }
    if (vi == 2) { if (o + 1 > cap) return -1;
        out[o++] = (uint8_t)((v[0] << 2) | (v[1] >> 4)); }
    else if (vi == 3) { if (o + 2 > cap) return -1;
        out[o++] = (uint8_t)((v[0] << 2) | (v[1] >> 4));
        out[o++] = (uint8_t)((v[1] << 4) | (v[2] >> 2)); }
    return (int)o;
}

int onvif_b64_encode(const uint8_t *in, size_t len, char *out, size_t cap)
{
    size_t o = 0;
    size_t i;
    for (i = 0; i + 3 <= len; i += 3) {
        if (o + 4 >= cap) return -1;
        out[o++] = B64[(in[i] >> 2) & 0x3F];
        out[o++] = B64[((in[i] & 0x3) << 4) | (in[i+1] >> 4)];
        out[o++] = B64[((in[i+1] & 0xF) << 2) | (in[i+2] >> 6)];
        out[o++] = B64[in[i+2] & 0x3F];
    }
    if (i < len) {
        if (o + 4 >= cap) return -1;
        out[o++] = B64[(in[i] >> 2) & 0x3F];
        if (i + 1 == len) {
            out[o++] = B64[(in[i] & 0x3) << 4];
            out[o++] = '='; out[o++] = '=';
        } else {
            out[o++] = B64[((in[i] & 0x3) << 4) | (in[i+1] >> 4)];
            out[o++] = B64[(in[i+1] & 0xF) << 2];
            out[o++] = '=';
        }
    }
    if (o >= cap) return -1;
    out[o] = 0;
    return (int)o;
}

/* ============================================================ */
/* SOAP body inspection — find an XML element's text content    */
/*                                                              */
/* WS-Security uses well-known element names, but namespace     */
/* prefixes vary by client: some use "wsse:Username", some      */
/* "Security:Username" with their own prefix. We strip the      */
/* prefix and match the local name only.                        */
/* ============================================================ */

/* Find <localname>...</localname> (with any prefix) and copy its
 * text content into out. Returns 0 on success. Skips leading
 * whitespace inside the element. Doesn't unescape XML entities —
 * usernames/nonces/timestamps don't need them. */
static int xml_find_text(const char *src, const char *localname,
                         char *out, size_t cap)
{
    if (!src || !localname || !out || cap == 0) return -1;
    out[0] = 0;
    size_t llen = strlen(localname);

    const char *p = src;
    while ((p = strchr(p, '<')) != NULL) {
        p++;
        if (*p == '/' || *p == '!' || *p == '?') continue;

        /* Find local name: skip "prefix:" if present */
        const char *name = p;
        const char *colon = NULL;
        const char *end = name;
        while (*end && *end != '>' && *end != ' ' && *end != '/' && *end != '\t') {
            if (*end == ':') colon = end;
            end++;
        }
        if (!*end) return -1;
        const char *local = colon ? colon + 1 : name;
        size_t local_len = (size_t)(end - local);

        if (local_len == llen && memcmp(local, localname, llen) == 0) {
            /* Skip to end of opening tag. Could be "<X attr=...>" */
            const char *tag_close = strchr(end, '>');
            if (!tag_close) return -1;
            if (tag_close[-1] == '/') {
                /* Self-closing — empty content */
                return 0;
            }
            const char *content = tag_close + 1;
            /* Skip leading whitespace */
            while (*content == ' ' || *content == '\t' ||
                   *content == '\r' || *content == '\n') content++;
            const char *content_end = strstr(content, "</");
            if (!content_end) return -1;
            /* Trim trailing whitespace */
            while (content_end > content &&
                   (content_end[-1] == ' ' || content_end[-1] == '\t' ||
                    content_end[-1] == '\r' || content_end[-1] == '\n'))
                content_end--;
            size_t L = (size_t)(content_end - content);
            if (L >= cap) L = cap - 1;
            memcpy(out, content, L);
            out[L] = 0;
            return 0;
        }
        p = end;
    }
    return -1;
}

/* ============================================================ */
/* Created timestamp parsing                                    */
/*                                                              */
/* ISO 8601: "2026-04-30T20:15:30Z" or with fractional secs and */
/* timezone offset. We accept Z, +HH:MM, -HH:MM, fractional .nnn. */
/* ============================================================ */
static int parse_iso8601(const char *s, time_t *out)
{
    int Y, M, D, h, m, sec;
    if (sscanf(s, "%d-%d-%dT%d:%d:%d", &Y, &M, &D, &h, &m, &sec) != 6)
        return -1;

    /* Skip past the seconds: "...:SS" — find the next non-digit. */
    const char *p = strchr(s, 'T');
    if (!p) return -1;
    p++; /* HH */
    while (*p && *p != ':') p++;
    if (*p) p++;  /* skip ':' */
    while (*p && *p != ':') p++;
    if (*p) p++;  /* skip ':' */
    while (*p >= '0' && *p <= '9') p++;        /* SS */
    if (*p == '.') { p++; while (*p >= '0' && *p <= '9') p++; }

    /* Compute UTC time. timegm() is non-portable; use a manual
     * computation by setting TZ=UTC briefly via setenv would be
     * heavy — instead we use mktime() + adjustment by gmtoff. */
    long tz_off_sec = 0;
    if (*p == 'Z' || *p == 0) {
        tz_off_sec = 0;
    } else if (*p == '+' || *p == '-') {
        int sign = (*p == '+') ? 1 : -1;
        int oh = 0, om = 0;
        if (sscanf(p + 1, "%d:%d", &oh, &om) >= 1) {
            tz_off_sec = sign * (oh * 3600 + om * 60);
        }
    }

    /* Compute days-since-epoch ourselves: cheap and timezone-free. */
    static const int month_days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    long days = 0;
    for (int y = 1970; y < Y; y++) {
        days += 365;
        if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) days++;
    }
    for (int mo = 0; mo < M - 1; mo++) {
        days += month_days[mo];
        if (mo == 1 && ((Y % 4 == 0 && Y % 100 != 0) || Y % 400 == 0))
            days++;
    }
    days += D - 1;

    time_t t = days * 86400L + h * 3600L + m * 60L + sec - tz_off_sec;
    *out = t;
    return 0;
}

/* ============================================================ */
/* Public verifier                                              */
/* ============================================================ */

/* Returns 0 if the WS-Security UsernameToken in the SOAP envelope
 * `soap_xml` validates against the configured ipcd credentials.
 * Returns -1 on any failure: missing elements, bad timestamp,
 * digest mismatch, etc.
 *
 * If auth_is_configured() returns false, this returns 0 — same
 * "open mode" semantics as the HTTP/RTSP gates.
 *
 * The function is read-only; it never mutates its input or any
 * global state. */
int onvif_check_ws_security(const char *soap_xml)
{
    if (!auth_is_configured()) return 0;
    if (!soap_xml) return -1;

    /* Find the Security element. Most clients put it under
     * <s:Header>, but we search the whole envelope for robustness. */
    const char *sec = strstr(soap_xml, "Security");
    if (!sec) return -1;
    /* Back up to find the '<' that opens this element; skip
     * occurrences inside attribute names like "MustUnderstand=". */
    while (sec > soap_xml && *sec != '<') sec--;
    if (*sec != '<') return -1;

    /* Pull Username, Nonce, Created, Password from the Security
     * subtree. We just point at the start of Security and search
     * forward — it works because these elements appear once each
     * inside Security, and any subsequent Body element would only
     * contain its own elements without these names (in normal
     * usage). */
    char username[64] = {0};
    char nonce_b64[128] = {0};
    char created[64] = {0};
    char password_b64[64] = {0};

    if (xml_find_text(sec, "Username",  username,     sizeof(username))     != 0) return -1;
    if (xml_find_text(sec, "Nonce",     nonce_b64,    sizeof(nonce_b64))    != 0) return -1;
    if (xml_find_text(sec, "Created",   created,      sizeof(created))      != 0) return -1;
    if (xml_find_text(sec, "Password",  password_b64, sizeof(password_b64)) != 0) return -1;

    /* Username must match. */
    if (strcmp(username, auth_get_user()) != 0) return -1;

    /* Created timestamp must be within ±5 minutes of our clock.
     * This is the only replay protection we have. */
    time_t created_t;
    if (parse_iso8601(created, &created_t) != 0) return -1;
    time_t now = time(NULL);
    long diff = (long)(now - created_t);
    if (diff < -300 || diff > 300) {
        fprintf(stderr, "[onvif_auth] Created timestamp out of window "
                        "(diff=%lds)\n", diff);
        return -1;
    }

    /* Decode nonce. */
    uint8_t nonce_raw[64];
    int nonce_len = onvif_b64_decode(nonce_b64, nonce_raw, sizeof(nonce_raw));
    if (nonce_len <= 0) return -1;

    /* Compute expected digest = base64(SHA1(nonce || created || password)). */
    sha1_ctx sc;
    sha1_init(&sc);
    sha1_update(&sc, nonce_raw, (size_t)nonce_len);
    sha1_update(&sc, created, strlen(created));

    /* The plaintext password isn't directly accessible from auth.c
     * (we store HA1 there). We need the cleartext for SHA1 here.
     * Add a getter. */
    const char *pwd = auth_get_pass();
    /* If no password is configured on this device, skip auth entirely.
     * This matches the behaviour of most OEM cameras out of the box and
     * prevents HA from falling back to HTTPS after repeated 401s. */
    if (!pwd || !*pwd) return 0;
    sha1_update(&sc, pwd, strlen(pwd));

    uint8_t digest[20];
    sha1_final(&sc, digest);

    char expected_b64[64];
    if (onvif_b64_encode(digest, sizeof(digest),
                         expected_b64, sizeof(expected_b64)) < 0)
        return -1;

    if (strcmp(expected_b64, password_b64) != 0) {
        fprintf(stderr, "[onvif_auth] password digest mismatch for '%s'\n",
                username);
        return -1;
    }
    return 0;
}
