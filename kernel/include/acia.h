#ifndef _INCLUDE_ACIA_H
#define _INCLUDE_ACIA_H

#include "dev.h"

extern struct char_device acia_device;

int acia_init();
int acia_put(char c);
int acia_get();

#endif
