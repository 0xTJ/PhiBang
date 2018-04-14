#ifndef _INCLUDE_file_sys_H
#define _INCLUDE_file_sys_H

#include <sys/types.h>

struct inode {
    ino_t ino;
    uint8_t fs_num;
    dev_t dev;
    uint8_t ext_mount;
    uint8_t refs;
};

struct mount;

struct fs_ops {
    void (*mount)(struct mount *mount);
    void (*read_inode)(struct inode *inodep);
    void (*write_inode)(struct inode *inodep);
    ino_t (*find_ino)(char *path);
};

struct inode_ops {
    size_t (*read)(struct inode *inodep, uint8_t *buf, size_t size, off_t offset);
    ssize_t (*write)(struct inode *inodep, uint8_t *buf, size_t size, off_t offset);
    int (*open)(struct inode *inodep, ino_t ino);
    // ino_t (*srch_dir)(struct inode *inodep, char *name);
    //inoptr (*find_dir)
};

struct file_sys {
    struct fs_ops fs_ops;
    struct inode_ops inode_ops;
};

struct mount {
    struct inode *mount_point;
    dev_t dev;
    uint8_t fs_num;
    struct inode *fs_root;
};

extern struct inode ino_tab[];
extern struct file_sys *fs_tab[];
extern struct mount mnt_tab[];

extern const struct inode *root_node;

unsigned short add_fs(struct file_sys *fs);
struct inode *alloc_inode();
void free_inode(struct inode *inode);
unsigned short alloc_mount();
void free_mount(unsigned short mount_num);
struct inode *follow_path(struct inode *root, char *path);
size_t get_path_unit(char *part_path, char *path);

#endif
