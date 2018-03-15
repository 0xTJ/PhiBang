#include <stdio.h>

int fputs(const char *s, FILE *stream) {
    int fd = stream->fd;
    
    switch (stream->mode) {
    case _MODE_WRITE:
    case _MODE_READ_WRITE:
        while (*s != 0)
            put(fd, *(s++));
        return 0;
    default:
        return EOF;
    }
}
