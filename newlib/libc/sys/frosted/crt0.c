#include <fcntl.h>

extern void exit(int code);
extern int main();
extern void _init_signal();
extern void __libc_init_array(void);

/* no argv, argc for now */
void _start(char *argv[])
{
    int ex;
    int argc = 0;

    if (argv) {
        while (argv[argc] != 0)
            argc++;
    }

    __libc_init_array();
    ex = main(argc, argv);
    exit(ex);
}
