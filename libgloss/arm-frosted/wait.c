/*
 * Stub version of wait.
 */

#include <errno.h>

int wait(int  *status)
{
    int ret = sys_waitpid(-1, status, 0);
    if (ret < 0) { 
        errno = 0 - ret;
        return -1;
    }
    return ret;
}

int waitpid(int pid, int *status, int options)
{
    return sys_waitpid(pid, status, options);
}

