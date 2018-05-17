#include "syscall.h"
#include <unistd.h>

void  * const syscalls[256] = {
    /* Proc */  [0x00] =    _exit,  yield,  execvp, getpid, chdir,
    /* IO   */  [0x20] =    open,   close,  read,   write,  mount
};
