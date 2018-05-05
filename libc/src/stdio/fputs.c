#include <stdio.h>
#include <string.h>
#include <unistd.h>

int fputs(const char *restrict s, FILE *restrict stream) {
    size_t len = strlen(s);
    ssize_t res = write(stream->fd, s, len);
    if (res < len) {
        stream->is_err = 1;
        return EOF;
    } else {
        return 0;
    }
}
