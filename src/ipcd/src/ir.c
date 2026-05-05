/*
 * ir.c — IR-cut filter and IR-LED day/night control.
 *
 * What we learned from the device
 * --------------------------------
 *   - The IR-LED is a standard sysfs LED:
 *         /sys/class/leds/irled/brightness    (0 = off, 255 = on)
 *     Writing this directly works. The kernel driver routes to a
 *     GPIO (visible at /sys/class/leds/irled/ak_led_info/gpio_num,
 *     reports "5" on this board). We don't care about the GPIO
 *     number — we use the LED API.
 *
 *   - The IR-cut filter is a polarized solenoid driven by two GPIO
 *     lines. On this board the kernel exports them as gpio81 +
 *     gpio42 BUT only after some boot-time userspace agent
 *     (anyka_ipc / hal_ir.c) calls into them. Out of the box from
 *     our process those GPIOs are NOT exported; trying to write
 *     /sys/class/gpio/gpioN/value silently fails. We probe for
 *     /sys/class/leds/ircut_a + /sys/class/leds/ircut_b first
 *     (which is how some firmware revisions of the same SoC expose
 *     it); if not present, we attempt the gpio export route; if
 *     that also fails, we just leave the filter where it was
 *     (still works in good light, slightly off colour at night
 *     but the picture is recoverable).
 *
 *   - The Anyka SDK exposes ak_vpss_get_cur_lumi() and
 *     ak_vpss_get_auto_day_night_level(). We use these as the
 *     SOURCE OF TRUTH for the current scene level. The actual
 *     hardware actuation (LED on/off, filter flip) is OUR job.
 *
 * State machine
 * -------------
 *   AUTO mode:
 *     thread polls SDK every 2s
 *       if level changed (day -> night): turn IR-LED on, flip filter
 *       if level changed (night -> day): turn IR-LED off, flip filter
 *
 *   OFF mode (force day):
 *     IR-LED forced to 0, filter forced to "day" (a=1 b=0 pulse)
 *     poll thread does nothing
 *
 *   FORCE_NIGHT mode:
 *     IR-LED forced to 255, filter forced to "night" (a=0 b=1 pulse)
 *     poll thread does nothing
 *
 * The poll thread is always running while the module is initialised;
 * it just observes-only-no-action when mode != AUTO.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/stat.h>

#include "ipcd.h"

/* SDK prototype — only one function needed: read current AE luma.
 * The other day/night APIs (ak_vpss_set_auto_day_night_param /
 * get_auto_day_night_level / soft_ps_*) didn't behave as documented
 * on this firmware ISP. We get the luma here and run our own
 * detector — see poll_thread() below. */
extern int ak_vpss_get_cur_lumi(int dev_id, int *lumi);

/* sysfs paths */
#define IRLED_BRIGHTNESS    "/sys/class/leds/irled/brightness"

/* IR-cut paths probed at init. The kernel exposes them in one of
 * three styles; we accept any of them. */
static const char *IRCUT_A_CANDIDATES[] = {
    "/sys/class/leds/ircut_a/brightness",
    "/sys/class/leds/ircut/ircut_a",
    "/sys/class/gpio/gpio81/value",
    NULL,
};
static const char *IRCUT_B_CANDIDATES[] = {
    "/sys/class/leds/ircut_b/brightness",
    "/sys/class/leds/ircut/ircut_b",
    "/sys/class/gpio/gpio42/value",
    NULL,
};

/* ---------------------------------------------------------------- */
/* sysfs helpers                                                    */
/* ---------------------------------------------------------------- */
static int sysfs_write_str(const char *path, const char *val)
{
    int fd = open(path, O_WRONLY);
    if (fd < 0) return -1;
    ssize_t n = write(fd, val, strlen(val));
    close(fd);
    return (n > 0) ? 0 : -1;
}

static int sysfs_write_int(const char *path, int val)
{
    char buf[16];
    snprintf(buf, sizeof(buf), "%d", val);
    return sysfs_write_str(path, buf);
}

static int path_exists(const char *path)
{
    struct stat st;
    return stat(path, &st) == 0;
}

/* If gpioN/value is requested and the gpio isn't exported yet, try
 * to export it. Best effort — failure here just means we can't
 * drive the IR-cut filter; the IR-LED still works. */
