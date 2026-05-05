/*
 * onvif_events.c — ONVIF Events service (PullPoint subscriptions
 * + simple motion detector based on ak_vpss_md_get_stat).
 *
 * Frigate (and most ONVIF clients with motion support) use the
 * PullPoint pattern:
 *
 *   1) Client calls CreatePullPointSubscription. We allocate a
 *      subscription, return its address (just our events_service
 *      URL with a ?token= query param).
 *   2) Client periodically calls PullMessages on that URL, with a
 *      timeout (PT60S typical). We block up to that timeout,
 *      returning any motion events that have queued since the last
 *      pull.
 *   3) Client calls Unsubscribe to clean up. (We also auto-clean
 *      subscriptions older than the renewal time.)
 *
 * The motion detector is a separate thread polling
 * ak_vpss_md_get_stat() every ~200ms. It computes a sum of the
 * 1536-byte stat buffer (which is actually the 3D-NR delta data —
 * see comments below) and applies hysteresis: N consecutive
 * samples above threshold = motion ON, M consecutive samples below
 * = motion OFF. Each transition is queued as an event for every
 * active subscription.
 *
 * No event filtering by topic: we always emit
 * tns1:RuleEngine/CellMotionDetector/Motion. Frigate is happy with
 * that. Real ONVIF Profile T has a richer event schema; we don't
 * need it.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>

#include "ipcd.h"

/* ============================================================ */
/* SDK extern for motion stats — same as cap_pipeline.c uses    */
/* but we only need the read API.                               */
/* ============================================================ */
extern int ak_vpss_md_get_stat(int dev, void *buf);

/* ============================================================ */
/* SOAP envelope (minimal, our own — events service doesn't     */
/* share the onvif.c envelope to keep the modules independent). */
/* ============================================================ */
#define EV_ENV_OPEN \
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"                            \
    "<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\""       \
    " xmlns:wsa=\"http://www.w3.org/2005/08/addressing\""                   \
    " xmlns:wsnt=\"http://docs.oasis-open.org/wsn/b-2\""                    \
    " xmlns:tev=\"http://www.onvif.org/ver10/events/wsdl\""                 \
    " xmlns:tt=\"http://www.onvif.org/ver10/schema\""                       \
    " xmlns:tns1=\"http://www.onvif.org/ver10/topics\">"                    \
    "<s:Body>"
#define EV_ENV_CLOSE  "</s:Body></s:Envelope>"

/* ============================================================ */
/* Subscription state                                           */
/* ============================================================ */
#define MAX_SUBSCRIPTIONS  4
#define MAX_QUEUED_EVENTS  32

typedef struct {
    int    motion_on;          /* 1 if this is a "motion start" event */
    time_t timestamp;
} event_t;

typedef struct {
    int      in_use;
    char     token[40];
    time_t   created;
    time_t   last_pull;

    pthread_mutex_t mtx;
    pthread_cond_t  cv;
    event_t  queue[MAX_QUEUED_EVENTS];
    int      qhead, qcount;
} sub_t;

static sub_t g_subs[MAX_SUBSCRIPTIONS];
static pthread_mutex_t g_subs_mtx = PTHREAD_MUTEX_INITIALIZER;

static int       g_motion_state;
static pthread_t g_md_tid;
static int       g_md_run;

/* ============================================================ */
/* Time helpers                                                 */
/* ============================================================ */
static void iso8601(time_t t, char *out, size_t cap)
{
    struct tm utc;
    gmtime_r(&t, &utc);
    snprintf(out, cap, "%04d-%02d-%02dT%02d:%02d:%02dZ",
             utc.tm_year + 1900, utc.tm_mon + 1, utc.tm_mday,
             utc.tm_hour, utc.tm_min, utc.tm_sec);
}

/* Parse "PT60S" / "PT5M" duration. Returns seconds, or 60 on parse
 * failure. Accepts only the simple forms ONVIF clients use. */
static int parse_duration_secs(const char *s)
{
    if (!s || s[0] != 'P' || s[1] != 'T') return 60;
    int v = 0;
    for (const char *p = s + 2; *p; p++) {
        if (*p >= '0' && *p <= '9') {
            v = v * 10 + (*p - '0');
        } else if (*p == 'S') {
            return v;
        } else if (*p == 'M') {
            return v * 60;
        } else if (*p == 'H') {
            return v * 3600;
        }
    }
    return 60;
}

