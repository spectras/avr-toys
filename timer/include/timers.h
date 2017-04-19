#ifndef TIMERS_H
#define TIMERS_H

#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>

typedef unsigned char timer_t;
typedef bool (*tick_handler_t)(void * ptr);

extern unsigned long _timer_current_ticks;

void tick_init();
void tick_stop();

unsigned long tick_get();
inline unsigned long tick_get_cli() { return _timer_current_ticks; }
void tick_wait(unsigned ms, uint8_t mode);


timer_t tick_register(unsigned period, tick_handler_t cb, void * ptr);
void tick_unregister(timer_t id);

#endif
