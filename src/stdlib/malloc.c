#include <stdlib.h>

void minit(void *heap_base, size_t heap_size) {
    
    heap_head = heap_base;
    heap_tail = (void *)((char *)heap_base + heap_size - sizeof(struct _alloc_header));
    
    heap_head->type = FREE;
    heap_head->prev_free_ptr = NULL;
    heap_head->next_free_ptr = heap_tail;
    heap_head->zone_size = 0;
    
    heap_tail->type = FREE;
    heap_tail->prev_free_ptr = heap_head;
    heap_tail->next_free_ptr = NULL;
    heap_tail->zone_size = 0;
    
    def_zone((void *)((char *)heap_base + sizeof(struct _alloc_header)), heap_size - 2 * sizeof(struct _alloc_header), FREE);
}

void *malloc(size_t size) {
    struct _alloc_header *zone = heap_head;
    
    if (size == 0)
        return NULL;
    
    do {
        if (zone->zone_size >= size)
            break;
        zone = zone->next_free_ptr;
    } while (zone != NULL);
    
    if (zone == NULL)
        return NULL;
    
    if (zone->zone_size >= size + 2 * sizeof(struct _alloc_header)) {     // Possible issues with integer overflow
        def_zone((void *)((char *)zone + size + sizeof(struct _alloc_header)), zone->zone_size - size - sizeof(struct _alloc_header), FREE);
        def_zone(zone, size, USED);
    } else {
        def_zone(zone, zone->zone_size, USED);
    }
    
    return zone;
}
