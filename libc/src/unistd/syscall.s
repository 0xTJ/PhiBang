    .area   _CODE

__syscall::
    rst 0x30
    ret nc              ; ok
    ld  (_errno), hl    ; error path
    ld  hl, #0xFFFF
    ret

    .area   _DATA

_errno::    .blkb    2
