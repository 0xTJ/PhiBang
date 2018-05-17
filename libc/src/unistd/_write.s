    .module _write
    .area	_CODE

_write::
        ld      a, #0x06
        ld      bc, #0x0006
        jp      __syscall
