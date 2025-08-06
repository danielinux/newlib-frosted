/*
 * Frosted version of exit.
 */

#include "sys/frosted.h"
#include <errno.h>
#include <stdio.h>

extern int sys_exit(int val);

static inline void buf_close(void) {
    fclose(stdin);
    fclose(stdout);
    fclose(stderr);
    stdin = NULL;
    stdout = NULL;
    stderr = NULL;
}

int _exit(int val) {
    buf_close();
    return sys_exit(val);
}


