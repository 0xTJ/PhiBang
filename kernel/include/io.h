#ifndef _INCLUDE_IO_H
#define _INCLUDE_IO_H

#include "types.h"

enum file_mode { MODE_NONE = 0, MODE_READ, MODE_WRITE, MODE_READ_WRITE };

struct driver {
    char name[8];
    void (*put)(char c);
    char (*get)();
    int (*control)(void *desc);
};

#define VNODE_CHILDREN 8

struct vnode;
struct vnode {
    struct driver *driver;
    /* inode_t inode_num; */
    struct vnode *children[VNODE_CHILDREN];
    struct vnode *parent;
};

#define MAX_OPEN_FILES 16

struct ofile {
    enum file_mode mode;
    size_t offset;
    struct vnode *vnode_p;
};

extern struct vnode *vfs_root;
extern struct ofile ofile_table[];
extern struct vnode vnode_table[];

int reg_vnode(struct vnode *parent, struct driver *driver_desc, int name/*, inode_t inode_num*/);

int reg_ofile(struct vnode *vnode_p, enum file_mode mode);

void reg_fd(int proc, int fd, int file_index);

int get(int fd);
void put(int fd, int c);

#endif
