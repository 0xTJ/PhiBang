#include <unistd.h>
#include <fcntl.h>
#include "proc.h"
#include "kio.h"
#include "fs.h"

fs_node_t *_traverse_path(fs_node_t *cur, const char *path) {
    do {
        if (cur->flags & FS_MOUNTPOINT)
            cur = cur->ptr;
        else {
            char chunk[16];
            char *chunk_mid = chunk;
            path++;
            while (*path != '/' && *path != '\0')
                *chunk_mid++ = *path++;
            *chunk_mid = '\0';

            cur = finddir_fs(cur, chunk);
        }
    } while (cur != NULL && *path != NULL);
    
    while (cur && cur->flags & FS_MOUNTPOINT)
        cur = cur->ptr;
    
    return cur;
}

int open(const char *path, int oflag, ...) {
    fs_node_t *cur;
    int fd = 0;
    
    cur = _traverse_path(fs_root, path);
    if (cur == NULL)
        return -1;
    
    open_fs(cur, 1, 1);

    do {
        if (proc_table[proc_cur].ofile_tab[fd] == NULL)
            break;
        fd++;
    } while (fd < RLIMIT_NOFILE - 1);
    
    if (fd >= RLIMIT_NOFILE - 1)
        return -1;
    
    proc_table[proc_cur].ofile_tab[fd] = kmalloc(sizeof(struct ofile));
    proc_table[proc_cur].ofile_tab[fd]->oflag = oflag;
    proc_table[proc_cur].ofile_tab[fd]->offset = 0;
    proc_table[proc_cur].ofile_tab[fd]->node = cur;
    
    return fd;
}

int close(int fildes) {
    close_fs(proc_table[proc_cur].ofile_tab[fildes]->node);
    kfree(proc_table[proc_cur].ofile_tab[fildes]);
    proc_table[proc_cur].ofile_tab[fildes] = NULL;
    return 0;
}

size_t read(int fildes, void *buffer, size_t nbyte) {
    struct ofile *filep;

    if (fildes < 0 || fildes >= RLIMIT_NOFILE || nbyte == 0 || buffer == NULL)
        return 0;

    filep = proc_table[proc_cur].ofile_tab[fildes];
    if (filep == NULL)
        return 0;

    if (filep->oflag & O_ACCMODE & O_RDWR || filep->oflag & O_ACCMODE & O_RDONLY) {
        fs_node_t *node = filep->node;
        size_t res;

        if (node == NULL)
            return 0;

        res = read_fs(node, filep->offset, nbyte, buffer);
        if (filep->offset > 0)
            filep->offset += res;
        return res;
    } else {
        return 0;
    }
}

ssize_t write(int fildes, const void *buffer, size_t nbyte) {
    struct ofile *filep;
    
    if (fildes < 0 || fildes >= RLIMIT_NOFILE || nbyte == 0 || buffer == NULL)
        return -1;

    filep = proc_table[proc_cur].ofile_tab[fildes];
    if (filep == NULL)
        return -1;

    if (filep->oflag & O_ACCMODE & O_RDWR || filep->oflag & O_ACCMODE & O_WRONLY) {
        fs_node_t *node = filep->node;
        size_t res;

        if (node == NULL)
            return 0;

        res = write_fs(node, filep->offset, nbyte, buffer);
        if (filep->offset > 0)
            filep->offset += res;
        return res;
    } else {
        return -1;
    }
}

int mount(char *device, char *path, int fs_num) {// use dev path
    (void)device; (void)path; (void)fs_num;
    return -1;
}
