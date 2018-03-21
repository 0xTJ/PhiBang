#include "acia.h"
#include "constants.h"

struct driver acia_vnode = {
    "acia\0\0\0",
    acia_put,
    acia_get,
    NULL
};
