#include <stdio.h>
#include <string.h>
#include <unistd.h>

int fputs(const char *s, FILE *stream) {
    write(stream->fd, s, strlen(s));
    return 0;
}
