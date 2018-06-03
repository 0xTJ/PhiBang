        .module __execvp
        .area   _CODE

__execvp::
        ld      a, #0x02
        ld      bc, #0x0004
        jp      __syscall
