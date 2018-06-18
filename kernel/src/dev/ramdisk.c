#include "dev/ramdisk.h"
#include <string.h>

#define BLOCK_SIZE 1
#define SIZE 64

unsigned char ramdisk[SIZE];

const struct block_device ramdisk_device = {
    BLOCK_SIZE,
    SIZE / BLOCK_SIZE,
    init_ramdisk,
    read_ramdisk,
    write_ramdisk
};

int init_ramdisk() {
    memset(ramdisk, 0, SIZE);
    return 0;
}

int read_ramdisk(void *buffer, unsigned long block) {
    memcpy(buffer, ramdisk + (block * BLOCK_SIZE), BLOCK_SIZE);
    return 0;
}

int write_ramdisk(void *buffer, unsigned long block) {
    memcpy(ramdisk + (block * BLOCK_SIZE), buffer, BLOCK_SIZE);
    return 0;
}