static int try_export_gpio(const char *gpio_value_path)
{
    /* Extract NN from "/sys/class/gpio/gpioNN/value" */
    const char *p = strstr(gpio_value_path, "/gpio");
    if (!p) return -1;
    p += 5;
    char num[8] = {0};
    int i = 0;
    while (*p >= '0' && *p <= '9' && i < 7) num[i++] = *p++;
    if (i == 0) return -1;
    if (sysfs_write_str("/sys/class/gpio/export", num) != 0) {
        /* Already exported? open dir to check. */
        char dir[64];
        snprintf(dir, sizeof(dir), "/sys/class/gpio/gpio%s", num);
        if (!path_exists(dir)) return -1;
    }
    /* Set direction = out */
    char dirpath[80];
    snprintf(dirpath, sizeof(dirpath), "/sys/class/gpio/gpio%s/direction", num);
    sysfs_write_str(dirpath, "out");
    return 0;
}

/* ---------------------------------------------------------------- */
/* State                                                            */
/* ---------------------------------------------------------------- */
static struct {
    pthread_mutex_t mtx;
    int             initialized;

    ir_mode_t       mode;
    int             cur_level;     /* 0 day / 1 night */
    unsigned int    cur_luma;

    /* Day/night thresholds. The factory_cfg defaults are used; you
     * can tune them at runtime via ir_set_thresholds() if needed.
     * Numbers are AE-gain units as returned by ak_vpss_get_cur_lumi:
     *   bright daylight scene  ~  10..50
     *   indoor lights on       ~ 100..600
     *   indoor lights off      ~ 3000..15000
     *   covered lens           ~ 14000+
     */
    unsigned int    day_to_night_lum;   /* 8600 — go night when luma >= */
    unsigned int    night_to_day_lum;   /* 1024 — go day   when luma <= */

    /* Resolved sysfs paths after probing (NULL if not available). */
    const char     *ircut_a;
    const char     *ircut_b;
    int             irled_ok;       /* 1 if we can write irled */

    pthread_t       poll_tid;
    int             poll_run;
    int             poll_started;
} I = {
    .mtx = PTHREAD_MUTEX_INITIALIZER,
    .mode = IR_MODE_AUTO,
    .day_to_night_lum = 8600,
    .night_to_day_lum = 1024,
};

/* ---------------------------------------------------------------- */
/* Hardware actuation                                               */
/* ---------------------------------------------------------------- */
static void irled_set(int on)
{
    if (!I.irled_ok) return;
    sysfs_write_int(IRLED_BRIGHTNESS, on ? 255 : 0);
}

/* Pulse the IR-cut filter to a polarity (to_night: 1 night, 0 day).
 * It's a solenoid, ~100ms hold then release both lines. */
static void ircut_set(int to_night)
{
    if (!I.ircut_a || !I.ircut_b) return;
    if (to_night) {
        sysfs_write_int(I.ircut_a, 0);
        sysfs_write_int(I.ircut_b, 1);
    } else {
        sysfs_write_int(I.ircut_a, 1);
        sysfs_write_int(I.ircut_b, 0);
    }
    usleep(100 * 1000);
    sysfs_write_int(I.ircut_a, 0);
    sysfs_write_int(I.ircut_b, 0);
}

/* Apply both: LED + filter. Called on transition or forced-mode set. */
static void hw_apply(int night)
{
    irled_set(night);
    ircut_set(night);
    fprintf(stderr, "[ir] hw -> %s "
            "(led=%s, ircut=%s)\n",
            night ? "night" : "day",
            I.irled_ok ? (night ? "on" : "off") : "n/a",
            I.ircut_a   ? (night ? "night-pulse" : "day-pulse") : "n/a");
}

