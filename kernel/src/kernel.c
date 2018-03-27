#include <stdbool.h>
#include "proc.h"
#include "acia.h"
#include "io.h"

void init() {
    reg_vnode(vfs_root, NULL, 0);
    reg_vnode(vfs_root->children[0], &acia_driver, 0);

    reg_ofile(vfs_root->children[0]->children[0], MODE_READ);
    reg_ofile(vfs_root->children[0]->children[0], MODE_WRITE);

    proc_table[1].fd_table[0] = ofile_table + 0;
    proc_table[1].fd_table[1] = ofile_table + 1;
    proc_table[1].fd_table[2] = ofile_table + 1;

    write(1, "HELLO", 5);
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
    heap.free = true;

    proc_init_enter1(init);
}
