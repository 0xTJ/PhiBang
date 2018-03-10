#ifndef _INCLUDE_STDLIB_H
#define _INCLUDE_STDLIB_H

/* TYPES */

#ifndef _TYPEDEF_size_t
typedef unsigned short int size_t;
#define _TYPEDEF_size_t
#endif

struct _block_meta {
  size_t size;
  struct _block_meta *next;
  int free;
  int magic;
};

#define _SIZE__block_meta sizeof(struct _block_meta)

/* MACROS */

#ifndef NULL
#define NULL (0)
#endif
#ifndef MB_CUR_MAX
#define MB_CUR_MAX (2)
#endif

/* FUNCTIONS */

void *calloc(size_t nmemb, size_t size);
void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);

void _mem_init(struct _block_meta *heap, size_t heap_size);
struct _block_meta *_find_free_block(struct _block_meta **last, size_t size);
struct _block_meta *_get_block_ptr(void *ptr);
void *_get_block(struct _block_meta *ptr);

#endif
