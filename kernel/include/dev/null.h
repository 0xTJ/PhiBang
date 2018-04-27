#ifndef _INCLUDE_NULL_H
#define _INCLUDE_NULL_H

#include "dev.h"

extern struct char_device null_device;

int null_init();
int null_put(char c);
int null_get();

#endif
