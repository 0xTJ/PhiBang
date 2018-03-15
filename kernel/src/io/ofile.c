#include "io.h"
#include "constants.h"

struct ofile ofile_table[16];

void reg_ofile(int file_index, int vnode_index, enum file_mode mode) {
    struct ofile *target = ofile_table + file_index;
    
    if (file_index < 0 || vnode_index < 0)
        return;
    
    target->mode = mode;
    target->offset = 0;
    target->vnode_p = vnode_table + vnode_index;
    target->ref_count = 0;
    target->vnode_p->ref_count++;
}

void dereg_ofile(int file_index) {
    struct ofile *target = ofile_table + file_index;
    
    if (file_index < 0)
        return;
    
    if (target->mode != MODE_NONE && target->ref_count == 0) {
        target->mode = MODE_NONE;
        target->offset = 0;
        target->vnode_p->ref_count--;
        
        /*
        if (target->vnode_p->ref_count < 1)
            dereg_vnode_by_p(target->vnode_p);
        */
        
        target->vnode_p = NULL;
    }
}

void dereg_ofile_by_p(struct ofile *target) {
    if (target->mode != MODE_NONE && target->ref_count == 0) {
        target->mode = MODE_NONE;
        target->offset = 0;
        target->vnode_p->ref_count--;
        
        /*  Uncomment these lines to automatically unmount when not referenced.
        if (target->vnode_p->ref_count < 1)
            dereg_vnode_by_p(target->vnode_p);
        */
        
        target->vnode_p = NULL;
    }
}
