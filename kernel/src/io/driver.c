#include "io.h"

#define DRIVER_COUNT 16

struct driver *driver_table[DRIVER_COUNT];

int reg_driver(struct driver *driver_p) {
    int i = 0;
    int found_spot = -1;
    
    do {
        if (driver_table[i] == NULL) {
            found_spot = i;
            break;
        }
    } while (i++ < DRIVER_COUNT - 1);
    
    if (found_spot < 0)
        return -1;
    
    driver_table[found_spot] = driver_p;
}
