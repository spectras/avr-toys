#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay_basic.h>
#include <tools/lcd1602.h>
#include <tools/wait.h>
#include <string.h>

#include "config.h"

const lcd1602_descriptor_t screen = {
    {
        &PORTD,
        1 << SHIFTER_DATA_BIT,
        1 << SHIFTER_STROBE_BIT,
        1 << SHIFTER_OUTPUT_BIT
    },
    1 << SCREEN_RS_BIT,
    LCD1602_CMD_FN_2LINE
};

int main (void)
{
    PRR = (1<<PRTWI)
        | (1<<PRTIM0)
        | (1<<PRTIM1)
        | (1<<PRADC);

    DDRB = (1<<5);
    DDRD = 0xf0;
    PORTB = 0x00;
    PORTD = 0x00;

    wait16(LCD1602_DELAY_CYCLES);

    lcd_init(&screen);
    lcd_send_string(&screen, "Hello, Sophie!");

    lcd_moveto(&screen, 1, 0);
    wait16(LCD1602_DELAY_CYCLES);
    lcd_send_string(&screen, "Ca va?");

    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
}
