#include "io.h"
#include "proc.h"

int get(int fd) {
    struct ofile *this_file = proc_table[proc_cur].fd_table[fd];
    return this_file->vnode_p->get();
}

void put(int fd, int c) {
    struct ofile *this_file = proc_table[proc_cur].fd_table[fd];
    this_file->vnode_p->put((char)c);
}
