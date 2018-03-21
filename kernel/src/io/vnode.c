#include "io.h"
#include "mem.h"
#include "constants.h"

struct vnode vfs_root_s = {
    NULL,
    {0},
    NULL
};

struct vnode *vfs_root = &vfs_root_s;

int reg_vnode(struct vnode *parent, struct driver *driver_desc, int name/*, inode_t inode_num*/) {
    int i = 0;
    struct vnode *new_vnode;
    
    if (parent == NULL)
        return -1;  /* No parent given */
    
    if (name < 0 || name >= VNODE_CHILDREN)
        return -2;  /* Invalid name */
    
    if (parent->children[name] != NULL)
        return -3;  /* Name already used */
    
    new_vnode = alloc(sizeof(struct vnode), 0);
    
    if (new_vnode == NULL)
        return -4;  /* No space for vnode in RAM */
    
    parent->children[name] = new_vnode;
    
    if (driver_desc != NULL)
        new_vnode->driver = driver_desc;
    
    i = 0;
    do {
        new_vnode->children[i] = NULL;
    } while (i++ < VNODE_CHILDREN - 1);
    
    new_vnode->parent = parent;
    
    return name;
}
