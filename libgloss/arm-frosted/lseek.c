/*
 * Frosted version of lseek.
 */

#include <errno.h>
extern int sys_seek(int fd, int offset, int  whence);

int lseek (int fd, int offset, int whence)
{
    return sys_seek(fd, offset, whence);
}
