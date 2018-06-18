#include "dev/null.h"
#include <stddef.h>
#include <eof.h>

struct char_device null_device = {
    NULL,
    null_put,
    null_get,
};

int null_put(char c) {
    return c;
}

int null_get() {
    return EOF;
}
