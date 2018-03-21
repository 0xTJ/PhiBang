#include "proc.h"
#include <stdio.h>

int user_proc_count = 0;
int proc_cur = 0;
int proc_user_cur = 0;
int proc_next = 0;
struct proc_desc proc_table[TASK_MAX];

volatile void (*tmp_entry)(void);
volatile void *tmp_stack_pointer;
volatile int tmp_pid;

void proc_init() {
    int i = 0;
    do {
        proc_table[i].status = 0;
        i++;
    } while (i < TASK_MAX);

    proc_table[0].status = 1;
}

int proc_create(size_t stack_size, void (*entry)(void)) {
    void *stack_bottom;
    int pid;
    tmp_entry = entry;
    
    if (user_proc_count >= TASK_MAX - 1)
        return -1;
    
    for (pid = 0; pid < TASK_MAX; pid++) {
        if (proc_table[pid].status == 0)
            break;
    }
    if (pid == TASK_MAX)
        return -1;
    
    stack_bottom = alloc(stack_size, -2);
    if (stack_bottom == NULL)
        return -1;
    
    proc_table[pid].status = 1;
    proc_table[pid].stack_size = stack_size;
    proc_table[pid].stack_bottom = stack_bottom;
    proc_table[pid].stack_pointer = (void *)((char *)stack_bottom + stack_size - 1);
    
    proc_setup(pid, entry);
    
    user_proc_count++;
    return pid;
}

void proc_setup(int pid, void (*entry)(void)) __critical {
    tmp_pid = pid;
    tmp_entry = entry;
    
    __asm
    push    af
    push    bc
    push    de
    push    hl
    push    ix
    ld      (_tmp_stack_pointer), sp
    __endasm;
    
    proc_table[proc_cur].stack_pointer = tmp_stack_pointer;
    tmp_stack_pointer = proc_table[tmp_pid].stack_pointer;
    
    __asm
    ld      sp, (_tmp_stack_pointer)
    ld      hl, #_proc_exit
    push    hl
    ld      hl, (_tmp_entry)
    push    hl
    ld      hl, #0
    push    hl  ; Extra to accomodate __critical
    push    hl
    push    hl
    push    hl
    push    hl
    push    hl
    ld      (_tmp_stack_pointer), sp
    __endasm;
    
    proc_table[tmp_pid].stack_pointer = tmp_stack_pointer;
    tmp_stack_pointer = proc_table[proc_cur].stack_pointer;
    
    __asm
    ld      sp, (_tmp_stack_pointer)
    pop     ix
    pop     hl
    pop     de
    pop     bc
    pop     af
    __endasm;
}

void proc_switch() __critical {
    if (proc_table[proc_next].status == 0)
        return;

    __asm
    push    af
    push    bc
    push    de
    push    hl
    push    ix
    ld      (_tmp_stack_pointer), sp
    __endasm;
    
    proc_table[proc_cur].stack_pointer = tmp_stack_pointer;
    tmp_stack_pointer = proc_table[proc_next].stack_pointer;
    
    __asm
    ld      sp, (_tmp_stack_pointer)
    pop     ix
    pop     hl
    pop     de
    pop     bc
    pop     af
    __endasm;
    
    proc_cur = proc_next;
    if (proc_cur > 0)
        proc_user_cur = proc_cur;
}

void proc_exit() __critical {
    proc_next = 0;
    
    tmp_stack_pointer = proc_table[proc_next].stack_pointer;
    
    __asm
    ld      sp, (_tmp_stack_pointer)
    pop     ix
    pop     hl
    pop     de
    pop     bc
    pop     af
    __endasm;
    
    proc_delete(proc_cur);
    
    proc_cur = proc_next;
    proc_user_cur = -1;
}

void proc_delete(unsigned short pid) {
    /* close files */
    proc_table[pid].status = 0;
    free(proc_table[pid].stack_bottom);
    user_proc_count--;
}
