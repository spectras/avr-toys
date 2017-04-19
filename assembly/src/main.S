#include <avr/io.h>
#include "config.h"

OFF_DELAY   = 400 * CLOCK/1000 / 6
ON_DELAY    = 100 * CLOCK/1000 / 6


    .section .text

    .global main
main:
    sbi     _SFR_IO_ADDR(DDRB), PB5

    eor     r1, r1
    ldi     r20, 1

init_off:
    ldi     r16, (OFF_DELAY & 0x000000ff) >> 0
    ldi     r17, (OFF_DELAY & 0x0000ff00) >> 8
    ldi     r18, (OFF_DELAY & 0x00ff0000) >> 16
    ldi     r19, (OFF_DELAY & 0xff000000) >> 24

loop_off:
    sub     r16, r20         ; 1 cycle
    sbc     r17, r1          ; 1 cycle
    sbc     r18, r1          ; 1 cycle
    sbc     r19, r1          ; 1 cycle
    brne    loop_off         ; 2 cycles
    sbi     _SFR_IO_ADDR(PORTB), PB5

    ldi     r16, (ON_DELAY & 0x000000ff) >> 0
    ldi     r17, (ON_DELAY & 0x0000ff00) >> 8
    ldi     r18, (ON_DELAY & 0x00ff0000) >> 16
    ldi     r19, (ON_DELAY & 0xff000000) >> 24

loop_on:
    sub     r16, r20         ; 1 cycle
    sbc     r17, r1          ; 1 cycle
    sbc     r18, r1          ; 1 cycle
    sbc     r19, r1          ; 1 cycle
    brne    loop_on

    cbi     _SFR_IO_ADDR(PORTB), PB5
    jmp     init_off
