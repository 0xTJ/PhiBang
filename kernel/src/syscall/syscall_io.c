#include <unistd.h>
#include "proc.h"
#include "fs.h"

size_t read(int fildes, void *buf, size_t nbyte) { // TODO: Check that this shouldn't be ssize_t
    return 0;
}

ssize_t write(int fildes, const void *buf, size_t nbyte) {
    return -1;
}
