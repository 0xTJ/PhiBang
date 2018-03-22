#include <unistd.h>

int chdir(const char *path) {
    
}

pid_t getpid(void) {
    return proc_table[proc_cur].pid;
}
