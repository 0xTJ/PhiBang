#include "proc.h"
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "kio.h"
#include "mem.h"

int proc_cur = 0;
struct proc_desc proc_table[TASK_MAX];

volatile void (*tmp_entry)(void);
volatile void *tmp_stack_pointer;
volatile int tmp_pid;
volatile void *tmp_stack;
volatile uint8_t tmp_stack_num;
extern void *kern_sp;

extern unsigned char proc_mem[RLIMIT_AS];

void proc_init_enter1(void (*entry)(void)) {
    int i, j;

    for (i = 0; i < TASK_MAX; i++) {
        proc_table[i].pid = 0;
        proc_table[i].mem = NULL;
        proc_table[i].stack_pointer = NULL;
        proc_table[i].root = NULL;
        proc_table[i].pwd = NULL;
        for (j = 0; j < RLIMIT_NOFILE; j++)
            proc_table[i].ofile_tab[j] = NULL;
    }

    proc_table[1].pid = 1;

    proc_table[1].mem = proc_mem;
    proc_table[1].stack_pointer = proc_mem + RLIMIT_AS;

    proc_cur = 1;

    tmp_entry = entry;
    tmp_stack_pointer = proc_table[1].stack_pointer;

    __asm
    push    af
    push    bc
    push    de
    push    hl
    push    iy
    ld      (_kern_sp), sp

    ld      sp, (_tmp_stack_pointer)
    ld      hl, #00001$
    push    hl
    ld      hl, (_tmp_entry)
    jp     (hl)

00001$:
    ld      sp, (_kern_sp)
    pop     iy
    pop     hl
    pop     de
    pop     bc
    pop     af
    __endasm;

    proc_table[1].pid = 0;
}

void proc_post_setup(fs_node_t *root_node) {
    proc_table[1].root = root_node;
    proc_table[1].pwd = root_node;
}

void save_curr_sp() __critical {
    proc_table[proc_cur].stack_pointer = tmp_stack_pointer;
}

void load_curr_sp() __critical {
    tmp_stack_pointer = proc_table[proc_cur].stack_pointer;

    __asm
    ld      sp, (_tmp_stack_pointer)
    __endasm;
}