/* ============================================================ */
/* XML helper (local copy — see comment in onvif_wsd.c)        */
/* ============================================================ */
static int xml_text(const char *src, const char *local, char *out, size_t cap)
{
    out[0] = 0;
    size_t Ll = strlen(local);
    const char *p = src;
    while ((p = strchr(p, '<')) != NULL) {
        p++;
        if (*p == '/' || *p == '!' || *p == '?') continue;
        const char *name = p;
        const char *colon = NULL;
        const char *end = name;
        while (*end && *end != '>' && *end != ' ' && *end != '/' && *end != '\t') {
            if (*end == ':') colon = end;
            end++;
        }
        if (!*end) return -1;
        const char *l = colon ? colon + 1 : name;
        if ((size_t)(end - l) == Ll && memcmp(l, local, Ll) == 0) {
            const char *gt = strchr(end, '>');
            if (!gt) return -1;
            if (gt[-1] == '/') return 0;
            const char *c = gt + 1;
            while (*c == ' ' || *c == '\t' || *c == '\r' || *c == '\n') c++;
            const char *ce = strstr(c, "</");
            if (!ce) return -1;
            while (ce > c && (ce[-1] == ' ' || ce[-1] == '\t' ||
                              ce[-1] == '\r' || ce[-1] == '\n')) ce--;
            size_t L = (size_t)(ce - c);
            if (L >= cap) L = cap - 1;
            memcpy(out, c, L);
            out[L] = 0;
            return 0;
        }
        p = end;
    }
    return -1;
}

/* ============================================================ */
/* Subscription management                                      */
/* ============================================================ */
static sub_t *sub_find(const char *token)
{
    if (!token || !*token) return NULL;
    for (int i = 0; i < MAX_SUBSCRIPTIONS; i++) {
        if (g_subs[i].in_use && strcmp(g_subs[i].token, token) == 0)
            return &g_subs[i];
    }
    return NULL;
}

static sub_t *sub_alloc(void)
{
    /* GC: any subscription idle for > 5 minutes is reclaimed. */
    time_t now = time(NULL);
    for (int i = 0; i < MAX_SUBSCRIPTIONS; i++) {
        if (g_subs[i].in_use &&
            (now - g_subs[i].last_pull) > 300) {
            fprintf(stderr,
                "[onvif] subscription %s GC'd (idle %lds)\n",
                g_subs[i].token, (long)(now - g_subs[i].last_pull));
            g_subs[i].in_use = 0;
            pthread_mutex_destroy(&g_subs[i].mtx);
            pthread_cond_destroy(&g_subs[i].cv);
        }
    }
    for (int i = 0; i < MAX_SUBSCRIPTIONS; i++) {
        if (!g_subs[i].in_use) {
            memset(&g_subs[i], 0, sizeof(g_subs[i]));
            pthread_mutex_init(&g_subs[i].mtx, NULL);
            pthread_cond_init(&g_subs[i].cv, NULL);
            /* 32-hex-char token, plenty unique enough */
            uint8_t r[16] = {0};
            int fd = open("/dev/urandom", O_RDONLY);
            if (fd >= 0) { (void)!read(fd, r, sizeof(r)); close(fd); }
            else { struct timespec ts; clock_gettime(CLOCK_MONOTONIC, &ts);
                memcpy(r, &ts, sizeof(ts) < sizeof(r) ? sizeof(ts) : sizeof(r));
            }
            for (int j = 0; j < 16; j++) {
                snprintf(g_subs[i].token + j*2, 3, "%02x", r[j]);
            }
            g_subs[i].in_use   = 1;
            g_subs[i].created  = now;
            g_subs[i].last_pull = now;
            return &g_subs[i];
        }
    }
    return NULL;
}

static void sub_free(sub_t *s)
{
    if (!s || !s->in_use) return;
    pthread_mutex_lock(&s->mtx);
    s->in_use = 0;
    pthread_cond_broadcast(&s->cv);
    pthread_mutex_unlock(&s->mtx);
    pthread_mutex_destroy(&s->mtx);
    pthread_cond_destroy(&s->cv);
    memset(s, 0, sizeof(*s));
}

/* Push an event to every active subscription. Called from the
 * motion detector thread. */
