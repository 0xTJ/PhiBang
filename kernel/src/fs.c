#include "fs.h"
#include "kio.h"

fs_node_t *fs_root = NULL;

struct dirent dirent;

size_t read_fs(fs_node_t *node, off_t offset, size_t size, uint8_t *buffer) {
  if (node->read != NULL)
    return node->read(node, offset, size, buffer);
  else
    return 0;
}

ssize_t write_fs(fs_node_t *node, off_t offset, size_t size, uint8_t *buffer) {
  if (node->write != NULL)
    return node->write(node, offset, size, buffer);
  else
    return -1;
}

void open_fs(fs_node_t *node, uint8_t read, uint8_t write) {
  if (node->open != NULL)
    node->open(node, read, write);
  else
    return;
}

void close_fs(fs_node_t *node) {
  if (node->close != NULL)
    node->close(node);
  else
    return;
}

struct dirent *readdir_fs(fs_node_t *node, uint32_t index) {
    if ((node->flags & (uint32_t)0x7) == FS_DIRECTORY && node->readdir != NULL)
        return node->readdir(node, index);
    else
        return NULL;
}

fs_node_t *finddir_fs(fs_node_t *node, char *name) {
    if ((node->flags & (uint32_t)0x7) == FS_DIRECTORY && node->finddir != NULL)
        return node->finddir(node, name);
    else
        return NULL;
}
