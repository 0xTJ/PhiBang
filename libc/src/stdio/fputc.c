#include <stdio.h>

int fputc(int c, FILE *stream) {
    int fd = stream->fd;
    
    switch (stream->mode) {
    case _MODE_WRITE:
    case _MODE_READ_WRITE:
        put(fd, c);
        return c;
    default:
        stream->is_err = -1;
        return EOF;
    }
}
