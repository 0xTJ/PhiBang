#include "mem.h"

void *global_base = NULL;

struct block_meta *get_block_ptr(void *ptr) {
  return (struct block_meta*)ptr - 1;
}

void *get_block(struct block_meta *ptr) {
  return (void*)(ptr + 1);
}

struct block_meta *find_free_block(struct block_meta **last, size_t size) {
  struct block_meta *current = global_base;
  while (current != NULL && !(current->free && current->size >= size)) {
    *last = current;
    current = current->next;
  }
  return current;
}

void mem_init(struct block_meta *heap, size_t heap_size) {
    heap->size = heap_size - SIZE_block_meta;
    heap->next = NULL;
    heap->free = 1;
    heap->pid = -1;
    global_base = heap;
}

void *alloc(size_t size, int pid) {
    struct block_meta *block;

    if (size <= 0)
        return NULL;

    if (global_base == NULL) {
          return NULL;
          /* Should be defined at process 0 start */
          /* Other processes should ask the kernel to alloc() and give them a block. */
    } else {
        struct block_meta *last = global_base;
        block = find_free_block(&last, size);
        if (block == NULL) {
            return NULL;
        } else {
            if (block->size >= 2 * SIZE_block_meta) {
                struct block_meta *next_block = (void *)((char *)get_block(block) + size);
                next_block->size = block->size - size - SIZE_block_meta;
                next_block->next = block->next;
                next_block->free = 1;
                next_block->pid = -1;
                
                block->size = size;
                block->next = next_block;
            }
            block->free = 0;
            block->pid = pid;
        }
    }

    return (block + 1);
}

void free(void *ptr) {
    struct block_meta *block_ptr;
    
    if (ptr == NULL)
        return;
    
    /* TODO: consider merging blocks. */
    block_ptr = get_block_ptr(ptr);
    block_ptr->free = 1;
    block_ptr->pid = -1;
}