#include "syscall.h"
#include <unistd.h>
#include <fcntl.h>

void const * const syscalls[256] = {
    /* Proc */  [0x00] =    _exit,  /*yield*/NULL,  execvp, getpid, chdir,
    /* IO   */  [0x20] =    open,   close,  read,   write,  /*mount*/NULL
};
