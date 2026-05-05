/*
 * button.c — reset-button watcher v4 (event0 with EVIOCGRAB).
 *
 * What we know from `btn_dump`:
 *   - The kernel correctly emits PRESS (value=1) and RELEASE (value=0)
 *     events for the reset button.
 *   - Keycode used is 116 (KEY_POWER).
 *
 * What was wrong with v2: events were going missing while the daemon
 * ran. Most likely cause: another process was opening /dev/input/event0
 * and consuming events, leaving us with a partial stream. The factory
 * firmware has helpers (cmd_serverd, the IPC stack) that may grab
 * input events.
 *
 * Fix: open event0 with EVIOCGRAB to claim exclusive access. If
 * another process already holds the grab, our open succeeds but
 * EVIOCGRAB returns EBUSY and we log it loudly so we know what's
 * happening.
 *
 * v3 (sysfs polling) failed because gpio84 is owned by the gpio-keys
 * driver, blocking export. We're not going down that path.
 *
 * State machine: deadline-based, identical to v2/v3:
 *   PRESS (value=1) → arm deadline = now + RESET_MS
 *   RELEASE (value=0) → cancel
 *   AUTOREPEAT (value=2) → ignore
 *   At each loop, fire if held && now >= deadline.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <poll.h>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <sys/reboot.h>
#include <time.h>

#include "ipcd.h"

#define BTN_POLL_MS         100
#define KEYCODE_RESET       116    /* KEY_POWER, confirmed via btn_dump */

static long now_ms(void)
{
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return (long)t.tv_sec * 1000 + t.tv_nsec / 1000000;
}

static void do_factory_reset(void)
{
    fprintf(stderr, "[btn] LONG PRESS confirmed — wiping creds and rebooting\n");
    led_set(LED_RED,  LED_ON);
    led_set(LED_BLUE, LED_OFF);

    /* Wipe wifi credentials */
    wifi_cfg_wipe();

    /* Wipe auth credentials too. Without this, a factory reset would
     * leave the user locked out of the web UI / RTSP / ONVIF after
     * re-provisioning wifi: their old password would still be active
     * and they almost certainly don't remember it (otherwise they
     * wouldn't be doing a factory reset). Empty user+pass disables
     * auth entirely; the new owner sets it again from the Auth tab. */
    auth_set_creds("", "");

    sync();
    sleep(1);
    reboot(RB_AUTOBOOT);
    /* not reached */
}

static void *button_thread(void *arg)
{
    (void)arg;

    fprintf(stderr,
        "[btn] watcher v4 (event0, exclusive grab) starting on %s\n",
        INPUT_EVENT_DEV);

    int fd = open(INPUT_EVENT_DEV, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "[btn] open(%s): %s\n",
                INPUT_EVENT_DEV, strerror(errno));
        return NULL;
    }

    /* Claim exclusive access. If this fails with EBUSY, another
     * process is consuming events from this device — that explains
     * v2's missing-release symptom. */
    if (ioctl(fd, EVIOCGRAB, 1) != 0) {
        fprintf(stderr,
            "[btn] EVIOCGRAB failed: %s — another process holds "
            "/dev/input/event0; events may be split between us and it\n",
            strerror(errno));
        /* We continue anyway; whatever events we *do* see we'll handle. */
    } else {
        fprintf(stderr, "[btn] exclusive grab acquired\n");
    }

    int  is_held              = 0;
    long release_deadline_ms  = 0;
    long warn_deadline_ms     = 0;
    int  warned               = 0;

    struct pollfd pfd = { .fd = fd, .events = POLLIN };

    for (;;) {
        int timeout = is_held ? BTN_POLL_MS : -1;
        int pr = poll(&pfd, 1, timeout);

        if (pr < 0) {
            if (errno == EINTR) continue;
            usleep(100 * 1000);
            continue;
        }

        if (pr > 0 && (pfd.revents & POLLIN)) {
            struct input_event ev;
            ssize_t n = read(fd, &ev, sizeof(ev));
            if (n != (ssize_t)sizeof(ev)) {
                if (errno == EINTR) continue;
                usleep(50 * 1000);
                continue;
            }
            /* Ignore everything except KEY events on our specific
             * keycode. SYN events and other types arrive in the same
             * stream and must not be treated as button transitions. */
            if (ev.type != EV_KEY || ev.code != KEYCODE_RESET) {
                goto check_deadline;
            }

            switch (ev.value) {
            case 0: { /* PRESS — Anyka driver: line active low */
                long t = now_ms();
                if (is_held) {
                    /* If we somehow missed a release, treat this as a
                     * fresh press — never accumulate across clicks. */
                    fprintf(stderr,
                        "[btn] press while held — restarting timer\n");
                }
                is_held             = 1;
                release_deadline_ms = t + BUTTON_HOLD_MS_RESET;
                warn_deadline_ms    = t + BUTTON_HOLD_MS_RESET / 2;
                warned              = 0;
                fprintf(stderr,
                    "[btn] PRESS  t=%ld code=%u deadline=%ld\n",
                    t, ev.code, release_deadline_ms);
                break;
            }
            case 1: { /* RELEASE — Anyka driver: line back to high */
                long t = now_ms();
                if (is_held) {
                    long held = t - (release_deadline_ms - BUTTON_HOLD_MS_RESET);
                    fprintf(stderr,
                        "[btn] RELEASE t=%ld code=%u held=%ld ms → no-op\n",
                        t, ev.code, held);
                }
                is_held             = 0;
                release_deadline_ms = 0;
                warn_deadline_ms    = 0;
                if (warned) {
                    led_set(LED_RED, LED_OFF);
                    warned = 0;
                }
                break;
            }
            case 2: /* AUTOREPEAT — ignore */
                break;
            default:
                break;
            }
        }

    check_deadline:
        if (is_held) {
            long t = now_ms();
            if (t >= release_deadline_ms) {
                /* Disarm before firing for safety */
                is_held             = 0;
                release_deadline_ms = 0;
                do_factory_reset();
            } else if (!warned && t >= warn_deadline_ms) {
                led_set(LED_RED, LED_BLINK_FAST);
                warned = 1;
            }
        }
    }
    /* unreachable */
}

int button_thread_start(void)
{
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    int rc = pthread_create(&tid, &attr, button_thread, NULL);
    pthread_attr_destroy(&attr);
    return rc == 0 ? 0 : -1;
}