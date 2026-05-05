/*
 * onvif_wsd.c — WS-Discovery responder.
 *
 * ONVIF cameras advertise themselves on UDP multicast 239.255.255.250
 * port 3702 using WS-Discovery (a SOAP-over-UDP protocol). When a
 * client (e.g. ONVIF Device Manager, Frigate's auto-discovery)
 * sends a Probe message to that address, every camera on the LAN
 * answers with a ProbeMatch identifying itself.
 *
 * We implement just two messages:
 *   - Receive: <Probe> with optional Types filter
 *     We answer if Types contains either:
 *       - dn:NetworkVideoTransmitter
 *       - tds:Device
 *     or is empty.
 *   - Send: <ProbeMatches> with our XAddrs (the device service URL).
 *
 * We also send <Hello> on startup and <Bye> on shutdown — polite,
 * not strictly required, but improves discovery latency.
 *
 * One thread, blocking recvfrom on the multicast socket. The
 * thread runs for the lifetime of the ONVIF subsystem.
 *
 * Address detection: we don't know our own LAN IP statically. On
 * each Probe, we read the IP of the iface that received the
 * multicast packet (via IP_PKTINFO ancillary data), and use that
 * as the host part of the XAddrs URL. This handles the case where
 * the cam has wlan0 and wlan1 simultaneously (AP + STA) and gets
 * probed on both.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <ifaddrs.h>

#include "ipcd.h"

#define WSD_GROUP_ADDR  "239.255.255.250"
#define WSD_PORT        3702

/* How often the thread re-enumerates interfaces and tries to (re-)join
 * the multicast group on any new iface. Picks up wlan0 once netmgr
 * brings STA up, and survives wifi reassoc. */
#define WSD_REJOIN_PERIOD_SEC  10

static pthread_t g_wsd_tid;
static int       g_wsd_run;
static int       g_wsd_sock = -1;

/* Forward declarations — implementations follow wsd_join_all_ifaces. */
static void wsd_send_hello(const char *our_ip);
static void wsd_send_bye(void);

/* Remember which iface IPs we've already joined the multicast group
 * on, so re-join attempts are idempotent. Keeping IPs (not names) is
 * easier and matches what `imr_interface` actually wants. The list
 * is small (1-3 entries on this device). */
#define MAX_JOINED_IFACES 8
static struct {
    uint32_t ip;          /* network byte order; 0 = empty slot */
    char     name[IFNAMSIZ];
} g_joined[MAX_JOINED_IFACES];

/* Try to join the WSD multicast group on every up, multicast-capable,
 * non-loopback iface that has an IPv4 address and that we haven't
 * joined yet. Returns the count of new joins this call. Logs each
 * success/failure once. Safe to call repeatedly; the kernel returns
 * EADDRINUSE for already-joined ifaces, which we filter out via the
 * g_joined cache. */
static int wsd_join_all_ifaces(int sock)
{
    struct ifaddrs *ifa_head = NULL;
    if (getifaddrs(&ifa_head) != 0) {
        fprintf(stderr, "[wsd] getifaddrs: %s\n", strerror(errno));
        return 0;
    }

    int new_joins = 0;
    for (struct ifaddrs *ifa = ifa_head; ifa; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) continue;
        if (ifa->ifa_addr->sa_family != AF_INET) continue;
        if (!(ifa->ifa_flags & IFF_UP)) continue;
        if (!(ifa->ifa_flags & IFF_MULTICAST)) continue;
        if (ifa->ifa_flags & IFF_LOOPBACK) continue;

        struct sockaddr_in *in4 = (struct sockaddr_in *)ifa->ifa_addr;
        uint32_t ip = in4->sin_addr.s_addr;
        if (ip == 0) continue;

        /* Already joined? */
        int already = 0, free_slot = -1;
        for (int i = 0; i < MAX_JOINED_IFACES; i++) {
            if (g_joined[i].ip == ip) { already = 1; break; }
            if (g_joined[i].ip == 0 && free_slot < 0) free_slot = i;
        }
        if (already) continue;
        if (free_slot < 0) continue;  /* table full, unlikely */

        struct ip_mreq mreq;
        mreq.imr_multiaddr.s_addr = inet_addr(WSD_GROUP_ADDR);
        mreq.imr_interface.s_addr = ip;
        if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP,
                       &mreq, sizeof(mreq)) < 0) {
            /* EADDRINUSE means we already joined some other way —
             * cache it as "joined" so we don't keep retrying. Other
             * errors get logged once, also cached so we don't
             * logspam every 10s for an iface in a weird state. */
            if (errno != EADDRINUSE) {
                fprintf(stderr,
                    "[wsd] IP_ADD_MEMBERSHIP via %s (%s): %s\n",
                    ifa->ifa_name, inet_ntoa(in4->sin_addr),
                    strerror(errno));
            }
            /* Cache anyway to avoid logspam. We still listen for
             * unicast Probes on this socket. */
            g_joined[free_slot].ip = ip;
            snprintf(g_joined[free_slot].name,
                     sizeof(g_joined[free_slot].name),
                     "%s", ifa->ifa_name);
            continue;
        }

        g_joined[free_slot].ip = ip;
        snprintf(g_joined[free_slot].name,
                 sizeof(g_joined[free_slot].name),
                 "%s", ifa->ifa_name);
        fprintf(stderr, "[wsd] joined %s on %s (%s)\n",
                WSD_GROUP_ADDR, ifa->ifa_name, inet_ntoa(in4->sin_addr));
        new_joins++;

        /* Send Hello on this iface so passive listeners (Home
         * Assistant) discover us without needing to send a Probe. */
        wsd_send_hello(inet_ntoa(in4->sin_addr));
    }

    freeifaddrs(ifa_head);
    return new_joins;
}

