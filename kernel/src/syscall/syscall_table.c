#include "syscall.h"
#include <unistd.h>

void const *syscalls[] = {
    NULL, chdir, NULL, getpid, NULL, read, write
};