static void push_event_all(int motion_on)
{
    time_t now = time(NULL);
    pthread_mutex_lock(&g_subs_mtx);
    for (int i = 0; i < MAX_SUBSCRIPTIONS; i++) {
        sub_t *s = &g_subs[i];
        if (!s->in_use) continue;
        pthread_mutex_lock(&s->mtx);
        if (s->qcount < MAX_QUEUED_EVENTS) {
            int idx = (s->qhead + s->qcount) % MAX_QUEUED_EVENTS;
            s->queue[idx].motion_on = motion_on;
            s->queue[idx].timestamp = now;
            s->qcount++;
            pthread_cond_signal(&s->cv);
        } /* else: queue full, drop. PullMessages was abandoned. */
        pthread_mutex_unlock(&s->mtx);
    }
    pthread_mutex_unlock(&g_subs_mtx);
}

/* ============================================================ */
/* Motion detector                                              */
/*                                                              */
/* ak_vpss_md_get_stat fills 1536 bytes of "3D-NR stat info" —   */
/* the per-block delta values from the noise reducer, which     */
/* doubles as a cheap motion signal. Each byte is a 0..255      */
/* delta from the previous frame for one block of the image.    */
/*                                                              */
/* We sum all bytes; idle scenes give very low values, motion   */
/* gives high. Threshold and hysteresis frame counts are        */
/* conservative defaults that work for typical indoor scenes.  */
/* Frigate's own detector does the real work — our event just  */
/* primes its analysis pipeline.                                */
/* ============================================================ */
#define MD_STAT_BYTES        1536
#define MD_THRESHOLD_DEFAULT 1500    /* sum of 1536 bytes; 1500 ≈ 1/byte */
#define MD_ON_FRAMES         3       /* consecutive >threshold to trigger ON */
#define MD_OFF_FRAMES        8       /* consecutive <threshold to trigger OFF */
#define MD_POLL_MS           200

/* Mutable threshold — read by the motion thread, settable from
 * cfgfile load and from the /api/config endpoint. We use plain
 * atomic int reads; on ARM single-word reads/writes are
 * naturally atomic and the worst-case race is "the threshold
 * changes mid-evaluation" which is harmless. */
static int g_md_threshold = MD_THRESHOLD_DEFAULT;

void motion_set_threshold(int t)
{
    if (t < 0) t = 0;
    if (t > 1536 * 255) t = 1536 * 255;
    g_md_threshold = t;
    fprintf(stderr, "[md] threshold set to %d\n", t);
}

int motion_get_threshold(void)
{
    return g_md_threshold;
}

static unsigned long md_compute_sum(const uint8_t *buf)
{
    unsigned long s = 0;
    for (int i = 0; i < MD_STAT_BYTES; i++) s += buf[i];
    return s;
}

static void *motion_thread(void *arg)
{
    (void)arg;
    uint8_t stat[MD_STAT_BYTES];
    int above = 0, below = 0;
    int curr_state = 0;

    /* Brief warm-up — the stat buffer can be all zeros for the
     * first few frames after VI starts. Ignore early samples. */
    for (int i = 0; i < 10 && g_md_run; i++) usleep(MD_POLL_MS * 1000);

    while (g_md_run) {
        int rc = ak_vpss_md_get_stat(0, stat);
        if (rc != 0) {
            usleep(MD_POLL_MS * 1000);
            continue;
        }
        unsigned long sum = md_compute_sum(stat);
        int thr = g_md_threshold;
        if (sum > (unsigned long)thr) {
            above++; below = 0;
            if (!curr_state && above >= MD_ON_FRAMES) {
                curr_state = 1;
                g_motion_state = 1;
                fprintf(stderr, "[md] motion ON (sum=%lu)\n", sum);
                push_event_all(1);
            }
        } else {
            below++; above = 0;
            if (curr_state && below >= MD_OFF_FRAMES) {
                curr_state = 0;
                g_motion_state = 0;
                fprintf(stderr, "[md] motion OFF\n");
                push_event_all(0);
            }
        }
        usleep(MD_POLL_MS * 1000);
    }
    return NULL;
}

