/*
 * ptz_motor.h — motor hardware layer interface.
 * Positions are RAW STEPS; ONVIF layer handles normalisation.
 */
#ifndef PTZ_MOTOR_H
#define PTZ_MOTOR_H

#define PTZ_AXIS_PAN   0
#define PTZ_AXIS_TILT  1

/* Current raw-step position from sysfs, or -1 on error. */
int  ptz_motor_get_pos(int axis);

/* Absolute move to a raw-step target (clamped, chunked, blocking). */
int  ptz_motor_goto(int axis, int target);

/* Relative move by raw steps (clamped, blocking). */
int  ptz_motor_move_rel(int axis, int steps);

/* Start/adjust continuous motion. Velocities are ONVIF space -1..+1.
 * Nonzero starts a background thread; zero on both axes idles it. */
void ptz_motor_continuous(float pan_vel, float tilt_vel);

/* Stop all continuous motion. */
void ptz_motor_stop(void);

/* Report calibrated step limits for an axis. */
void ptz_motor_limits(int axis, int *lo, int *hi);

#endif
