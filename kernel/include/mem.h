#ifndef _INCLUDE_MEM_H
#define _INCLUDE_MEM_H

#include <stdbool.h>
#include <stddef.h>

/* TYPES */

struct block_meta {
  size_t size;  /* Must be first element in struct */
  struct block_meta *next;
  bool free;
};

/* FUNCTIONS */

struct block_meta *get_block_ptr(void *ptr);
void *get_block(struct block_meta *ptr);
struct block_meta *find_free_block(struct block_meta *current, size_t size);
void mem_init(struct block_meta *heap, size_t heap_size);
void *alloc(size_t size, struct block_meta *heap);
void free(void *ptr);

#endif
