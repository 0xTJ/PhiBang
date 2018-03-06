#include "proc.h"
#include <stdlib.h>
    
unsigned short proc_count = 0;
unsigned short proc_cur = 0;
unsigned short proc_next = 0;
struct proc_desc proc_table[TASK_MAX];

const static volatile void *tmp_entry;
static volatile void *tmp_stack_pointer;
static volatile unsigned short tmp_id;

void proc_0_init() {
    if (proc_count == 0) {
        proc_table[0].status = 1;
        proc_table[0].entry = NULL;
        proc_count = 1;
    }
}

unsigned short proc_create(size_t stack_size, void (*entry)(void)) {
    void *stack_bottom;
    
    if (proc_count == 0)
        return -1;
    if (proc_count >= TASK_MAX - 1)
        return -2;
    
    for (tmp_id = 0; tmp_id < TASK_MAX; tmp_id++) {
        if (proc_table[tmp_id].status == 0)
            break;
    }
    if (tmp_id == TASK_MAX)
        return -3;
    
    stack_bottom = malloc(stack_size);
    if (stack_bottom == NULL)
        return -4;
    
    tmp_entry = entry;
    
    proc_table[tmp_id].status = 1;
    proc_table[tmp_id].stack_size = stack_size;
    proc_table[tmp_id].stack_bottom = stack_bottom;
    proc_table[tmp_id].stack_pointer = (void *)((char *)stack_bottom + stack_size - 1);
    
    __asm
    push    af
    push    bc
    push    de
    push    hl
    push    ix
    ld      (_tmp_stack_pointer), sp
    __endasm;
    
    proc_table[proc_cur].stack_pointer = tmp_stack_pointer;
    tmp_stack_pointer = proc_table[tmp_id].stack_pointer;
    
    __asm
    ld      sp, (_tmp_stack_pointer)
    ld      hl, #_proc_exit
    push    hl
    ld      hl, (_tmp_entry)
    push    hl
    ld      hl, #0
    push    hl
    push    hl
    push    hl
    push    hl
    push    hl
    ld      (_tmp_stack_pointer), sp
    __endasm;
    
    proc_table[tmp_id].stack_pointer = tmp_stack_pointer;
    tmp_stack_pointer = proc_table[proc_cur].stack_pointer;
    
    __asm
    ld      sp, (_tmp_stack_pointer)
    pop     ix
    pop     hl
    pop     de
    pop     bc
    pop     af
    __endasm;
    
    proc_count++;
    return tmp_id;
}

void proc_delete(unsigned short tmp_id) {
    proc_table[tmp_id].status = 0;
    free(proc_table[tmp_id].stack_bottom);
    proc_count--;
}

void proc_switch() {
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
}

void proc_exit() {
    proc_delete(proc_cur);
    
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
    
    proc_cur = proc_next;
}
