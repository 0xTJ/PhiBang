#include <stdio.h>

int ferror(FILE *stream) {
    return stream->is_err;
}
