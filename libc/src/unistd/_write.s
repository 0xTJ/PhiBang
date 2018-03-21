        .area	_CODE

_write:
        ld  hl, #06
        jp  __syscall
