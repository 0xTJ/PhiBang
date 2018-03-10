#include <stdlib.h>

extern void *_global_base;

void *malloc(size_t size) {
    struct _block_meta *block;

    if (size <= 0)
        return NULL;

    if (_global_base == NULL) {
          return NULL;
          /* Should be defined at process 0 start */
          /* Other processes should ask the kernel to malloc() and give them a block. */
    } else {
        struct _block_meta *last = _global_base;
        block = _find_free_block(&last, size);
        if (block == NULL) {
            return NULL;
        } else {
            if (block->size >= 2 * _SIZE__block_meta) {
                struct _block_meta *next_block = (void *)((char *)_get_block(block) + size);
                next_block->size = block->size - size - _SIZE__block_meta;
                next_block->next = block->next;
                next_block->free = 1;
                next_block->magic = 0x5555;
                
                block->size = size;
                block->next = next_block;
            }
            block->free = 0;
            block->magic = 0x7777;
        }
    }

    return (block + 1);
}
