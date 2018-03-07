#include <stdlib.h>

struct block_meta {
  size_t size;
  struct block_meta *next;
  int free;
};

#define META_SIZE sizeof(struct block_meta)

static void *global_base = NULL;

/* Helper Functions */

void minit(struct block_meta *heap, size_t heap_size) {
    heap->size = heap_size - META_SIZE;
    heap->next = NULL;
    heap->free = 1;
    global_base = heap;
}

static struct block_meta *find_free_block(struct block_meta **last, size_t size) {
  struct block_meta *current = global_base;
  while (current && !(current->free && current->size >= size)) {
    *last = current;
    current = current->next;
  }
  return current;
}

static struct block_meta *request_space(struct block_meta* last, size_t size) {
  struct block_meta *block;
  block = sbrk(0);
  void *request = sbrk(size + META_SIZE);
  if (request == (void*) -1) {
    return NULL; // sbrk failed.
  }

  if (last) { // NULL on first request.
    last->next = block;
  }
  block->size = size;
  block->next = NULL;
  block->free = 0;
  block->magic = 0x12345678;
  return block;
}

static struct block_meta *get_block_ptr(void *ptr) {
  return (struct block_meta*)ptr - 1;
}

static void *get_block(struct block_meta *ptr) {
  return (void*)(ptr + 1);
}

/* Global Functions */

void *malloc(size_t size) {
    struct block_meta *block;

    if (size <= 0)
        return NULL;

    if (global_base == NULL) {
          __asm
          halt
          __endasm;
          return NULL;
          /* Should be defined at process 0 start */
          /* Other processes should ask the kernel to malloc() and give them a block. */
    } else {
        struct block_meta *last = global_base;
        block = find_free_block(&last, size);
        if (block == NULL) {
            return NULL;
        } else {
            if (block->size >= 2 * META_SIZE) {
                struct block_meta *next_block = (void *)((char *)get_block(block) + size);
                next_block->size = block->size - size - META_SIZE;
                next_block->next = block->next;
                next_block->free = 1;
                
                block->size = size;
                block->next = next_block;
            }
            block->free = 0;
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
}
