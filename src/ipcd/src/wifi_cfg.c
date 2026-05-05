/*
 * wifi_cfg.c — load/save Wi-Fi credentials on jffs2.
 *
 * File format (key=value, one per line, no quoting needed for ASCII SSID/PSK):
 *   ssid=MyHomeNet
 *   psk=hunter2hunter2
 *
 * SSID limit 32 bytes per 802.11; we allow up to 63 to be safe.
 * PSK: 8..63 chars for WPA2-PSK passphrase, or 64 hex chars for raw PMK.
 *
 * Atomicity: we write to .tmp + fsync + rename. jffs2 honours rename().
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

#include "ipcd.h"

static void rstrip(char *s)
{
    size_t n = strlen(s);
    while (n && (s[n-1] == '\n' || s[n-1] == '\r' || s[n-1] == ' ' || s[n-1] == '\t'))
        s[--n] = 0;
}

int wifi_cfg_load(struct wifi_cfg *out)
{
    memset(out, 0, sizeof(*out));
    FILE *f = fopen(WIFI_CONF_PATH, "r");
    if (!f) return -1;

    char line[256];
    while (fgets(line, sizeof(line), f)) {
        rstrip(line);
        if (line[0] == '#' || line[0] == 0) continue;
        char *eq = strchr(line, '=');
        if (!eq) continue;
        *eq = 0;
        const char *k = line;
        const char *v = eq + 1;
        if (!strcmp(k, "ssid")) {
            strncpy(out->ssid, v, sizeof(out->ssid) - 1);
        } else if (!strcmp(k, "psk")) {
            strncpy(out->psk, v, sizeof(out->psk) - 1);
        }
    }
    fclose(f);

    out->configured = (out->ssid[0] != 0);
    return 0;
}

int wifi_cfg_save(const struct wifi_cfg *in)
{
    if (!in->ssid[0]) {
        errno = EINVAL;
        return -1;
    }
    char tmp[256];
    snprintf(tmp, sizeof(tmp), "%s.tmp", WIFI_CONF_PATH);

    int fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd < 0) return -1;

    FILE *f = fdopen(fd, "w");
    if (!f) { close(fd); return -1; }

    fprintf(f, "# proxycam wifi credentials — written by web UI\n");
    fprintf(f, "ssid=%s\n", in->ssid);
    fprintf(f, "psk=%s\n",  in->psk);
    fflush(f);
    fsync(fileno(f));
    fclose(f);

    if (rename(tmp, WIFI_CONF_PATH) != 0) return -1;

    /* Ensure the rename hits the device. On jffs2 a sync of the dir is
     * not strictly portable; sync() is the hammer-but-correct option.
     * This is once-per-provisioning so cost is negligible. */
    sync();
    return 0;
}

int wifi_cfg_wipe(void)
{
    int r = unlink(WIFI_CONF_PATH);
    if (r != 0 && errno != ENOENT) return -1;
    sync();
    return 0;
}