/* ============================================================ */
/* SOAP responses                                               */
/* ============================================================ */
static size_t op_create_pullpoint(char *out, size_t cap,
                                  const char *host, int port)
{
    sub_t *s = NULL;
    pthread_mutex_lock(&g_subs_mtx);
    s = sub_alloc();
    pthread_mutex_unlock(&g_subs_mtx);
    if (!s) {
        int n = snprintf(out, cap,
            EV_ENV_OPEN
            "<s:Fault>"
              "<s:Code><s:Value>s:Receiver</s:Value></s:Code>"
              "<s:Reason><s:Text xml:lang=\"en\">No free subscription slots</s:Text></s:Reason>"
            "</s:Fault>"
            EV_ENV_CLOSE);
        return (n > 0 && (size_t)n < cap) ? (size_t)n : 0;
    }

    char now_s[40], term_s[40];
    time_t now = time(NULL);
    iso8601(now,            now_s,  sizeof(now_s));
    iso8601(now + 60 * 10,  term_s, sizeof(term_s));

    int n = snprintf(out, cap,
        EV_ENV_OPEN
        "<tev:CreatePullPointSubscriptionResponse>"
          "<tev:SubscriptionReference>"
            "<wsa:Address>http://%s:%d/onvif/events_service?token=%s</wsa:Address>"
          "</tev:SubscriptionReference>"
          "<wsnt:CurrentTime>%s</wsnt:CurrentTime>"
          "<wsnt:TerminationTime>%s</wsnt:TerminationTime>"
        "</tev:CreatePullPointSubscriptionResponse>"
        EV_ENV_CLOSE,
        host, port, s->token, now_s, term_s);
    return (n > 0 && (size_t)n < cap) ? (size_t)n : 0;
}

static size_t op_pull_messages(char *out, size_t cap,
                               const char *body, const char *token)
{
    sub_t *s = sub_find(token);
    if (!s) {
        int n = snprintf(out, cap,
            EV_ENV_OPEN
            "<s:Fault>"
              "<s:Code><s:Value>s:Sender</s:Value></s:Code>"
              "<s:Reason><s:Text xml:lang=\"en\">No such subscription</s:Text></s:Reason>"
            "</s:Fault>"
            EV_ENV_CLOSE);
        return (n > 0 && (size_t)n < cap) ? (size_t)n : 0;
    }

    /* Honor the Timeout. Frigate sends PT60S typically. We cap at
     * 60s ourselves so the HTTP client doesn't timeout the socket. */
    char timeout_str[32] = {0};
    xml_text(body, "Timeout", timeout_str, sizeof(timeout_str));
    int timeout_secs = parse_duration_secs(timeout_str);
    if (timeout_secs > 60) timeout_secs = 60;
    if (timeout_secs < 1)  timeout_secs = 1;

    /* Wait for an event or timeout. */
    pthread_mutex_lock(&s->mtx);
    s->last_pull = time(NULL);
    if (s->qcount == 0) {
        struct timespec deadline;
        clock_gettime(CLOCK_REALTIME, &deadline);
        deadline.tv_sec += timeout_secs;
        while (s->qcount == 0 && s->in_use) {
            int rc = pthread_cond_timedwait(&s->cv, &s->mtx, &deadline);
            if (rc != 0) break;
        }
    }

    /* Drain up to MAX_QUEUED events into the response. Most clients
     * ask for "MessageLimit=1" but accept many. */
    char now_s[40], term_s[40];
    time_t now = time(NULL);
    iso8601(now,           now_s,  sizeof(now_s));
    iso8601(now + 60 * 10, term_s, sizeof(term_s));

    size_t pos = 0;
    int n = snprintf(out, cap,
        EV_ENV_OPEN
        "<tev:PullMessagesResponse>"
          "<tev:CurrentTime>%s</tev:CurrentTime>"
          "<tev:TerminationTime>%s</tev:TerminationTime>",
        now_s, term_s);
    if (n < 0 || (size_t)n >= cap) { pthread_mutex_unlock(&s->mtx); return 0; }
    pos = (size_t)n;

    int events_to_emit = s->qcount;
    for (int i = 0; i < events_to_emit && pos < cap; i++) {
        int idx = (s->qhead + i) % MAX_QUEUED_EVENTS;
        char ts_str[40];
        iso8601(s->queue[idx].timestamp, ts_str, sizeof(ts_str));
        const char *state = s->queue[idx].motion_on ? "true" : "false";

        n = snprintf(out + pos, cap - pos,
            "<wsnt:NotificationMessage>"
              "<wsnt:Topic Dialect=\"http://docs.oasis-open.org/wsn/t-1/TopicExpression/Concrete\">"
                "tns1:RuleEngine/CellMotionDetector/Motion"
              "</wsnt:Topic>"
              "<wsnt:Message>"
                "<tt:Message UtcTime=\"%s\" PropertyOperation=\"Changed\">"
                  "<tt:Source>"
                    "<tt:SimpleItem Name=\"VideoSourceConfigurationToken\" Value=\"vsrc0\"/>"
                    "<tt:SimpleItem Name=\"VideoAnalyticsConfigurationToken\" Value=\"va0\"/>"
                    "<tt:SimpleItem Name=\"Rule\" Value=\"MotionRule\"/>"
                  "</tt:Source>"
                  "<tt:Data>"
                    "<tt:SimpleItem Name=\"IsMotion\" Value=\"%s\"/>"
                  "</tt:Data>"
                "</tt:Message>"
              "</wsnt:Message>"
            "</wsnt:NotificationMessage>",
            ts_str, state);
        if (n < 0 || (size_t)n >= cap - pos) break;
        pos += (size_t)n;
    }

    /* Pop the events we emitted. */
    s->qhead = (s->qhead + events_to_emit) % MAX_QUEUED_EVENTS;
    s->qcount -= events_to_emit;
    pthread_mutex_unlock(&s->mtx);

    n = snprintf(out + pos, cap - pos,
        "</tev:PullMessagesResponse>" EV_ENV_CLOSE);
    if (n < 0 || (size_t)n >= cap - pos) return 0;
    pos += (size_t)n;
    return pos;
}

