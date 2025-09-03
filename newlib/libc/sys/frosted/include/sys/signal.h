/* sys/signal.h */

#ifndef _SYS_SIGNAL_H
#define _SYS_SIGNAL_H
#include <unistd.h>

typedef unsigned long sigset_t;


/*
 * Structure used in sigaltstack call.
 */
typedef struct sigaltstack {
  void     *ss_sp;    /* Stack base or pointer.  */
  int       ss_flags; /* Flags.  */
  size_t    ss_size;  /* Stack size.  */
} stack_t;

#define SIG_SETMASK 0	/* set mask with sigprocmask() */
#define SIG_BLOCK 1	/* set of signals to block */
#define SIG_UNBLOCK 2	/* set of signals to, well, unblock */

/* These depend upon the type of sigset_t, which right now 
   is always a long.. They're in the POSIX namespace, but
   are not ANSI. */
#define sigaddset(what,sig) (*(what) |= (1<<(sig)), 0)
#define sigdelset(what,sig) (*(what) &= ~(1<<(sig)), 0)
#define sigemptyset(what)   (*(what) = 0, 0)
#define sigfillset(what)    (*(what) = ~(0), 0)
#define sigismember(what,sig) (((*(what)) & (1<<(sig))) != 0)

int sigprocmask(int how, const sigset_t *set, sigset_t *oset);

int pthread_sigmask(int how, const sigset_t *set, sigset_t *oset);


#ifndef _SIGNAL_H_
/* Some applications take advantage of the fact that <sys/signal.h>
 * and <signal.h> are equivalent in glibc.  Allow for that here.  */
#include <signal.h>
#endif
#endif /* _SYS_SIGNAL_H */
