/*
 * Frosted version of kill.
 */

#include "sys/frosted.h"
#include <errno.h>
extern int sys_kill(int pid, int  sig);

int _kill_r(int pid, int sig)
{
    int ret = sys_kill(pid, sig);
    if (ret < 0) {
        errno = 0 - ret;
        ret = -1;
    }
    return ret;
}
