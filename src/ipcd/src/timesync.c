/*
 * timesync.c — set system clock via NTP after STA comes up.
 *
 * Two phases:
 *   1) timesync_oneshot(): blocking, ~10s timeout. We use BusyBox
 *      ntpd -nq which runs once and exits.
 *   2) timesync_daemon_start(): spawn ntpd in background to keep the
 *      clock disciplined.
 *
 * We don't bother with `date -s 2026-01-01` here because rc.local
 * already runs `hwclock -s` after loading ak_rtc.ko. If RTC battery
 * is dead and clock starts at 2000-01-01, NTP will jump us forward
 * regardless. NTP one-shot tolerates large step.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>

#include "ipcd.h"

#define NTP_PEERS_DEFAULT \
    "-p pool.ntp.org -p time.google.com -p time.cloudflare.com"

/* Run a command with a wall-clock timeout. Returns child exit status,
 * or -1 on spawn failure / timeout. */
static int run_with_timeout(const char *argv0, char *const argv[], int timeout_s)
{
    pid_t pid = fork();
    if (pid < 0) return -1;
    if (pid == 0) {
        execvp(argv0, argv);
        _exit(127);
    }
    time_t deadline = time(NULL) + timeout_s;
    while (time(NULL) < deadline) {
        int st;
        pid_t r = waitpid(pid, &st, WNOHANG);
        if (r == pid) return WIFEXITED(st) ? WEXITSTATUS(st) : -1;
        usleep(200 * 1000);
    }
    kill(pid, SIGKILL);
    waitpid(pid, NULL, 0);
    return -1;
}

int timesync_oneshot(void)
{
    /* BusyBox ntpd: -n no-fork, -q quit-after-sync, -p peer */
    char *argv[] = {
        "ntpd", "-nq",
        "-p", "pool.ntp.org",
        "-p", "time.google.com",
        "-p", "time.cloudflare.com",
        NULL
    };
    int rc = run_with_timeout("ntpd", argv, 15);
    if (rc != 0) {
        fprintf(stderr, "[time] ntpd -nq failed (rc=%d), keeping current clock\n", rc);
        return -1;
    }
    /* Best effort: persist to RTC if available */
    int sysrc = system("hwclock -w 2>/dev/null");
    (void)sysrc;
    return 0;
}

int timesync_daemon_start(void)
{
    /* fire-and-forget; if a previous ntpd lingers, kill it first */
    int sysrc = system("killall -q ntpd; "
           "ntpd -p pool.ntp.org -p time.google.com -p time.cloudflare.com "
           "2>/dev/null");
    (void)sysrc;
    return 0;
}
