#ifndef _INCLUDE_PROC_H
#define _INCLUDE_PROC_H

#include <stddef.h>
#include <stdio.h>

#define TASK_MAX (8)

struct proc_desc {
    unsigned char status;
    size_t stack_size;
    void *stack_bottom;
    void *stack_pointer;
    FILE *streams[FOPEN_MAX];
};

extern unsigned short int proc_next;
extern unsigned short int proc_cur;

void proc_init();
void wipe_proc(struct proc_desc *desc);
unsigned short int proc_create(size_t stack_size, void (*entry)(void));
void proc_delete(unsigned short id);
void proc_switch();
void proc_exit();

#endif