static size_t op_unsubscribe(char *out, size_t cap, const char *token)
{
    pthread_mutex_lock(&g_subs_mtx);
    sub_t *s = sub_find(token);
    if (s) sub_free(s);
    pthread_mutex_unlock(&g_subs_mtx);

    int n = snprintf(out, cap,
        EV_ENV_OPEN
        "<wsnt:UnsubscribeResponse/>"
        EV_ENV_CLOSE);
    return (n > 0 && (size_t)n < cap) ? (size_t)n : 0;
}

static size_t op_renew(char *out, size_t cap, const char *token)
{
    sub_t *s = sub_find(token);
    if (s) {
        pthread_mutex_lock(&s->mtx);
        s->last_pull = time(NULL);
        pthread_mutex_unlock(&s->mtx);
    }
    char now_s[40], term_s[40];
    time_t now = time(NULL);
    iso8601(now,           now_s,  sizeof(now_s));
    iso8601(now + 60 * 10, term_s, sizeof(term_s));
    int n = snprintf(out, cap,
        EV_ENV_OPEN
        "<wsnt:RenewResponse>"
          "<wsnt:TerminationTime>%s</wsnt:TerminationTime>"
          "<wsnt:CurrentTime>%s</wsnt:CurrentTime>"
        "</wsnt:RenewResponse>"
        EV_ENV_CLOSE,
        term_s, now_s);
    return (n > 0 && (size_t)n < cap) ? (size_t)n : 0;
}

/* ============================================================ */
/* Service-level dispatch (called from onvif.c)                 */
/*                                                              */
/* The token of a subscription operation comes either from a    */
/* "?token=..." in the URL (which onvif.c hands us in body or  */
/* parses out separately) or from a SubscriptionId / similar    */
/* element. We look in the SOAP body for an explicit token,     */
/* and fall back to one we extract from the original POST URL  */
/* if our caller passed it via the (still TODO) host_header.   */
/*                                                              */
/* For now, we look for the token only in the URL path, which  */
/* the http server parses and passes via a thread-local hack.   */
/* Cleaner: pass it as an explicit arg. We'll do that.         */
/* ============================================================ */

