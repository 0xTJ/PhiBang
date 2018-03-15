#include "constants.h"
#include "proc.h"
#include "acia.h"
#include <stdio.h>

void init() {
    reg_vnode(0, &acia_vnode);
    
    reg_ofile(0, 0, MODE_READ);
    reg_ofile(1, 0, MODE_WRITE);
    
    reg_fd(0, 0, 0);
    reg_fd(0, 1, 1);
    reg_fd(0, 2, 1);
}

void main() {
    char s[100];
    _setup_stdio();
    init();
    fputs("\x1b[30;107m", stdout);
    while (1) {
        fgets(s, 10, stdin);
        fputs(s, stdout);
    }
}
