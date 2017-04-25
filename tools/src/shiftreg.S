#include <avr/io.h>
#include "config.h"

    .section .text.shiftreg,"ax",@progbits

    .global shiftreg_send

data_mask = 18
data_mask_inv = 19
strobe_mask = 20
strobe_mask_inv = 21
value = 22
port_value = 23
counter = 26

    ; Total cycles => (3 for rcall) + 12 + 91 + 4 = 110
    ; r24-r25  => reg
    ; r22 => value
shiftreg_send:
    movw    r30, r24                        ; Z points at reg descriptor
    ld      r24, Z+
    ld      r25, Z+
    ld      data_mask, Z+
    ld      strobe_mask, Z+
    movw    r30, r24                        ; Z points at IO port
    mov     data_mask_inv, data_mask
    com     data_mask_inv
    mov     strobe_mask_inv, strobe_mask
    com     strobe_mask_inv
    ld      port_value, Z
    ldi     counter, 8

.Lshiftreg_loop:
    ; Output data bit - 5*8 cycles
    sbrs    value, 7
    and     port_value, data_mask_inv       ; 0 out data bit if carry clear
    sbrc    value, 7
    or      port_value, data_mask           ; set data bit if carry set
    st      Z, port_value                   ; write data bit

    ; Generate rising edge on strobe
    or      port_value, strobe_mask         ; 8
    st      Z, port_value                   ; 8

    ; Restore strobe and loop
    and     port_value, strobe_mask_inv     ; 8
    lsl     value                           ; 8  ; move next bit into bit 7
    dec     counter                         ; 8
    st      Z, port_value                   ; 8
    brne    .Lshiftreg_loop                 ; 15

    ret
