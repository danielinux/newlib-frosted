#include <sys/mman.h>
#include <stdint.h>
#include <unistd.h>


extern void *sys_mmap(uint32_t size);
extern int sys_munmap(void *address, uint32_t size);


void *mmap(void *addr, size_t length, int prot, int flags,
        int fd, off_t offset)
{
    /* Ignore suggestion (Frosted specific, physical memory */
    (void)addr;
    (void)prot;
    (void)flags;
    (void)fd;
    (void)offset;
    return sys_mmap(length);
}

int munmap(void *addr, size_t length);
{
    return sys_munmap(addr, length);
}
