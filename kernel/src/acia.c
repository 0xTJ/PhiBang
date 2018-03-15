#include "acia.h"
#include "constants.h"

struct vnode acia_vnode = {
    TYPE_CHAR_DEVICE,
    0,
    0,
    acia_put,
    acia_get,
    NULL
};
