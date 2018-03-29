#include "ramdisk.h"
#include <string.h>

#define BLOCK_SIZE 128
#define SIZE 512

char ramdisk[SIZE];

struct block_device ramdisk_device = {
    BLOCK_SIZE,
    SIZE / BLOCK_SIZE,
    init_ramdisk,
    read_ramdisk,
    write_ramdisk
};

int init_ramdisk() {
    memset(ramdisk, 0, SIZE);
}

int read_ramdisk(void *buffer, unsigned long block) {
    memcpy(buffer, ramdisk + (block * BLOCK_SIZE), BLOCK_SIZE);
    return 0;
}

int write_ramdisk(void *buffer, unsigned long block) {
    memcpy(ramdisk + (block * BLOCK_SIZE), buffer, BLOCK_SIZE);
    return 0;
}
