#include <unistd.h>
#include "proc.h"

size_t read(int fildes, void *buf, size_t nbyte) {
    struct vnode *this_vnode = proc_table[proc_cur].fd_table[fildes]->vnode_p;
    size_t i;
    
    if (nbyte == 0)
        return 0;
    
    for (i = 0; i < nbyte; i++) {
        int got;
        got = this_vnode->driver->get();
        
        if (got < 0) {
            proc_table[proc_cur].fd_table[fildes]->offset += i;
            return i;
        }
        
        ((char *)buf)[i] = got;
    }
    
    proc_table[proc_cur].fd_table[fildes]->offset += nbyte;
    return nbyte;
}

extern int acia_put(char c);

ssize_t write(int fildes, const void *buf, size_t nbyte) {
    struct vnode *this_vnode = proc_table[proc_cur].fd_table[fildes]->vnode_p;
    size_t i;
    
    if (nbyte == 0)
        return 0;
    
    for (i = 0; i < nbyte; i++) {
        if (this_vnode->driver->put(((char *)buf)[i]) < 0) {
            if (i == 0)
                return -1;
            else
                return i;
        }
    }
    
    return nbyte;
}
