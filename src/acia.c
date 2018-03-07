#include "acia.h"

struct driver acia_driver = {
    acia_read,
    acia_write
};

size_t acia_read(void *buf, size_t count) {
    size_t i = 0;
    do {
        ((char *)buf)[i] = acia_get();
        i++;
    } while (i < count);
    return count;
}

size_t acia_write(const void *buf, size_t nbytes) {
    size_t i = 0;
    do {
         acia_put(((const char *)buf)[i]);
         i++;
    } while (i < nbytes);
    return nbytes;
}
