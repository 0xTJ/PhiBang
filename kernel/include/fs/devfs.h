#ifndef _INCLUDE_DEVFS_H
#define _INCLUDE_DEVFS_H

#include "fs.h"
#include <stdbool.h>

void _devfs_add(size_t index, bool is_block, char *name);

fs_node_t *initialise_devfs();

#endif
