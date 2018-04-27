#ifndef _INCLUDE_ZERO_H
#define _INCLUDE_ZERO_H

#include "dev.h"

extern struct char_device zero_device;

int zero_init();
int zero_put(char c);
int zero_get();

#endif
