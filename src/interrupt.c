#include "acia.h"

void interrupt() {
    unsigned short saved_proc_cur = proc_cur;
    unsigned short saved_proc_next = proc_next;
    proc_next = 0;
    proc_switch();
    acia_int();
}
