#ifndef _INCLUDE_DEV_H
#define _INCLUDE_DEV_H

#include <sys/types.h>

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

extern struct device device_table[];

dev_t add_device(void *device, enum DevType type);
void remove_device(dev_t device);

#endif
