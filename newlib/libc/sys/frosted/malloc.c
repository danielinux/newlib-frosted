/*
 * Frosted version of malloc.
 */

#include "sys/frosted.h"
#include <errno.h>

#define MALLOC_PAGE_SIZE 4096
#define ALIGN(x, a) (((x) + ((a) - 1)) & ~((a) - 1))

extern void* sys_mmap(uint32_t size);

void * _sbrk_r(unsigned int incr)
{
    static unsigned char *heap = NULL;
    uint32_t sz;
    void *old_heap = heap;
    if (incr <= 0)
        return NULL;

    sz = ALIGN(incr, MALLOC_PAGE_SIZE);

    if (((incr >> 2) << 2) != incr)
        incr = ((incr >> 2) + 1) << 2;

    if (old_heap == NULL)
		old_heap = heap = (unsigned char *)sys_mmap(sz);
    if (!heap)
        return NULL;
    heap += incr;
    return old_heap;
}
