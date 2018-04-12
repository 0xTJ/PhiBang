#include <unistd.h>
#include "proc.h"
#include "filesys.h"
#include "io.h"

int open(const char *path, int oflag/*, ...*/) {
    
}

size_t read(int fildes, void *buf, size_t nbyte) {
    struct ofile *filep;
    
    if (fildes < 0 || fildes >= RLIMIT_NOFILE || nbyte == 0 || buf == NULL)
        return 0;

    filep = proc_table[proc_cur].fd_table[fildes];
    if (filep == NULL)
        return 0;

    switch (filep->mode) {
    case MODE_READ:
    case MODE_READ_WRITE:
        {
            struct inode *inodep = filep->inodep;
            struct file_sys *fsp;
            size_t res;
            
            if (inodep == NULL)
                return 0;
            
            fsp = fs_tab[inodep->fs_num];
            if (fsp == NULL || fsp->inode_ops.read == NULL)
                return 0;
            
            res = fsp->inode_ops.write(inodep, buf, nbyte, filep->offset);
            if (res > 1)
                filep->offset += res;
            return res;
        }
    default:
        return 0;
    }
}

ssize_t write(int fildes, const void *buf, size_t nbyte) {
    struct ofile *filep;
    
    if (fildes < 0 || fildes >= RLIMIT_NOFILE || nbyte == 0 || buf == NULL)
        return 0;

    filep = proc_table[proc_cur].fd_table[fildes];
    if (filep == NULL)
        return 0;

    switch (filep->mode) {
    case MODE_WRITE:
    case MODE_READ_WRITE:
        {
            struct inode *inodep = filep->inodep;
            struct file_sys *fsp;
            ssize_t res;
            
            if (inodep == NULL)
                return 0;
            
            fsp = fs_tab[inodep->fs_num];
            if (fsp == NULL || fsp->inode_ops.write == NULL)
                return 0;
            
            res = fsp->inode_ops.write(inodep, buf, nbyte, filep->offset);
            if (res > 1)
                filep->offset += res;
            return res;
        }
    default:
        return 0;
    }
}

int mount(dev_t dev_num, char *path, int fs) {// USE FS NAMES, use dev path
    struct file_sys *fs = fs_tab[fs];
    if (fs == NULL)
        return -1;
    
    
}
