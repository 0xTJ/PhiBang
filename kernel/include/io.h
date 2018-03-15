#ifndef _INCLUDE_IO_H
#define _INCLUDE_IO_H

#include "types.h"

enum file_type { TYPE_NONE = 0, TYPE_CHAR_DEVICE };
enum file_mode { MODE_NONE = 0, MODE_READ, MODE_WRITE, MODE_READ_WRITE };

struct vnode {
    enum file_type type;
    size_t size;
    size_t ref_count;
    void (*put)(char c);
    char (*get)();
    int (*control)(void *desc);
};

struct ofile {
    enum file_mode mode;
    size_t offset;
    struct vnode *vnode_p;
    size_t ref_count;
};

extern struct ofile ofile_table[];
extern struct vnode vnode_table[];

void reg_vnode(int index, struct vnode *driver_desc);
void dereg_vnode(int index);
void dereg_vnode_by_p(struct vnode *target);

void reg_ofile(int file_index, int vnode_index, enum file_mode mode);
void dereg_ofile(int file_index);
void dereg_ofile_by_p(struct ofile *target);

void reg_fd(int proc, int fd, int file_index);
void dereg_fd(int proc, int fd);

int get(int fd);
void put(int fd, int c);

#endif
