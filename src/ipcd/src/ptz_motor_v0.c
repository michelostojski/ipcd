/*
 * ptz_motor.c — motor hardware layer for the Anyka ak_motor driver.
 *
 * Reverse-engineered control for the two HZF-24BYJ48 steppers on the
 * AK39EV330 PT cameras:
 *
 *   - MOVE is ioctl 0x40046d40 with a signed int by pointer: a RELATIVE
 *     step delta, capped by the driver to ~295 steps per call. Positive
 *     and negative both work.
 *   - POSITION is read from sysfs current_pos (the ioctl POS read returns
 *     0 on this build, so we always use sysfs).
 *   - The motor must be INITIALISED by the stock cmd_serverd running at
 *     boot; ipcd does not re-init it. (cmd_serverd is tiny and does not
 *     touch the sensor, so it coexists with ipcd.)
 *
 * Calibrated ranges (measured on the author's unit — adjust if yours
 * differs): pan 20..3380, tilt 100..1300.
 *
 * All positions here are RAW STEPS. The ONVIF layer converts to/from
 * the normalised -1.0..+1.0 ONVIF coordinate space.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <errno.h>

#include "ptz_motor.h"

#define IOCTL_MOVE 0x40046d40   /* arg: int* signed relative step delta */

#define PAN_DEV   "/dev/motor0"
#define TILT_DEV  "/dev/motor1"
#define PAN_SYSFS  "/sys/devices/platform/motor0/motor/current_pos"
#define TILT_SYSFS "/sys/devices/platform/motor1/motor/current_pos"

/* Calibrated safe travel limits (raw steps). */
#define PAN_MIN   50
#define PAN_MAX   3350
#define TILT_MIN  130
#define TILT_MAX  1270

#define STEP_CAP  250           /* max steps per single ioctl move        */

/* One mutex serialises all motor access: the driver is not re-entrant
 * and a continuous-move thread must not race a goto. */
static pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;

/* Continuous-move state, driven by a background thread. */
static pthread_t   g_cont_thread;
static int         g_cont_running = 0;   /* thread alive?          */
static int         g_cont_pan_dir = 0;   /* -1,0,+1                */
static int         g_cont_tilt_dir = 0;
static int         g_cont_stop = 0;

static int axis_dev_open(int axis)
{
    const char *dev = (axis == PTZ_AXIS_PAN) ? PAN_DEV : TILT_DEV;
    int fd = open(dev, O_RDWR);
    if (fd < 0) fprintf(stderr, "[ptz] open %s: %s\n", dev, strerror(errno));
    return fd;
}

static void axis_limits(int axis, int *lo, int *hi)
{
    if (axis == PTZ_AXIS_PAN) { *lo = PAN_MIN;  *hi = PAN_MAX;  }
    else                      { *lo = TILT_MIN; *hi = TILT_MAX; }
}

int ptz_motor_get_pos(int axis)
{
    const char *path = (axis == PTZ_AXIS_PAN) ? PAN_SYSFS : TILT_SYSFS;
    FILE *f = fopen(path, "r");
    if (!f) return -1;
    char buf[64];
    if (!fgets(buf, sizeof(buf), f)) { fclose(f); return -1; }
    fclose(f);
    /* format: "current-pos:1700" — take digits after the colon */
    char *colon = strchr(buf, ':');
    if (!colon) return -1;
    return atoi(colon + 1);
}

/* Issue one capped relative move (raw steps). Returns 0 on success.
 * Caller holds g_lock. */
static int move_rel_locked(int axis, int delta)
{
    if (delta > STEP_CAP)  delta = STEP_CAP;
    if (delta < -STEP_CAP) delta = -STEP_CAP;
    if (delta == 0) return 0;

    int fd = axis_dev_open(axis);
    if (fd < 0) return -1;
    int d = delta;
    int r = ioctl(fd, IOCTL_MOVE, &d);
    close(fd);
    if (r < 0) {
        fprintf(stderr, "[ptz] move ioctl axis=%d delta=%d: %s\n",
                axis, delta, strerror(errno));
        return -1;
    }
    return 0;
}

