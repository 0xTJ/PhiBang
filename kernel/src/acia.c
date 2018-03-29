#include "acia.h"
#include <stddef.h>

struct char_device acia_device = {
    acia_init,
    acia_put,
    acia_get,
};
