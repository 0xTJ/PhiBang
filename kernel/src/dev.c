#include "dev.h"
#include <stddef.h>
#include <string.h>
#include "fs/devfs.h"
#include "fs.h"
#include "mem.h"

struct device dev_tab[DEVICE_COUNT];

void init_devices() {
    size_t i;
    for (i = 0; i < DEVICE_COUNT; i++) {
        dev_tab[i].type = NO_DEV;
        dev_tab[i].dev_desc = NULL;
    }
}

dev_t add_device(void *device, bool is_block, char *name) {
    size_t i = 0;
    ssize_t found_spot = -1;

    do {
        if (dev_tab[i].type == NO_DEV) {
            found_spot = i;
            break;
        }
    } while (i++ < DEVICE_COUNT - 1);

    if (found_spot < 0)
        return -1;

    dev_tab[found_spot].type = is_block ? BLOCK_DEV : CHAR_DEV;
    dev_tab[found_spot].dev_desc = device;

    if (is_block)
        if (((struct block_device *)device)->init != NULL)
            ((struct block_device *)device)->init();
    else
        if (((struct char_device *)device)->init != NULL)
            ((struct char_device *)device)->init();

    _devfs_add(i, is_block, name); 

    return found_spot;
}

void remove_device(dev_t device) {
    dev_tab[device].type = NO_DEV;
    dev_tab[device].dev_desc = NULL;
}
