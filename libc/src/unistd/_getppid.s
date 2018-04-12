        .area	_CODE

_getppid::
        ld  hl, #04
        jp  __syscall
