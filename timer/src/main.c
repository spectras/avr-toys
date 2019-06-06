#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <string.h>

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

    DDR(BUTTON0)    &= ~(1 << BUTTON0_BIT); /* make it input */
    DDR(BUTTON1)    &= ~(1 << BUTTON1_BIT); /* make it input */
    PORT(BUTTON0)   |= (1 << BUTTON0_BIT);  /* enable pull-up resistor */
    PORT(BUTTON1)   |= (1 << BUTTON1_BIT);  /* enable pull-up resistor */
    CLKPR = 0x80;                           /* reset clock prescaler */
    CLKPR = 0x06;                           /* set clock prescaler to 64 */

    segments_init();
    tick_init();
    sei();

    uint8_t x[4] = {0, 0, 0, 0};
    bool freeze_pressed = false;
    bool frozen = true;

    for(;;) {
        segments_set_figures(x, 1);
        tick_wait(100, SLEEP_MODE_IDLE);

        if ((PIN(BUTTON1) & (1 << BUTTON1_BIT)) == 0) {
            if (!freeze_pressed) {
                frozen = !frozen;
            }
            freeze_pressed = true;
        } else {
            freeze_pressed = false;
        }

        if ((PIN(BUTTON0) & (1 << BUTTON0_BIT)) == 0) {
            memset(x, 0, sizeof(x));
        } else {
            if (!frozen) {
                if (++x[0] == 10) {
                    x[0] = 0;
                    if (++x[1] == 10) {
                        x[1] = 0;
                        if (++x[2] == 10) {
                            x[2] = 0;
                            if (++x[3] == 10) {
                                x[3] = 0;
                            }
                        }
                    }
                }
            }
        }
    }
}
