	.area   _CODE

interrupt::
    di
    call    _interrupt_c
    ei
    reti
