#ifndef _INCLUDE_ACIA_H
#define _INCLUDE_ACIA_H

#include "dev.h"

extern struct char_device acia_device;

void acia_init();
void acia_init0();
int acia_put(char c);
int acia_get();

#endif
