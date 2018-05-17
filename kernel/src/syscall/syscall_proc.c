#include <unistd.h>
#include "proc.h"

int chdir(const char *path) {
    
}

pid_t getpid(void) {
    return proc_table[proc_cur].pid;
}

extern void *sysc_ret;
extern void *curr_sp;
extern fs_node_t *initrd_root;
int execvp(const char *file, char *const argv[]) {
    read_fs(_traverse_path(initrd_root, file), 0, 0x0800, (void *)0xA000);
    sysc_ret = 0xA000;
    curr_sp = 0xB000;
    argv;
}

void _exit(int status) {
    
}
