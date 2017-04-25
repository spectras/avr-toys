#include "config.h"

    .section .text.wait32,"ax",@progbits

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
