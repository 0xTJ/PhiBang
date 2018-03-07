#ifndef _INCLUDE_STDLIB_H
#define _INCLUDE_STDLIB_H

/* TYPES */

#ifndef _TYPEDEF_SIZE_T
typedef unsigned short int size_t;
#define _TYPEDEF_SIZE_T
#endif

struct block_meta {
  size_t size;
  struct block_meta *next;
  int free;
  int magic;
};


/* MACROS */

#ifndef NULL
#define NULL (0)
#endif

#ifndef EXIT_FAILURE
#define EXIT_FAILURE (1)
#endif

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS (0)
#endif

#ifndef RAND_MAX
#define RAND_MAX (0)
#endif

#ifndef MB_CUR_MAX
#define MB_CUR_MAX (2)
#endif


/* FUNCTIONS */

void mem_init(struct block_meta *heap, size_t heap_size);
void *k_calloc(size_t nmemb, size_t size);
void k_free(void *ptr);
void *k_malloc(size_t size);
void *k_realloc(void *ptr, size_t size);

#endif
