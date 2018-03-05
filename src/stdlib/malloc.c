#include <stdlib.h>

struct alloc_header;
struct alloc_header {
    char magic_word[8];
    struct alloc_header *prev_free_ptr;
    struct alloc_header *next_free_ptr;
    size_t zone_size;
};

struct alloc_header *heap_header;

void minit(void *heap_base, size_t heap_size) {
    struct alloc_header *first_free;
    
    heap_header = heap_base;
    first_free = heap_header + sizeof(struct alloc_header);
    
    heap_header->magic_word[0] = 'F';
    heap_header->magic_word[1] = ' ';
    heap_header->magic_word[2] = 'R';
    heap_header->magic_word[3] = ' ';
    heap_header->magic_word[4] = 'E';
    heap_header->magic_word[5] = ' ';
    heap_header->magic_word[6] = 'E';
    heap_header->magic_word[7] = 0;
    
    heap_header->prev_free_ptr = NULL;
    heap_header->next_free_ptr = first_free;
    
    heap_header->zone_size = 0;
    
    first_free->magic_word[0] = 'F';
    first_free->magic_word[1] = ' ';
    first_free->magic_word[2] = 'R';
    first_free->magic_word[3] = ' ';
    first_free->magic_word[4] = 'E';
    first_free->magic_word[5] = ' ';
    first_free->magic_word[6] = 'E';
    first_free->magic_word[7] = 0;
    
    first_free->prev_free_ptr = heap_header;
    first_free->next_free_ptr = NULL;
    
    first_free->zone_size = heap_size - 2 * sizeof(struct alloc_header);
}

void *malloc(size_t size) {
    struct alloc_header *zone = heap_header;
    
    if (size == 0)
        return NULL;
    
    do {
        if (zone->zone_size >= size)
            break;
        zone = zone->next_free_ptr;
    } while (zone != NULL);
    
    if (zone == NULL)
        return NULL;
    
    zone->magic_word[0] = 'U';
    zone->magic_word[1] = ' ';
    zone->magic_word[2] = 'S';
    zone->magic_word[3] = ' ';
    zone->magic_word[4] = 'E';
    zone->magic_word[5] = ' ';
    zone->magic_word[6] = 'D';
    zone->magic_word[7] = 0;
    
    if (zone->zone_size >= size + 2 * sizeof(struct alloc_header)) {     // Possible issues with integer overflow
        struct alloc_header *new_free_zone = (struct alloc_header *)((char *)(zone) + sizeof(struct alloc_header) + size);
        *((struct alloc_header **)0x80A0) = new_free_zone;
        
        new_free_zone->magic_word[0] = 'F';
        new_free_zone->magic_word[1] = ' ';
        new_free_zone->magic_word[2] = 'R';
        new_free_zone->magic_word[3] = ' ';
        new_free_zone->magic_word[4] = 'E';
        new_free_zone->magic_word[5] = ' ';
        new_free_zone->magic_word[6] = 'E';
        new_free_zone->magic_word[7] = 0;
        
        new_free_zone->prev_free_ptr = zone->prev_free_ptr;
        new_free_zone->next_free_ptr = zone->next_free_ptr;
        
        new_free_zone->zone_size = zone->zone_size - size - sizeof(struct alloc_header); 
    
        if (zone->prev_free_ptr != NULL)
            zone->prev_free_ptr->next_free_ptr = new_free_zone;
        if (zone->next_free_ptr != NULL)
            zone->next_free_ptr->prev_free_ptr = new_free_zone;
        
        zone->zone_size = size;
    } else {
        if (zone->prev_free_ptr != NULL)
            zone->prev_free_ptr->next_free_ptr = zone->next_free_ptr;
        if (zone->next_free_ptr != NULL)
            zone->next_free_ptr->prev_free_ptr = zone->prev_free_ptr;
    }
    
    return zone;
}
