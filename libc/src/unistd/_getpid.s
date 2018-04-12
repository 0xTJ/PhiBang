        .area	_CODE

_getpid::
        ld  hl, #03
        jp  __syscall
