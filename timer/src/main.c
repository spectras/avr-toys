#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sleep.h>

#include "config.h"
#include "io.h"
#include "segments.h"
#include "timers.h"

void wait(unsigned ms);

int main (void)
{
    PRR = (1<<PRTWI)
        | (1<<PRTIM0)
        | (1<<PRTIM1)
        | (1<<PRADC);

    PORT(BUTTON0)   |= (1 << BUTTON0_BIT);
    PORT(BUTTON1)   |= (1 << BUTTON1_BIT);

    segments_init();
    tick_init();
    sei();

    uint16_t x = 0;
    bool freeze_pressed = false;
    bool frozen = true;

    for(;;) {
        segments_set_value(x, 1);
        tick_wait(100, SLEEP_MODE_PWR_SAVE);

        if ((PIN(BUTTON1) & (1 << BUTTON1_BIT)) == 0) {
            if (!freeze_pressed) {
                frozen = !frozen;
            }
            freeze_pressed = true;
        } else {
            freeze_pressed = false;
        }

        if ((PIN(BUTTON0) & (1 << BUTTON0_BIT)) == 0) {
            x = 0;
        } else {
            if (!frozen) { x += 1; }
        }
    }
}
