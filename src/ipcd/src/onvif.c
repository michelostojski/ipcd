/*
 * onvif.c — ONVIF SOAP dispatcher (Device + Media services).
 *
 * Implements the minimum surface of ONVIF Profile S that Frigate /
 * Home Assistant / ONVIF Device Manager actually call:
 *
 *   Device service:
 *     GetSystemDateAndTime  (no auth — used by clients to sync time)
 *     GetDeviceInformation
 *     GetCapabilities
 *     GetServices
 *     GetSystemUris
 *     GetNetworkInterfaces
 *     GetScopes
 *     GetUsers
 *
 *   Media service:
 *     GetProfiles
 *     GetVideoSources
 *     GetVideoEncoderConfigurations
 *     GetStreamUri
 *     GetSnapshotUri
 *
 * Plus Events (CreatePullPointSubscription / PullMessages) in
 * onvif_events.c, and WS-Discovery in onvif_wsd.c.
 *
 * SOAP parsing: minimal. We don't run a full XML parser; we just
 * search for <localname> tokens and copy their text content. ONVIF
 * messages are stereotyped enough that this works in practice. The
 * lookup is case-sensitive and prefix-stripping (so "tds:Profile"
 * matches "Profile") via xml_find_text in onvif_auth.c (sort of —
 * we have a copy here for symmetry; will refactor later if needed).
 *
 * SOAP responses: built with snprintf into a stack-or-heap buffer.
 * The XML itself is hardcoded with %s placeholders for dynamic
 * fields. Frigate doesn't care about whitespace or formatting.
 *
 * Namespaces: we always emit the wsdl: and tt: prefixes that the
 * official ONVIF schemas use. Some clients are picky about this;
 * a few (looking at you, Hikvision NVRs) reject unfamiliar prefix
 * schemes. Frigate is forgiving.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <net/if.h>

#include "ipcd.h"

/* ============================================================ */
/* Hardcoded device facts                                       */
/* ============================================================ */
#define ONVIF_MFG          "ipcd"
#define ONVIF_MODEL        "AK39EV330"
#define ONVIF_FW_VERSION   IPCD_VERSION
#define ONVIF_HARDWARE_ID  "ak39ev330-sc2331"
#define ONVIF_SERIAL       "0000000001"

/* Profile token strings used in URIs and SOAP responses. Stable
 * IDs that ONVIF clients cache. */
#define PROFILE_TOKEN_MAIN  "main"
#define PROFILE_TOKEN_SUB   "sub"
#define VSRC_TOKEN          "vsrc0"
#define VENC_TOKEN_MAIN     "venc_main"
#define VENC_TOKEN_SUB      "venc_sub"

/* ============================================================ */
/* Tiny XML helper (forward declared from onvif_auth.c)         */
/* ============================================================ */
static int xml_find_text(const char *src, const char *localname,
                         char *out, size_t cap);

/* ============================================================ */
/* Operation name extraction                                    */
/*                                                              */
/* SOAP body looks like:                                        */
/*   <s:Body><tds:GetCapabilities>...</tds:GetCapabilities>     */
/*   </s:Body>                                                  */
/* We pluck the local name of the first child of <Body> as the  */
/* operation name. ONVIF clients always put exactly one         */
/* operation per request.                                       */
/* ============================================================ */
static int find_operation(const char *soap_xml, char *op, size_t cap)
{
    op[0] = 0;
    /* Locate the body open tag */
    const char *p = strstr(soap_xml, ":Body");
    if (!p) p = strstr(soap_xml, "<Body");
    if (!p) return -1;
    /* Skip past the opening tag */
    p = strchr(p, '>');
    if (!p) return -1;
    p++;

    /* Find next non-whitespace, expect '<' */
    while (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n') p++;
    if (*p != '<') return -1;
    p++;

    /* Read element name; skip prefix */
    const char *name = p;
    const char *colon = NULL;
    while (*p && *p != '>' && *p != ' ' && *p != '/' && *p != '\t' &&
           *p != '\r' && *p != '\n') {
        if (*p == ':') colon = p;
        p++;
    }
    const char *local = colon ? colon + 1 : name;
    size_t L = (size_t)(p - local);
    if (L >= cap) L = cap - 1;
    memcpy(op, local, L);
    op[L] = 0;
    return 0;
}

/* Same XML text extractor as onvif_auth.c. Duplicated rather than
 * exported — keeps the modules independent. */
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
            const char *tag_close = strchr(end, '>');
            if (!tag_close) return -1;
            if (tag_close[-1] == '/') return 0;
            const char *content = tag_close + 1;
            while (*content == ' ' || *content == '\t' ||
                   *content == '\r' || *content == '\n') content++;
            const char *content_end = strstr(content, "</");
            if (!content_end) return -1;
            while (content_end > content &&
                   (content_end[-1] == ' ' || content_end[-1] == '\t' ||
                    content_end[-1] == '\r' || content_end[-1] == '\n'))
                content_end--;
            size_t Lc = (size_t)(content_end - content);
            if (Lc >= cap) Lc = cap - 1;
            memcpy(out, content, Lc);
            out[Lc] = 0;
            return 0;
        }
        p = end;
    }
    return -1;
}

/* ============================================================ */
/* Host parsing for absolute-URL building                       */
/*                                                              */
/* The Host: header looks like "192.168.1.42:80" or              */
/* "cam.local". We split into host part (without port) and port. */
/* ============================================================ */
static void split_host(const char *host_hdr, char *host_only, size_t cap,
                       int *port)
{
    host_only[0] = 0;
    *port = 80;
    if (!host_hdr || !*host_hdr) {
        snprintf(host_only, cap, "0.0.0.0");
        return;
    }
    const char *colon = strchr(host_hdr, ':');
    if (colon) {
        size_t L = (size_t)(colon - host_hdr);
        if (L >= cap) L = cap - 1;
        memcpy(host_only, host_hdr, L);
        host_only[L] = 0;
        *port = atoi(colon + 1);
        if (*port <= 0) *port = 80;
    } else {
        snprintf(host_only, cap, "%s", host_hdr);
    }
}

/* ============================================================ */
/* SOAP envelope helpers                                        */
/* ============================================================ */

/* The SOAP envelope wrapper. All ONVIF responses use SOAP 1.2
 * (xmlns:s = http://www.w3.org/2003/05/soap-envelope). We declare
 * all the namespaces we'll need across operations once, in the
 * envelope, so each operation body can use the prefixes freely. */
#define SOAP_ENV_OPEN \
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"                            \
    "<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\""       \
    " xmlns:tds=\"http://www.onvif.org/ver10/device/wsdl\""                 \
    " xmlns:trt=\"http://www.onvif.org/ver10/media/wsdl\""                  \
    " xmlns:tev=\"http://www.onvif.org/ver10/events/wsdl\""                 \
    " xmlns:tt=\"http://www.onvif.org/ver10/schema\""                       \
    " xmlns:wsa=\"http://www.w3.org/2005/08/addressing\""                   \
    " xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\""                       \
    " xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">"             \
    "<s:Body>"

#define SOAP_ENV_CLOSE  "</s:Body></s:Envelope>"

