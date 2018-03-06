#include <stdlib.h>

void free(void *ptr) {
    redef_zone(ptr, FREE);
}
