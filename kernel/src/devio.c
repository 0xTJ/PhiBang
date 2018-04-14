#include "devio.h"
#include <stddef.h>

struct device device_table[DEVICE_COUNT]; // rename to dev_tab

void kprint(char *s);
dev_t add_device(void *device, enum DevType type) {
    int i = 1;
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
    
    {
        char tmp[2] = { -1, '\0' };
        kprint("Added device of type ");
        tmp[0] = '0' + type;
        kprint(tmp);
        kprint(" as device ");
        tmp[0] = '0' + found_spot;
        kprint(tmp);
        kprint(".\n");
    }
    
    return found_spot;
}

void remove_device(dev_t device) {
    device_table[device].type = NO_DEV;
    device_table[device].dev_desc = NULL;
}
