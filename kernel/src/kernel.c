#include <stdbool.h>
#include "proc.h"
#include "acia.h"
#include "ramdisk.h"
#include "dev.h"
#include "fs.h"
#include "sfs.h"

void kprint(char *s) {
    while (*s != '\0')
        acia_put(*s++);
}

void init() {
    kprint("\n\nLoading PhiBang\n\n");
    
    add_device(&acia_device, CHAR_DEV);
    add_device(&ramdisk_device, BLOCK_DEV);
    
    sfs_fs_type.mount(&sfs_fs_type, 1);
    
    acia_put('0'+((struct block_device *)(device_table[1].dev_desc))->read_dir(0));
    ((struct block_device *)(device_table[1].dev_desc))->write_dir(0,1);
    acia_put('0'+((struct block_device *)(device_table[1].dev_desc))->read_dir(0));
    ((struct block_device *)(device_table[1].dev_desc))->write_dir(0,0);
    acia_put('0'+((struct block_device *)(device_table[1].dev_desc))->read_dir(0));
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

    proc_init_enter1(init);
}
