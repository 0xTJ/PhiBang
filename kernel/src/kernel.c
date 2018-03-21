#include "constants.h"
#include "proc.h"
#include "acia.h"
#include "io.h"
#include <stdio.h>

extern void (*sosh_main)(void);

void init() {
    reg_vnode(vfs_root, NULL, 0);
    reg_vnode(vfs_root, NULL, 5);
    reg_vnode(vfs_root->children[0], &acia_vnode, 0);
    
    reg_ofile(vfs_root->children[0]->children[0], MODE_READ);
    reg_ofile(vfs_root->children[0]->children[0], MODE_WRITE);
    
    reg_fd(0, 0, 0);
    reg_fd(0, 1, 1);
    reg_fd(0, 2, 1);
}

void ls(int pid) {
    struct vnode *pwd = proc_table[pid].pwd;
    int i;
    
    if (proc_table[pid].status < 1)
        return;
    
    for (i = 0; i < VNODE_CHILDREN; i++) {
        if (pwd->children[i] != NULL) {
            putchar(i + '0');
            putchar('\n');
        }
    }
}

void main() {
    _setup_stdio();
    init();
    
    puts("\nSTART\n");
    ls(0);
    puts("\nHALT\n");
}
