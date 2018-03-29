#ifndef _INCLUDE_BFS_H
#define _INCLUDE_BFS_H

#include "fs.h"

extern struct fs_type bfs_fs;

struct super_block *bfs_mount(struct fs_type *type, struct block_device *block_device);
struct inode *bfs_alloc_inode(struct super_block *sb);
void bfs_destroy_inode(struct inode *inode);

#endif
