#include "io.h"
#include "proc.h"

struct driver *fd_table[TASK_MAX * FOPEN_MAX] = {0};

size_t read(int fd, void *buf, size_t count) {
    struct driver *file_num = fd_table[proc_cur * FOPEN_MAX + fd];
    size_t tmp = file_num->read(buf, count);
    return tmp;
}

size_t write(int fd, const void *buf, size_t nbytes) {
    struct driver *file_num = fd_table[proc_cur * FOPEN_MAX + fd];
    size_t tmp = file_num->write(buf, nbytes);
    return tmp;
}
