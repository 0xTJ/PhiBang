#include <stdio.h>

int fgetc(FILE *stream) {
    int fd = stream->fd;
    int gotten;
    
    switch (stream->mode) {
    case _MODE_READ:
    case _MODE_READ_WRITE:
        gotten = get(fd);
        if (gotten == EOF)
            stream->is_eof = EOF;
        else
            stream->is_eof = 0;
        return gotten;
    default:
        stream->is_err = -1;
        return EOF;
    }
}
