#include "io.h"
#include "proc.h"

struct vnode vnode_table[16];
struct open_file open_file_table[16];



int get(int fd) {
    struct open_file *this_file = proc_table[proc_cur].fd_table[fd];
    return this_file->vnode_p->get();
}

void put(int fd, int c) {
    struct open_file *this_file = proc_table[proc_cur].fd_table[fd];
    this_file->vnode_p->put((char)c);
}
