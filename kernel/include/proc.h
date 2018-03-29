#ifndef _INCLUDE_PROC_H
#define _INCLUDE_PROC_H

#include <sys/resource.h>
#include <unistd.h>
#include "mem.h"

#define TASK_MAX (1 + 1)

struct proc_desc {
    pid_t pid;
    
    size_t stack_size;
    void *stack_bottom;
    void *stack_pointer;
    
    struct block_meta *heap;
    
    struct vnode *root;
    struct vnode *pwd;
    
    struct ofile *fd_table[RLIMIT_NOFILE];
};

extern int proc_next;
extern int proc_cur;
extern struct proc_desc proc_table[];

void proc_init_enter1(void (*entry)(void));
void proc_switch();

#endif
