#include <avr/io.h>
#include <tools/lcd1602.h>
#include <tools/shiftreg.h>
#include <tools/wait.h>
#include <stdbool.h>

#if VOLTAGE >= 5
#define ENABLE_DURATION 230
#elif VOLTAGE >= 3
#define ENABLE_DURATION 450
#else
#error  Unknown duration for ENABLE at this voltage
#endif

#define ENABLE_CYCLES   (ENABLE_DURATION/(1000000000/CLOCK))
#define STRINGIFY(x)    #x
#define INSERT(x)       STRINGIFY(x)


void lcd_init(const lcd1602_descriptor_t * lcd)
{
    lcd_send_command(lcd, LCD1602_CMD_FN | lcd->function | LCD1602_CMD_FN_8BIT);
    wait16(LCD1602_DELAY_CYCLES);
    lcd_send_command(lcd, LCD1602_CMD_CLEAR);
    wait32((15200000/(10000000000/CLOCK)));
    lcd_send_command(lcd, LCD1602_CMD_DISPLAY | LCD1602_CMD_DISPLAY_POWER);
    wait16(LCD1602_DELAY_CYCLES);
}

void lcd_send_command(const lcd1602_descriptor_t * lcd, uint8_t cmd)
{
    uint8_t dummy;
    shiftreg_send(&lcd->shiftreg, cmd);
    __asm__ volatile (
        "ld     __tmp_reg__, %a[port]\n\t"
        "or     __tmp_reg__, %[mask]\n\t"
        "st     %a[port], __tmp_reg__\n\t"
        "com    %[mask]\n\t"
        "and    __tmp_reg__, %[mask]\n\t"
        ".if " INSERT(ENABLE_CYCLES) " > 2\n\t"
        "nop\n\t"
        ".endif\n\t"
        ".if " INSERT(ENABLE_CYCLES) " > 3\n\t"
        "nop\n\t"
        ".endif\n\t"
        ".if " INSERT(ENABLE_CYCLES) " > 4\n\t"
        "nop\n\t"
        ".endif\n\t"
        ".if " INSERT(ENABLE_CYCLES) " > 5\n\t"
        "nop\n\t"
        ".endif\n\t"
        ".if " INSERT(ENABLE_CYCLES) " > 6\n\t"
        "nop\n\t"
        ".endif\n\t"
        ".if " INSERT(ENABLE_CYCLES) " > 7\n\t"
        "nop\n\t"
        ".endif\n\t"
        "st     %a[port], __tmp_reg__\n\t"
        : "=r" (dummy)
        : [port] "e" (lcd->shiftreg.port),
          [mask] "0" (lcd->shiftreg.output_bit)
        : "r0"
    );
}

void lcd_send_string(const lcd1602_descriptor_t * lcd, const char * str)
{
    *lcd->shiftreg.port |= lcd->register_bit;
    for (; *str != '\0'; str += 1) {
        lcd_send_command(lcd, *str);
        wait16(LCD1602_DELAY_CYCLES);
    }
    *lcd->shiftreg.port &= ~lcd->register_bit;
}

void lcd_define_char(const lcd1602_descriptor_t * lcd, char c,
                     const uint8_t * bitmap)
{
    uint8_t dots = ((lcd->function & LCD1602_CMD_FN_11DOTS) != 0) ? 11 : 8;
    c &= 0x07;

    lcd_send_command(lcd, LCD1602_CMD_MOVEC | (dots * c));
    wait16(LCD1602_DELAY_CYCLES);
    *lcd->shiftreg.port |= lcd->register_bit;
    for(int8_t x = dots; x >= 0; x -= 1, bitmap += 1) {
        lcd_send_command(lcd, *bitmap);
        wait16(LCD1602_DELAY_CYCLES);
    }
    *lcd->shiftreg.port &= ~lcd->register_bit;
    lcd_send_command(lcd, LCD1602_CMD_MOVED | 0x00);
    wait16(LCD1602_DELAY_CYCLES);
}
