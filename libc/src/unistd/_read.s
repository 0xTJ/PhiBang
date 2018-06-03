        .module _read
        .area   _CODE

_read::
        ld      a, #0x22
        ld      bc, #0x0006
        jp  __syscall
