#ifndef _INCLUDE_STDLIB_H
#define _INCLUDE_STDLIB_H

#ifndef _DEFINED_NULL
#define NULL 0
#define _DEFINED_NULL
#endif

#ifndef _DEFINED_EXIT_FAILURE
#define EXIT_FAILURE 1
#define _DEFINED_EXIT_FAILURE
#endif

#ifndef _DEFINED_EXIT_SUCCESS
#define EXIT_SUCCESS 1
#define _DEFINED_EXIT_SUCCESS
#endif

#ifndef _DEFINED_SIZE_T
typedef unsigned short int size_t;
#define _DEFINED_SIZE_T
#endif

#ifndef _DEFINED_WCHAR_T
typedef unsigned short int wchar_t;
#define _DEFINED_WCHAR_T
#endif

#ifndef _DEFINED_DIV_T
typedef struct {
  int quot;
  int rem;
} div_t;
#define _DEFINED_DIV_T
#endif

#ifndef _DEFINED_LDIV_T
typedef struct {
  long int quot;
  long int rem;
} ldiv_t;
#define _DEFINED_LDIV_T
#endif

enum zone_type { FREE=5, USED };

struct _alloc_header;
struct _alloc_header {
    enum zone_type type;
    struct _alloc_header *prev_free_ptr;
    struct _alloc_header *next_free_ptr;
    size_t zone_size;
};

extern struct _alloc_header *heap_head;
extern struct _alloc_header *heap_tail;

void *malloc(size_t size);
void free(void *ptr);

void def_zone(void *ptr, size_t size, enum zone_type type);
void redef_zone(void *ptr, enum zone_type type);

#endif  // NDEF _INCLUDE_STDLIB_H
