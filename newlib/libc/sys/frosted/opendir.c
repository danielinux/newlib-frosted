/*
 * Frosted version of opendir.
 */

#include "sys/frosted.h"
#include <errno.h>
#include <dirent.h>
#include <stdint.h>
extern int sys_opendir(const char *path);

DIR *opendir(const char *path)
{
    int fd = sys_opendir(path);
    if (fd < 0) {
        errno = 0 - fd;
        return NULL;
    }
    return (DIR *)(intptr_t)(fd + 1);
}
