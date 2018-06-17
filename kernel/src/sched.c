#include "sched.h"
#include "kio.h"
#include "proc.h"

extern void *curr_sp;
void sched(void) {
    proc_table[proc_cur].stack_pointer = curr_sp;
    proc_cur = 1;
    if (proc_table[proc_cur].pid == 0) {
        KLOG(INFO, "Looping forever");
        while (1);
    }
    curr_sp = proc_table[proc_cur].stack_pointer;
}
