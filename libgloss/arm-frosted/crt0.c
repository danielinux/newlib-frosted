#include <fcntl.h>
 
extern void exit(int code);
extern int main (int argc, char *argv[]);
extern void _init_signal();
 
/* no argv, argc for now */
void _start(char *argv[]) {
    int ex;
    int argc = 0;
    if (argv) {
        while(argv[argc] != 0)
            argc++;
    }
    ex = main(argc, argv);
    exit(ex);
}

void _fini(void) __attribute__((weak));
void _fini(void) {}
