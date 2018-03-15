#ifndef _INCLUDE_PROC_H
#define _INCLUDE_PROC_H

#include "mem.h"
#include "io.h"
#include "constants.h"

#define TASK_MAX (8)

struct proc_desc {
    char status;
    size_t stack_size;
    void *stack_bottom;
    void *stack_pointer;
    struct ofile *fd_table[FOPEN_MAX];
};

extern int proc_next;
extern int proc_cur;
extern struct proc_desc proc_table[TASK_MAX];

void proc_init();
int proc_create(size_t stack_size, void (*entry)(void));
void proc_setup(int pid, void (*entry)(void));
void proc_delete(unsigned short pid);
void proc_switch();
void proc_exit();

#endif
