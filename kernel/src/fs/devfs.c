#include "fs/devfs.h"
#include <string.h>
#include <stdio.h>
#include "kio.h"
#include "mem.h"
#include "dev.h"

fs_node_t *devfs_root;
fs_node_t *dev_root_nodes[DEVICE_COUNT];

static size_t devfs_read(fs_node_t *node, off_t offset, size_t size, uint8_t *buffer) {
    size_t i = 0;
    switch (node->flags & (uint32_t)0x7) {
    case FS_CHARDEVICE:
        if (((struct char_device *)dev_tab[node->inode].dev_desc)->get == NULL)
            return 0;

        while (i < size) {
            int tmp = ((struct char_device *)dev_tab[node->inode].dev_desc)->get();
            if (tmp == EOF)
                break;
            *buffer++ = tmp;
            i++;
        }
        return i;
    case FS_BLOCKDEVICE:
    }
    return 0;
}

static ssize_t devfs_write(fs_node_t *node, off_t offset, size_t size, uint8_t *buffer) {
    size_t i = 0;
    switch (node->flags & (uint32_t)0x7) {
    case FS_CHARDEVICE:
        if (((struct char_device *)dev_tab[node->inode].dev_desc)->put == NULL)
            return -1;

        while (i < size) {
            if (((struct char_device *)dev_tab[node->inode].dev_desc)->put(*buffer++) < 0)
                return -1;
            i++;
        }
        return i;
    case FS_BLOCKDEVICE:
    }
    return -1;
}

static struct dirent *devfs_readdir(fs_node_t *node, uint32_t index) {
    if (node != devfs_root)
        return NULL;
    if (index >= DEVICE_COUNT)
        return NULL;
    if (dev_tab[index].type == NO_DEV)
        return NULL;
    strcpy(dirent.d_name, dev_root_nodes[index]->name);
    dirent.d_ino = index;
    return &dirent;
}

static fs_node_t *devfs_finddir(fs_node_t *node, char *name) {
    size_t i;

    for (i = 0; i < DEVICE_COUNT; i++) {
        if (dev_tab[i].type == NO_DEV)
            continue;
        if (!strcmp(name, dev_root_nodes[i]->name))
            return dev_root_nodes[i];
    }
    return NULL;
}

void _devfs_add(size_t index, bool is_block, char *name) {
    if (is_block)
        kprint("WARNING: Block devices not yet implemented.\n");
    
    dev_root_nodes[index] = kmalloc(sizeof(fs_node_t));
    strcpy(dev_root_nodes[index]->name, name);
    dev_root_nodes[index]->mask = dev_root_nodes[index]->uid = dev_root_nodes[index]->gid = 0;
    dev_root_nodes[index]->length = 0;
    dev_root_nodes[index]->inode = index;
    if (is_block)
        dev_root_nodes[index]->flags = FS_BLOCKDEVICE;
    else
        dev_root_nodes[index]->flags = FS_CHARDEVICE;
    dev_root_nodes[index]->read = devfs_read;
    dev_root_nodes[index]->write = devfs_write;
    dev_root_nodes[index]->readdir = 0;
    dev_root_nodes[index]->finddir = 0;
    dev_root_nodes[index]->open = 0;
    dev_root_nodes[index]->close = 0;
    dev_root_nodes[index]->impl = 0;
}

fs_node_t *initialise_devfs() {
    size_t i;

    // Initialise the root directory.
    devfs_root = (fs_node_t *)kmalloc(sizeof(fs_node_t));
    strcpy(devfs_root->name, "devfs");
    devfs_root->mask = devfs_root->uid = devfs_root->gid = devfs_root->inode = devfs_root->length = 0;
    devfs_root->flags = FS_DIRECTORY;
    devfs_root->read = 0;
    devfs_root->write = 0;
    devfs_root->open = 0;
    devfs_root->close = 0;
    devfs_root->readdir = &devfs_readdir;
    devfs_root->finddir = &devfs_finddir;
    devfs_root->ptr = 0;
    devfs_root->impl = 0;

      // For every file...
    for (i = 0; i < DEVICE_COUNT; i++)
        dev_root_nodes[i] = NULL;

    init_devices();

    return devfs_root;
}
