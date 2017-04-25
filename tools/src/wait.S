#include "config.h"

    .section .text.waitx,"ax",@progbits

    .global wait16

wait16:
    movw    r22, r24
    clr     r24
    clr     r25
    ;rjmp    wait32          ; implicit

    .global wait32

wait32:
    ldi     r18, 6           ; 6 cycles per iteration
.Lwait32_loop:
    sub     r22, r18         ; 1 cycle
    sbc     r23, r1          ; 1 cycle
    sbc     r24, r1          ; 1 cycle
    sbc     r25, r1          ; 1 cycle
    brcc    .Lwait32_loop     ; 2 cycles
    ret
