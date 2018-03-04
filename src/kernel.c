#include <stdio.h>
#include "proc.h"

int a;

void test() {
    printf("test1-1");
    proc_next = 0;
    proc_switch();
    printf("test2-1");
}

void main() {
    printf("test0-0");
    proc_0_init();
    proc_next = proc_create(200, test);
    proc_switch();
    printf("test0-1");
    proc_next = 1;
    proc_switch();
    printf("test0-2");
    proc_next = 1;
    proc_switch();
    printf("test0-3");
}
