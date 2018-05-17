        .module __Exit
        .area   _CODE

__Exit::
        ld  hl, #0x00
        jp  __syscall
