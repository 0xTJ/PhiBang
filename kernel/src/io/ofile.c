#include "io.h"

struct ofile ofile_table[MAX_OPEN_FILES];

int reg_ofile(struct vnode *vnode_p, enum file_mode mode) {
    int i = 0;
    int found_spot = -1;
    struct ofile *target;
    
    do {
        if (ofile_table[i].mode == MODE_NONE) {
            found_spot = i;
            break;
        }
    } while (i++ < MAX_OPEN_FILES - 1);
    
    if (found_spot < 0)
        return -1;
    
    target = ofile_table + found_spot;
    
    target->mode = mode;
    target->offset = 0;
    target->vnode_p = vnode_p;
    
    return found_spot;
}
