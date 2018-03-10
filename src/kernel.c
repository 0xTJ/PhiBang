#include "proc.h"
#include "io.h"
#include "acia.h"

void init() {
    struct vnode *v_acia = vnode_table + 0;
    
    struct open_file *acia_read = open_file_table + 0;
    struct open_file *acia_write = open_file_table + 1;
    
    v_acia->size = TYPE_BIN_STREAM;
    v_acia->size = 0;
    v_acia->ref_count = 0;
    v_acia->put = acia_put;
    v_acia->get = acia_get;
    v_acia->control = NULL;
    
    acia_read->mode = MODE_READ;
    acia_read->offset = 0;
    acia_read->vnode_p = v_acia;
    acia_read->vnode_p->ref_count++;
    acia_read->ref_count = 0;
    
    acia_write->mode = MODE_WRITE;
    acia_write->offset = 0;
    acia_write->vnode_p = v_acia;
    acia_write->vnode_p->ref_count++;
    acia_write->ref_count = 0;
    
    proc_table[0].fd_table[0] = acia_read;
    proc_table[0].fd_table[0]->ref_count++;
    proc_table[0].fd_table[1] = acia_write;
    proc_table[0].fd_table[1]->ref_count++;
    proc_table[0].fd_table[2] = acia_write;
    proc_table[0].fd_table[2]->ref_count++;
}

int main() {
    init();
    put(1, 'f');
}