/* SOAP fault for unsupported operations / auth failure / errors. */
static size_t emit_fault(char *out, size_t cap, const char *code,
                         const char *reason)
{
    int n = snprintf(out, cap,
        SOAP_ENV_OPEN
        "<s:Fault>"
          "<s:Code><s:Value>s:%s</s:Value></s:Code>"
          "<s:Reason><s:Text xml:lang=\"en\">%s</s:Text></s:Reason>"
        "</s:Fault>"
        SOAP_ENV_CLOSE,
        code, reason);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

/* ============================================================ */
/* Device service operations                                    */
/* ============================================================ */

static size_t op_get_system_date_and_time(char *out, size_t cap)
{
    time_t now = time(NULL);
    struct tm utc;
    gmtime_r(&now, &utc);

    int n = snprintf(out, cap,
        SOAP_ENV_OPEN
        "<tds:GetSystemDateAndTimeResponse>"
          "<tds:SystemDateAndTime>"
            "<tt:DateTimeType>NTP</tt:DateTimeType>"
            "<tt:DaylightSavings>false</tt:DaylightSavings>"
            "<tt:TimeZone><tt:TZ>UTC</tt:TZ></tt:TimeZone>"
            "<tt:UTCDateTime>"
              "<tt:Time><tt:Hour>%d</tt:Hour><tt:Minute>%d</tt:Minute>"
              "<tt:Second>%d</tt:Second></tt:Time>"
              "<tt:Date><tt:Year>%d</tt:Year><tt:Month>%d</tt:Month>"
              "<tt:Day>%d</tt:Day></tt:Date>"
            "</tt:UTCDateTime>"
          "</tds:SystemDateAndTime>"
        "</tds:GetSystemDateAndTimeResponse>"
        SOAP_ENV_CLOSE,
        utc.tm_hour, utc.tm_min, utc.tm_sec,
        utc.tm_year + 1900, utc.tm_mon + 1, utc.tm_mday);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

static size_t op_get_device_information(char *out, size_t cap)
{
    int n = snprintf(out, cap,
        SOAP_ENV_OPEN
        "<tds:GetDeviceInformationResponse>"
          "<tds:Manufacturer>%s</tds:Manufacturer>"
          "<tds:Model>%s</tds:Model>"
          "<tds:FirmwareVersion>%s</tds:FirmwareVersion>"
          "<tds:SerialNumber>%s</tds:SerialNumber>"
          "<tds:HardwareId>%s</tds:HardwareId>"
        "</tds:GetDeviceInformationResponse>"
        SOAP_ENV_CLOSE,
        ONVIF_MFG, ONVIF_MODEL, ONVIF_FW_VERSION,
        ONVIF_SERIAL, ONVIF_HARDWARE_ID);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

static size_t op_get_capabilities(char *out, size_t cap,
                                  const char *host, int port)
{
    int n = snprintf(out, cap,
        SOAP_ENV_OPEN
        "<tds:GetCapabilitiesResponse>"
          "<tds:Capabilities>"
            "<tt:Device>"
              "<tt:XAddr>http://%s:%d/onvif/device_service</tt:XAddr>"
              "<tt:Network><tt:IPFilter>false</tt:IPFilter>"
                "<tt:ZeroConfiguration>false</tt:ZeroConfiguration>"
                "<tt:IPVersion6>false</tt:IPVersion6>"
                "<tt:DynDNS>false</tt:DynDNS></tt:Network>"
              "<tt:System><tt:DiscoveryResolve>false</tt:DiscoveryResolve>"
                "<tt:DiscoveryBye>true</tt:DiscoveryBye>"
                "<tt:RemoteDiscovery>false</tt:RemoteDiscovery>"
                "<tt:SystemBackup>false</tt:SystemBackup>"
                "<tt:SystemLogging>false</tt:SystemLogging>"
                "<tt:FirmwareUpgrade>false</tt:FirmwareUpgrade>"
                "<tt:SupportedVersions><tt:Major>2</tt:Major>"
                "<tt:Minor>5</tt:Minor></tt:SupportedVersions></tt:System>"
              "<tt:Security><tt:TLS1.1>false</tt:TLS1.1>"
                "<tt:TLS1.2>false</tt:TLS1.2>"
                "<tt:OnboardKeyGeneration>false</tt:OnboardKeyGeneration>"
                "<tt:AccessPolicyConfig>false</tt:AccessPolicyConfig>"
                "<tt:X.509Token>false</tt:X.509Token>"
                "<tt:SAMLToken>false</tt:SAMLToken>"
                "<tt:KerberosToken>false</tt:KerberosToken>"                "<tt:RELToken>false</tt:RELToken></tt:Security>"
            "</tt:Device>"
            "<tt:Events>"
              "<tt:XAddr>http://%s:%d/onvif/events_service</tt:XAddr>"
              "<tt:WSSubscriptionPolicySupport>false</tt:WSSubscriptionPolicySupport>"
              "<tt:WSPullPointSupport>true</tt:WSPullPointSupport>"
              "<tt:WSPausableSubscriptionManagerInterfaceSupport>false"
              "</tt:WSPausableSubscriptionManagerInterfaceSupport>"
            "</tt:Events>"
            "<tt:Media>"
              "<tt:XAddr>http://%s:%d/onvif/media_service</tt:XAddr>"
              "<tt:StreamingCapabilities>"
                "<tt:RTPMulticast>false</tt:RTPMulticast>"
                "<tt:RTP_TCP>true</tt:RTP_TCP>"
                "<tt:RTP_RTSP_TCP>true</tt:RTP_RTSP_TCP>"
              "</tt:StreamingCapabilities>"
            "</tt:Media>"

            "<tt:PTZ>"
              "<tt:XAddr>http://%s:%d/onvif/ptz_service</tt:XAddr>"
            "</tt:PTZ>"
          "</tds:Capabilities>"
        "</tds:GetCapabilitiesResponse>"
        SOAP_ENV_CLOSE,
        host, port, host, port, host, port,host, port);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

static size_t op_get_services(char *out, size_t cap,
                              const char *host, int port)
{
    /* GetServices is similar to GetCapabilities but newer (ONVIF
     * 2.x clients prefer it). We list the same 3 services. */
    int n = snprintf(out, cap,
        SOAP_ENV_OPEN
        "<tds:GetServicesResponse>"
          "<tds:Service>"
            "<tds:Namespace>http://www.onvif.org/ver10/device/wsdl</tds:Namespace>"
            "<tds:XAddr>http://%s:%d/onvif/device_service</tds:XAddr>"
            "<tds:Version><tt:Major>2</tt:Major><tt:Minor>5</tt:Minor></tds:Version>"
          "</tds:Service>"
          "<tds:Service>"
            "<tds:Namespace>http://www.onvif.org/ver10/media/wsdl</tds:Namespace>"
            "<tds:XAddr>http://%s:%d/onvif/media_service</tds:XAddr>"
            "<tds:Version><tt:Major>2</tt:Major><tt:Minor>5</tt:Minor></tds:Version>"
          "</tds:Service>"
          "<tds:Service>"
            "<tds:Namespace>http://www.onvif.org/ver10/events/wsdl</tds:Namespace>"
            "<tds:XAddr>http://%s:%d/onvif/events_service</tds:XAddr>"
            "<tds:Version><tt:Major>2</tt:Major><tt:Minor>5</tt:Minor></tds:Version>"
           "</tds:Service>"

          "<tds:Service>"

            "<tds:Namespace>http://www.onvif.org/ver20/ptz/wsdl</tds:Namespace>"

            "<tds:XAddr>http://%s:%d/onvif/ptz_service</tds:XAddr>"

            "<tds:Version><tt:Major>2</tt:Major><tt:Minor>5</tt:Minor></tds:Version>"

          "</tds:Service>"

        "</tds:GetServicesResponse>"

        SOAP_ENV_CLOSE,

        host, port, host, port, host, port, host, port);
       
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

static size_t op_get_scopes(char *out, size_t cap)
{
    int n = snprintf(out, cap,
        SOAP_ENV_OPEN
        "<tds:GetScopesResponse>"
          "<tds:Scopes><tt:ScopeDef>Fixed</tt:ScopeDef>"
            "<tt:ScopeItem>onvif://www.onvif.org/type/Network_Video_Transmitter</tt:ScopeItem>"
          "</tds:Scopes>"
          "<tds:Scopes><tt:ScopeDef>Fixed</tt:ScopeDef>"
            "<tt:ScopeItem>onvif://www.onvif.org/Profile/Streaming</tt:ScopeItem>"
          "</tds:Scopes>"
          "<tds:Scopes><tt:ScopeDef>Fixed</tt:ScopeDef>"
            "<tt:ScopeItem>onvif://www.onvif.org/Profile/S</tt:ScopeItem>"
          "</tds:Scopes>"
          "<tds:Scopes><tt:ScopeDef>Configurable</tt:ScopeDef>"
            "<tt:ScopeItem>onvif://www.onvif.org/name/" ONVIF_MODEL "</tt:ScopeItem>"
          "</tds:Scopes>"
          "<tds:Scopes><tt:ScopeDef>Configurable</tt:ScopeDef>"
            "<tt:ScopeItem>onvif://www.onvif.org/hardware/" ONVIF_HARDWARE_ID "</tt:ScopeItem>"
          "</tds:Scopes>"
        "</tds:GetScopesResponse>"
        SOAP_ENV_CLOSE);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

static size_t op_get_users(char *out, size_t cap)
{
    /* We have one user — the auth user. ONVIF Profile S clients
     * sometimes call this to discover credentials structure. */
    int n = snprintf(out, cap,
        SOAP_ENV_OPEN
        "<tds:GetUsersResponse>"
          "<tds:User>"
            "<tt:Username>%s</tt:Username>"
            "<tt:UserLevel>Administrator</tt:UserLevel>"
          "</tds:User>"
        "</tds:GetUsersResponse>"
        SOAP_ENV_CLOSE,
        auth_get_user());
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

/* ============================================================ */
/* Media service operations                                     */
/* ============================================================ */

/* Helper: encode a profile element. main vs sub differ in resolution
 * and bitrate. The codec field is constrained by the ONVIF Media1
 * schema enum (JPEG|MPEG4|H264) — H.265 is not in the enum, it
 * lives in Media2's separate schema. We therefore always advertise
 * "H264" here, even for HEVC streams. The actual codec is detected
 * by the client when it parses the SDP from the RTSP server: the
 * H.265 NALU types are unambiguous, ffmpeg / GStreamer / VLC pick
 * up the codec from the m=video / a=rtpmap line, not from the ONVIF
 * declaration. ODM has its own decoder and may show "no preview"
 * for the HEVC stream, but that's fine — our target clients
 * (Frigate, ODM-discovery, Home Assistant) work this way.
 *
 * If we wanted to advertise H.265 honestly we would need to
 * implement Media2 service (different WSDL, different SOAP
 * actions). Out of scope for now.
 *
 * The wrapper_tag parameter selects the outer element:
 *   "Profiles" for GetProfilesResponse (each in an array)
 *   "Profile"  for GetProfileResponse  (a single element)
 * Yes, the schema really does name the array element "Profiles"
 * (plural) for every occurrence; that's how the WSDL was written. */
static size_t emit_profile(char *out, size_t cap,
                           const char *wrapper_tag,
                           const char *token,
                           int width, int height, int fps,
                           int kbps, int is_h264,
                           const char *venc_token)
{
    /* Media1 enum is JPEG|MPEG4|H264. Always advertise H264 — see
     * comment above. */
    const char *codec_name = "H264";
    int gov = fps * 2;
    (void)is_h264;  /* in case future code differentiates */

    int n = snprintf(out, cap,
        "<trt:%s fixed=\"true\" token=\"%s\">"
          "<tt:Name>%s</tt:Name>"
          "<tt:VideoSourceConfiguration token=\"" VSRC_TOKEN "\">"
            "<tt:Name>" VSRC_TOKEN "</tt:Name>"
            "<tt:UseCount>2</tt:UseCount>"
            "<tt:SourceToken>" VSRC_TOKEN "</tt:SourceToken>"
            "<tt:Bounds x=\"0\" y=\"0\" width=\"1920\" height=\"1080\"/>"
          "</tt:VideoSourceConfiguration>"
          "<tt:VideoEncoderConfiguration token=\"%s\">"
            "<tt:Name>%s</tt:Name>"
            "<tt:UseCount>1</tt:UseCount>"
            "<tt:Encoding>%s</tt:Encoding>"
            "<tt:Resolution><tt:Width>%d</tt:Width><tt:Height>%d</tt:Height></tt:Resolution>"
            "<tt:Quality>5.0</tt:Quality>"
            "<tt:RateControl>"
              "<tt:FrameRateLimit>%d</tt:FrameRateLimit>"
              "<tt:EncodingInterval>1</tt:EncodingInterval>"
              "<tt:BitrateLimit>%d</tt:BitrateLimit>"
            "</tt:RateControl>"
            "<tt:H264><tt:GovLength>%d</tt:GovLength>"
              "<tt:H264Profile>Main</tt:H264Profile></tt:H264>"
            "<tt:Multicast><tt:Address><tt:Type>IPv4</tt:Type>"
              "<tt:IPv4Address>0.0.0.0</tt:IPv4Address></tt:Address>"
              "<tt:Port>0</tt:Port><tt:TTL>1</tt:TTL>"
              "<tt:AutoStart>false</tt:AutoStart></tt:Multicast>"
            "<tt:SessionTimeout>PT60S</tt:SessionTimeout>"
          "</tt:VideoEncoderConfiguration>"
                    "<tt:PTZConfiguration token=\"ptzcfg0\">"
            "<tt:Name>ptzcfg0</tt:Name>"
            "<tt:UseCount>2</tt:UseCount>"
            "<tt:NodeToken>ptznode0</tt:NodeToken>"
            "<tt:DefaultAbsolutePantTiltPositionSpace>http://www.onvif.org/ver10/tptz/PanTiltSpaces/PositionGenericSpace</tt:DefaultAbsolutePantTiltPositionSpace>"
            "<tt:DefaultContinuousPanTiltVelocitySpace>http://www.onvif.org/ver10/tptz/PanTiltSpaces/VelocityGenericSpace</tt:DefaultContinuousPanTiltVelocitySpace>"
            "<tt:DefaultPTZSpeed><tt:PanTilt x=\"0.5\" y=\"0.5\" space=\"http://www.onvif.org/ver10/tptz/PanTiltSpaces/GenericSpeedSpace\"/></tt:DefaultPTZSpeed>"
            "<tt:DefaultPTZTimeout>PT5S</tt:DefaultPTZTimeout>"
          "</tt:PTZConfiguration>"
        "</trt:%s>",
        wrapper_tag, token, token,
        venc_token, venc_token,
        codec_name, width, height, fps, kbps * 1000, gov,
        wrapper_tag);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

/* Stream-config descriptor: the per-profile data we need to emit a
 * profile XML block. Used by both GetProfiles (loop) and GetProfile
 * (lookup by token). Built from the live capture_cfg. */
struct profile_view {
    const char *token;
    int   width, height;
    int   fps, kbps;
    int   is_h264;
    const char *venc_token;
    int   enabled;
};

static void build_profile_views(struct profile_view v[2])
{
    struct capture_cfg cfg;
    capture_cfg_get(&cfg);

    v[0].token       = PROFILE_TOKEN_MAIN;
    v[0].width       = 1920;
    v[0].height      = 1080;
    v[0].fps         = cfg.fps;
    v[0].kbps        = cfg.main_kbps;
    v[0].is_h264     = (cfg.main_codec != CAP_CODEC_HEVC);
    v[0].venc_token  = VENC_TOKEN_MAIN;
    v[0].enabled     = cfg.enable_main;

    v[1].token       = PROFILE_TOKEN_SUB;
    v[1].width       = 640;
    v[1].height      = 360;
    v[1].fps         = cfg.fps;
    v[1].kbps        = cfg.sub_kbps;
    v[1].is_h264     = (cfg.sub_codec != CAP_CODEC_HEVC);
    v[1].venc_token  = VENC_TOKEN_SUB;
    v[1].enabled     = cfg.enable_sub;
}

static size_t op_get_profiles(char *out, size_t cap)
{
    struct profile_view views[2];
    build_profile_views(views);

    size_t total = 0;
    int n = snprintf(out, cap,
        SOAP_ENV_OPEN "<trt:GetProfilesResponse>");
    if (n < 0 || (size_t)n >= cap) return 0;
    total += (size_t)n;

    for (int i = 0; i < 2; i++) {
        if (!views[i].enabled) continue;
        size_t pn = emit_profile(out + total, cap - total,
            "Profiles",
            views[i].token, views[i].width, views[i].height,
            views[i].fps, views[i].kbps, views[i].is_h264,
            views[i].venc_token);
        if (!pn) return 0;
        total += pn;
    }

    n = snprintf(out + total, cap - total,
        "</trt:GetProfilesResponse>" SOAP_ENV_CLOSE);
    if (n < 0 || (size_t)n >= cap - total) return 0;
    total += (size_t)n;
    return total;
}

/* GetProfile (singular): lookup by ProfileToken in body. Returns a
 * single <trt:Profile>, or a fault if the token is unknown.
 *
 * ODM and most modern ONVIF clients call GetProfile per-profile
 * after a GetProfiles enumeration, to fetch fresh details — so
 * implementing it is essential for the "Live Video" tab to work,
 * even though semantically it returns the same data we already
 * gave in GetProfiles. */
static size_t op_get_profile(char *out, size_t cap, const char *body)
{
    char token[64] = {0};
    /* xml_find_text is local to onvif.c — same one used elsewhere.
     * The body has the request element <trt:GetProfile>...
     *   <trt:ProfileToken>main</trt:ProfileToken>
     * </trt:GetProfile>. We search for ProfileToken anywhere. */
    xml_find_text(body, "ProfileToken", token, sizeof(token));

    struct profile_view views[2];
    build_profile_views(views);

    struct profile_view *match = NULL;
    for (int i = 0; i < 2; i++) {
        if (views[i].enabled && strcmp(views[i].token, token) == 0) {
            match = &views[i];
            break;
        }
    }
    if (!match) {
        return emit_fault(out, cap, "Sender",
            "No such profile (token unknown or stream disabled)");
    }

    size_t total = 0;
    int n = snprintf(out, cap,
        SOAP_ENV_OPEN "<trt:GetProfileResponse>");
    if (n < 0 || (size_t)n >= cap) return 0;
    total += (size_t)n;

    size_t pn = emit_profile(out + total, cap - total,
        "Profile",
        match->token, match->width, match->height,
        match->fps, match->kbps, match->is_h264,
        match->venc_token);
    if (!pn) return 0;
    total += pn;

    n = snprintf(out + total, cap - total,
        "</trt:GetProfileResponse>" SOAP_ENV_CLOSE);
    if (n < 0 || (size_t)n >= cap - total) return 0;
    total += (size_t)n;
    return total;
}

/* Helper: emit the bare <trt:Configurations> / <trt:Configuration>
 * element for one VENC. Used by GetVideoEncoderConfigurations
 * (plural, array of <trt:Configurations>) and
 * GetVideoEncoderConfiguration (singular, one <trt:Configuration>). */
static size_t emit_venc_config(char *out, size_t cap,
                               const char *wrapper_tag,
                               const struct profile_view *v)
{
    int n = snprintf(out, cap,
        "<trt:%s token=\"%s\">"
          "<tt:Name>%s</tt:Name>"
          "<tt:UseCount>1</tt:UseCount>"
          "<tt:Encoding>H264</tt:Encoding>"
          "<tt:Resolution><tt:Width>%d</tt:Width><tt:Height>%d</tt:Height></tt:Resolution>"
          "<tt:Quality>5.0</tt:Quality>"
          "<tt:RateControl>"
            "<tt:FrameRateLimit>%d</tt:FrameRateLimit>"
            "<tt:EncodingInterval>1</tt:EncodingInterval>"
            "<tt:BitrateLimit>%d</tt:BitrateLimit>"
          "</tt:RateControl>"
          "<tt:H264><tt:GovLength>%d</tt:GovLength>"
            "<tt:H264Profile>Main</tt:H264Profile></tt:H264>"
          "<tt:Multicast><tt:Address><tt:Type>IPv4</tt:Type>"
            "<tt:IPv4Address>0.0.0.0</tt:IPv4Address></tt:Address>"
            "<tt:Port>0</tt:Port><tt:TTL>1</tt:TTL>"
            "<tt:AutoStart>false</tt:AutoStart></tt:Multicast>"
          "<tt:SessionTimeout>PT60S</tt:SessionTimeout>"
        "</trt:%s>",
        wrapper_tag, v->venc_token, v->venc_token,
        v->width, v->height, v->fps, v->kbps * 1000, v->fps * 2,
        wrapper_tag);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

static size_t op_get_venc_configs(char *out, size_t cap)
{
    struct profile_view views[2];
    build_profile_views(views);

    size_t total = 0;
    int n = snprintf(out, cap,
        SOAP_ENV_OPEN "<trt:GetVideoEncoderConfigurationsResponse>");
    if (n < 0 || (size_t)n >= cap) return 0;
    total += (size_t)n;

    for (int i = 0; i < 2; i++) {
        if (!views[i].enabled) continue;
        size_t pn = emit_venc_config(out + total, cap - total,
                                     "Configurations", &views[i]);
        if (!pn) return 0;
        total += pn;
    }

    n = snprintf(out + total, cap - total,
        "</trt:GetVideoEncoderConfigurationsResponse>" SOAP_ENV_CLOSE);
    if (n < 0 || (size_t)n >= cap - total) return 0;
    return total + (size_t)n;
}

static size_t op_get_venc_config(char *out, size_t cap, const char *body)
{
    char token[64] = {0};
    xml_find_text(body, "ConfigurationToken", token, sizeof(token));

    struct profile_view views[2];
    build_profile_views(views);

    struct profile_view *match = NULL;
    for (int i = 0; i < 2; i++) {
        if (views[i].enabled && strcmp(views[i].venc_token, token) == 0) {
            match = &views[i];
            break;
        }
    }
    if (!match) {
        return emit_fault(out, cap, "Sender",
            "No such video encoder configuration token");
    }

    size_t total = 0;
    int n = snprintf(out, cap,
        SOAP_ENV_OPEN "<trt:GetVideoEncoderConfigurationResponse>");
    if (n < 0 || (size_t)n >= cap) return 0;
    total += (size_t)n;

    size_t pn = emit_venc_config(out + total, cap - total,
                                 "Configuration", match);
    if (!pn) return 0;
    total += pn;

    n = snprintf(out + total, cap - total,
        "</trt:GetVideoEncoderConfigurationResponse>" SOAP_ENV_CLOSE);
    if (n < 0 || (size_t)n >= cap - total) return 0;
    return total + (size_t)n;
}

/* GetVideoEncoderConfigurationOptions advertises the value ranges
 * the client may set. We declare a minimal but valid set: the
 * resolution we support, GOP length range, FPS range, bitrate
 * range. ODM uses this to populate combo boxes in the "Configure"
 * dialog. We don't allow set-config (it would be Tier-2 anyway and
 * we don't implement SetVideoEncoderConfiguration), but ODM will
 * at least show the dialog without errors. */
static size_t op_get_venc_config_options(char *out, size_t cap,
                                         const char *body)
{
    /* Ignore any ConfigurationToken — we return the same options
     * for every configuration. ODM happens to accept that. */
    (void)body;

    int n = snprintf(out, cap,
        SOAP_ENV_OPEN
        "<trt:GetVideoEncoderConfigurationOptionsResponse>"
          "<trt:Options>"
            "<tt:QualityRange><tt:Min>1</tt:Min><tt:Max>10</tt:Max></tt:QualityRange>"
            "<tt:H264>"
              "<tt:ResolutionsAvailable>"
                "<tt:Width>1920</tt:Width><tt:Height>1080</tt:Height>"
              "</tt:ResolutionsAvailable>"
              "<tt:ResolutionsAvailable>"
                "<tt:Width>640</tt:Width><tt:Height>360</tt:Height>"
              "</tt:ResolutionsAvailable>"
              "<tt:GovLengthRange><tt:Min>1</tt:Min><tt:Max>120</tt:Max></tt:GovLengthRange>"
              "<tt:FrameRateRange><tt:Min>1</tt:Min><tt:Max>30</tt:Max></tt:FrameRateRange>"
              "<tt:EncodingIntervalRange><tt:Min>1</tt:Min><tt:Max>1</tt:Max></tt:EncodingIntervalRange>"
              "<tt:H264ProfilesSupported>Baseline</tt:H264ProfilesSupported>"
              "<tt:H264ProfilesSupported>Main</tt:H264ProfilesSupported>"
            "</tt:H264>"
          "</trt:Options>"
        "</trt:GetVideoEncoderConfigurationOptionsResponse>"
        SOAP_ENV_CLOSE);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

/* GetVideoSourceConfigurations / GetVideoSourceConfiguration: there
 * is only one VI source on this hardware, so we always return one. */
static size_t op_get_vsrc_configs(char *out, size_t cap)
{
    int n = snprintf(out, cap,
        SOAP_ENV_OPEN
        "<trt:GetVideoSourceConfigurationsResponse>"
          "<trt:Configurations token=\"" VSRC_TOKEN "\">"
            "<tt:Name>" VSRC_TOKEN "</tt:Name>"
            "<tt:UseCount>2</tt:UseCount>"
            "<tt:SourceToken>" VSRC_TOKEN "</tt:SourceToken>"
            "<tt:Bounds x=\"0\" y=\"0\" width=\"1920\" height=\"1080\"/>"
          "</trt:Configurations>"
        "</trt:GetVideoSourceConfigurationsResponse>"
        SOAP_ENV_CLOSE);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

static size_t op_get_vsrc_config(char *out, size_t cap)
{
    int n = snprintf(out, cap,
        SOAP_ENV_OPEN
        "<trt:GetVideoSourceConfigurationResponse>"
          "<trt:Configuration token=\"" VSRC_TOKEN "\">"
            "<tt:Name>" VSRC_TOKEN "</tt:Name>"
            "<tt:UseCount>2</tt:UseCount>"
            "<tt:SourceToken>" VSRC_TOKEN "</tt:SourceToken>"
            "<tt:Bounds x=\"0\" y=\"0\" width=\"1920\" height=\"1080\"/>"
          "</trt:Configuration>"
        "</trt:GetVideoSourceConfigurationResponse>"
        SOAP_ENV_CLOSE);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

static size_t op_get_video_sources(char *out, size_t cap)
{
    int n = snprintf(out, cap,
        SOAP_ENV_OPEN
        "<trt:GetVideoSourcesResponse>"
          "<trt:VideoSources token=\"" VSRC_TOKEN "\">"
            "<tt:Framerate>30</tt:Framerate>"
            "<tt:Resolution>"
              "<tt:Width>1920</tt:Width><tt:Height>1080</tt:Height>"
            "</tt:Resolution>"
          "</trt:VideoSources>"
        "</trt:GetVideoSourcesResponse>"
        SOAP_ENV_CLOSE);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

static size_t op_get_stream_uri(char *out, size_t cap,
                                const char *body,
                                const char *host, int port)
{
    (void)port;
    /* The request says which profile token; we map to /main or /sub. */
    char token[64] = {0};
    xml_find_text(body, "ProfileToken", token, sizeof(token));

    struct capture_cfg cfg;
    capture_cfg_get(&cfg);

    const char *path = "/main";
    if (token[0] && strcmp(token, PROFILE_TOKEN_SUB) == 0) path = "/sub";

    /* RTSP URL — the rtsp_server listens on cfg.rtsp_port (default 8554).
     * If auth is enabled we include user@host so VLC etc. can connect
     * directly; Frigate ignores embedded creds but accepts them. */
    char userpart[80] = {0};
    if (auth_is_configured()) {
        snprintf(userpart, sizeof(userpart), "%s:%s@",
                 auth_get_user(), auth_get_pass());
    }

    int n = snprintf(out, cap,
        SOAP_ENV_OPEN
        "<trt:GetStreamUriResponse>"
          "<trt:MediaUri>"
            "<tt:Uri>rtsp://%s%s:%d%s</tt:Uri>"
            "<tt:InvalidAfterConnect>false</tt:InvalidAfterConnect>"
            "<tt:InvalidAfterReboot>false</tt:InvalidAfterReboot>"
            "<tt:Timeout>PT0S</tt:Timeout>"
          "</trt:MediaUri>"
        "</trt:GetStreamUriResponse>"
        SOAP_ENV_CLOSE,
        userpart, host, cfg.rtsp_port, path);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

static size_t op_get_snapshot_uri(char *out, size_t cap,
                                  const char *host, int port)
{
    int n = snprintf(out, cap,
        SOAP_ENV_OPEN
        "<trt:GetSnapshotUriResponse>"
          "<trt:MediaUri>"
            "<tt:Uri>http://%s:%d/snapshot.jpg</tt:Uri>"
            "<tt:InvalidAfterConnect>false</tt:InvalidAfterConnect>"
            "<tt:InvalidAfterReboot>false</tt:InvalidAfterReboot>"
            "<tt:Timeout>PT0S</tt:Timeout>"
          "</trt:MediaUri>"
        "</trt:GetSnapshotUriResponse>"
        SOAP_ENV_CLOSE,
        host, port);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

/* ============================================================ */
/* GetNetworkInterfaces                                         */
/*                                                              */
/* HA calls this to resolve the device's IP for stream URIs.   */
/* We detect the local IP dynamically from the network ifaces;  */
/* if we can't, we fall back to returning an empty IP — the    */
/* client already knows the IP (it's talking to us), so the    */
/* presence of the element matters more than the value.        */
/* ============================================================ */
static void get_local_ip(char *out, size_t cap)
{
    snprintf(out, cap, "0.0.0.0");
    struct ifaddrs *ifa_head = NULL;
    if (getifaddrs(&ifa_head) != 0) return;
    for (struct ifaddrs *ifa = ifa_head; ifa; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) continue;
        if (ifa->ifa_addr->sa_family != AF_INET) continue;
        if (ifa->ifa_flags & IFF_LOOPBACK) continue;
        if (!(ifa->ifa_flags & IFF_UP)) continue;
        struct sockaddr_in *in4 = (struct sockaddr_in *)ifa->ifa_addr;
        uint32_t ip = ntohl(in4->sin_addr.s_addr);
        /* Prefer non-169.254.x.x link-local. */
        if ((ip >> 16) == 0xA9FE) continue;
        snprintf(out, cap, "%s", inet_ntoa(in4->sin_addr));
        break;
    }
    freeifaddrs(ifa_head);
}

static size_t op_get_network_interfaces(char *out, size_t cap)
{
    char ip[24];
    get_local_ip(ip, sizeof(ip));

    /* Read MAC address from sysfs.  Try wlan0 first (STA/AP iface),
     * fall back to eth0, then give up and use zeros. */
    char mac[18] = "00:00:00:00:00:00";
    const char *mac_ifaces[] = { "wlan0", "eth0", NULL };
    for (int i = 0; mac_ifaces[i]; i++) {
        char path[64];
        snprintf(path, sizeof(path),
                 "/sys/class/net/%s/address", mac_ifaces[i]);
        FILE *mf = fopen(path, "r");
        if (mf) {
            char buf[20] = {0};
            if (fgets(buf, sizeof(buf), mf)) {
                /* Strip trailing newline. */
                size_t L = strlen(buf);
                while (L > 0 && (buf[L-1] == '\n' || buf[L-1] == '\r'))
                    buf[--L] = 0;
                if (L == 17)   /* "xx:xx:xx:xx:xx:xx" */
                    snprintf(mac, sizeof(mac), "%s", buf);
            }
            fclose(mf);
            if (mac[0] != '0' || mac[1] != '0') break; /* got a real MAC */
        }
    }

    int n = snprintf(out, cap,
        SOAP_ENV_OPEN
        "<tds:GetNetworkInterfacesResponse>"
          "<tds:NetworkInterfaces token=\"eth0\">"
            "<tt:Enabled>true</tt:Enabled>"
            "<tt:Info>"
              "<tt:Name>wlan0</tt:Name>"
              "<tt:HwAddress>%s</tt:HwAddress>"
              "<tt:MTU>1500</tt:MTU>"
            "</tt:Info>"
            "<tt:IPv4>"
              "<tt:Enabled>true</tt:Enabled>"
              "<tt:Config>"
                "<tt:Manual>"
                  "<tt:Address>%s</tt:Address>"
                  "<tt:PrefixLength>24</tt:PrefixLength>"
                "</tt:Manual>"
                "<tt:DHCP>true</tt:DHCP>"
              "</tt:Config>"
            "</tt:IPv4>"
          "</tds:NetworkInterfaces>"
        "</tds:GetNetworkInterfacesResponse>"
        SOAP_ENV_CLOSE,
        mac, ip);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

/* ============================================================ */
/* GetSystemUris                                                */
/*                                                              */
/* Returns the HTTP management URL. HA uses this to confirm    */
/* connectivity and derive the device web UI URL.              */
/* ============================================================ */
static size_t op_get_system_uris(char *out, size_t cap,
                                  const char *host, int port)
{
    int n = snprintf(out, cap,
        SOAP_ENV_OPEN
        "<tds:GetSystemUrisResponse>"
          "<tds:SystemLogUris/>"
          "<tds:SupportInfoUri/>"
          "<tds:Extension/>"
        "</tds:GetSystemUrisResponse>"
        SOAP_ENV_CLOSE);
    (void)host; (void)port;
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

/* ============================================================ */
/* GetServiceCapabilities (Device + Media)                      */
/*                                                              */
/* HA and Frigate call this on the device service and on the   */
/* media service before deciding which features to enable. We  */
/* advertise the minimal-but-accurate capability set.          */
/* ============================================================ */
static size_t op_get_device_service_capabilities(char *out, size_t cap)
{
    int n = snprintf(out, cap,
        SOAP_ENV_OPEN
        "<tds:GetServiceCapabilitiesResponse>"
          "<tds:Capabilities>"
            "<tds:Network"
              " IPFilter=\"false\""
              " ZeroConfiguration=\"false\""
              " IPVersion6=\"false\""
              " DynDNS=\"false\""
              " Dot11Configuration=\"false\""
              " HostnameFromDHCP=\"false\""
              " NTP=\"0\"/>"
            "<tds:Security"
              " TLS1.0=\"false\""
              " TLS1.1=\"false\""
              " TLS1.2=\"false\""
              " OnboardKeyGeneration=\"false\""
              " AccessPolicyConfig=\"false\""
              " DefaultAccessPolicy=\"false\""
              " Dot1X=\"false\""
              " RemoteUserHandling=\"false\""
              " X.509Token=\"false\""
              " SAMLToken=\"false\""
              " KerberosToken=\"false\""
              " UsernameToken=\"true\""
              " HttpDigest=\"false\""
              " RELToken=\"false\"/>"
            "<tds:System"
              " DiscoveryResolve=\"false\""
              " DiscoveryBye=\"true\""
              " RemoteDiscovery=\"false\""
              " SystemBackup=\"false\""
              " SystemLogging=\"false\""
              " FirmwareUpgrade=\"false\""
              " HttpFirmwareUpgrade=\"false\""
              " HttpSystemBackup=\"false\""
              " HttpSystemLogging=\"false\""
              " HttpSupportInformation=\"false\""
              " StorageConfiguration=\"false\"/>"
          "</tds:Capabilities>"
        "</tds:GetServiceCapabilitiesResponse>"
        SOAP_ENV_CLOSE);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

static size_t op_get_media_service_capabilities(char *out, size_t cap)
{
    int n = snprintf(out, cap,
        SOAP_ENV_OPEN
        "<trt:GetServiceCapabilitiesResponse>"
          "<trt:Capabilities"
            " SnapshotUri=\"true\""
            " Rotation=\"false\""
            " VideoSourceMode=\"false\""
            " OSD=\"false\""
            " EXICompression=\"false\">"
            "<trt:ProfileCapabilities MaximumNumberOfProfiles=\"2\"/>"
            "<trt:StreamingCapabilities"
              " RTPMulticast=\"false\""
              " RTP_TCP=\"true\""
              " RTP_RTSP_TCP=\"true\""
              " NonAggregateControl=\"false\"/>"
          "</trt:Capabilities>"
        "</trt:GetServiceCapabilitiesResponse>"
        SOAP_ENV_CLOSE);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

/* ============================================================ */
/* GetHostname                                                  */
/*                                                              */
/* Some clients (ONVIF Device Manager, certain HA versions)    */
/* call GetHostname as part of device enumeration. It's safe   */
/* to return a static name.                                     */
/* ============================================================ */
static size_t op_get_hostname(char *out, size_t cap)
{
    char hostname[64] = "ipcamera";
    gethostname(hostname, sizeof(hostname) - 1);
    int n = snprintf(out, cap,
        SOAP_ENV_OPEN
        "<tds:GetHostnameResponse>"
          "<tds:HostnameInformation>"
            "<tt:FromDHCP>true</tt:FromDHCP>"
            "<tt:Name>%s</tt:Name>"
          "</tds:HostnameInformation>"
        "</tds:GetHostnameResponse>"
        SOAP_ENV_CLOSE,
        hostname);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

/* ============================================================ */
/* GetNTP                                                       */
/* ============================================================ */
static size_t op_get_ntp(char *out, size_t cap)
{
    int n = snprintf(out, cap,
        SOAP_ENV_OPEN
        "<tds:GetNTPResponse>"
          "<tds:NTPInformation>"
            "<tt:FromDHCP>false</tt:FromDHCP>"
            "<tt:NTPManual>"
              "<tt:Type>DNS</tt:Type>"
              "<tt:DNSname>pool.ntp.org</tt:DNSname>"
            "</tt:NTPManual>"
          "</tds:NTPInformation>"
        "</tds:GetNTPResponse>"
        SOAP_ENV_CLOSE);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

/* ============================================================ */
/* GetDNS                                                       */
/* ============================================================ */
static size_t op_get_dns(char *out, size_t cap)
{
    int n = snprintf(out, cap,
        SOAP_ENV_OPEN
        "<tds:GetDNSResponse>"
          "<tds:DNSInformation>"
            "<tt:FromDHCP>true</tt:FromDHCP>"
          "</tds:DNSInformation>"
        "</tds:GetDNSResponse>"
        SOAP_ENV_CLOSE);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

/* ============================================================ */
/* GetNetworkProtocols                                          */
/*                                                              */
/* Advertises which management protocols are active. We expose  */
/* HTTP on :80 and RTSP on the configured port.                 */
/* ============================================================ */
static size_t op_get_network_protocols(char *out, size_t cap)
{
    struct capture_cfg cfg;
    capture_cfg_get(&cfg);
    int n = snprintf(out, cap,
        SOAP_ENV_OPEN
        "<tds:GetNetworkProtocolsResponse>"
          "<tds:NetworkProtocols>"
            "<tt:Name>HTTP</tt:Name>"
            "<tt:Enabled>true</tt:Enabled>"
            "<tt:Port>80</tt:Port>"
          "</tds:NetworkProtocols>"
          "<tds:NetworkProtocols>"
            "<tt:Name>RTSP</tt:Name>"
            "<tt:Enabled>true</tt:Enabled>"
            "<tt:Port>%d</tt:Port>"
          "</tds:NetworkProtocols>"
        "</tds:GetNetworkProtocolsResponse>"
        SOAP_ENV_CLOSE,
        cfg.rtsp_port);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

/* ============================================================ */
/* GetDiscoveryMode                                             */
/* ============================================================ */
static size_t op_get_discovery_mode(char *out, size_t cap)
{
    int n = snprintf(out, cap,
        SOAP_ENV_OPEN
        "<tds:GetDiscoveryModeResponse>"
          "<tds:DiscoveryMode>Discoverable</tds:DiscoveryMode>"
        "</tds:GetDiscoveryModeResponse>"
        SOAP_ENV_CLOSE);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

/* ============================================================ */
/* GetNetworkDefaultGateway                                     */
/* ============================================================ */
static size_t op_get_network_default_gateway(char *out, size_t cap)
{
    /* Read the default gateway from /proc/net/route. The route
     * table entry with Iface matching our wlan0 and Destination=0
     * carries the gateway in hex little-endian format. */
    char gw[24] = "0.0.0.0";
    FILE *f = fopen("/proc/net/route", "r");
    if (f) {
        char line[256];
        /* Skip header line. */
        if (fgets(line, sizeof(line), f)) {
            while (fgets(line, sizeof(line), f)) {
                char iface[16]; unsigned int dest, gateway;
                if (sscanf(line, "%15s %x %x", iface, &dest, &gateway) == 3
                    && dest == 0 && gateway != 0) {
                    /* gateway is in host-endian after sscanf %x */
                    struct in_addr a;
                    a.s_addr = gateway;  /* already network byte order from hex */
                    snprintf(gw, sizeof(gw), "%s", inet_ntoa(a));
                    break;
                }
            }
        }
        fclose(f);
    }

    int n = snprintf(out, cap,
        SOAP_ENV_OPEN
        "<tds:GetNetworkDefaultGatewayResponse>"
          "<tds:NetworkGateway>"
            "<tt:IPv4Address>%s</tt:IPv4Address>"
          "</tds:NetworkGateway>"
        "</tds:GetNetworkDefaultGatewayResponse>"
        SOAP_ENV_CLOSE,
        gw);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

/* ============================================================ */
/* GetCertificates / GetCertificatesStatus                      */
/*                                                              */
/* We don't support TLS, so we return empty lists. Clients      */
/* that call these just want to know what's installed; an empty */
/* response is valid per the schema and better than a fault.    */
/* ============================================================ */
static size_t op_get_certificates(char *out, size_t cap)
{
    /* Return an explicit empty response body instead of a self-closing
     * tag.  WCF/.NET XML deserializers (used by ODM) map a self-closing
     * element to null rather than an empty list, causing a
     * "Object reference not set" NullReferenceException on the caller
     * side.  An explicit open+close tag with no children maps to an
     * empty list, which is what we want. */
    int n = snprintf(out, cap,
        SOAP_ENV_OPEN
        "<tds:GetCertificatesResponse>"
        "</tds:GetCertificatesResponse>"
        SOAP_ENV_CLOSE);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

static size_t op_get_certificates_status(char *out, size_t cap)
{
    int n = snprintf(out, cap,
        SOAP_ENV_OPEN
        "<tds:GetCertificatesStatusResponse>"
        "</tds:GetCertificatesStatusResponse>"
        SOAP_ENV_CLOSE);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

/* ============================================================ */
/* Top-level dispatcher                                         */
/* ============================================================ */

int onvif_dispatch(const char *service_path, const char *query,
                   const char *body, const char *host_header,
                   char *out, size_t cap, size_t *out_len)
{
    char op[64];
    if (find_operation(body, op, sizeof(op)) != 0) {
        *out_len = emit_fault(out, cap, "Sender",
                              "Could not parse SOAP body");
        return 0;
    }

    char host[80]; int port;
    split_host(host_header, host, sizeof(host), &port);

    /* GetSystemDateAndTime is the only auth-free operation. Clients
     * call it first to sync time before computing UsernameToken
     * digests. */
    int needs_auth = (strcmp(op, "GetSystemDateAndTime") != 0);
    if (needs_auth && onvif_check_ws_security(body) != 0) {
        *out_len = emit_fault(out, cap, "Sender:NotAuthorized",
                              "Authentication required");
        return 0;
    }

    /* Service routing: /onvif/events_service goes to onvif_events.c */
    if (strcmp(service_path, "/onvif/events_service") == 0) {
        return onvif_events_dispatch(op, query, body, host, port,
                                     out, cap, out_len);
    }
    if (strcmp(service_path, "/onvif/ptz_service") == 0) {
        size_t pn = onvif_ptz_dispatch(op, body, out, cap);
        if (pn == 0)
            pn = emit_fault(out, cap, "Receiver:ActionNotSupported", op);
        *out_len = pn;
        return 0;
    }

    /* Device + Media share the same handler set; we just match by
     * operation name. Some deployments split them by service path
     * but most cameras (including Hik, Dahua) accept any op on any
     * service path, and so do we. */
    size_t n = 0;
    if      (!strcmp(op, "GetSystemDateAndTime"))
        n = op_get_system_date_and_time(out, cap);
    else if (!strcmp(op, "GetDeviceInformation"))
        n = op_get_device_information(out, cap);
    else if (!strcmp(op, "GetCapabilities"))
        n = op_get_capabilities(out, cap, host, port);
    else if (!strcmp(op, "GetServices"))
        n = op_get_services(out, cap, host, port);
    else if (!strcmp(op, "GetScopes"))
        n = op_get_scopes(out, cap);
    else if (!strcmp(op, "GetUsers"))
        n = op_get_users(out, cap);
    else if (!strcmp(op, "GetProfiles"))
        n = op_get_profiles(out, cap);
    else if (!strcmp(op, "GetProfile"))
        n = op_get_profile(out, cap, body);
    else if (!strcmp(op, "GetVideoEncoderConfigurations"))
        n = op_get_venc_configs(out, cap);
    else if (!strcmp(op, "GetVideoEncoderConfiguration"))
        n = op_get_venc_config(out, cap, body);
    else if (!strcmp(op, "GetVideoEncoderConfigurationOptions"))
        n = op_get_venc_config_options(out, cap, body);
    else if (!strcmp(op, "GetVideoSourceConfigurations"))
        n = op_get_vsrc_configs(out, cap);
    else if (!strcmp(op, "GetVideoSourceConfiguration"))
        n = op_get_vsrc_config(out, cap);
    else if (!strcmp(op, "GetVideoSources"))
        n = op_get_video_sources(out, cap);
    else if (!strcmp(op, "GetStreamUri"))
        n = op_get_stream_uri(out, cap, body, host, port);
    else if (!strcmp(op, "GetSnapshotUri"))
        n = op_get_snapshot_uri(out, cap, host, port);
    else if (!strcmp(op, "GetNetworkInterfaces"))
        n = op_get_network_interfaces(out, cap);
    else if (!strcmp(op, "GetSystemUris"))
        n = op_get_system_uris(out, cap, host, port);
    else if (!strcmp(op, "GetServiceCapabilities")) {
        /* Return the capability set appropriate for the service path.
         * Media path gets media capabilities; everything else gets
         * device capabilities. */
        if (strstr(service_path, "media"))
            n = op_get_media_service_capabilities(out, cap);
        else
            n = op_get_device_service_capabilities(out, cap);
    }
    else if (!strcmp(op, "GetHostname"))
        n = op_get_hostname(out, cap);
    else if (!strcmp(op, "GetNTP"))
        n = op_get_ntp(out, cap);
    else if (!strcmp(op, "GetDNS"))
        n = op_get_dns(out, cap);
    else if (!strcmp(op, "GetUsers")) {
        /* HA calls GetUsers to verify credentials exist before
         * attempting authenticated calls. Return the configured
         * user (or a placeholder if none is set). */
        const char *u = auth_get_user();
        if (!u || !*u) u = "admin";
        char tmp[256];
        int r = snprintf(tmp, sizeof(tmp),
            SOAP_ENV_OPEN
            "<tds:GetUsersResponse>"
              "<tds:User>"
                "<tt:Username>%s</tt:Username>"
                "<tt:UserLevel>Administrator</tt:UserLevel>"
              "</tds:User>"
            "</tds:GetUsersResponse>"
            SOAP_ENV_CLOSE, u);
        n = (r > 0 && (size_t)r < cap) ? (size_t)r : 0;
        if (n) memcpy(out, tmp, n + 1);
    }
    else if (!strcmp(op, "GetNetworkProtocols"))
        n = op_get_network_protocols(out, cap);
    else if (!strcmp(op, "GetDiscoveryMode"))
        n = op_get_discovery_mode(out, cap);
    else if (!strcmp(op, "GetNetworkDefaultGateway"))
        n = op_get_network_default_gateway(out, cap);
    else if (!strcmp(op, "GetCertificates"))
        n = op_get_certificates(out, cap);
    else if (!strcmp(op, "GetCertificatesStatus"))
        n = op_get_certificates_status(out, cap);
    else if (!strcmp(op, "GetNodes")   || !strcmp(op, "GetNode") ||
        !strcmp(op, "ContinuousMove") || !strcmp(op, "Stop") ||
        !strcmp(op, "AbsoluteMove")   || !strcmp(op, "RelativeMove") ||
        !strcmp(op, "GetConfigurations") ||
        !strcmp(op, "GetConfiguration")  ||
        !strcmp(op, "GetConfigurationOptions")) {
        n = onvif_ptz_dispatch(op, body, out, cap);
    }
    else {
        fprintf(stderr, "[onvif] unsupported operation: %s\n", op);
        n = emit_fault(out, cap, "Receiver:ActionNotSupported", op);
    }

    if (n == 0) {
        /* Buffer too small or snprintf error. Fall back to fault. */
        n = emit_fault(out, cap, "Receiver", "Internal error");
    }
    *out_len = n;
    return 0;
}

/* ============================================================ */
/* Init / shutdown                                              */
/* ============================================================ */

int onvif_init(void)
{
    if (onvif_wsd_start() != 0) {
        fprintf(stderr, "[onvif] WSD start failed (discovery won't work)\n");
        /* Non-fatal: clients can still connect by IP directly. */
    }
    if (onvif_events_init() != 0) {
        fprintf(stderr, "[onvif] events init failed (motion won't work)\n");
    }
    fprintf(stderr, "[onvif] ready\n");
    return 0;
}

void onvif_shutdown(void)
{
    onvif_wsd_stop();
    onvif_events_shutdown();
    fprintf(stderr, "[onvif] stopped\n");
}
