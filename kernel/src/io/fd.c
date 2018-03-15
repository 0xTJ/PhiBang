#include "io.h"
#include "proc.h"
#include "constants.h"

void reg_fd(int proc, int fd, int file_index) {
    if (proc < 0 || fd < 0 || file_index < 0)
        return;
    
    proc_table[proc].fd_table[fd] = ofile_table + file_index;
    proc_table[proc].fd_table[fd]->ref_count++;
}

void dereg_fd(int proc, int fd) {
    if (proc < 0 || fd < 0)
        return;
    
    if (proc_table[proc].fd_table[fd] != NULL) {
        proc_table[proc].fd_table[fd]->ref_count--;
        
        /*  Uncomment these lines to automatically unmount when not referenced.
        if (proc_table[proc].fd_table[fd]->ref_count < 1)
            dereg_file_by_p(proc_table[proc].fd_table[fd]);
        */
        
        proc_table[proc].fd_table[fd] = NULL;
    }
}