/* ---------------------------------------------------------------- */
/* Polling thread                                                   */
/*                                                                  */
/* The Anyka SDK exposes ak_vpss_set_auto_day_night_param() and    */
/* ak_vpss_get_auto_day_night_level(), but on this firmware they  */
/* simply do not switch the level no matter what we feed them.    */
/* (We tried correct struct shape, both directions of polling,    */
/* aggressive thresholds — never returns level=1.) The parallel   */
/* ak_vpss_set_soft_ps_param API exists too but is mutex-coupled  */
/* with the auto_day_night one, equally opaque, and needs RGB-    */
/* dispersion calibration we don't have.                           */
/*                                                                  */
/* What DOES work reliably is ak_vpss_get_cur_lumi(): it returns  */
/* meaningful AE-gain numbers that scale predictably with scene   */
/* darkness (luma=20 in daylight, luma=14000+ when blacked out). */
/* So we run our own state machine: read luma, apply hysteresis, */
/* count consecutive samples, decide. No SDK black box involved.  */
/*                                                                  */
/* Hysteresis: scene must stay above day_to_night_lum for          */
/* `night_confirm_samples` consecutive polls before D->N, and     */
/* below night_to_day_lum for `day_confirm_samples` polls before */
/* N->D. That's what the SDK was supposed to do for us — we just */
/* implement it directly.                                          */
/* ---------------------------------------------------------------- */
#define IR_POLL_PERIOD_MS       500     /* poll every 500 ms */
#define IR_NIGHT_CONFIRM_HITS   4       /* 2 s of dark scene  */
#define IR_DAY_CONFIRM_HITS     4       /* 2 s of bright scene */

static void *poll_thread(void *arg)
{
    (void)arg;
    /* Per-direction confirmation counters. Both are reset to 0 on
     * any sample that disagrees with the trend, so transient
     * conditions (camera flash, opening a door) don't toggle. */
    int night_hits = 0;
    int day_hits   = 0;

    while (I.poll_run) {
        /* Sleep first so the AE has time to settle after capture
         * starts; without this the first few luma reads are noise. */
        for (int i = 0; i < IR_POLL_PERIOD_MS / 100 && I.poll_run; i++)
            usleep(100 * 1000);
        if (!I.poll_run) break;

        int lumi = 0;
        if (ak_vpss_get_cur_lumi(0, &lumi) != 0) continue;

        pthread_mutex_lock(&I.mtx);
        I.cur_luma = (unsigned int)lumi;
        ir_mode_t mode    = I.mode;
        int       my_lvl  = I.cur_level;
        unsigned  hi      = (unsigned)lumi >= I.day_to_night_lum;
        unsigned  lo      = (unsigned)lumi <= I.night_to_day_lum;
        pthread_mutex_unlock(&I.mtx);

        if (mode != IR_MODE_AUTO) {
            night_hits = day_hits = 0;
            continue;
        }

        if (my_lvl == 0) {
            /* Currently in day; watching for D->N. */
            if (hi)      night_hits++;
            else         night_hits = 0;
            day_hits = 0;
            if (night_hits >= IR_NIGHT_CONFIRM_HITS) {
                fprintf(stderr,
                    "[ir] level transition: day -> night "
                    "(luma=%d, %d consecutive samples > %u)\n",
                    lumi, night_hits, I.day_to_night_lum);
                pthread_mutex_lock(&I.mtx);
                I.cur_level = 1;
                pthread_mutex_unlock(&I.mtx);
                hw_apply(1);
                night_hits = day_hits = 0;
            }
        } else {
            /* Currently in night; watching for N->D. */
            if (lo)      day_hits++;
            else         day_hits = 0;
            night_hits = 0;
            if (day_hits >= IR_DAY_CONFIRM_HITS) {
                fprintf(stderr,
                    "[ir] level transition: night -> day "
                    "(luma=%d, %d consecutive samples < %u)\n",
                    lumi, day_hits, I.night_to_day_lum);
                pthread_mutex_lock(&I.mtx);
                I.cur_level = 0;
                pthread_mutex_unlock(&I.mtx);
                hw_apply(0);
                night_hits = day_hits = 0;
            }
        }
    }
    return NULL;
}

/* ---------------------------------------------------------------- */
/* Probing                                                          */
/* ---------------------------------------------------------------- */
static const char *probe_ircut(const char **candidates)
{
    for (int i = 0; candidates[i]; i++) {
        if (path_exists(candidates[i])) return candidates[i];
        /* Special case: gpioN/value — try to export. */
        if (strstr(candidates[i], "/sys/class/gpio/")) {
            if (try_export_gpio(candidates[i]) == 0 &&
                path_exists(candidates[i])) {
                return candidates[i];
            }
        }
    }
    return NULL;
}

