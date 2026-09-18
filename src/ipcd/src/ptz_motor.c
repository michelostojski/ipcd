/*
 * ptz_motor.c — motor hardware layer for the Anyka ak_motor driver.
 * v2: reliable Stop for continuous move.
 *
 * Movement: ioctl 0x40046d40, signed relative step delta by pointer,
 * capped ~295/call by the driver. Position read from sysfs current_pos.
 * Motor must be init'd by stock cmd_serverd running at boot.
 *
 * Calibrated ranges: pan 20..3380, tilt 100..1300 (safe: 50..3350 / 130..1270).
 *
 * Continuous move for autotracking: a background thread nudges the axis
 * in small steps while a direction is set. Stop clears the direction and
 * the thread halts within one tick (~60ms). The per-tick step is small so
 * Stop is responsive; velocity scales the step size.
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

#define IOCTL_MOVE  0x40046d40
#define IOCTL_SPEED 0x40046d44
#define MOTOR_SPEED 600          /* hz; matches what makes it actually turn */

#define PAN_DEV   "/dev/motor0"
#define TILT_DEV  "/dev/motor1"
#define PAN_SYSFS  "/sys/devices/platform/motor0/motor/current_pos"
#define TILT_SYSFS "/sys/devices/platform/motor1/motor/current_pos"

#define PAN_MIN   50
#define PAN_MAX   3350
#define TILT_MIN  130
#define TILT_MAX  1270

#define GOTO_STEP_CAP  250
#define CONT_STEP_MAX  250
#define CONT_TICK_US   60000

static pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;

static pthread_t g_cont_thread;
static int       g_cont_running = 0;
static int       g_cont_exit    = 0;
static int       g_pan_step     = 0;
static int       g_tilt_step    = 0;

static int axis_dev(int axis, const char **dev)
{
    if (axis == PTZ_AXIS_PAN)  { *dev = PAN_DEV;  return 0; }
    if (axis == PTZ_AXIS_TILT) { *dev = TILT_DEV; return 0; }
    return -1;
}

void ptz_motor_limits(int axis, int *lo, int *hi)
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
    char *ok = fgets(buf, sizeof(buf), f);
    fclose(f);
    if (!ok) return -1;
    char *colon = strchr(buf, ':');
    if (!colon) return -1;
    return atoi(colon + 1);
}

static int move_rel_locked(int axis, int delta)
{
    if (delta == 0) return 0;
    if (delta >  GOTO_STEP_CAP) delta =  GOTO_STEP_CAP;
    if (delta < -GOTO_STEP_CAP) delta = -GOTO_STEP_CAP;
    const char *dev;
    if (axis_dev(axis, &dev) != 0) return -1;
    int fd = open(dev, O_RDWR);
    if (fd < 0) { fprintf(stderr, "[ptz] open %s failed\n", dev); fflush(stderr); return -1; }
    /* set speed first, then move — matches the working ak_ptz2 "smove" */
    int spd = MOTOR_SPEED;
    ioctl(fd, IOCTL_SPEED, &spd);
    int d = delta;
    int r = ioctl(fd, IOCTL_MOVE, &d);
    close(fd);
    fprintf(stderr, "[ptz] move axis=%d delta=%d ret=%d\n", axis, delta, r);
    fflush(stderr);
    return r;
}

int ptz_motor_goto(int axis, int target)
{
    int lo, hi;
    ptz_motor_limits(axis, &lo, &hi);
    if (target < lo) target = lo;
    if (target > hi) target = hi;

    pthread_mutex_lock(&g_lock);
    for (int i = 0; i < 40; i++) {
        int cur = ptz_motor_get_pos(axis);
        if (cur < 0) break;
        int diff = target - cur;
        if (diff > -15 && diff < 15) break;
        move_rel_locked(axis, diff);
        usleep(120000);
    }
    pthread_mutex_unlock(&g_lock);
    return 0;
}

int ptz_motor_move_rel(int axis, int steps)
{
    int cur = ptz_motor_get_pos(axis);
    if (cur < 0) return -1;
    return ptz_motor_goto(axis, cur + steps);
}

static void *cont_fn(void *arg)
{
    (void)arg;
    for (;;) {
        pthread_mutex_lock(&g_lock);
        int exit_now = g_cont_exit;
        int ps = g_pan_step;
        int ts = g_tilt_step;
        pthread_mutex_unlock(&g_lock);

        if (exit_now) break;

        if (ps == 0 && ts == 0) {
            usleep(CONT_TICK_US);
            continue;
        }

        pthread_mutex_lock(&g_lock);
        ps = g_pan_step;
        ts = g_tilt_step;
        if (ps) {
            int lo, hi; ptz_motor_limits(PTZ_AXIS_PAN, &lo, &hi);
            int cur = ptz_motor_get_pos(PTZ_AXIS_PAN);
            if (cur >= 0 && ((ps > 0 && cur < hi) || (ps < 0 && cur > lo)))
                move_rel_locked(PTZ_AXIS_PAN, ps);
            else
                g_pan_step = 0;
        }
        if (ts) {
            int lo, hi; ptz_motor_limits(PTZ_AXIS_TILT, &lo, &hi);
            int cur = ptz_motor_get_pos(PTZ_AXIS_TILT);
            if (cur >= 0 && ((ts > 0 && cur < hi) || (ts < 0 && cur > lo)))
                move_rel_locked(PTZ_AXIS_TILT, ts);
            else
                g_tilt_step = 0;
        }
        pthread_mutex_unlock(&g_lock);
        usleep(CONT_TICK_US);
    }
    return NULL;
}

static int vel_to_step(float v)
{
    if (v >  1.0f) v =  1.0f;
    if (v < -1.0f) v = -1.0f;
    int s = (int)(v * (float)CONT_STEP_MAX);
    if (v >  0.02f && s <  80) s =  80;
    if (v < -0.02f && s > -80) s = -80;
    if (v > -0.02f && v < 0.02f) s = 0;
    return s;
}

void ptz_motor_continuous(float pan_vel, float tilt_vel)
{
    pan_vel  = -pan_vel;   /* invert pan direction */
    tilt_vel = -tilt_vel;  /* invert tilt direction */
    pthread_mutex_lock(&g_lock);
    g_pan_step  = vel_to_step(pan_vel);
    g_tilt_step = vel_to_step(tilt_vel);
    if (!g_cont_running) {
        g_cont_exit = 0;
        if (pthread_create(&g_cont_thread, NULL, cont_fn, NULL) == 0)
            g_cont_running = 1;
    }
    pthread_mutex_unlock(&g_lock);
    fprintf(stderr, "[ptz] continuous pan_step=%d tilt_step=%d\n",
            g_pan_step, g_tilt_step);
    fflush(stderr);
}

void ptz_motor_stop(void)
{
    pthread_mutex_lock(&g_lock);
    g_pan_step  = 0;
    g_tilt_step = 0;
    pthread_mutex_unlock(&g_lock);
    fprintf(stderr, "[ptz] stop\n");
    fflush(stderr);
}
