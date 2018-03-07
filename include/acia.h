#ifndef _INCLUDE_ACIA_H
#define _INCLUDE_ACIA_H

#include <stddef.h>
#include "io.h"

extern struct driver acia_driver;

void acia_init();
void acia_put(char c);
char acia_get();
size_t acia_read(void *buf, size_t count);
size_t acia_write(const void *buf, size_t nbytes);

#endif
