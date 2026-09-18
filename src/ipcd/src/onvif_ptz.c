/*
 * onvif_ptz.c — ONVIF PTZ service handlers for ipcd.
 *
 * Implements the subset of the ONVIF PTZ service that Frigate's
 * autotracking uses:
 *
 *   GetConfigurations / GetConfiguration
 *   GetConfigurationOptions
 *   GetNodes / GetNode
 *   GetStatus
 *   ContinuousMove   (autotracking's primary command)
 *   Stop
 *   AbsoluteMove
 *   RelativeMove
 *
 * ONVIF coordinate space is normalised: pan/tilt positions and
 * velocities run -1.0..+1.0. We map that onto the motor's raw step
 * ranges (see ptz_motor.c). PositionSpace / VelocitySpace use the
 * ONVIF generic spaces.
 *
 * This file follows the same conventions as onvif.c: static op_*
 * functions returning bytes written, hardcoded XML with %s/%f
 * placeholders, SOAP_ENV_OPEN/CLOSE wrappers. The dispatcher in
 * onvif.c calls onvif_ptz_dispatch() for the PTZ ops.
 *
 * The PTZ config/node/profile tokens must be STABLE (clients cache
 * them) and the profile must reference the PTZ configuration or
 * Frigate won't treat the profile as PTZ-capable.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ipcd.h"
#include "ptz_motor.h"

/* Stable tokens, referenced from the media profile too. */
#define PTZ_NODE_TOKEN    "ptznode0"
#define PTZ_CONFIG_TOKEN  "ptzcfg0"

/* Re-declared here (onvif.c has the master copies as macros). Keep in
 * sync with onvif.c. */
#define PTZ_SOAP_ENV_OPEN \
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" \
    "<s:Envelope xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\"" \
    " xmlns:tt=\"http://www.onvif.org/ver10/schema\"" \
    " xmlns:tptz=\"http://www.onvif.org/ver20/ptz/wsdl\">" \
    "<s:Body>"
#define PTZ_SOAP_ENV_CLOSE "</s:Body></s:Envelope>"

/* xml_find_text lives in onvif.c/onvif_auth.c; we need a local copy to
 * pull ProfileToken / velocity numbers out of the request body. Small
 * enough to duplicate. */
