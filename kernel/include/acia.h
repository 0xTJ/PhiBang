#ifndef _INCLUDE_ACIA_H
#define _INCLUDE_ACIA_H

#include "io.h"

extern struct driver acia_driver;

void acia_init();
void acia_init0();
int acia_put(char c);
int acia_get();

#endif