int onvif_events_dispatch(const char *op, const char *query,
                          const char *body,
                          const char *host, int port,
                          char *out, size_t cap, size_t *out_len)
{
    /* Subscription token resolution:
     *
     *   1) Primary: from URL query string ?token=...  (set when
     *      we issued the SubscriptionReference.Address in
     *      CreatePullPointSubscriptionResponse). This is what
     *      well-behaved clients including Frigate use.
     *
     *   2) Fallback: scan the SOAP body for a wsa:Address element
     *      that contains "?token=...". Some homebrew test scripts
     *      put the subscription URL in a wsa:To header inside the
     *      Body instead of a real Header — the body lookup catches
     *      those too.
     *
     * Both produce the same token. The query path is preferred
     * because it costs no XML parsing. */
    char token[64] = {0};

    /* (1) From the query string. */
    if (query && *query) {
        const char *t = strstr(query, "token=");
        if (t == query || (t && t[-1] == '&')) {
            t += 6;
            size_t L = strcspn(t, "&");
            if (L >= sizeof(token)) L = sizeof(token) - 1;
            memcpy(token, t, L);
            token[L] = 0;
        }
    }

    /* (2) Fallback: scan body for <wsa:Address>...?token=...</...>. */
    if (!token[0]) {
        char addr[256] = {0};
        if (xml_text(body, "Address", addr, sizeof(addr)) == 0) {
            const char *t = strstr(addr, "token=");
            if (t) {
                t += 6;
                size_t L = strcspn(t, "& \t\r\n\"<");
                if (L >= sizeof(token)) L = sizeof(token) - 1;
                memcpy(token, t, L);
                token[L] = 0;
            }
        }
    }

    size_t n = 0;
    if (!strcmp(op, "CreatePullPointSubscription")) {
        n = op_create_pullpoint(out, cap, host, port);
    } else if (!strcmp(op, "PullMessages")) {
        n = op_pull_messages(out, cap, body, token);
    } else if (!strcmp(op, "Unsubscribe")) {
        n = op_unsubscribe(out, cap, token);
    } else if (!strcmp(op, "Renew")) {
        n = op_renew(out, cap, token);
    } else if (!strcmp(op, "GetEventProperties")) {
        /* Some clients ask for this to discover supported topics.
         * We advertise just our motion topic. */
        int nn = snprintf(out, cap,
            EV_ENV_OPEN
            "<tev:GetEventPropertiesResponse>"
              "<tev:TopicNamespaceLocation>"
                "http://www.onvif.org/onvif/ver10/topics/topicns.xml"
              "</tev:TopicNamespaceLocation>"
              "<wsnt:FixedTopicSet>true</wsnt:FixedTopicSet>"
              "<wstop:TopicSet xmlns:wstop=\"http://docs.oasis-open.org/wsn/t-1\">"
                "<tns1:RuleEngine>"
                  "<CellMotionDetector>"
                    "<Motion wstop:topic=\"true\">"
                      "<tt:MessageDescription IsProperty=\"true\">"
                        "<tt:Source>"
                          "<tt:SimpleItemDescription Name=\"VideoSourceConfigurationToken\" Type=\"tt:ReferenceToken\"/>"
                        "</tt:Source>"
                        "<tt:Data>"
                          "<tt:SimpleItemDescription Name=\"IsMotion\" Type=\"xsd:boolean\"/>"
                        "</tt:Data>"
                      "</tt:MessageDescription>"
                    "</Motion>"
                  "</CellMotionDetector>"
                "</tns1:RuleEngine>"
              "</wstop:TopicSet>"
              "<wsnt:TopicExpressionDialect>"
                "http://docs.oasis-open.org/wsn/t-1/TopicExpression/Concrete"
              "</wsnt:TopicExpressionDialect>"
              "<tev:MessageContentFilterDialect>"
                "http://www.onvif.org/ver10/tev/messageContentFilter/ItemFilter"
              "</tev:MessageContentFilterDialect>"
            "</tev:GetEventPropertiesResponse>"
            EV_ENV_CLOSE);
        if (nn > 0 && (size_t)nn < cap) n = (size_t)nn;
    } else {
        int nn = snprintf(out, cap,
            EV_ENV_OPEN
            "<s:Fault>"
              "<s:Code><s:Value>s:Receiver:ActionNotSupported</s:Value></s:Code>"
              "<s:Reason><s:Text xml:lang=\"en\">%s not supported</s:Text></s:Reason>"
            "</s:Fault>"
            EV_ENV_CLOSE,
            op);
        if (nn > 0 && (size_t)nn < cap) n = (size_t)nn;
    }

    *out_len = n;
    return 0;
}

/* ============================================================ */
/* Init / shutdown                                              */
/* ============================================================ */
int onvif_events_init(void)
{
    g_md_run = 1;
    if (pthread_create(&g_md_tid, NULL, motion_thread, NULL) != 0) {
        fprintf(stderr, "[md] pthread_create failed\n");
        g_md_run = 0;
        return -1;
    }
    fprintf(stderr, "[md] motion detector started "
                    "(threshold=%d, on=%d frames, off=%d frames)\n",
            g_md_threshold, MD_ON_FRAMES, MD_OFF_FRAMES);
    return 0;
}

void onvif_events_shutdown(void)
{
    if (g_md_run) {
        g_md_run = 0;
        pthread_join(g_md_tid, NULL);
    }
    pthread_mutex_lock(&g_subs_mtx);
    for (int i = 0; i < MAX_SUBSCRIPTIONS; i++) {
        if (g_subs[i].in_use) sub_free(&g_subs[i]);
    }
    pthread_mutex_unlock(&g_subs_mtx);
}
