    .module syscall
    .area   _CODE

syscall::
    ld      de, #_syscalls
    add     hl, hl
    add     hl, de
    ld      e, (hl)
    inc     hl
    ld      d, (hl)
    push    de
    reti
