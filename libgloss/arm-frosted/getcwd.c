/*
 * Frosted version of getcwd.
 */

#include "sys/frosted.h"
#include <errno.h>
#include <stddef.h>
extern char * sys_getcwd(char *, int);

char *getcwd(char *buf, int size)
{
    char* ret = NULL;
    if (buf)
        ret = sys_getcwd(buf, size);
    if (ret == NULL)
        errno = -EFAULT;
    return ret;
}
