	.area   _CODE

interrupt::
    di
    call    _interrupt
    ei
    reti
