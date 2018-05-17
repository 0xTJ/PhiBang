        .module __exit
        .area   _CODE

__exit::
        ld      hl, #0x00
        jp      __syscall
