/*
 * Stub version of getentropy.
 */

#include "config.h"
#include <_ansi.h>
#include <_syslist.h>
#include <errno.h>
#undef errno
extern int errno;
#include "warning.h"

int
_getentropy (void *buf,
        unsigned int buflen)
{
  errno = ENOSYS;
  return -1;
}

stub_warning(_getentropy)
