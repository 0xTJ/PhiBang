        .area	_CODE

_fork:
        ld  hl, #02
        jp  __syscall
