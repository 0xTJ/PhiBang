        .module __exit
        .area   _CODE

__exit::
        ld      a, #0x00
        ld      bc, #0x0002
        jp      __syscall
