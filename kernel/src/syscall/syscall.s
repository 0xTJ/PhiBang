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
    pop     de
    ld      (_sysc_ret), de
    call    enter_kernel

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
    ld      (buff), sp
    ld      sp, hl

    ld      hl, #_syscalls
    ld      c, a
    ld      b, #0

    add     hl, bc
    add     hl, bc          ; Address of address of syscall function in HL

    ld      e, (hl)
    inc     hl
    ld      d, (hl)         ; Address of syscall function in DE
    ld      hl, #10000$
    push    hl              ; Setup stack for pretend call
    ex      de, hl
    jp      (hl)            ; to syscall function

10000$:
    ld      sp, (buff)
    
    call    exit_kernel
    ld      de, (_sysc_ret)
    push    de

    reti

enter_kernel::
    ld      (buff), hl
    pop     hl
    ld      (_curr_sp), sp
    ld      sp, (_kern_sp)
    push    hl
    ld      hl, (buff)
    ret

exit_kernel::
    ld      (buff), hl
    pop     hl
    ld      (_kern_sp), sp
    ld      sp, (_curr_sp)
    push    hl
    ld      hl, (buff)
    ret

    .area _DATA

buff:       .blkb   2
_curr_sp::   .blkb   2
_kern_sp::   .blkb   2
_sysc_ret:: .blkb   2
