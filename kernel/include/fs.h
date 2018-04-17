#ifndef _INCLUDE_FS_H
#define _INCLUDE_FS_H

#include <dirent.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

#define FS_FILE        0x01
#define FS_DIRECTORY   0x02
#define FS_CHARDEVICE  0x03
#define FS_BLOCKDEVICE 0x04
#define FS_PIPE        0x05
#define FS_SYMLINK     0x06
#define FS_MOUNTPOINT  0x08

struct fs_node;

typedef size_t (*read_type_t)(struct fs_node *, off_t, size_t, uint8_t *);
typedef ssize_t (*write_type_t)(struct fs_node *, off_t, size_t, uint8_t *);
typedef void (*open_type_t)(struct fs_node *, uint8_t, uint8_t);
typedef void (*close_type_t)(struct fs_node *);
typedef struct dirent * (*readdir_type_t)(struct fs_node *, uint32_t);
typedef struct fs_node * (*finddir_type_t)(struct fs_node *, char *name);

typedef struct fs_node
{
   char name[NAME_MAX + 1];     // The filename.
   uint32_t mask;        // The permissions mask.
   uint32_t uid;         // The owning user.
   uint32_t gid;         // The owning group.
   uint32_t flags;       // Includes the node type. See #defines above.
   uint32_t inode;       // This is device-specific - provides a way for a filesystem to identify files.
   uint32_t length;      // Size of the file, in bytes.
   uint32_t impl;        // An implementation-defined number.
   read_type_t read;
   write_type_t write;
   open_type_t open;
   close_type_t close;
   readdir_type_t readdir;
   finddir_type_t finddir;
   struct fs_node *ptr; // Used by mountpoints and symlinks.
} fs_node_t;

extern fs_node_t *fs_root;

// Standard read/write/open/close functions. Note that these are all suffixed with
// _fs to distinguish them from the read/write/open/close which deal with file descriptors
// not file nodes.
size_t read_fs(fs_node_t *node, off_t offset, size_t size, uint8_t *buffer);
ssize_t write_fs(fs_node_t *node, off_t offset, size_t size, uint8_t *buffer);
void open_fs(fs_node_t *node, uint8_t read, uint8_t write);
void close_fs(fs_node_t *node);
struct dirent *readdir_fs(fs_node_t *node, uint32_t index);
fs_node_t *finddir_fs(fs_node_t *node, char *name);

#endif
