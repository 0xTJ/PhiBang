#include <unistd.h>
#include "proc.h"
// #include "filesys.h"
// #include "io.h"

int open(const char *path, int oflag/*, ...*/) {
    return -1;
}

size_t read(int fildes, void *buf, size_t nbyte) {
    // struct ofile *filep;

    // if (fildes < 0 || fildes >= RLIMIT_NOFILE || nbyte == 0 || buf == NULL)
        // return 0;

    // filep = proc_table[proc_cur].fd_table[fildes];
    // if (filep == NULL)
        // return 0;

    // switch (filep->mode) {
    // case MODE_READ:
    // case MODE_READ_WRITE:
        // {
            // struct inode *inodep = filep->inodep;
            // struct file_sys *fsp;
            // size_t res;

            // if (inodep == NULL)
                // return 0;

            // fsp = fs_tab[inodep->fs_num];
            // if (fsp == NULL || fsp->inode_ops.read == NULL)
                // return 0;

            // res = fsp->inode_ops.write(inodep, buf, nbyte, filep->offset);
            // if (res > 1)
                // filep->offset += res;
            // return res;
        // }
    // default:
        return 0;
    // }
}

ssize_t write(int fildes, const void *buf, size_t nbyte) {
    // struct ofile *filep;

    // if (fildes < 0 || fildes >= RLIMIT_NOFILE || nbyte == 0 || buf == NULL)
        // return 0;

    // filep = proc_table[proc_cur].fd_table[fildes];
    // if (filep == NULL)
        // return 0;

    // switch (filep->mode) {
    // case MODE_WRITE:
    // case MODE_READ_WRITE:
        // {
            // struct inode *inodep = filep->inodep;
            // struct file_sys *fsp;
            // ssize_t res;

            // if (inodep == NULL)
                // return 0;

            // fsp = fs_tab[inodep->fs_num];
            // if (fsp == NULL || fsp->inode_ops.write == NULL)
                // return 0;

            // res = fsp->inode_ops.write(inodep, buf, nbyte, filep->offset);
            // if (res > 1)
                // filep->offset += res;
            // return res;
        // }
    // default:
        return -1;
    // }
}

void kprint(char *s);

int mount(dev_t dev_num, char *path, int fs_num) {// use dev path
    // struct file_sys *fsp;
    // struct inode *fs_root;
    // struct inode *mount_point;
    // uint8_t mnt_num;

    // fsp = fs_tab[fs_num];
    // if (fsp == NULL)
        return -1;

    // mount_point = follow_path(root_node, path); // close if anything was opened on later fail
    // if (mount_point == NULL) {
        // kprint("Mount path not found");
        // return -1;
    // }

    // if (mount_point->ext_mount != 0) {
        // kprint("Mount point already used");
        // return -1;
    // }

    // fs_root = alloc_inode();
    // if (fs_root == NULL)
        // return -1;

    // mnt_num = alloc_mount();
    // if (mnt_num == 0)
        // return -1;

    // mount_point->ext_mount = mnt_num;
    // mnt_tab[mnt_num].mount_point = mount_point;
    // mnt_tab[mnt_num].dev = dev_num;
    // mnt_tab[mnt_num].fs_root = fs_root;
    // mnt_tab[mnt_num].fs_num = fs_num;

    // fsp->fs_ops.mount(mnt_num);

    // {
        // char tmp[2] = { -1, '\0' };
        // kprint("Mounted device ");
        // tmp[0] = '0' + dev_num;
        // kprint(tmp);
        // kprint(" with fs ");
        // tmp[0] = '0' + mnt_num;
        // kprint(tmp);
        // kprint(" to \"");
        // kprint(path);
        // kprint("\".\n");
    // }

    // {
        // char tmp[2] = { -1, '\0' };
        // kprint("Mounted inode ");
        // tmp[0] = '0' + fs_root->ino;
        // kprint(tmp);
        // kprint(" of mount ");
        // tmp[0] = '0' + mnt_num;
        // kprint(tmp);
        // kprint(" to inode ");
        // tmp[0] = '0' + mnt_tab[mnt_num].mount_point->ino;
        // kprint(tmp);
        // kprint(" of mount ");
        // tmp[0] = '0' + mnt_tab[mnt_num].mount_point->mnt_num;
        // kprint(tmp);
        // kprint(".\n");
    // }
}
