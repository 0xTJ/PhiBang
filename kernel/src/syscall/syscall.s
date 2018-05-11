    .module syscall
    .area   _CODE

;   syscall
;   Kernel mode system call receiver
;   Passes system call information to function
;
;   Entry registers
;       A - Syscall number
;       BC - Parameters length
;       HL - Parameter stack address
;

syscall::
    call    enter_kernel

    push    af
    push    bc
    push    de
    push    hl
    push    hl
    ld      hl, #'['
    push    hl
    call    _kput
    pop     hl
    call    _kput_uint16
    pop     hl
    pop     hl
    pop     de
    pop     bc
    pop     af

    push    af
    push    bc
    push    de
    push    hl
    push    bc
    ld      hl, #']'
    push    hl
    call    _kput
    pop     hl
    call    _kput_uint16
    pop     bc
    pop     hl
    pop     de
    pop     bc
    pop     af

;; TODO: check for bc == 0
    add     hl, bc
    dec     hl
    ld      (buff), sp
    ld      de, (buff)
    dec     de
    ld      (buff), bc
    lddr
    ld      bc, (buff)
    inc     de
    ex      de, hl
    ld      sp, hl

    ld      hl, #_syscalls
    ld      c, a
    ld      b, #0

    push    af
    push    bc
    push    de
    push    hl
    push    bc
    ld      hl, #'{'
    push    hl
    call    _kput
    pop     hl
    call    _kput_uint16
    pop     bc
    pop     hl
    pop     de
    pop     bc
    pop     af

    add     hl, bc
    add     hl, bc          ; Address of address of syscall function in HL

    push    af
    push    bc
    push    de
    push    hl
    push    hl
    ld      hl, #'}'
    push    hl
    call    _kput
    pop     hl
    call    _kput_uint16
    pop     hl
    pop     hl
    pop     de
    pop     bc
    pop     af

    ld      e, (hl)
    inc     hl
    ld      d, (hl)         ; Address of syscall function in DE
    ld      hl, #10000$
    push    hl              ; Setup stack for pretend call
    ex      de, hl
    jp      (hl)            ; to syscall function

;; RESTORE STACK HERE

10000$:

    call    exit_kernel

    reti

enter_kernel::
    ld      (buff), hl
    pop     hl
    ld      (curr_sp), sp
    ld      sp, (kern_sp)
    push    hl
    ld      hl, (buff)
    ret

exit_kernel::
    ld      (buff), hl
    pop     hl
    ld      (kern_sp), sp
    ld      sp, (curr_sp)
    push    hl
    ld      hl, (buff)
    ret

    .area _DATA

buff:       .blkb   2

curr_sp::   .blkb   2
kern_sp::   .blkb   2
buff_hl:    .blkb   2
