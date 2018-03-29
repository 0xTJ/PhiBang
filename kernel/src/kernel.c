#include <stdbool.h>
#include "proc.h"
#include "acia.h"
#include "ramdisk.h"
#include "dev.h"

void init() {
    
}

struct block_meta heap;

void main() {
    __asm
    push    hl
    ld      hl, #l__HEAP
    ld      (_heap), hl ;// Only works if size is the first element of struct block_meta
    pop hl
    __endasm;

    heap.size = heap.size - sizeof(struct block_meta);
    heap.next = NULL;
    heap.k_free = true;

    add_device(&acia_device, CHAR_DEV);
    add_device(&ramdisk_device, BLOCK_DEV);

    proc_init_enter1(init);
}
