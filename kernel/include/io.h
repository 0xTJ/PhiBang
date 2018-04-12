#ifndef _INCLUDE_IO_H
#define _INCLUDE_IO_H

#include <stddef.h>
#include <sys/types.h>
#include <unistd.h>
#include "filesys.h"

enum file_mode { MODE_NONE = 0, MODE_READ, MODE_WRITE, MODE_READ_WRITE };

#define MAX_OPEN_FILES 16

struct ofile {
    enum file_mode mode;
    off_t offset;
    struct inode *inodep;
};

extern struct ofile ofile_table[];

#endif
