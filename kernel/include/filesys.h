#ifndef _INCLUDE_file_sys_H
#define _INCLUDE_file_sys_H

#include <sys/types.h>

struct inode {
    ino_t inode_num;
    uint8_t fs_num;
    dev_t dev_num;
    struct mount *ext_mount;
    uint8_t refs;
};

struct fs_ops {
    void (*mount)(struct mount *mount);
    void (*read_inode)(struct inode *inodep);
    void (*write_inode)(struct inode *inodep);
};

struct inode_ops {
    size_t (*read)(struct inode *inodep, uint8_t *buf, size_t size, off_t offset);
    ssize_t (*write)(struct inode *inodep, uint8_t *buf, size_t size, off_t offset);
    struct inode *(*srch_dir)(struct inode *inodep, char *name);
    //inoptr (*find_dir)
};

struct file_sys {
    struct fs_ops fs_ops;
    struct inode_ops inode_ops;
};

struct mount {
    dev_t dev;
    struct inode *mount_point;
    struct inode *fs_root;
    struct file_sys *p_fs;
};

extern struct inode ino_tab[];
extern struct file_sys *fs_tab[];
extern struct mount mnt_tab[];

#endif
