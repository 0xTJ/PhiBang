#include "acia.h"
#include <stddef.h>

struct driver acia_driver = {
    acia_init,
    acia_put,
    acia_get,
    NULL
};
