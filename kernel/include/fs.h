#ifndef _INCLUDE_FS_H
#define _INCLUDE_FS_H

#include <sys/types.h>

struct fs_type {
    const char *name;
    struct super_block *(*mount)(struct fs_type *, dev_t dev);
};

struct super_block {
    unsigned short block_size;
    struct fs_type *type;
    struct sb_ops *ops;
    struct block_device *dev;
};

struct sb_ops {
    struct inode *(*alloc_inode)(struct super_block *);
    void (*destroy_inode)(struct inode *);
};

struct inode {
    unsigned short ino;
    struct in_ops *ops;
    struct in_file_ops *file_ops;
    struct super_block *sb;
};

struct in_ops {
    int (*create)(struct inode *, struct dentry *, char *);
    int (*mkdir)(struct inode *, struct dentry *, char *);
};

struct in_file_ops {
    ssize_t (*read)(struct file *, char *, size_t, off_t);
    ssize_t (*write)(struct file *, const char *, size_t, off_t);
    int (*open)(struct inode *, struct file *);
};

struct dentry {
    struct dent_ops *ops;
    struct inode inode;
    char name[];
};

struct dent_ops {
    void *nul;
};

struct file {
    struct dentry *dentry;
};

#endif
