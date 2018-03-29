#include "dev.h"
#include <stddef.h>

#define DEVICE_COUNT 16

struct device device_table[DEVICE_COUNT];

dev_t add_device(void *device, enum DevType type) {
    int i = 0;
    int found_spot = -1;
    
    do {
        if (device_table[i].type == NO_DEV) {
            found_spot = i;
            break;
        }
    } while (i++ < DEVICE_COUNT - 1);
    
    if (found_spot < 0)
        return -1;
    
    device_table[found_spot].type = type;
    device_table[found_spot].dev_desc = device;
    
    switch (type) {
    case CHAR_DEV:
        if (((struct char_device *)device)->init != NULL)
            ((struct char_device *)device)->init();
        break;
    case BLOCK_DEV:
        if (((struct block_device *)device)->init != NULL)
            ((struct block_device *)device)->init();
        break;
    }
    
    return found_spot;
}

void remove_device(dev_t device) {
    device_table[device].type = NO_DEV;
    device_table[device].dev_desc = NULL;
}
