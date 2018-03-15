#ifndef _INCLUDE_MEM_H
#define _INCLUDE_MEM_H

#include "types.h"
#include "constants.h"

extern void *global_base;

/* TYPES */

struct block_meta {
  size_t size;
  struct block_meta *next;
  int free;
  int pid;
};

#define SIZE_block_meta sizeof(struct block_meta)

/* FUNCTIONS */

struct block_meta *get_block_ptr(void *ptr);
void *get_block(struct block_meta *ptr);
struct block_meta *find_free_block(struct block_meta **last, size_t size);
void mem_init(struct block_meta *heap, size_t heap_size);
void *alloc(size_t size, int pid);
void free(void *ptr);

#endif
