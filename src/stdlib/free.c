#include <stdlib.h>

void free(void *ptr) {
    struct _block_meta *block_ptr;
    
    if (ptr == NULL)
        return;
    
    /* TODO: consider merging blocks. */
    block_ptr = _get_block_ptr(ptr);
    block_ptr->free = 1;
    block_ptr->magic = 0x5555;
}
