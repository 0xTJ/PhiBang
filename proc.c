#include "proc.h"
#include <stdlib.h>
#include <stdio.h>
    
int16_t proc_count = 0;
int16_t proc_cur = 0;
int16_t proc_next = 0;
struct proc_desc proc_table[TASK_MAX];

const static volatile void *tmp_entry;
static volatile void *tmp_stack_pointer;

void proc_0_init() {
    if (proc_count == 0) {
        proc_table[0].status = 1;
        proc_table[0].entry = NULL;
        proc_count = 1;
    }
}

int16_t proc_create(size_t stack_size, void (*entry)(void)) {
    uint8_t *stack_bottom;
    int16_t id;
    
    if (proc_count == 0)
        return -1;
    if (proc_count >= TASK_MAX - 1)
        return -2;
    
    for (id = 0; id < TASK_MAX; id++) {
        if (proc_table[id].status == 0)
            break;
    }
    if (id == TASK_MAX)
        return -3;
    
    stack_bottom = malloc(stack_size);
    if (stack_bottom == NULL)
        return -4;
    
    tmp_entry =     entry;
    
    proc_table[id].status = 1;
    proc_table[id].stack_size = stack_size;
    proc_table[id].stack_bottom = stack_bottom;
    proc_table[id].stack_pointer = stack_bottom + stack_size - 1;
    
    __asm
    push    af
    push    bc
    push    de
    push    hl
    push    ix
    ld      (_tmp_stack_pointer), sp
    __endasm;
    
    proc_table[proc_cur].stack_pointer = tmp_stack_pointer;
    tmp_stack_pointer = proc_table[id].stack_pointer;
    
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
    
    proc_table[id].stack_pointer = tmp_stack_pointer;
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
    return id;
}

void proc_delete(uint8_t id) {
    proc_table[id].status = 0;
    free(proc_table[id].stack_bottom);
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