/* Drop cached joins for ifaces that are no longer present/up. The
 * kernel implicitly drops the membership when the iface goes away,
 * but our cache wouldn't know — leading us to skip the re-join
 * when the iface comes back. Called from the periodic re-scan. */
static void wsd_prune_dead_joins(void)
{
    struct ifaddrs *ifa_head = NULL;
    if (getifaddrs(&ifa_head) != 0) return;

    for (int i = 0; i < MAX_JOINED_IFACES; i++) {
        if (g_joined[i].ip == 0) continue;
        int still_alive = 0;
        for (struct ifaddrs *ifa = ifa_head; ifa; ifa = ifa->ifa_next) {
            if (!ifa->ifa_addr || ifa->ifa_addr->sa_family != AF_INET) continue;
            struct sockaddr_in *in4 = (struct sockaddr_in *)ifa->ifa_addr;
            if (in4->sin_addr.s_addr == g_joined[i].ip &&
                (ifa->ifa_flags & IFF_UP)) {
                still_alive = 1; break;
            }
        }
        if (!still_alive) {
            fprintf(stderr, "[wsd] iface %s gone, dropping cached join\n",
                    g_joined[i].name);
            g_joined[i].ip = 0;
            g_joined[i].name[0] = 0;
        }
    }
    freeifaddrs(ifa_head);
}

/* Generate a random-ish UUID. We don't have proper randomness on
 * this device but RFC 4122 only needs uniqueness in practice. We
 * mix /dev/urandom (best effort) with PID and time. */
static void make_uuid(char out[40])
{
    uint8_t r[16] = {0};
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd >= 0) {
        if (read(fd, r, sizeof(r)) != sizeof(r)) {
            /* fall through to mix-in below */
        }
        close(fd);
    }
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    r[0] ^= (uint8_t)(ts.tv_sec);
    r[1] ^= (uint8_t)(ts.tv_nsec >> 8);
    r[2] ^= (uint8_t)getpid();

    /* Set RFC 4122 version (4) and variant bits. */
    r[6] = (r[6] & 0x0F) | 0x40;
    r[8] = (r[8] & 0x3F) | 0x80;

    snprintf(out, 40,
        "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
        r[0],r[1],r[2],r[3], r[4],r[5], r[6],r[7],
        r[8],r[9], r[10],r[11],r[12],r[13],r[14],r[15]);
}

/* Persistent device UUID — same across the lifetime of the process,
 * regenerated on restart. ONVIF cache layers tolerate this. */
static char g_device_uuid[40];

/* MAC address of the primary iface, formatted as "xx-xx-xx-xx-xx-xx"
 * (hyphens, not colons — that is the onvif:// scope convention).
 * Populated at wsd_start time and used in all discovery messages. */
static char g_device_mac[24] = "00-00-00-00-00-00";

