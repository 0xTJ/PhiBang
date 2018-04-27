#ifndef _INCLUDE_INITRD_H
#define _INCLUDE_INITRD_H

#include <stdint.h>
#include "fs.h"

typedef struct {
   uint32_t nfiles;
   uint8_t loaded;
} initrd_header_t;

typedef struct {
   uint8_t magic;       // Magic number, for error checking.
   uint8_t name[65];       // Filename.
   uint16_t offset;       // Offset in the initrd that the file starts.
   uint16_t length;       // Length of the file.
} initrd_file_header_t;

fs_node_t *initialise_initrd(size_t location);

#endif
