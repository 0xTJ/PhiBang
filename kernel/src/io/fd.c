#include "io.h"
#include "proc.h"

void reg_fd(int proc, int fd, int file_index) {
    if (proc < 0 || fd < 0 || file_index < 0)
        return;
    
    proc_table[proc].fd_table[fd] = ofile_table + file_index;
}