static void read_device_mac(void)
{
    const char *ifaces[] = { "wlan0", "eth0", NULL };
    for (int i = 0; ifaces[i]; i++) {
        char path[64];
        snprintf(path, sizeof(path), "/sys/class/net/%s/address", ifaces[i]);
        FILE *f = fopen(path, "r");
        if (!f) continue;
        char raw[20] = {0};
        if (fgets(raw, sizeof(raw), f)) {
            /* raw is "aa:bb:cc:dd:ee:ff\n" — convert colons to hyphens */
            size_t L = strlen(raw);
            while (L > 0 && (raw[L-1] == '\n' || raw[L-1] == '\r'))
                raw[--L] = 0;
            if (L == 17) {
                for (size_t j = 0; j < L; j++)
                    g_device_mac[j] = (raw[j] == ':') ? '-' : raw[j];
                g_device_mac[17] = 0;
                fclose(f);
                return;
            }
        }
        fclose(f);
    }
}

/* Pull a child element's text from an XML envelope. Reuses the
 * same approach as onvif_auth.c but local for minimal coupling. */
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

/* Build a ProbeMatches reply. relates_to is the MessageID of the
 * incoming Probe (we copy it into our wsa:RelatesTo). The XAddr
 * uses the IP we received the probe on. */
static size_t build_probe_match(char *out, size_t cap,
                                const char *relates_to,
                                const char *our_ip)
{
    char msg_id[40];
    make_uuid(msg_id);

    int n = snprintf(out, cap,
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
        "<s:Envelope"
          " xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\""
          " xmlns:wsa=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\""
          " xmlns:d=\"http://schemas.xmlsoap.org/ws/2005/04/discovery\""
          " xmlns:dn=\"http://www.onvif.org/ver10/network/wsdl\""
          " xmlns:tds=\"http://www.onvif.org/ver10/device/wsdl\">"
          "<s:Header>"
            "<wsa:MessageID>urn:uuid:%s</wsa:MessageID>"
            "<wsa:RelatesTo>%s</wsa:RelatesTo>"
            "<wsa:To>http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous</wsa:To>"
            "<wsa:Action>http://schemas.xmlsoap.org/ws/2005/04/discovery/ProbeMatches</wsa:Action>"
          "</s:Header>"
          "<s:Body>"
            "<d:ProbeMatches>"
              "<d:ProbeMatch>"
                "<wsa:EndpointReference>"
                  "<wsa:Address>urn:uuid:%s</wsa:Address>"
                "</wsa:EndpointReference>"
                "<d:Types>dn:NetworkVideoTransmitter tds:Device</d:Types>"
                "<d:Scopes>"
                  "onvif://www.onvif.org/type/Network_Video_Transmitter "
                  "onvif://www.onvif.org/Profile/Streaming "
                  "onvif://www.onvif.org/Profile/S "
                  "onvif://www.onvif.org/name/AK39EV330 "
                  "onvif://www.onvif.org/hardware/ak39ev330-sc2331 "
                  "onvif://www.onvif.org/mac/%s"
                "</d:Scopes>"
                "<d:XAddrs>http://%s:80/onvif/device_service</d:XAddrs>"
                "<d:MetadataVersion>1</d:MetadataVersion>"
              "</d:ProbeMatch>"
            "</d:ProbeMatches>"
          "</s:Body>"
        "</s:Envelope>",
        msg_id, relates_to, g_device_uuid, g_device_mac, our_ip);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

/* Build a Hello announcement.  Sent unsolicited to the WSD multicast
 * group when the device first joins the network (and after every
 * successful multicast group join for a new iface).
 * Home Assistant's ONVIF integration listens passively for Hello
 * messages to populate its discovery list — it does NOT send Probe
 * requests like ODM does.  Without Hello, HA never discovers the
 * camera automatically. */
static size_t build_hello(char *out, size_t cap, const char *our_ip)
{
    char msg_id[40];
    make_uuid(msg_id);

    int n = snprintf(out, cap,
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
        "<s:Envelope"
          " xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\""
          " xmlns:wsa=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\""
          " xmlns:d=\"http://schemas.xmlsoap.org/ws/2005/04/discovery\""
          " xmlns:dn=\"http://www.onvif.org/ver10/network/wsdl\""
          " xmlns:tds=\"http://www.onvif.org/ver10/device/wsdl\">"
          "<s:Header>"
            "<wsa:MessageID>urn:uuid:%s</wsa:MessageID>"
            "<wsa:To>urn:schemas-xmlsoap-org:ws:2005:04:discovery</wsa:To>"
            "<wsa:Action>http://schemas.xmlsoap.org/ws/2005/04/discovery/Hello</wsa:Action>"
          "</s:Header>"
          "<s:Body>"
            "<d:Hello>"
              "<wsa:EndpointReference>"
                "<wsa:Address>urn:uuid:%s</wsa:Address>"
              "</wsa:EndpointReference>"
              "<d:Types>dn:NetworkVideoTransmitter tds:Device</d:Types>"
              "<d:Scopes>"
                "onvif://www.onvif.org/type/Network_Video_Transmitter "
                "onvif://www.onvif.org/Profile/Streaming "
                "onvif://www.onvif.org/Profile/S "
                "onvif://www.onvif.org/name/AK39EV330 "
                "onvif://www.onvif.org/hardware/ak39ev330-sc2331 "
                "onvif://www.onvif.org/mac/%s"
              "</d:Scopes>"
              "<d:XAddrs>http://%s:80/onvif/device_service</d:XAddrs>"
              "<d:MetadataVersion>1</d:MetadataVersion>"
            "</d:Hello>"
          "</s:Body>"
        "</s:Envelope>",
        msg_id, g_device_uuid, g_device_mac, our_ip);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

/* Build a Bye announcement.  Sent to the multicast group on shutdown
 * so clients can immediately remove the device from their lists. */
static size_t build_bye(char *out, size_t cap)
{
    char msg_id[40];
    make_uuid(msg_id);

    int n = snprintf(out, cap,
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
        "<s:Envelope"
          " xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\""
          " xmlns:wsa=\"http://schemas.xmlsoap.org/ws/2004/08/addressing\""
          " xmlns:d=\"http://schemas.xmlsoap.org/ws/2005/04/discovery\""
          " xmlns:dn=\"http://www.onvif.org/ver10/network/wsdl\""
          " xmlns:tds=\"http://www.onvif.org/ver10/device/wsdl\">"
          "<s:Header>"
            "<wsa:MessageID>urn:uuid:%s</wsa:MessageID>"
            "<wsa:To>urn:schemas-xmlsoap-org:ws:2005:04:discovery</wsa:To>"
            "<wsa:Action>http://schemas.xmlsoap.org/ws/2005/04/discovery/Bye</wsa:Action>"
          "</s:Header>"
          "<s:Body>"
            "<d:Bye>"
              "<wsa:EndpointReference>"
                "<wsa:Address>urn:uuid:%s</wsa:Address>"
              "</wsa:EndpointReference>"
              "<d:Types>dn:NetworkVideoTransmitter tds:Device</d:Types>"
              "<d:Scopes>"
                "onvif://www.onvif.org/type/Network_Video_Transmitter "
                "onvif://www.onvif.org/Profile/Streaming "
                "onvif://www.onvif.org/Profile/S "
                "onvif://www.onvif.org/name/AK39EV330 "
                "onvif://www.onvif.org/hardware/ak39ev330-sc2331"
              "</d:Scopes>"
              "<d:MetadataVersion>1</d:MetadataVersion>"
            "</d:Bye>"
          "</s:Body>"
        "</s:Envelope>",
        msg_id, g_device_uuid);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

/* Send Hello to the WSD multicast group from the given source IP.
 * Called once per new iface join. */
static void wsd_send_hello(const char *our_ip)
{
    char msg[2048];
    size_t mlen = build_hello(msg, sizeof(msg), our_ip);
    if (mlen == 0) return;

    struct sockaddr_in dst = {0};
    dst.sin_family      = AF_INET;
    dst.sin_addr.s_addr = inet_addr(WSD_GROUP_ADDR);
    dst.sin_port        = htons(WSD_PORT);

    /* Set the outgoing iface so the packet leaves from the right IP. */
    struct in_addr src;
    src.s_addr = inet_addr(our_ip);
    setsockopt(g_wsd_sock, IPPROTO_IP, IP_MULTICAST_IF,
               &src, sizeof(src));

    ssize_t sent = sendto(g_wsd_sock, msg, mlen, 0,
                          (struct sockaddr *)&dst, sizeof(dst));
    if (sent < 0)
        fprintf(stderr, "[wsd] Hello sendto: %s\n", strerror(errno));
    else
        fprintf(stderr, "[wsd] Hello -> %s (xaddr=%s)\n",
                WSD_GROUP_ADDR, our_ip);
}

/* Send Bye to the multicast group. Best-effort — called from stop(). */
static void wsd_send_bye(void)
{
    if (g_wsd_sock < 0) return;

    char msg[2048];
    size_t mlen = build_bye(msg, sizeof(msg));
    if (mlen == 0) return;

    struct sockaddr_in dst = {0};
    dst.sin_family      = AF_INET;
    dst.sin_addr.s_addr = inet_addr(WSD_GROUP_ADDR);
    dst.sin_port        = htons(WSD_PORT);

    sendto(g_wsd_sock, msg, mlen, 0,
           (struct sockaddr *)&dst, sizeof(dst));
    fprintf(stderr, "[wsd] Bye sent\n");
}

/* Get the IP address of the iface a given multicast packet arrived
 * on. Uses IP_PKTINFO ancillary data: the ifindex tells us *which*
 * iface received it, but in_pktinfo doesn't directly carry that
 * iface's unicast IP for multicast packets — both ipi_addr and
 * ipi_spec_dst are set to the multicast group address.
 *
 * So: extract ifindex, then look up the iface's IPv4 in our
 * g_joined cache (which we keep up-to-date via wsd_join_all_ifaces).
 * Falls back to "0.0.0.0" if we can't determine it; the caller
 * skips replies in that case. */
static void recv_dst_ip(struct msghdr *msg, char *out, size_t cap)
{
    snprintf(out, cap, "0.0.0.0");
    int ifindex = -1;
    for (struct cmsghdr *c = CMSG_FIRSTHDR(msg); c; c = CMSG_NXTHDR(msg, c)) {
        if (c->cmsg_level == IPPROTO_IP && c->cmsg_type == IP_PKTINFO) {
            struct in_pktinfo *pi = (struct in_pktinfo *)CMSG_DATA(c);
            ifindex = pi->ipi_ifindex;
            break;
        }
    }
    if (ifindex < 0) return;

    /* Map ifindex -> iface name -> IP via getifaddrs. We could
     * cache this in g_joined too, but the lookup is cheap (a
     * dozen entries on this device) and avoids stale data after
     * a wifi reassoc. */
    char ifname[IFNAMSIZ];
    if (!if_indextoname((unsigned int)ifindex, ifname)) return;

    struct ifaddrs *head = NULL;
    if (getifaddrs(&head) != 0) return;
    for (struct ifaddrs *ifa = head; ifa; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr || ifa->ifa_addr->sa_family != AF_INET) continue;
        if (strcmp(ifa->ifa_name, ifname) != 0) continue;
        struct sockaddr_in *in4 = (struct sockaddr_in *)ifa->ifa_addr;
        snprintf(out, cap, "%s", inet_ntoa(in4->sin_addr));
        break;
    }
    freeifaddrs(head);
}

static int is_probe_for_us(const char *body)
{
    /* We answer if action is Probe and either Types is missing or
     * mentions NetworkVideoTransmitter / Device / something we are. */
    if (!strstr(body, "Probe")) return 0;

    char types[256] = {0};
    if (xml_text(body, "Types", types, sizeof(types)) != 0) {
        /* No Types element = match-all */
        return 1;
    }
    if (!types[0]) return 1;

    if (strstr(types, "NetworkVideoTransmitter")) return 1;
    if (strstr(types, "Device"))                  return 1;
    if (strstr(types, "device:Device"))           return 1;
    if (strstr(types, "tds:Device"))              return 1;
    return 0;
}

static void *wsd_thread(void *arg)
{
    (void)arg;
    char buf[4096];
    char ctrl[256];

    /* Set a recv timeout so the thread wakes up periodically and
     * re-scans interfaces. Without this, if WSD starts before
     * netmgr brings wlan0 up (the common case at boot), the
     * initial multicast join fails with ENODEV and we never join
     * once the iface arrives. */
    struct timeval tv = { .tv_sec = WSD_REJOIN_PERIOD_SEC, .tv_usec = 0 };
    setsockopt(g_wsd_sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    time_t last_scan = 0;

    while (g_wsd_run) {
        /* Periodic iface rescan + multicast (re-)join. Cheap; only
         * iterates getifaddrs and pokes setsockopt for new IPs. */
        time_t now = time(NULL);
        if (now - last_scan >= WSD_REJOIN_PERIOD_SEC) {
            wsd_prune_dead_joins();
            wsd_join_all_ifaces(g_wsd_sock);
            last_scan = now;
        }

        struct sockaddr_in from;
        struct iovec iov = { buf, sizeof(buf) - 1 };
        struct msghdr msg = {0};
        msg.msg_name    = &from;
        msg.msg_namelen = sizeof(from);
        msg.msg_iov     = &iov;
        msg.msg_iovlen  = 1;
        msg.msg_control    = ctrl;
        msg.msg_controllen = sizeof(ctrl);

        ssize_t n = recvmsg(g_wsd_sock, &msg, 0);
        if (n < 0) {
            /* Timeout fires every WSD_REJOIN_PERIOD_SEC — that's
             * intentional, loop back and rescan ifaces. */
            if (errno == EINTR || errno == EAGAIN ||
                errno == EWOULDBLOCK) continue;
            fprintf(stderr, "[wsd] recvmsg: %s\n", strerror(errno));
            usleep(100 * 1000);
            continue;
        }
        buf[n] = 0;
        if (!is_probe_for_us(buf)) continue;

        /* Extract the MessageID for RelatesTo */
        char msg_id[80];
        if (xml_text(buf, "MessageID", msg_id, sizeof(msg_id)) != 0) {
            /* No MessageID = malformed Probe; ignore */
            continue;
        }

        /* Determine which iface this came in on */
        char our_ip[24];
        recv_dst_ip(&msg, our_ip, sizeof(our_ip));
        if (strcmp(our_ip, "0.0.0.0") == 0) {
            /* Couldn't tell — fall back to from.sin_addr's network
             * (probably wrong but better than nothing) */
            continue;
        }

        char reply[2048];
        size_t rlen = build_probe_match(reply, sizeof(reply),
                                        msg_id, our_ip);
        if (rlen == 0) continue;

        ssize_t sent = sendto(g_wsd_sock, reply, rlen, 0,
                              (struct sockaddr *)&from, sizeof(from));
        if (sent < 0) {
            fprintf(stderr, "[wsd] sendto: %s\n", strerror(errno));
        } else {
            fprintf(stderr, "[wsd] ProbeMatch -> %s:%d (xaddr=%s)\n",
                    inet_ntoa(from.sin_addr), ntohs(from.sin_port),
                    our_ip);
        }
    }
    return NULL;
}

int onvif_wsd_start(void)
{
    make_uuid(g_device_uuid);
    read_device_mac();
    fprintf(stderr, "[wsd] device uuid=%s mac=%s\n",
            g_device_uuid, g_device_mac);

    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0) {
        fprintf(stderr, "[wsd] socket: %s\n", strerror(errno));
        return -1;
    }
    int one = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
#ifdef SO_REUSEPORT
    setsockopt(s, SOL_SOCKET, SO_REUSEPORT, &one, sizeof(one));
#endif
    /* Ask the kernel to deliver us the destination address per
     * packet — needed to know which iface the probe came in on. */
    setsockopt(s, IPPROTO_IP, IP_PKTINFO, &one, sizeof(one));

    struct sockaddr_in addr = {0};
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port        = htons(WSD_PORT);
    if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        fprintf(stderr, "[wsd] bind :%d: %s\n", WSD_PORT, strerror(errno));
        close(s);
        return -1;
    }

    /* The actual multicast group join is done by the worker thread
     * (see wsd_join_all_ifaces): we need to enumerate up ifaces
     * explicitly because at startup wlan0 typically hasn't been
     * brought up by netmgr yet, and INADDR_ANY-based joins fail
     * silently in that case. The thread rescans every 10s and
     * picks up new ifaces (e.g. STA after association, or AP
     * after fallback). */

    g_wsd_sock = s;
    g_wsd_run  = 1;
    memset(g_joined, 0, sizeof(g_joined));
    if (pthread_create(&g_wsd_tid, NULL, wsd_thread, NULL) != 0) {
        fprintf(stderr, "[wsd] pthread_create failed\n");
        close(s);
        g_wsd_sock = -1;
        g_wsd_run = 0;
        return -1;
    }
    fprintf(stderr, "[wsd] listening on udp :%d (group %s, "
                    "joining ifaces dynamically)\n",
            WSD_PORT, WSD_GROUP_ADDR);
    return 0;
}

void onvif_wsd_stop(void)
{
    if (!g_wsd_run) return;
    g_wsd_run = 0;
    /* Send Bye before closing the socket so listeners remove us. */
    wsd_send_bye();
    if (g_wsd_sock >= 0) {
        /* Unblock the recvmsg by shutting down the socket.
         * SHUT_RD on a UDP socket isn't universally honored, but
         * close() definitely is — and our thread will see -1 + errno
         * on the next iteration. */
        shutdown(g_wsd_sock, SHUT_RDWR);
        close(g_wsd_sock);
        g_wsd_sock = -1;
    }
    pthread_join(g_wsd_tid, NULL);
    fprintf(stderr, "[wsd] stopped\n");
}
