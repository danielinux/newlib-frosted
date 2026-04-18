/*
 * Frosted version of malloc.
 */

#include "sys/frosted.h"
#include <errno.h>
#include <stdint.h>
#include <errno.h>
#include <sys/reent.h>

extern void* sys_mmap(uint32_t size);

#ifndef PAGE_SIZE
#define PAGE_SIZE 4096u
#endif

/* Ask the kernel for at least this much per region so wolfSSL/wolfSSH/
 * micropython heaps don't immediately hit the region cap. The supervisor
 * ultimately honours any page-aligned size; requesting 16 KB chunks keeps
 * nano-malloc's region bookkeeping cheap. */
#ifndef MIN_REGION_BYTES
#define MIN_REGION_BYTES (16u * 1024u)
#endif

#ifndef MAX_HEAP_REGIONS
#define MAX_HEAP_REGIONS 16u
#endif

#ifndef SBRK_ALIGN
#define SBRK_ALIGN 8u   // keep 8 or 16 to make malloc happy
#endif

static inline uintptr_t align_up(uintptr_t x, uintptr_t a)
{
    return (x + (a-1)) & ~(a-1);
}

static inline uintptr_t align_dn(uintptr_t x, uintptr_t a)
{
    return x & ~(a-1);
}

static inline uintptr_t round_up_pages(uintptr_t n)
{
    return align_up(n, PAGE_SIZE);
}

typedef struct {
    uint8_t *base;       /* Initial allocation (to track shrinks) */
    uint8_t *cur;        /* next free byte in current region */
    uint8_t *limit;      /* 1 past last usable byte in current region */
    unsigned regions_used;
    unsigned init;
} heap_state_t;

static heap_state_t g_heap;

/* Ask kernel for a new region >= min_bytes, switch current region to it. */
static int heap_grow(struct _reent *r, size_t min_bytes)
{
    unsigned int len, bias;
    void *base;
    uintptr_t b, aligned;

    if (g_heap.regions_used >= MAX_HEAP_REGIONS) {
        if (r) r->_errno = ENOMEM;
        return -1;
    }

    /* Minimum region — satisfies min_bytes while amortising syscall cost. */
    if (min_bytes < MIN_REGION_BYTES)
        min_bytes = MIN_REGION_BYTES;
    len = round_up_pages(min_bytes);
    base = sys_mmap(len);
    if (base == (void*)-1 || base == NULL) {
        if (r) r->_errno = ENOMEM;
        return -1;
    }

    b = (uintptr_t)base;
    // Keep an alignment bias inside the new region; userspace never sees it
    aligned = align_up(b, SBRK_ALIGN);
    bias = (size_t)(aligned - b);
    if (bias > len) { 
        if (r)
            r->_errno = ENOMEM; 
        return -1; 
    }
    g_heap.base  = (uint8_t*)aligned;
    g_heap.cur   = (uint8_t*)aligned;
    g_heap.limit = (uint8_t*)(b + len);
    g_heap.regions_used++;
    return 0;
}

void *_sbrk_r(struct _reent *r, ptrdiff_t incr)
{
    unsigned int need;
    void *prev_break;
    /* lazy init: no heap yet */
    if (!g_heap.init) {
        g_heap.base = g_heap.cur = g_heap.limit = NULL;
        g_heap.regions_used = 0;
        g_heap.init = 1;
    }

    /* Special case: sbrk(0) returns current break */
    if (incr == 0) {
        return (void*)g_heap.cur;
    }

    if (incr < 0) {
        unsigned int dec;
        /* Shrink if possible (within the current region) */
        dec = (unsigned int)(-incr);
        if ((g_heap.cur - dec) >= g_heap.base) {
            g_heap.cur -= dec;
            return (void*)g_heap.cur;
        } else {
            if (r) r->_errno = EINVAL;
            return NULL;
        }
    }

    need = (unsigned int)incr;
    // Ensure there is a current region with enough space
    if ((g_heap.base == NULL) || (g_heap.cur + need > g_heap.limit)) {
        if (heap_grow(r, need) != 0) {
            return NULL;
        }
    }

    // Serve from current region
    prev_break = (void*)g_heap.cur;
    g_heap.cur += need;
    return prev_break;
}

