#include <stdio.h>

char *fgets(char *s, int n, FILE *stream) {
    int fd = stream->fd;
    int i = 0;
    int in;
    
    switch (stream->mode) {
    case _MODE_READ:
    case _MODE_READ_WRITE:
        while (i < n - 1) {
            in = get(fd);
            if (in == EOF)
                break;
            if (in == '\n') {
                *(s + i++) = in;
                break;
            }
            *(s + i++) = in;
        }
        *(s + i) = '\0';
        return s;
    default:
        return EOF;
    }
}
