	.module crt0
	.globl	_main

init:
    call    gsinit
    call    _main
exit:
    call    (__exit)
    jr      (exit)

	;; Ordering of segments for the linker.
	.area	_HOME
	.area	_CODE
	.area	_INITIALIZER
	.area   _GSINIT
	.area   _GSFINAL

	.area	_DATA
    .ds 240
	.area	_INITIALIZED
	.area	_BSEG
	.area   _BSS
	.area   _HEAP
    
	.area   _GSINIT
gsinit::
	ld	bc, #l__INITIALIZER
	ld	a, b
	or	a, c
	jr	Z, gsinit_next
	ld	de, #s__INITIALIZED
	ld	hl, #s__INITIALIZER
	ldir
gsinit_next:

	.area   _GSFINAL
	ret
