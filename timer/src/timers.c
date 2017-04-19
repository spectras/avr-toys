#include <assert.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <util/atomic.h>
#include <stdint.h>
#include <stdlib.h>
#include "config.h"
#include "segments.h"
#include "timers.h"

/****************************************************************************/

#define CLOCK_RATIO (CLOCK / TICK_HZ)

#if CLOCK_RATIO < 256
#define PRESCALER   1
#define DIVIDER     CLOCK_RATIO

#elif CLOCK_RATIO < 256 * 8
#define PRESCALER   2
#define DIVIDER     CLOCK_RATIO/8

#elif CLOCK_RATIO < 256 * 8 * 4
#define PRESCALER   3
#define DIVIDER     CLOCK_RATIO/8/4

#elif CLOCK_RATIO < 256 * 8 * 4 * 2
#define PRESCALER   4
#define DIVIDER     CLOCK_RATIO/8/4/2

#elif CLOCK_RATIO < 256 * 8 * 4 * 2 * 2
#define PRESCALER   5
#define DIVIDER     CLOCK_RATIO/8/4/2/2

#elif CLOCK_RATIO < 256 * 8 * 4 * 2 * 2 * 2
#define PRESCALER   6
#define DIVIDER     CLOCK_RATIO/8/4/2/2/2

#elif CLOCK_RATIO < 256 * 8 * 4 * 2 * 2 * 2 * 4
#define PRESCALER   7
#define DIVIDER     CLOCK_RATIO/8/4/2/2/2/4

#else
#error TICK_HZ is too low for CLOCK
#endif

/****************************************************************************/

unsigned long _timer_current_ticks = 0;


void tick_init()
{
    // Reset timer
    TCCR2B  = 0;            // Disable clock source
    TIFR2   = 0xff;         // Acknowledge all interrupts

    // Configure timings
    TCCR2A  = (1<<WGM21);   // Set CTC mode
    OCR2A   = DIVIDER;      // Set CTC max value
    TIMSK2  = (1<<OCIE2A);  // Timer will generate interrupts on comparator A match
    GTCCR   = (1<<PSRASY);  // Reset prescaler

    // Start timer
    TCNT2   = 0;            // Reset timer
    TCCR2B  = PRESCALER;    // Set prescaler factor and enable timer
}

void tick_stop()
{
    TCCR2B = 0;             // Disable clock
}

unsigned long tick_get()
{
    unsigned long value;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        value = _timer_current_ticks;
    }
    return value;
}

void tick_wait(unsigned ms, uint8_t mode)
{
    unsigned long until = tick_get() + (unsigned long)ms;
    set_sleep_mode(mode);
    sleep_enable();
    do {
        sleep_cpu();
    } while (tick_get() < until);
    sleep_disable();
}

/****************************************************************************/

ISR(TIMER2_COMPA_vect) {
    _timer_current_ticks += 1000/TICK_HZ;
    segments_show_next();
}
