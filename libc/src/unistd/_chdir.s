        .module _chdir
        .area   _CODE

_chdir::
        ld  hl, #01
        jp  __syscall
