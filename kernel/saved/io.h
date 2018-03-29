#ifndef _INCLUDE_IO_H
#define _INCLUDE_IO_H

#include <stddef.h>
#include <sys/types.h>
#include <unistd.h>

enum file_mode { MODE_NONE = 0, MODE_READ, MODE_WRITE, MODE_READ_WRITE };

#define MAX_OPEN_FILES 16

struct ofile {
    enum file_mode mode;
    off_t offset;
    struct dentry *dentry;
};

extern struct ofile ofile_table[];

int reg_ofile(struct vnode *vnode_p, enum file_mode mode);

void reg_fd(pid_t proc, int fd, int file_index);

#endif
