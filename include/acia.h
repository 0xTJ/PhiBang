#ifndef _INCLUDE_ACIA_H
#define _INCLUDE_ACIA_H

#include <stddef.h>
#include "io.h"

void acia_init();
void acia_init0();
void acia_put(char c);
char acia_get();

#endif
