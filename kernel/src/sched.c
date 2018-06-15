#include "sched.h"
#include "kio.h"
#include "proc.h"

extern void *curr_sp;
void sched(void) {
    KLOG(INFO, "Sched");
    
    proc_table[proc_cur].stack_pointer = curr_sp;
    proc_cur = 1;
    if (proc_table[proc_cur].pid == 0) {
        KLOG(ERROR, "Stopping failed");
        while (1);
    }
    curr_sp = proc_table[proc_cur].stack_pointer;
}
