        .area	_CODE

_read::
        ld  hl, #05
        jp  __syscall
