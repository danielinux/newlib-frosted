/*
 * Stub version of waitpid.
 */

#include <errno.h>
#include <sys/wait.h>
int sys_waitpid(uint32_t arg1, int *arg2, int arg3);

pid_t waitpid(pid_t pid, int *stat_loc, int options)
{
  return sys_waitpid(pid, stat_loc, options);
}

