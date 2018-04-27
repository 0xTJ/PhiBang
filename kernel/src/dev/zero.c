#include "dev/zero.h"
#include <stdio.h>

struct char_device zero_device = {
    NULL,
    zero_put,
    zero_get,
};

int zero_put(char c) {
    return c;
}

int zero_get() {
    return 0;
}
