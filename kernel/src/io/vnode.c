#include "io.h"
#include "constants.h"

struct vnode vnode_table[16];

void reg_vnode(int vnode_index, struct vnode *driver_desc) {
    struct vnode *target = vnode_table + vnode_index;
    
    if (vnode_index < 0)
        return;
    
    target->type = driver_desc->type;
    target->size = driver_desc->size;
    target->ref_count = 0;
    target->put = driver_desc->put;
    target->get = driver_desc->get;
    target->control = driver_desc->control;
}

void dereg_vnode(int vnode_index) {
    struct vnode *target = vnode_table + vnode_index;
    
    if (vnode_index < 0)
        return;
    
    if (target->type != TYPE_NONE && target->ref_count == 0) {
        target->type = TYPE_NONE;
        target->size = 0;
        target->put = NULL;
        target->get = NULL;
        target->control = NULL;
    }
}

void dereg_vnode_by_p(struct vnode *target) {
    if (target == NULL)
        return;
    
    if (target->type != TYPE_NONE && target->ref_count == 0) {
        target->type = TYPE_NONE;
        target->size = 0;
        target->put = NULL;
        target->get = NULL;
        target->control = NULL;
    }
}
