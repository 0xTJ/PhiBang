#ifndef _INCLUDE_IO_H
#define _INCLUDE_IO_H

#include <stddef.h>

struct driver {
    size_t (*read)(void *buf, size_t count);
    size_t (*write)(const void *buf, size_t nbytes);
};

size_t read(int fd, void *buf, size_t count);
size_t write(int fd, const void *buf, size_t nbytes);

#endif
