        .module _chdir
        .area   _CODE

_chdir::
        ld      a, #0x02
        ld      bc, #0x0006
        jp      __syscall
