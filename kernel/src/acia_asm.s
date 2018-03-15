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
        ret

_acia_get::
waitch:
        in      a, (0x80)
        bit     0, a
        jr      z, waitch
        in      a, (0x81)
        ld      l, a
        ret
    