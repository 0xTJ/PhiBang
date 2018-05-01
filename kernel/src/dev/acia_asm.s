	.module acia_asm
    .area   _CODE

_acia_init::
    ld      a, #0x96
    out     (0x80), a
    ret

_acia_put::
    pop     de
    pop     hl
    push    hl
    push    de
txbusy:
    in      a, (0x80)
    bit     1, a
    jr      z, txbusy
    ld      a, l
    out     (0x81), a
    ld      hl, #0
    ret

_acia_get::
    in      a, (0x80)
    bit     0, a
    jr      nz, gotchar
    ld      hl, #-1
    ret
gotchar:
    in      a, (0x81)
    ld      h, #0
    ld      l, a
    ret

_acia_get_wait::
waitch:
    in      a, (0x80)
    bit     0, a
    jr      z, waitch
    in      a, (0x81)
    ld      h, #0
    ld      l, a
    ret
