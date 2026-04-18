/*
 * Frosted version of closedir.
 */

#include "sys/frosted.h"
#include <errno.h>
#include <stdint.h>
#include <dirent.h>
extern int sys_closedir(int d);

int closedir(DIR *d)
{
    int ret;

    if (!d) {
        errno = EBADF;
        return -1;
    }

    ret = sys_closedir((int)((intptr_t)d - 1));
    if (ret < 0) {
        errno = 0 - ret;
        ret = -1;
    }
    return ret;
}
