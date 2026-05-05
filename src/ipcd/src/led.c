/*
 * led.c — drive /sys/class/leds/<name>/{brightness,trigger,delay_*}.
 *
 * Pattern (kernel docs):
 *   echo timer > trigger
 *   echo 500 > delay_on
 *   echo 500 > delay_off
 *   # blink at 1Hz (500/500ms)
 *
 *   echo none > trigger
 *   echo 0|1 > brightness
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "ipcd.h"

static int wfile(const char *path, const char *val)
{
    int fd = open(path, O_WRONLY);
    if (fd < 0) return -1;
    int n = write(fd, val, strlen(val));
    close(fd);
    return n < 0 ? -1 : 0;
}

int led_set(const char *led_path, led_mode_t mode)
{
    char p[256];

    switch (mode) {
    case LED_OFF:
        snprintf(p, sizeof(p), "%s/trigger",    led_path); wfile(p, "none");
        snprintf(p, sizeof(p), "%s/brightness", led_path); wfile(p, "0");
        return 0;
    case LED_ON:
        snprintf(p, sizeof(p), "%s/trigger",    led_path); wfile(p, "none");
        snprintf(p, sizeof(p), "%s/brightness", led_path); wfile(p, "1");
        return 0;
    case LED_BLINK_SLOW:
    case LED_BLINK_FAST: {
        const char *d = (mode == LED_BLINK_SLOW) ? "500" : "125";
        snprintf(p, sizeof(p), "%s/trigger", led_path); wfile(p, "timer");
        /* delay_on/off appear after trigger=timer is set */
        snprintf(p, sizeof(p), "%s/delay_on",  led_path); wfile(p, d);
        snprintf(p, sizeof(p), "%s/delay_off", led_path); wfile(p, d);
        return 0;
    }
    }
    return -1;
}
