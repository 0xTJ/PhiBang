#include <stdio.h>
#include <unistd.h>

int fputc(int c, FILE *stream) {
    unsigned char c_u_char = c;
    ssize_t res = write(stream->fd, &c_u_char, 1);
    if (res <= 0) {
        stream->is_err = 1;
        return EOF;
    } else {
        return c_u_char;
    }
}
