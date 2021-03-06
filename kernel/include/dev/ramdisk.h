#ifndef _INCLUDE_RAMDISK_H
#define _INCLUDE_RAMDISK_H

#include "dev.h"

extern const struct block_device ramdisk_device;

int init_ramdisk();
int read_ramdisk(void *buffer, unsigned long block);
int write_ramdisk(void *buffer, unsigned long block);

#endif
