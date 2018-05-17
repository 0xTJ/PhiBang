        .module _getppid
        .area   _CODE

_getppid::
        ld      a, #0
        ld      bc, #0x0006
        jp      __syscall
