#include "proc.h"
#include <stdlib.h>
#include <string.h>
    
int user_proc_count = 0;
int proc_cur = 0;
int proc_next = 0;
struct proc_desc proc_table[TASK_MAX];

const static volatile void *_tmp_entry;
static volatile void *_tmp_stack_pointer;
static volatile int _tmp_pid;

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
    
    if (user_proc_count >= TASK_MAX - 1)
        return -1;
    
    for (pid = 0; pid < TASK_MAX; pid++) {
        if (proc_table[pid].status == 0)
            break;
    }
    if (pid == TASK_MAX)
        return -1;
    
    stack_bottom = malloc(stack_size);
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
    _tmp_pid = pid;
    _tmp_entry = entry;
    
    __asm
    push    af
    push    bc
    push    de
    push    hl
    push    ix
    ld      (__tmp_stack_pointer), sp
    __endasm;
    
    proc_table[proc_cur].stack_pointer = _tmp_stack_pointer;
    _tmp_stack_pointer = proc_table[_tmp_pid].stack_pointer;
    
    __asm
    ld      sp, (__tmp_stack_pointer)
    ld      hl, #_proc_exit
    push    hl
    ld      hl, (__tmp_entry)
    push    hl
    ld      hl, #0
    push    hl
    push    hl
    push    hl
    push    hl
    push    hl
    ld      (__tmp_stack_pointer), sp
    __endasm;
    
    proc_table[_tmp_pid].stack_pointer = _tmp_stack_pointer;
    _tmp_stack_pointer = proc_table[proc_cur].stack_pointer;
    
    __asm
    ld      sp, (__tmp_stack_pointer)
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
    ld      (__tmp_stack_pointer), sp
    __endasm;
    
    proc_table[proc_cur].stack_pointer = _tmp_stack_pointer;
    _tmp_stack_pointer = proc_table[proc_next].stack_pointer;
    
    __asm
    ld      sp, (__tmp_stack_pointer)
    pop     ix
    pop     hl
    pop     de
    pop     bc
    pop     af
    __endasm;
    
    proc_cur = proc_next;
}

void proc_exit() __critical {
    proc_next = 0;
    
    _tmp_stack_pointer = proc_table[proc_next].stack_pointer;
    
    __asm
    ld      sp, (__tmp_stack_pointer)
    pop     ix
    pop     hl
    pop     de
    pop     bc
    pop     af
    __endasm;
    
    proc_delete(proc_cur);
    
    proc_cur = proc_next;
}

void proc_delete(unsigned short pid) {
    /* close files */
    proc_table[pid].status = 0;
    free(proc_table[pid].stack_bottom);
    user_proc_count--;
}
