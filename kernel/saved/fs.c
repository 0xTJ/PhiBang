#include "fs.h"

ssize_t reg_fs(struct fs_type *fs_type) {
    size_t i = 0;
    
    do {
        if (fs_table[i] == NULL)
            break;
        i++;
    } while (i < FS_MAX - 1);
    
    if (i == FS_MAX)
        return -1;
    
    fs_table[i] = fs_type;
    return i;
}
