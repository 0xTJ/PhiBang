#include <stdio.h>
#include <unistd.h>

int fgetc(FILE *stream) {
    unsigned char c;
    size_t res = read(stream->fd, &c, 1);
    if (res == 0) {
        stream->is_eof = EOF;
        return EOF;
    } else {
        return c;
    }
}
