#include "proc.h"
#include "io.h"
#include "acia.h"

void test1(void) {
    __asm
    push AF
    ld      A, #10
    out     (10), A
    pop AF
    __endasm;
    proc_next = 0;
    proc_switch();
    proc_exit();
    __asm
    push AF
    ld      A, #12
    out     (12), A
    pop AF
    __endasm;
}

int main() {
    char tmp[10];
    fd_table[0] = &acia_driver;
    
    proc_next = proc_create(30, test1);
    proc_switch();
    __asm
    push AF
    ld      A, #11
    out     (11), A
    pop AF
    __endasm;
    proc_next = 1;
    proc_switch();
    __asm
    push AF
    ld      A, #13
    out     (13), A
    pop AF
    __endasm;
    proc_next = 1;
    proc_switch();
    __asm
    push AF
    ld      A, #14
    out     (14), A
    pop AF
    __endasm;
    
    
    while (1) {
        acia_read(tmp, 1);
        acia_write(tmp, 1);
    }
    
    return 0;
}
