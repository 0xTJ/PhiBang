#ifndef _INCLUDE_FS_H
#define _INCLUDE_FS_H

#include <sys/types.h>
#include "io.h"
#include "dev.h"

#define FS_MAX 4

struct super_block {
    unsigned long block_size;
    struct block_device *block_device;
    struct fs_type *type;
    struct inode *(*alloc_inode)(struct super_block *sb);
    void (*destroy_inode)(struct inode *inode);
    struct super_block *next;
};

struct fs_type {
    struct super_block *sb_list;
    struct super_block *(*mount)(struct fs_type *type, struct block_device *block_device);
};

struct inode {
    struct super_block sb;
    ssize_t (*read)(struct ofile *ofile, char *buf, size_t n, off_t offset);
    ssize_t (*write)(struct ofile *ofile, const char *buf, size_t n, off_t offset);
};

struct fs_type *fs_table[FS_MAX];

extern struct fs_type bfs_fs;

ssize_t reg_fs(struct fs_type *fs_type);

int reg_ofile(struct inode *inode, enum file_mode mode);

#endif
