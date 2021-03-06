#include "fs/initrd.h"
#include <dirent.h>
#include <string.h>
#include "kio.h"
#include "mem.h"

initrd_header_t *initrd_header;     // The header.
initrd_file_header_t *file_headers; // The list of file headers.
fs_node_t *initrd_root;             // Our root directory node.
fs_node_t *initrd_dev;              // We also add a directory node for /dev, so we can mount devfs later on.
fs_node_t *root_nodes;              // List of file nodes.
size_t nroot_nodes;                    // Number of file nodes.
off_t global_offset;

static size_t initrd_read(fs_node_t *node, off_t offset, size_t size, uint8_t *buffer) {
    initrd_file_header_t header; // Optimise to use pointer maybe?
    memcpy(&header, &file_headers[node->inode], sizeof(initrd_file_header_t));
    if (offset > header.length)
        return 0;
    if (offset + size > header.length)
        size = header.length - offset;
    memcpy(buffer, (uint8_t *)(header.offset + global_offset + offset), size);

    return size;
}

static struct dirent *initrd_readdir(fs_node_t *node, uint32_t index) {
   if (node == initrd_root && index == 0)
   {
     strcpy(dirent.d_name, "dev");
     dirent.d_name[3] = 0; // Make sure the string is NULL-terminated.
     dirent.d_ino = 0;
     return &dirent;
   }

   if (index - 1 >= nroot_nodes)
       return NULL;
   strcpy(dirent.d_name, root_nodes[index - 1].name);
   dirent.d_name[strlen(root_nodes[index - 1].name)] = 0; // Make sure the string is NULL-terminated.
   dirent.d_ino = root_nodes[index - 1].inode;
   return &dirent;
}

static fs_node_t *initrd_finddir(fs_node_t *node, char *name) {
    size_t i;

    if (node == initrd_root && !strcmp(name, "dev"))
       return initrd_dev;

    for (i = 0; i < nroot_nodes; i++)
       if (!strcmp(name, root_nodes[i].name))
           return &root_nodes[i];
    return NULL;
}

fs_node_t *initialise_initrd(size_t location) {
    size_t i;

    // Initialise the main and file header pointers and populate the root directory.
    initrd_header = (initrd_header_t *)location;
    file_headers = (initrd_file_header_t *)(location + sizeof(initrd_header_t));

    // Initialise the root directory.
    initrd_root = (fs_node_t *)kmalloc(sizeof(fs_node_t));
    strcpy(initrd_root->name, "initrd");
    initrd_root->mask = initrd_root->uid = initrd_root->gid = initrd_root->inode = initrd_root->length = 0;
    initrd_root->flags = FS_DIRECTORY;
    initrd_root->read = 0;
    initrd_root->write = 0;
    initrd_root->open = 0;
    initrd_root->close = 0;
    initrd_root->readdir = initrd_readdir;
    initrd_root->finddir = initrd_finddir;
    initrd_root->ptr = 0;
    initrd_root->impl = 0;

    // Initialise the /dev directory (required!)
    initrd_dev = (fs_node_t *)kmalloc(sizeof(fs_node_t));
    strcpy(initrd_dev->name, "dev");
    initrd_dev->mask = initrd_dev->uid = initrd_dev->gid = initrd_dev->inode = initrd_dev->length = 0;
    initrd_dev->inode = 1;
    initrd_dev->flags = FS_DIRECTORY;
    initrd_dev->read = 0;
    initrd_dev->write = 0;
    initrd_dev->open = 0;
    initrd_dev->close = 0;
    initrd_dev->readdir = initrd_readdir;
    initrd_dev->finddir = initrd_finddir;
    initrd_dev->ptr = 0;
    initrd_dev->impl = 0;

    root_nodes = (fs_node_t *)kmalloc(sizeof(fs_node_t) * initrd_header->nfiles);
    nroot_nodes = initrd_header->nfiles;

      // For every file...
    for (i = 0; i < initrd_header->nfiles; i++)
    {
        global_offset = location;
        // Create a new file node.
        strcpy(root_nodes[i].name, file_headers[i].name);
        root_nodes[i].mask = root_nodes[i].uid = root_nodes[i].gid = 0;
        root_nodes[i].length = file_headers[i].length;
        root_nodes[i].inode = i;
        root_nodes[i].flags = FS_FILE;
        root_nodes[i].read = initrd_read;
        root_nodes[i].write = 0;
        root_nodes[i].readdir = 0;
        root_nodes[i].finddir = 0;
        root_nodes[i].open = 0;
        root_nodes[i].close = 0;
        root_nodes[i].impl = 0;
    }

    return initrd_root;
}

