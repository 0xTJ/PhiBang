#ifndef _INCLUDE_IO_H
#define _INCLUDE_IO_H

#include <stddef.h>

enum file_type { TYPE_NONE = 0, TYPE_BIN_STREAM };
enum file_mode { MODE_NONE = 0, MODE_READ, MODE_WRITE, MODE_READ_WRITE };

struct vnode {
    enum file_type type;
    size_t size;
    size_t ref_count;
    void (*put)(char c);
    char (*get)();
    int (*control)(void *desc);
};

struct open_file {
    enum file_mode mode;
    size_t offset;
    struct vnode *vnode_p;
    size_t ref_count;
};

extern struct open_file open_file_table[];
extern struct vnode vnode_table[];

int get(int fd);
void put(int fd, int c);

#endif