/* ---------------------------------------------------------------- */
/* Public API                                                       */
/* ---------------------------------------------------------------- */
int ir_init(void)
{
    pthread_mutex_lock(&I.mtx);
    if (I.initialized) { pthread_mutex_unlock(&I.mtx); return 0; }

    /* Probe hardware. */
    I.irled_ok = path_exists(IRLED_BRIGHTNESS);
    I.ircut_a  = probe_ircut(IRCUT_A_CANDIDATES);
    I.ircut_b  = probe_ircut(IRCUT_B_CANDIDATES);

    fprintf(stderr,
        "[ir] hardware probe: irled=%s, ircut_a=%s, ircut_b=%s\n",
        I.irled_ok ? IRLED_BRIGHTNESS : "(none)",
        I.ircut_a ? I.ircut_a : "(none)",
        I.ircut_b ? I.ircut_b : "(none)");

    fprintf(stderr,
        "[ir] manual day/night detection: D->N=%u, N->D=%u, "
        "poll=%dms, confirm=%d samples\n",
        I.day_to_night_lum, I.night_to_day_lum,
        IR_POLL_PERIOD_MS, IR_NIGHT_CONFIRM_HITS);

    I.initialized = 1;
    I.mode        = IR_MODE_AUTO;
    I.cur_level   = 0;
    I.cur_luma    = 0;
    pthread_mutex_unlock(&I.mtx);

    /* Start in day-mode safely (LED off, filter to day). */
    hw_apply(0);

    I.poll_run = 1;
    if (pthread_create(&I.poll_tid, NULL, poll_thread, NULL) != 0) {
        fprintf(stderr, "[ir] poll thread spawn failed\n");
        I.poll_run = 0;
        return -1;
    }
    I.poll_started = 1;
    return 0;
}

void ir_shutdown(void)
{
    if (I.poll_started) {
        I.poll_run = 0;
        pthread_join(I.poll_tid, NULL);
        I.poll_started = 0;
    }
    /* Leave hardware in a safe state: LED off. */
    irled_set(0);
    pthread_mutex_lock(&I.mtx);
    I.initialized = 0;
    pthread_mutex_unlock(&I.mtx);
}

int ir_set_mode(ir_mode_t mode)
{
    /* For forced modes we also pin cur_level to match, so when the
     * user goes back to AUTO the poll thread starts from a sensible
     * point. The SDK doesn't know about forced modes; it relies on
     * the level we feed it. */
    int forced_level = -1;
    switch (mode) {
    case IR_MODE_OFF:           forced_level = 0; break;
    case IR_MODE_FORCE_NIGHT:   forced_level = 1; break;
    case IR_MODE_AUTO:                            break;
    }

    pthread_mutex_lock(&I.mtx);
    I.mode = mode;
    if (forced_level >= 0) I.cur_level = forced_level;
    int level = I.cur_level;
    pthread_mutex_unlock(&I.mtx);

    fprintf(stderr, "[ir] mode -> %s\n",
        mode == IR_MODE_OFF ? "off (day forced)"
        : mode == IR_MODE_AUTO ? "auto"
        : "force night");

    /* Apply hardware now so the user gets immediate feedback. */
    hw_apply(level);
    return 0;
}

ir_mode_t ir_get_mode(void)
{
    pthread_mutex_lock(&I.mtx);
    ir_mode_t m = I.mode;
    pthread_mutex_unlock(&I.mtx);
    return m;
}

int ir_get_level(void)
{
    pthread_mutex_lock(&I.mtx);
    int l = I.cur_level;
    pthread_mutex_unlock(&I.mtx);
    return l;
}

unsigned int ir_get_luma(void)
{
    pthread_mutex_lock(&I.mtx);
    unsigned int u = I.cur_luma;
    pthread_mutex_unlock(&I.mtx);
    return u;
}

/* Threshold accessors: which=1 -> day_to_night_lum,
 *                      which=0 -> night_to_day_lum. */
void ir_set_threshold(int which, unsigned int value)
{
    if (value == 0) return;             /* sanity */
    pthread_mutex_lock(&I.mtx);
    if (which) I.day_to_night_lum = value;
    else       I.night_to_day_lum = value;
    pthread_mutex_unlock(&I.mtx);
    fprintf(stderr, "[ir] threshold %s -> %u\n",
        which ? "day_to_night_lum" : "night_to_day_lum", value);
}

unsigned int ir_get_threshold(int which)
{
    pthread_mutex_lock(&I.mtx);
    unsigned int v = which ? I.day_to_night_lum : I.night_to_day_lum;
    pthread_mutex_unlock(&I.mtx);
    return v;
}
