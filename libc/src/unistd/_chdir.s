        .module _chdir
        .area   _CODE

_chdir::
        ld      a, #0x04
        ld      bc, #0x0002
        jp      __syscall
