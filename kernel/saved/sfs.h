#ifndef _INCLUDE_SFS_H
#define _INCLUDE_SFS_H

#include "fs.h"

const struct fs_type sfs_fs_type;

struct super_block *sfs_mount(struct fs_type *, dev_t dev);

struct inode *(*sfs_alloc_inode)(struct super_block *);
void (*sfs_destroy_inode)(struct inode *);

int (*sfs_create)(struct inode *, struct dentry *, char *);
int (*sfs_mkdir)(struct inode *, struct dentry *, char *);

ssize_t (*sfs_read)(struct file *, char *, size_t, off_t);
ssize_t (*sfs_write)(struct file *, const char *, size_t, off_t);
int (*sfs_open)(struct inode *, struct file *);

#endif
