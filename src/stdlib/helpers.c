#include <stdlib.h>

struct _alloc_header *heap_head;
struct _alloc_header *heap_tail;

// TODO: Properly sort list

void def_zone(void *ptr, size_t size, enum zone_type type) {
    struct _alloc_header *zone = ptr;
    
    zone->zone_size = size;
    
    if (type == FREE) {
        zone->prev_free_ptr = heap_tail->prev_free_ptr;
        zone->next_free_ptr = heap_tail;
        heap_tail->prev_free_ptr->next_free_ptr = zone;
        heap_tail->prev_free_ptr = zone;
    } else {
        zone->prev_free_ptr = NULL;
        zone->next_free_ptr = NULL;
    }
    
    zone->type = type;
}

void redef_zone(void *ptr, enum zone_type type) {
    struct _alloc_header *zone = ptr;
    
    if (zone->type == type)
        return;
    
    if (zone->type == FREE) {
        if (zone->prev_free_ptr == NULL || zone->next_free_ptr == NULL)
            return;
        zone->prev_free_ptr->next_free_ptr = zone->next_free_ptr;
        zone->next_free_ptr->prev_free_ptr = zone->prev_free_ptr;
    }
    
    if (type == FREE) {
        zone->prev_free_ptr = heap_tail->prev_free_ptr;
        zone->next_free_ptr = heap_tail;
        heap_tail->prev_free_ptr->next_free_ptr = zone;
        heap_tail->prev_free_ptr = zone;
    } else {
        zone->prev_free_ptr = NULL;
        zone->next_free_ptr = NULL;
    }
    
    zone->type = type;
}
