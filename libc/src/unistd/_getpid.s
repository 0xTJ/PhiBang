        .module _getpid
        .area   _CODE

_getpid::
        ld      a, #0
        ld      bc, #0x0006
        jp      __syscall
