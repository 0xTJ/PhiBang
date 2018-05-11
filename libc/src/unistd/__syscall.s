    .module __syscall
    .area   _CODE

;   __syscall
;   User mode system caller
;   Passes address to parameter stack address and syscall number in HL and A respectively
;
;   Entry registers
;       BC - Parameters length
;       A - Syscall number
;
;   Return registers
;       HL - 0 on success, -1 on error

__syscall::
    pop     hl
    ld      (retaddr), hl   ; Store return address for later

    sbc     hl, hl          ; Load SP to HL, is independent of carry
    adc     hl, sp          ; because CY is subtracted then added back

    rst     0x30            ; Do syscall with syscall number in A, params. length in BC,
                            ; and stack params addr. in HL

    ld      de, (retaddr)   ; Put return addr. back on stack
    push    de

    ret     nc              ; Return with no error
    ld      (_errno), hl    ; Error path
    ld      hl, #0xFFFF     ; Return -1
    ret

    .area   _DATA

_errno::    .blkb   2       ; Global error value for syscalls
retaddr:    .blkb   2       ; Temporary address to return after syscall
