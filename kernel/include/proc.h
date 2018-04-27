#ifndef _INCLUDE_PROC_H
#define _INCLUDE_PROC_H

#include <sys/resource.h>
#include <unistd.h>
#include "fs.h"
#include "mem.h"

#define TASK_MAX (1 + 1)

enum file_mode { MODE_NONE = 0, MODE_READ, MODE_WRITE, MODE_READ_WRITE };

struct ofile {
    enum file_mode mode;
    off_t offset;
    fs_node_t *node;
};

struct proc_desc {
    pid_t pid;
    
    size_t stack_size;
    void *stack_bottom;
    void *stack_pointer;
    
    struct block_meta *heap;
    
    struct ofile *root;
    struct ofile *pwd;
    
    struct ofile *ofile_tab[RLIMIT_NOFILE];
};

extern int proc_next;
extern int proc_cur;
extern struct proc_desc proc_table[];

void proc_init_enter1(void (*entry)(void));
void proc_switch();

#endif
