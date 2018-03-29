#include "bfs.h"
#include "mem.h"

struct fs_type bfs_fs = {
    NULL,
    bfs_mount
};

extern struct block_meta heap;

struct super_block *bfs_mount(struct fs_type *type, struct block_device *block_device){
    struct super_block *new_sb;

    if (type->sb_list != NULL)
        return NULL;
    
    new_sb = k_alloc(sizeof(struct super_block), &heap);
    if (new_sb == NULL)
        return NULL;
    
    new_sb->block_size = block_device->block_size;
    new_sb->block_device = block_device;
    new_sb->type = type;
    new_sb->next = NULL;
    
    return new_sb;
}

struct inode *bfs_alloc_inode(struct super_block *sb) {
    struct inode *new_inode = k_alloc(sizeof(struct inode));
    if (new_inode != NULL) {
        new_inode->
    }
    return new_inode;
}

void bfs_destroy_inode(struct inode *inode) {
    
}
