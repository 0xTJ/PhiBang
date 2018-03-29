#include "sfs.h"
#include "mem.h"
#include "dev.h"

#define OFFSET_TIME_STAMP 0x0194
#define OFFSET_DATA_SIZE_BLKS 0x019C
#define OFFSET_INDEX_SIZE_BLKS 0x01A4
#define OFFSET_MAGIC 0x01AC
#define OFFSET_DATA_SIZE_BLK 0x01AF
#define OFFSET_TOTAL_BLKS 0x01B0
#define OFFSET_RES_BLKS 0x01B8
#define OFFSET_BLK_SIZE 0x01BC
#define OFFSET_CHECKSUM 0x01BD

const struct fs_type sfs_fs_type = {
    "sfs",
    sfs_mount
};

const struct sb_ops sfs_sb_ops = {0
    // sfs_alloc_inode,
    // sfs_destroy_inode
};

const struct in_ops sfs_in_ops = {0
    // sfs_create,
    // sfs_mkdir
};

const struct in_file_ops sfs_in_file_ops = {0
    // sfs_read,
    // sfs_write,
    // sfs_open
};

extern struct block_meta heap;

struct super_block *sfs_mount(struct fs_type *type, dev_t dev) {
    struct super_block *new_sb = k_alloc(sizeof(struct super_block), &heap);
    
    if (new_sb != NULL) {
        new_sb->block_size = ((struct block_device *)(device_table[dev].dev_desc))->read_dir(OFFSET_BLK_SIZE);
        new_sb->type = type;
        new_sb->ops = &sfs_sb_ops;
        new_sb->dev = device_table[dev].dev_desc;
    }
    
    return new_sb;
}

// struct inode *sfs_alloc_inode(struct super_block *sb) {
    // return NULL;
// }

// void sfs_destroy_inode(struct inode *inode) {
    // return;
// }

// int sfs_create(struct inode *inode, struct dentry *dentry, char *name) {
    // return -1;
// }

// int sfs_mkdir(struct inode *inode, struct dentry *dentry, char *name) {
    // return -1;
// }

// ssize_t sfs_read(struct file *file, char *buf, size_t num, off_t offset) {
    // return -1;
// }

// ssize_t sfs_write(struct file *file, const char *buf, size_t num, off_t offset) {
    // return -1;
// }

// int sfs_open(struct inode *inode, struct file *file) {
    // return -1;
// }
