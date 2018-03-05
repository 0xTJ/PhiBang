#ifndef _INCLUDE_PROC_H
#define _INCLUDE_PROC_H

#include <stdint.h>
#include <stddef.h>

#define TASK_MAX 4

struct proc_desc {
    uint8_t status;
    void (*entry)(void);
    size_t stack_size;
    void *stack_bottom;
    void *stack_pointer;
};

extern int16_t proc_next;
extern int16_t proc_cur;

void proc_0_init();
int16_t proc_create(size_t stack_size, void (*entry)(void));
void proc_delete(uint8_t id);
void proc_switch();
void proc_exit();

#endif  // NDEF _INCLUDE_PROC_H
