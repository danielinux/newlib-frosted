/*
 * Frosted version of unlink.
 */

#include "sys/frosted.h"
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#ifndef AT_REMOVEDIR
#define AT_REMOVEDIR 0x200
#endif

extern int sys_unlink(const char *name);

int unlink (const char * name)
{
    int ret = sys_unlink(name);
    if (ret < 0) {
        errno = 0 - ret;
        ret = -1;
    }
    return ret;
}

int unlinkat(int fd, const char *name, int flag)
{
    (void)fd;
    if (flag & AT_REMOVEDIR)
        return rmdir(name);
    else
        return unlink(name);
}
