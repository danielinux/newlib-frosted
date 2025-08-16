multilibtool_DATA += %D%/crt0.o
libobjs_a_SOURCES += %D%/crt0.c

multilibtool_LIBRARIES += %D%/libsim.a
%C%_libsim_a_SOURCES = \
	%D%/_exit.c \
	%D%/access.c \
	%D%/chmod.c \
	%D%/chown.c \
	%D%/close.c \
	%D%/creat.c \
	%D%/crt1.c \
	%D%/execv.c \
	%D%/execve.c \
	%D%/fork.c \
	%D%/fstat.c \
	%D%/getpid.c \
	%D%/gettime.c \
	%D%/isatty.c \
	%D%/kill.c \
	%D%/link.c \
	%D%/lseek.c \
	%D%/open.c \
	%D%/pipe.c \
	%D%/read.c \
	%D%/sbrk.c \
	%D%/stat.c \
	%D%/time.c \
	%D%/times.c \
	%D%/trap.S \
	%D%/unlink.c \
	%D%/utime.c \
	%D%/wait.c \
	%D%/write.c \
	%D%/opendir.c \
    %D%/closedir.c \
    %D%/readdir.c 