/* Move to an absolute raw-step target, chunked, clamped to limits. */
int ptz_motor_goto(int axis, int target)
{
    int lo, hi;
    axis_limits(axis, &lo, &hi);
    if (target < lo) target = lo;
    if (target > hi) target = hi;

    pthread_mutex_lock(&g_lock);
    for (int tries = 0; tries < 40; tries++) {
        int cur = ptz_motor_get_pos(axis);
        if (cur < 0) { pthread_mutex_unlock(&g_lock); return -1; }
        int diff = target - cur;
        if (diff > -15 && diff < 15) break;          /* arrived */
        if (move_rel_locked(axis, diff) != 0) {
            pthread_mutex_unlock(&g_lock);
            return -1;
        }
        usleep(120000);                              /* let it step */
    }
    pthread_mutex_unlock(&g_lock);
    return 0;
}

/* Relative move by raw steps (may exceed cap; we loop). Clamped. */
int ptz_motor_move_rel(int axis, int steps)
{
    int cur = ptz_motor_get_pos(axis);
    if (cur < 0) return -1;
    return ptz_motor_goto(axis, cur + steps);
}

/* ---------- continuous move (for autotracking) ---------- */

/* Background thread: while a direction is set, keep nudging that axis
 * in small increments until stopped or a limit is hit. Speed is folded
 * into the increment size (bigger step = faster pan). */
static void *cont_thread_fn(void *arg)
{
    (void)arg;
    while (!g_cont_stop) {
        int pdir, tdir;
        pthread_mutex_lock(&g_lock);
        pdir = g_cont_pan_dir;
        tdir = g_cont_tilt_dir;
        pthread_mutex_unlock(&g_lock);

        if (pdir == 0 && tdir == 0) {
            usleep(50000);
            continue;
        }

        pthread_mutex_lock(&g_lock);
        if (pdir) {
            int lo, hi; axis_limits(PTZ_AXIS_PAN, &lo, &hi);
            int cur = ptz_motor_get_pos(PTZ_AXIS_PAN);
            if (cur >= 0 && ((pdir > 0 && cur < hi) || (pdir < 0 && cur > lo)))
                move_rel_locked(PTZ_AXIS_PAN, pdir);
        }
        if (tdir) {
            int lo, hi; axis_limits(PTZ_AXIS_TILT, &lo, &hi);
            int cur = ptz_motor_get_pos(PTZ_AXIS_TILT);
            if (cur >= 0 && ((tdir > 0 && cur < hi) || (tdir < 0 && cur > lo)))
                move_rel_locked(PTZ_AXIS_TILT, tdir);
        }
        pthread_mutex_unlock(&g_lock);
        usleep(80000);
    }
    return NULL;
}

/* velocity in ONVIF space is -1.0..+1.0; map to a signed step increment.
 * We use up to ~STEP_CAP per tick so full velocity pans fast. */
static int vel_to_step(float v)
{
    if (v >  1.0f) v =  1.0f;
    if (v < -1.0f) v = -1.0f;
    int s = (int)(v * (float)STEP_CAP);
    /* ensure a nonzero nudge for small-but-nonzero velocities */
    if (v > 0.02f && s < 8)  s = 8;
    if (v < -0.02f && s > -8) s = -8;
    return s;
}

void ptz_motor_continuous(float pan_vel, float tilt_vel)
{
    pthread_mutex_lock(&g_lock);
    g_cont_pan_dir  = vel_to_step(pan_vel);
    g_cont_tilt_dir = vel_to_step(tilt_vel);
    if (!g_cont_running) {
        g_cont_stop = 0;
        if (pthread_create(&g_cont_thread, NULL, cont_thread_fn, NULL) == 0)
            g_cont_running = 1;
    }
    pthread_mutex_unlock(&g_lock);
}

void ptz_motor_stop(void)
{
    pthread_mutex_lock(&g_lock);
    g_cont_pan_dir = 0;
    g_cont_tilt_dir = 0;
    pthread_mutex_unlock(&g_lock);
}

void ptz_motor_limits(int axis, int *lo, int *hi)
{
    axis_limits(axis, lo, hi);
}
