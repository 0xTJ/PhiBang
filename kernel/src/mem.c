#include "mem.h"
#include "proc.h"

struct block_meta *get_block_ptr(void *ptr) {
  return (struct block_meta*)ptr - 1;
}

void *get_block(struct block_meta *ptr) {
  return (void*)(ptr + 1);
}

struct block_meta *find_free_block(struct block_meta *current, size_t size) {
  while (current->next != NULL && !(current->k_free && current->size >= size)) {
    current = current->next;
  }
  
  if (!(current->k_free && current->size >= size))
      current = NULL;
  
  return current;
}

void *k_alloc(size_t size, struct block_meta *heap) {
    struct block_meta *block;

    if (size <= 0)
        return NULL;

    block = find_free_block(heap, size);
    if (block == NULL) {
        return NULL;
    } else {
        if (block->size >= 2 * sizeof(struct block_meta)) {
            struct block_meta *next_block = (void *)((char *)get_block(block) + size);
            next_block->size = block->size - size - sizeof(struct block_meta);
            next_block->next = block->next;
            next_block->k_free = true;

            block->size = size;
            block->next = next_block;
        }
        block->k_free = false;
    }

    return (block + 1);
}

void k_free(void *ptr) {
    struct block_meta *block_ptr;

    if (ptr == NULL)
        return;

    /* TODO: consider merging blocks. */
    block_ptr = get_block_ptr(ptr);
    block_ptr->k_free = true;
}
