#ifndef _INCLUDE_PROC_H
#define _INCLUDE_PROC_H

#include <stddef.h>

#define TASK_MAX 4

struct proc_desc {
    unsigned char status;
    void (*entry)(void);
    size_t stack_size;
    void *stack_bottom;
    void *stack_pointer;
};

extern unsigned short int proc_next;
extern unsigned short int proc_cur;

void proc_0_init();
unsigned short int proc_create(size_t stack_size, void (*entry)(void));
void proc_delete(unsigned short id);
void proc_switch();
void proc_exit();

#endif  // NDEF _INCLUDE_PROC_H
