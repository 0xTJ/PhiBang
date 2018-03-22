#include "acia.h"
#include <stddef.h>

struct driver acia_vnode = {
    "acia\0\0\0",
    acia_put,
    acia_get,
    NULL
};
