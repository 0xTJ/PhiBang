#ifndef _INCLUDE_RAMDISK_H
#define _INCLUDE_RAMDISK_H

#include "devio.h"

extern const struct block_device ramdisk_device;

int init_ramdisk();
int read_ramdisk(void *buffer, unsigned long block);
int write_ramdisk(void *buffer, unsigned long block);
int read_dir_ramdisk(unsigned long long addr);
int write_dir_ramdisk(unsigned long long addr, unsigned char val);

#endif
