#include "filesys.h"
#include <stddef.h>

#define INODE_COUNT 32
struct inode ino_tab[INODE_COUNT];

#define FS_COUNT 4
struct file_sys *fs_tab[FS_COUNT] = { NULL };

#define MOUNT_COUNT 8
struct mount mnt_tab[MOUNT_COUNT];
