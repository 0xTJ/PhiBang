#ifndef _INCLUDE_IO_H
#define _INCLUDE_IO_H

#include <stddef.h>
#include <sys/types.h>
#include <unistd.h>

enum file_mode { MODE_NONE = 0, MODE_READ, MODE_WRITE, MODE_READ_WRITE };

struct driver {
    void (*init)();
    int (*put)(char c);
    int (*get)();
    void *(*control)(void *desc);
};

#define VNODE_CHILDREN 8

struct vnode {
    struct driver *driver;
    /* inode_t inode_num; */
    struct vnode *children[VNODE_CHILDREN];
    struct vnode *parent;
};

#define MAX_OPEN_FILES 16

struct ofile {
    enum file_mode mode;
    off_t offset;
    dev_t major_dev_id;
    dev_t minor_dev_id;
    unsigned long inode
};

extern struct vnode *vfs_root;
extern struct ofile ofile_table[];

int reg_vnode(struct vnode *parent, struct driver *driver_desc, int name/*, inode_t inode_num*/);

int reg_ofile(struct vnode *vnode_p, enum file_mode mode);

void reg_fd(pid_t proc, int fd, int file_index);

#endif
