/*
 * dns_spoof.c — minimal DNS responder for captive-portal mode.
 *
 * Listens on UDP/53. For every A query it receives, replies with
 * AP_LOCAL_IP. For AAAA (IPv6) queries it returns NXDOMAIN, which
 * pushes Android/iOS to fall back to the v4 query and follow the
 * spoof. For anything else it returns NXDOMAIN.
 *
 * Why this is needed: when a phone joins the AP, the OS probes
 * specific URLs to detect a captive portal:
 *   - Android: connectivitycheck.gstatic.com, www.google.com/generate_204
 *   - iOS:     captive.apple.com, www.apple.com/library/test/success.html
 *   - Windows: www.msftconnecttest.com/connecttest.txt
 *   - Various: clients3.google.com/generate_204, gstatic.com, etc.
 *
 * The phone first does a DNS lookup for these. With no real upstream
 * DNS reachable on our AP-only network, the lookup either times out
 * (after several seconds) or fails — and the phone shows "no internet"
 * without offering the captive portal sign-in. By answering EVERY
 * lookup with our own IP, the probe HTTP request lands on our HTTP
 * server, which already serves a 302 to / for known probe paths and
 * /index.html for unknown ones. The phone then pops up the standard
 * "Sign in to network" notification.
 *
 * Threading model: a single thread blocks on recvfrom() and replies.
 * No state, no zone files, no caching. Ten lines of protocol parsing
 * and we're done.
 *
 * DNS message format (RFC 1035, simplified):
 *   12-byte header:
 *     ID (2)  FLAGS (2)  QDCOUNT (2)  ANCOUNT (2)  NSCOUNT (2)  ARCOUNT (2)
 *   Question:
 *     QNAME (variable, length-prefixed labels, terminated by a 0 byte)
 *     QTYPE (2)
 *     QCLASS (2)
 *   Answer (when we reply):
 *     NAME (2 bytes: pointer 0xC00C → back to question name)
 *     TYPE (2)  CLASS (2)  TTL (4)  RDLENGTH (2)  RDATA (RDLENGTH bytes)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "ipcd.h"

#define DNS_PORT 53

#define DNS_TYPE_A     1
#define DNS_TYPE_AAAA 28

/* Flags layout for our reply:
 *   bit 15  QR=1 (response)
 *   bits 14-11 OPCODE (copy from query)
 *   bit 10  AA=1 (authoritative — eh, why not)
 *   bit 9   TC=0
 *   bit 8   RD (copy from query)
 *   bit 7   RA=0
 *   bits 6-4 Z=0
 *   bits 3-0 RCODE (0=NOERROR, 3=NXDOMAIN)
 */
#define DNS_RCODE_NOERROR  0
#define DNS_RCODE_NXDOMAIN 3

static int volatile g_dns_run = 1;
static int          g_dns_fd  = -1;

static uint16_t rd16(const unsigned char *p) { return (p[0] << 8) | p[1]; }
static void     wr16(unsigned char *p, uint16_t v) { p[0] = v >> 8; p[1] = v & 0xff; }
static void     wr32(unsigned char *p, uint32_t v)
{
    p[0] = v >> 24; p[1] = v >> 16; p[2] = v >> 8; p[3] = v & 0xff;
}

/* Skip past a QNAME (sequence of length-prefixed labels ending with 0).
 * Stops at end of buffer too. Returns offset of byte after the 0
 * terminator, or -1 on truncation. */
static int skip_qname(const unsigned char *buf, int len, int off)
{
    while (off < len) {
        unsigned char l = buf[off];
        if (l == 0) return off + 1;
        if ((l & 0xC0) == 0xC0) {        /* compression pointer */
            return off + 2;
        }
        off += 1 + l;
    }
    return -1;
}

