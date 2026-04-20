#include <dlfcn.h>
#include <stdint.h>

int sys_dlopen(uint32_t path, uint32_t mode);
int sys_dlsym(uint32_t handle, uint32_t symbol);
int sys_dlclose(uint32_t handle);

void *dlopen(const char *path, int mode)
{
    return (void *)(uintptr_t)sys_dlopen((uint32_t)(uintptr_t)path, (uint32_t)mode);
}

void *dlsym(void *handle, const char *symbol)
{
    return (void *)(uintptr_t)sys_dlsym((uint32_t)(uintptr_t)handle,
                                        (uint32_t)(uintptr_t)symbol);
}

int dlclose(void *handle)
{
    return sys_dlclose((uint32_t)(uintptr_t)handle);
}
