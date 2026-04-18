/*
 * Frosted version of readdir.
 */

#include "sys/frosted.h"
#include <dirent.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>
extern int sys_readdir(int d, struct dirent *ep);

static struct dirent static_ep;

int readdir_r(DIR *d, struct dirent *ep, struct dirent **res)
{
    int fd;
    int ret;

    if (!d) {
        errno = EBADF;
        *res = NULL;
        return -1;
    }

    fd = (int)((intptr_t)d - 1);
    ret = sys_readdir(fd, ep);
    if (ret < 0) {
        errno = 0 - ret;
        *res = NULL;
        ret = -1;
    }
    *res = ep;
    return ret;
}

struct dirent *readdir(DIR *d)
{
    int fd;
    int ret;

    if (!d) {
        errno = EBADF;
        return NULL;
    }

    fd = (int)((intptr_t)d - 1);
    memset(&static_ep, 0, sizeof(struct dirent));
    ret = sys_readdir(fd, &static_ep);
    if (ret == 0)
        return &static_ep;
    else
        return NULL;
}
