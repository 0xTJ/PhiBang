#include "proc.h"
#include <stdbool.h>
#include <string.h>
#include "io.h"
#include "mem.h"

int proc_cur = 0;
int proc_next = 0;
struct proc_desc proc_table[TASK_MAX];

volatile void (*tmp_entry)(void);
volatile void *tmp_stack_pointer;
volatile int tmp_pid;
volatile void *kernel_stack_pointer;

unsigned char proc_mem[RLIMIT_AS];

void proc_init_enter1(void (*entry)(void)) {
    int i, j;

    for (i = 0; i < TASK_MAX; i++) {
        proc_table[i].pid = 0;
        proc_table[i].stack_size = 0;
        proc_table[i].stack_bottom = NULL;
        proc_table[i].stack_pointer = NULL;
        proc_table[i].heap = NULL;
        proc_table[i].root = NULL;
        proc_table[i].pwd = NULL;
        for (j = 0; j < RLIMIT_NOFILE; j++)
            proc_table[i].fd_table[j] = NULL;
    }

    proc_table[1].pid = 1;

    proc_table[1].stack_size = RLIMIT_STACK;
    proc_table[1].stack_bottom = proc_mem + RLIMIT_AS - RLIMIT_STACK;
    proc_table[1].stack_pointer = proc_mem + RLIMIT_AS;

    proc_table[1].heap = (void *)proc_mem;
    proc_table[1].heap->size = proc_table[1].stack_bottom - get_block(proc_table[1].heap);
    proc_table[1].heap->next = NULL;
    proc_table[1].heap->free = true;

    proc_table[1].root = vfs_root;
    proc_table[1].pwd = vfs_root;

    for (i = 0; i < RLIMIT_NOFILE; i++)
        proc_table[1].fd_table[i] = NULL;

    proc_cur = 1;
    
    tmp_entry = entry;
    tmp_stack_pointer = proc_table[1].stack_pointer;

    __asm
    push    af
    push    bc
    push    de
    push    hl
    push    ix
    push    iy
    ld      (_kernel_stack_pointer), sp
    
    ld      sp, (_tmp_stack_pointer)
    ld      hl, #00001$
    push    hl
    ld      hl, (_tmp_entry)
    jp     (hl)

00001$:
    ld      sp, (_kernel_stack_pointer)
    pop     iy
    pop     ix
    pop     hl
    pop     de
    pop     bc
    pop     af
    
    __endasm;
}

void proc_switch() __critical {
    __asm
    push    af
    push    bc
    push    de
    push    hl
    push    ix
    push    iy
    ld      (_tmp_stack_pointer), sp
    __endasm;

    proc_table[proc_cur].stack_pointer = tmp_stack_pointer;
    tmp_stack_pointer = proc_table[proc_next].stack_pointer;

    __asm
    ld      sp, (_tmp_stack_pointer)
    pop     iy
    pop     ix
    pop     hl
    pop     de
    pop     bc
    pop     af
    __endasm;

    proc_cur = proc_next;
}
