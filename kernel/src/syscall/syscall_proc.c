#include <unistd.h>
#include "delrel.h"
#include "proc.h"
#include "mem.h"
#include "kio.h"

int chdir(const char *path) {
    path;
    return -1;
}

pid_t getpid(void) {
    return proc_table[proc_cur].pid;
}

extern void *sysc_ret;
extern void *curr_sp;
extern fs_node_t *initrd_root;
fs_node_t *_traverse_path(fs_node_t *cur, const char *path);
int execvp(const char *file, char *const argv[]) {
    struct drlHeader header;
    struct drlEntry *entries;
    fs_node_t *drlFd = _traverse_path(initrd_root, file);
    
    read_fs(drlFd, 0, sizeof(struct drlHeader), (void *)&header);
    entries = kmalloc(sizeof(struct drlEntry) * header.offLen);
    read_fs(drlFd, sizeof(struct drlHeader), sizeof(struct drlEntry) * header.offLen, (void *)entries);
    read_fs(drlFd, sizeof(struct drlHeader) + (sizeof(struct drlEntry) * header.offLen), 0x0800 - (sizeof(struct drlHeader) + sizeof(struct drlEntry) * header.offLen), (void *)0xA000);
    processDrl(&header, entries, (void *)0xA000, (void *)0xA800);
    sysc_ret = (void *)0xA000;
    curr_sp = (void *)0xB000;
    (void)argv;
    return -1;
}

void _exit(int status) {
    proc_table[proc_cur].pid = 0;
    (void)status;
}