static void *dns_thread(void *arg)
{
    (void)arg;

    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0) {
        fprintf(stderr, "[dns] socket: %s\n", strerror(errno));
        return NULL;
    }
    int one = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));

    struct sockaddr_in sa = {0};
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = htonl(INADDR_ANY);
    sa.sin_port        = htons(DNS_PORT);
    if (bind(s, (struct sockaddr *)&sa, sizeof(sa)) != 0) {
        fprintf(stderr, "[dns] bind 53: %s\n", strerror(errno));
        close(s);
        return NULL;
    }
    g_dns_fd = s;

    /* Pre-resolve our reply address (AP_LOCAL_IP is a string) */
    struct in_addr reply_addr;
    if (inet_aton(AP_LOCAL_IP, &reply_addr) == 0) {
        fprintf(stderr, "[dns] bad AP_LOCAL_IP: %s\n", AP_LOCAL_IP);
        close(s);
        return NULL;
    }

    fprintf(stderr, "[dns] spoofer up on UDP:53 → %s\n", AP_LOCAL_IP);

    unsigned char in_buf[1024];
    unsigned char out_buf[1024];

    while (g_dns_run) {
        struct sockaddr_in from;
        socklen_t fl = sizeof(from);
        ssize_t n = recvfrom(s, in_buf, sizeof(in_buf), 0,
                             (struct sockaddr *)&from, &fl);
        if (n < 12) continue;     /* malformed: too short for header */

        /* Header */
        uint16_t id      = rd16(in_buf + 0);
        uint16_t flags   = rd16(in_buf + 2);
        uint16_t qdcount = rd16(in_buf + 4);
        if (qdcount < 1) continue;

        /* Find QNAME end */
        int qname_off = 12;
        int after_qn  = skip_qname(in_buf, (int)n, qname_off);
        if (after_qn < 0 || after_qn + 4 > n) continue;
        uint16_t qtype  = rd16(in_buf + after_qn);
        /* uint16_t qclass = rd16(in_buf + after_qn + 2); */
        int qsection_len = after_qn + 4 - qname_off;

        /* Build reply: copy header + question, then append answer (if A). */
        int olen = 0;

        /* Copy header (12 bytes) */
        memcpy(out_buf, in_buf, 12);

        /* Set flags: QR=1, AA=1, RD copied from query, RA=0,
         * RCODE depending on type. */
        uint16_t out_flags = 0x8400;     /* QR=1 AA=1 */
        out_flags |= (flags & 0x0100);   /* RD copy */

        int give_answer = 0;
        if (qtype == DNS_TYPE_A) {
            give_answer = 1;
            out_flags |= DNS_RCODE_NOERROR;
            wr16(out_buf + 6, 1);        /* ANCOUNT = 1 */
        } else {
            /* AAAA, MX, TXT, ... — say NXDOMAIN to push the client
             * back to the IPv4 lookup which we *will* answer. */
            out_flags |= DNS_RCODE_NXDOMAIN;
            wr16(out_buf + 6, 0);        /* ANCOUNT = 0 */
        }
        wr16(out_buf + 2, out_flags);
        wr16(out_buf + 4, 1);            /* QDCOUNT = 1 */
        wr16(out_buf + 8, 0);            /* NSCOUNT = 0 */
        wr16(out_buf + 10, 0);           /* ARCOUNT = 0 */
        olen = 12;

        /* Copy the question section verbatim */
        memcpy(out_buf + olen, in_buf + qname_off, (size_t)qsection_len);
        olen += qsection_len;
        (void)id;  /* already copied via memcpy of header */

        if (give_answer) {
            /* Answer: name=pointer to QNAME (0xC00C),
             * type=A, class=IN, TTL=60, RDLENGTH=4, RDATA=AP_LOCAL_IP */
            if (olen + 16 > (int)sizeof(out_buf)) continue;
            wr16(out_buf + olen, 0xC00C);     olen += 2;     /* NAME ptr */
            wr16(out_buf + olen, DNS_TYPE_A); olen += 2;     /* TYPE A  */
            wr16(out_buf + olen, 1);          olen += 2;     /* CLASS IN */
            wr32(out_buf + olen, 60);         olen += 4;     /* TTL = 60 */
            wr16(out_buf + olen, 4);          olen += 2;     /* RDLENGTH */
            memcpy(out_buf + olen, &reply_addr.s_addr, 4); olen += 4;
        }

        sendto(s, out_buf, (size_t)olen, 0,
               (struct sockaddr *)&from, fl);
    }

    close(s);
    g_dns_fd = -1;
    return NULL;
}

int dns_spoof_start(void)
{
    g_dns_run = 1;
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    int rc = pthread_create(&tid, &attr, dns_thread, NULL);
    pthread_attr_destroy(&attr);
    return rc == 0 ? 0 : -1;
}

void dns_spoof_stop(void)
{
    g_dns_run = 0;
    int fd = g_dns_fd;
    if (fd >= 0) {
        /* Closing the socket unblocks recvfrom */
        shutdown(fd, SHUT_RDWR);
        close(fd);
        g_dns_fd = -1;
    }
}
