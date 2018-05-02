    .area   _CODE

__syscall::
    pop     de
    ld      (retaddr), de
    rst     0x30
    ld      de, (retaddr)
    push    de
    ret     nc              ; ok
    ld      (_errno), hl    ; error path
    ld      hl, #0xFFFF
    ret

    .area   _DATA

_errno::    .blkb   2
retaddr:  .blkb   2    
