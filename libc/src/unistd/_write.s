    .module _write
    .area	_CODE

_write::
        ld      bc, #0x0006
        ld      a, #0x06
        jp      __syscall
