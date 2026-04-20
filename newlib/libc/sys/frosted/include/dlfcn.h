#ifndef _DLFCN_H
#define _DLFCN_H

#define RTLD_LOCAL (0x0)
#define RTLD_LAZY  (0x1)
#define RTLD_NOW   (0x2)

void *dlopen(const char *path, int mode);
void *dlsym(void *handle, const char *symbol);
int dlclose(void *handle);

#endif
