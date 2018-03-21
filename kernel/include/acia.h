#ifndef _INCLUDE_ACIA_H
#define _INCLUDE_ACIA_H

#include "io.h"

extern struct driver acia_vnode;

void acia_init();
void acia_init0();
void acia_put(char c);
char acia_get();

#endif
