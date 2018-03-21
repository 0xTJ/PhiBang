        .area   _CODE
        
; Stolen from Fuzix
__syscall:
        ex	(sp), hl        ; hl is now return addr
                            ; stack is syscall
		ex	de, hl          ; save return addr in de
		rst	0x30
		ex	de, hl          ; undo the magic
		ex	(sp), hl
		ex	de, hl          ; return with HL
		ret	nc              ; ok
		ld	(_errno), hl    ; error path
		ld	hl, #0xFFFF
		ret

		.area   _DATA

_errno:		.word	0
