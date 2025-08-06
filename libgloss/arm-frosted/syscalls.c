/*
 * Redirect newlib's syscalls (with _underscore prefix) to Frosted's syscalls
 */

#include "syscalls.h"
#include <errno.h>
#include <stdint.h>
int sys_close(int fd);
int sys_vfork(void);
int sys_fstat(int fd, struct stat *buf);
int sys_isatty(int file);
int sys_kill(int pid, int sig);
int sys_link(char *oldpath, char *newpath);
int sys_stat(const char *path, struct stat *buf);
int sys_open(const char *pathname, int flags, ...);
int sys_read(int fd, void *buf, size_t count);
int sys_write(int fd, const void *buf, size_t count);
int sys_waitpid(int pid, int *wstatus, int options);
int sys_clock_gettime(struct timeval *tv, struct timezone *tz);
int sys_clock_settime(struct timeval *tv, struct timezone *tz);
int sys_unlink(const char *pathname);
int sys_getpid(void);
int sys_getppid(void);
int sys_seek(int fd, off_t offset, int whence);



int _close_r(struct _reent *ptr, int fd)
{
    (void)ptr;
    return sys_close(fd);
}

int _close(int fd)
{
    return sys_close(fd);
}
 
int _execve_r(struct _reent *ptr, char *name, char **argv, char **env)
{
    (void)ptr;
    return execve(name, argv, env);
}

int _execve(char *name, char **argv, char **env)
{
    return execve(name, argv, env);
}

int _fork_r(struct _reent *ptr)
{
    (void)ptr;
    return sys_vfork();
}

int _fork(void)
{
    return sys_vfork();
}

int _fstat_r(struct _reent *ptr, int fd, struct stat *st)
{
    (void)ptr;
    return sys_fstat(fd, st);
}

int _fstat(int fd, struct stat *st)
{
    return sys_fstat(fd, st);
}

int _getpid_r(struct _reent *ptr)
{
    (void)ptr;
    return sys_getpid();
}

int _getpid(void)
{
    return sys_getpid();
}

int _isatty_r(struct _reent *ptr, int file)
{
    (void)ptr;
    return sys_isatty(file);
}

int _isatty(int file)
{
    return sys_isatty(file);
}

int _kill(int pid, int sig)
{
    return sys_kill(pid, sig);
}

int _kill_r(int pid, int sig)
{
    return sys_kill(pid, sig);
}

int _link_r(struct _reent *ptr, char *existing, char *new)
{
    (void)ptr;
    return sys_link(existing, new);
}

int _link(char *existing, char *new)
{
    return sys_link(existing, new);
}

int _lseek_r(struct _reent *ptr, int fd, int offset, int whence)
{
    (void)ptr;
    return sys_seek(fd, offset, whence);
}

int _lseek(int fd, int offset, int whence)
{
    return sys_seek(fd, offset, whence);
}

int _open_r(struct _reent *ptr, char *file, int flags, int mode)
{
    (void)ptr;
    return sys_open(file, flags, mode);
}

int _open(char *file, int flags, int mode)
{
    return sys_open(file, flags, mode);
}

int _read_r(struct _reent *r_ptr, int file, char *ptr, int len)
{
    (void)r_ptr;
    return sys_read(file, ptr, len);
}


int _read(int file, char *ptr, int len)
{
    return sys_read(file, ptr, len);
}

int _stat_r(struct _reent *ptr, const char *file, struct stat *st)
{
    return sys_stat(file, st);
}

int _stat(const char *file, struct stat *st)
{
    return sys_stat(file, st);
}

clock_t _times_r(struct _reent *ptr, struct tms *buf)
{
    (void)ptr;
    return (clock_t)NULL;
}

clock_t _times(struct tms *buf)
{
    return (clock_t)NULL;
}

int _unlink_r(struct _reent *ptr,  char * name)
{
    (void)ptr;
    return sys_unlink(name);
}

int _unlink(char * name)
{
    return sys_unlink(name);
}

int _wait_r(struct _reent *ptr, int *status)
{
    (void)ptr;
    return sys_waitpid(-1, status, 0);
}

int _wait(int *status)
{
    return sys_waitpid(-1, status, 0);
}

int _write_r(struct _reent *r_ptr, int file, char *ptr, int len)
{
    (void)r_ptr;
    return sys_write(file, ptr, len);
}

int _write (int file, char *ptr, int len)
{
    return sys_write(file, ptr, len);
}

int _gettimeofday(struct timeval *tv, struct timezone *tz)
{
    return sys_clock_gettime(tv, tz);
}

int _gettimeofday_r(struct timeval *tv, struct timezone *tz)
{
    return sys_clock_gettime(tv, tz);
}

