#include "proc.h"
#include "acia.h"
#include "io.h"
#include <stdio.h>

extern void (*sosh_main)(void);

void init() {
    reg_vnode(vfs_root, NULL, 0);
    reg_vnode(vfs_root, NULL, 5);
    reg_vnode(vfs_root->children[0], &acia_vnode, 0);
    reg_vnode(vfs_root->children[5], NULL, 7);
    
    reg_ofile(vfs_root->children[0]->children[0], MODE_READ);
    reg_ofile(vfs_root->children[0]->children[0], MODE_WRITE);
    
    reg_fd(0, 0, 0);
    reg_fd(0, 1, 1);
    reg_fd(0, 2, 1);
}

void main() {    
    /*init();
    */
    __asm
    ld hl, #02
    rst 0x30
    __endasm;
}