static int ptz_xml_find_text(const char *src, const char *localname,
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
            const char *content_end = strstr(content, "</");
            if (!content_end) return -1;
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

/* Pull a float attribute (x= or y=) from the first PanTilt element.
 * ONVIF sends velocity/translation as:
 *   <tt:PanTilt x="0.5" y="-0.3" xmlns:...="...GenericSpace"/>
 * We scan for the attribute name within a PanTilt-ish context. */
static float find_attr_float(const char *body, const char *elem,
                             const char *attr, float dflt)
{
    /* Find the element (e.g. "PanTilt"). */
    const char *e = strstr(body, elem);
    if (!e) return dflt;

    /* Build the search key "attr=" (e.g. "x=") so we don't match a
     * stray 'x' inside xmlns/namespaces. Search only within this
     * element's tag (up to the next '>'). */
    char key[16];
    snprintf(key, sizeof(key), "%s=", attr);

    const char *tag_end = strchr(e, '>');
    const char *a = strstr(e, key);
    if (!a || (tag_end && a > tag_end)) return dflt;

    a += strlen(key);                 /* past "x=" */
    while (*a == '"' || *a == '\'' || *a == ' ') a++;   /* opening quote */
    return (float)atof(a);
}

/* raw step -> ONVIF normalised -1..+1 for an axis */
static float step_to_norm(int axis, int step)
{
    int lo, hi;
    ptz_motor_limits(axis, &lo, &hi);
    if (hi <= lo) return 0.0f;
    float f = (float)(step - lo) / (float)(hi - lo);   /* 0..1 */
    float v = f * 2.0f - 1.0f;                          /* -1..1 */
    if (v < -1.0f) v = -1.0f;                           /* clamp: pos may */
    if (v >  1.0f) v =  1.0f;                           /* drift past ends */
    return v;
}

/* ONVIF normalised -1..+1 -> raw step for an axis */
static int norm_to_step(int axis, float norm)
{
    int lo, hi;
    ptz_motor_limits(axis, &lo, &hi);
    if (norm < -1.0f) norm = -1.0f;
    if (norm >  1.0f) norm =  1.0f;
    float f = (norm + 1.0f) / 2.0f;                    /* 0..1 */
    return lo + (int)(f * (float)(hi - lo));
}

/* ============================================================ */
/* GetNodes / GetNode — describe the PT capabilities            */
/* ============================================================ */
static size_t ptz_node_xml(char *out, size_t cap, const char *wrapper)
{
    /* One PT node, no zoom. Generic position + velocity spaces,
     * ranges -1..1. MaximumNumberOfPresets kept modest. */
    int n = snprintf(out, cap,
        "<tptz:%s token=\"" PTZ_NODE_TOKEN "\">"
          "<tt:Name>PanTilt</tt:Name>"
          "<tt:SupportedPTZSpaces>"
            "<tt:AbsolutePanTiltPositionSpace>"
              "<tt:URI>http://www.onvif.org/ver10/tptz/PanTiltSpaces/PositionGenericSpace</tt:URI>"
              "<tt:XRange><tt:Min>-1.0</tt:Min><tt:Max>1.0</tt:Max></tt:XRange>"
              "<tt:YRange><tt:Min>-1.0</tt:Min><tt:Max>1.0</tt:Max></tt:YRange>"
            "</tt:AbsolutePanTiltPositionSpace>"
            "<tt:ContinuousPanTiltVelocitySpace>"
              "<tt:URI>http://www.onvif.org/ver10/tptz/PanTiltSpaces/VelocityGenericSpace</tt:URI>"
              "<tt:XRange><tt:Min>-1.0</tt:Min><tt:Max>1.0</tt:Max></tt:XRange>"
              "<tt:YRange><tt:Min>-1.0</tt:Min><tt:Max>1.0</tt:Max></tt:YRange>"
            "</tt:ContinuousPanTiltVelocitySpace>"
            "<tt:PanTiltSpeedSpace>"
              "<tt:URI>http://www.onvif.org/ver10/tptz/PanTiltSpaces/GenericSpeedSpace</tt:URI>"
              "<tt:XRange><tt:Min>0.0</tt:Min><tt:Max>1.0</tt:Max></tt:XRange>"
            "</tt:PanTiltSpeedSpace>"
          "</tt:SupportedPTZSpaces>"
          "<tt:MaximumNumberOfPresets>8</tt:MaximumNumberOfPresets>"
          "<tt:HomeSupported>true</tt:HomeSupported>"
        "</tptz:%s>",
        wrapper, wrapper);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

static size_t op_ptz_get_nodes(char *out, size_t cap)
{
    size_t total = 0;
    int n = snprintf(out, cap, PTZ_SOAP_ENV_OPEN "<tptz:GetNodesResponse>");
    if (n < 0 || (size_t)n >= cap) return 0;
    total += (size_t)n;
    size_t nn = ptz_node_xml(out + total, cap - total, "PTZNode");
    if (!nn) return 0;
    total += nn;
    n = snprintf(out + total, cap - total,
                 "</tptz:GetNodesResponse>" PTZ_SOAP_ENV_CLOSE);
    if (n < 0 || (size_t)n >= cap - total) return 0;
    return total + (size_t)n;
}

static size_t op_ptz_get_node(char *out, size_t cap)
{
    size_t total = 0;
    int n = snprintf(out, cap, PTZ_SOAP_ENV_OPEN "<tptz:GetNodeResponse>");
    if (n < 0 || (size_t)n >= cap) return 0;
    total += (size_t)n;
    size_t nn = ptz_node_xml(out + total, cap - total, "PTZNode");
    if (!nn) return 0;
    total += nn;
    n = snprintf(out + total, cap - total,
                 "</tptz:GetNodeResponse>" PTZ_SOAP_ENV_CLOSE);
    if (n < 0 || (size_t)n >= cap - total) return 0;
    return total + (size_t)n;
}

/* ============================================================ */
/* GetConfigurations / GetConfiguration                         */
/* ============================================================ */
static size_t ptz_config_xml(char *out, size_t cap, const char *wrapper)
{
    int n = snprintf(out, cap,
        "<tptz:%s token=\"" PTZ_CONFIG_TOKEN "\">"
          "<tt:Name>" PTZ_CONFIG_TOKEN "</tt:Name>"
          "<tt:UseCount>2</tt:UseCount>"
          "<tt:NodeToken>" PTZ_NODE_TOKEN "</tt:NodeToken>"
          "<tt:DefaultAbsolutePanTiltPositionSpace>"
            "http://www.onvif.org/ver10/tptz/PanTiltSpaces/PositionGenericSpace"
          "</tt:DefaultAbsolutePanTiltPositionSpace>"
          "<tt:DefaultRelativePanTiltTranslationSpace>"
            "http://www.onvif.org/ver10/tptz/PanTiltSpaces/TranslationGenericSpace"
          "</tt:DefaultRelativePanTiltTranslationSpace>"
          "<tt:DefaultContinuousPanTiltVelocitySpace>"
            "http://www.onvif.org/ver10/tptz/PanTiltSpaces/VelocityGenericSpace"
          "</tt:DefaultContinuousPanTiltVelocitySpace>"
          "<tt:DefaultPTZSpeed>"
            "<tt:PanTilt x=\"0.5\" y=\"0.5\" "
            "space=\"http://www.onvif.org/ver10/tptz/PanTiltSpaces/GenericSpeedSpace\"/>"
          "</tt:DefaultPTZSpeed>"
          "<tt:DefaultPTZTimeout>PT5S</tt:DefaultPTZTimeout>"
          "<tt:PanTiltLimits>"
            "<tt:Range>"
              "<tt:URI>http://www.onvif.org/ver10/tptz/PanTiltSpaces/PositionGenericSpace</tt:URI>"
              "<tt:XRange><tt:Min>-1.0</tt:Min><tt:Max>1.0</tt:Max></tt:XRange>"
              "<tt:YRange><tt:Min>-1.0</tt:Min><tt:Max>1.0</tt:Max></tt:YRange>"
            "</tt:Range>"
          "</tt:PanTiltLimits>"
        "</tptz:%s>",
        wrapper, wrapper);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

static size_t op_ptz_get_configurations(char *out, size_t cap)
{
    size_t total = 0;
    int n = snprintf(out, cap,
        PTZ_SOAP_ENV_OPEN "<tptz:GetConfigurationsResponse>");
    if (n < 0 || (size_t)n >= cap) return 0;
    total += (size_t)n;
    size_t cn = ptz_config_xml(out + total, cap - total, "PTZConfiguration");
    if (!cn) return 0;
    total += cn;
    n = snprintf(out + total, cap - total,
                 "</tptz:GetConfigurationsResponse>" PTZ_SOAP_ENV_CLOSE);
    if (n < 0 || (size_t)n >= cap - total) return 0;
    return total + (size_t)n;
}

static size_t op_ptz_get_configuration(char *out, size_t cap)
{
    size_t total = 0;
    int n = snprintf(out, cap,
        PTZ_SOAP_ENV_OPEN "<tptz:GetConfigurationResponse>");
    if (n < 0 || (size_t)n >= cap) return 0;
    total += (size_t)n;
    size_t cn = ptz_config_xml(out + total, cap - total, "PTZConfiguration");
    if (!cn) return 0;
    total += cn;
    n = snprintf(out + total, cap - total,
                 "</tptz:GetConfigurationResponse>" PTZ_SOAP_ENV_CLOSE);
    if (n < 0 || (size_t)n >= cap - total) return 0;
    return total + (size_t)n;
}

static size_t op_ptz_get_configuration_options(char *out, size_t cap)
{
    int n = snprintf(out, cap,
        PTZ_SOAP_ENV_OPEN
        "<tptz:GetConfigurationOptionsResponse>"
          "<tptz:PTZConfigurationOptions>"
            "<tt:Spaces>"
              "<tt:AbsolutePanTiltPositionSpace>"
                "<tt:URI>http://www.onvif.org/ver10/tptz/PanTiltSpaces/PositionGenericSpace</tt:URI>"
                "<tt:XRange><tt:Min>-1.0</tt:Min><tt:Max>1.0</tt:Max></tt:XRange>"
                "<tt:YRange><tt:Min>-1.0</tt:Min><tt:Max>1.0</tt:Max></tt:YRange>"
              "</tt:AbsolutePanTiltPositionSpace>"
              "<tt:RelativePanTiltTranslationSpace>"
                "<tt:URI>http://www.onvif.org/ver10/tptz/PanTiltSpaces/TranslationGenericSpace</tt:URI>"
                "<tt:XRange><tt:Min>-1.0</tt:Min><tt:Max>1.0</tt:Max></tt:XRange>"
                "<tt:YRange><tt:Min>-1.0</tt:Min><tt:Max>1.0</tt:Max></tt:YRange>"
              "</tt:RelativePanTiltTranslationSpace>"
              "<tt:ContinuousPanTiltVelocitySpace>"
                "<tt:URI>http://www.onvif.org/ver10/tptz/PanTiltSpaces/VelocityGenericSpace</tt:URI>"
                "<tt:XRange><tt:Min>-1.0</tt:Min><tt:Max>1.0</tt:Max></tt:XRange>"
                "<tt:YRange><tt:Min>-1.0</tt:Min><tt:Max>1.0</tt:Max></tt:YRange>"
              "</tt:ContinuousPanTiltVelocitySpace>"
              "<tt:PanTiltSpeedSpace>"
                "<tt:URI>http://www.onvif.org/ver10/tptz/PanTiltSpaces/GenericSpeedSpace</tt:URI>"
                "<tt:XRange><tt:Min>0.0</tt:Min><tt:Max>1.0</tt:Max></tt:XRange>"
              "</tt:PanTiltSpeedSpace>"
            "</tt:Spaces>"
            "<tt:PTZTimeout><tt:Min>PT1S</tt:Min><tt:Max>PT10S</tt:Max></tt:PTZTimeout>"
          "</tptz:PTZConfigurationOptions>"
        "</tptz:GetConfigurationOptionsResponse>"
        PTZ_SOAP_ENV_CLOSE);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

/* ============================================================ */
/* GetStatus — current position + movestate                     */
/* ============================================================ */
static size_t op_ptz_get_status(char *out, size_t cap)
{
    int pan  = ptz_motor_get_pos(PTZ_AXIS_PAN);
    int tilt = ptz_motor_get_pos(PTZ_AXIS_TILT);
    float px = step_to_norm(PTZ_AXIS_PAN,  pan  < 0 ? 0 : pan);
    float py = step_to_norm(PTZ_AXIS_TILT, tilt < 0 ? 0 : tilt);

    int n = snprintf(out, cap,
        PTZ_SOAP_ENV_OPEN
        "<tptz:GetStatusResponse>"
          "<tptz:PTZStatus>"
            "<tt:Position>"
              "<tt:PanTilt x=\"%.4f\" y=\"%.4f\" "
              "space=\"http://www.onvif.org/ver10/tptz/PanTiltSpaces/PositionGenericSpace\"/>"
            "</tt:Position>"
            "<tt:MoveStatus>"
              "<tt:PanTilt>IDLE</tt:PanTilt>"
            "</tt:MoveStatus>"
            "<tt:UtcTime>1970-01-01T00:00:00Z</tt:UtcTime>"
          "</tptz:PTZStatus>"
        "</tptz:GetStatusResponse>"
        PTZ_SOAP_ENV_CLOSE,
        px, py);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

/* ============================================================ */
/* ContinuousMove / Stop — the autotracking path                */
/* ============================================================ */
static size_t op_ptz_continuous_move(char *out, size_t cap, const char *body)
{
    float vx = find_attr_float(body, "PanTilt", "x", 0.0f);
    float vy = find_attr_float(body, "PanTilt", "y", 0.0f);
    fprintf(stderr, "[ptz] ContinuousMove parsed vx=%.3f vy=%.3f\n", vx, vy);
    fflush(stderr);
    ptz_motor_continuous(vx, vy);

    int n = snprintf(out, cap,
        PTZ_SOAP_ENV_OPEN
        "<tptz:ContinuousMoveResponse/>"
        PTZ_SOAP_ENV_CLOSE);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

static size_t op_ptz_stop(char *out, size_t cap)
{
    ptz_motor_stop();
    int n = snprintf(out, cap,
        PTZ_SOAP_ENV_OPEN "<tptz:StopResponse/>" PTZ_SOAP_ENV_CLOSE);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

/* ============================================================ */
/* AbsoluteMove / RelativeMove                                  */
/* ============================================================ */
static size_t op_ptz_absolute_move(char *out, size_t cap, const char *body)
{
    float x = find_attr_float(body, "PanTilt", "x", 0.0f);
    float y = find_attr_float(body, "PanTilt", "y", 0.0f);
    ptz_motor_goto(PTZ_AXIS_PAN,  norm_to_step(PTZ_AXIS_PAN,  x));
    ptz_motor_goto(PTZ_AXIS_TILT, norm_to_step(PTZ_AXIS_TILT, y));

    int n = snprintf(out, cap,
        PTZ_SOAP_ENV_OPEN "<tptz:AbsoluteMoveResponse/>" PTZ_SOAP_ENV_CLOSE);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

static size_t op_ptz_relative_move(char *out, size_t cap, const char *body)
{
    /* Translation is normalised too; scale by full range for a step delta. */
    float x = find_attr_float(body, "PanTilt", "x", 0.0f);
    float y = find_attr_float(body, "PanTilt", "y", 0.0f);
    int plo, phi, tlo, thi;
    ptz_motor_limits(PTZ_AXIS_PAN,  &plo, &phi);
    ptz_motor_limits(PTZ_AXIS_TILT, &tlo, &thi);
    if (x != 0.0f) ptz_motor_move_rel(PTZ_AXIS_PAN,  (int)(x * (phi - plo) / 2));
    if (y != 0.0f) ptz_motor_move_rel(PTZ_AXIS_TILT, (int)(y * (thi - tlo) / 2));

    int n = snprintf(out, cap,
        PTZ_SOAP_ENV_OPEN "<tptz:RelativeMoveResponse/>" PTZ_SOAP_ENV_CLOSE);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

/* GetServiceCapabilities — Frigate calls this during PTZ init.
 * Must return a valid Capabilities response, not a fault. */
static size_t op_ptz_get_service_capabilities(char *out, size_t cap)
{
    int n = snprintf(out, cap,
        PTZ_SOAP_ENV_OPEN
        "<tptz:GetServiceCapabilitiesResponse>"
          "<tptz:Capabilities EFlip=\"false\" Reverse=\"false\" "
            "GetCompatibleConfigurations=\"false\" "
            "MoveStatus=\"true\" StatusPosition=\"true\"/>"
        "</tptz:GetServiceCapabilitiesResponse>"
        PTZ_SOAP_ENV_CLOSE);
    if (n < 0 || (size_t)n >= cap) return 0;
    return (size_t)n;
}

/* ============================================================ */
/* Dispatch — called from onvif.c for PTZ operations            */
/* Returns bytes written, or 0 if op not handled here.          */
/* ============================================================ */
size_t onvif_ptz_dispatch(const char *op, const char *body,
                          char *out, size_t cap)
{
    if      (!strcmp(op, "GetNodes"))          return op_ptz_get_nodes(out, cap);
    else if (!strcmp(op, "GetNode"))           return op_ptz_get_node(out, cap);
    else if (!strcmp(op, "GetConfigurations")) return op_ptz_get_configurations(out, cap);
    else if (!strcmp(op, "GetConfiguration"))  return op_ptz_get_configuration(out, cap);
    else if (!strcmp(op, "GetConfigurationOptions")) return op_ptz_get_configuration_options(out, cap);
    else if (!strcmp(op, "GetServiceCapabilities")) return op_ptz_get_service_capabilities(out, cap);
    else if (!strcmp(op, "GetStatus"))         return op_ptz_get_status(out, cap);
    else if (!strcmp(op, "ContinuousMove"))    return op_ptz_continuous_move(out, cap, body);
    else if (!strcmp(op, "Stop"))              return op_ptz_stop(out, cap);
    else if (!strcmp(op, "AbsoluteMove"))      return op_ptz_absolute_move(out, cap, body);
    else if (!strcmp(op, "RelativeMove"))      return op_ptz_relative_move(out, cap, body);
    return 0;   /* not a PTZ op we handle */
}
