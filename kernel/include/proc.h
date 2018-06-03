#ifndef _INCLUDE_PROC_H
#define _INCLUDE_PROC_H

#include <sys/resource.h>
#include <unistd.h>
#include "fs.h"
#include "mem.h"

#define TASK_MAX (1 + 1)

struct ofile {
    int oflag;
    off_t offset;
    fs_node_t *node;
};

struct proc_desc {
    pid_t pid;

    void *mem;
    void *stack_pointer;

    fs_node_t *root;
    fs_node_t *pwd;

    struct ofile *ofile_tab[RLIMIT_NOFILE];
};

extern int proc_next;
extern int proc_cur;
extern struct proc_desc proc_table[];

void proc_init_enter1(void (*entry)(void));
void proc_post_setup(fs_node_t *root_node);
void proc_switch();

#endif
