#include "constants.h"
#include "proc.h"
#include "acia.h"
#include <stdio.h>

extern void (*sosh_main)(void);

void init() {
    reg_vnode(0, &acia_vnode);
    
    reg_ofile(0, 0, MODE_READ);
    reg_ofile(1, 0, MODE_WRITE);
    
    reg_fd(0, 0, 0);
    reg_fd(0, 1, 1);
    reg_fd(0, 2, 1);
}

void main() {
    char s[10];
    int sosh_pid = -1;

    _setup_stdio();
    init();
    
    puts("START\n");
    
    sosh_pid = proc_create(100, (void *)&sosh_main);
    
    reg_fd(sosh_pid, 0, 0);
    reg_fd(sosh_pid, 1, 1);
    reg_fd(sosh_pid, 2, 1);
    
    proc_next = sosh_pid;
    proc_switch();
    
    puts("HALT\n");
}
