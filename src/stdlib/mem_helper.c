#include <stdlib.h>

void *_global_base = NULL;

void _mem_init(struct _block_meta *heap, size_t heap_size) {
    heap->size = heap_size - _SIZE__block_meta;
    heap->next = NULL;
    heap->free = 1;
    heap->magic = 0x3333;
    _global_base = heap;
}

struct _block_meta *_find_free_block(struct _block_meta **last, size_t size) {
  struct _block_meta *current = _global_base;
  while (current != NULL && !(current->free && current->size >= size)) {
    *last = current;
    current = current->next;
  }
  return current;
}

struct _block_meta *_get_block_ptr(void *ptr) {
  return (struct _block_meta*)ptr - 1;
}

void *_get_block(struct _block_meta *ptr) {
  return (void*)(ptr + 1);
}
