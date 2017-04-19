#ifndef IO_H
#define IO_H

#include <avr/io.h>
#define PIN(code)   (*(&PINB + 3*(code-2)))
#define DDR(code)   (*(&DDRB + 3*(code-2)))
#define PORT(code)  (*(&PORTB + 3*(code-2)))

#endif
