#ifndef _INCLUDE_DEV_H
#define _INCLUDE_DEV_H

#include <stdint.h>
#include <sys/types.h>
#include <stdbool.h>

#define DEVICE_COUNT 4

enum DevType { NO_DEV = 0, CHAR_DEV, BLOCK_DEV };

struct char_device {
    int (*init)();
    int (*put)(char c);
    int (*get)();
};

struct block_device {
    unsigned short block_size;
    unsigned long block_count;
    int (*init)();
    int (*read)(void *buffer, unsigned long block);
    int (*write)(void *buffer, unsigned long block);
};

struct device {
    enum DevType type;
    void *dev_desc;
};

extern struct device dev_tab[DEVICE_COUNT];

void init_devices();
dev_t add_device(void *device, bool is_block, char *name);
void remove_device(dev_t device);

#endif
