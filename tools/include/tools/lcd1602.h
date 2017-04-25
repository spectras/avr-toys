#ifndef TOOLS_LCD1602_H
#define TOOLS_LCD1602_H

#include <tools/shiftreg.h>
#include "config.h"

typedef struct lcd1602_descriptor {
    shiftreg_descriptor_t   shiftreg;
    uint8_t                 register_bit;   /**< As bitmask in shiftreg.port */
    uint8_t                 function;       /**< Or of LCD1602_CMD_FN_* flags */
} lcd1602_descriptor_t;


void lcd_init(const lcd1602_descriptor_t * lcd);
void lcd_send_command(const lcd1602_descriptor_t * lcd, uint8_t cmd);
void lcd_send_string(const lcd1602_descriptor_t * lcd, const char * str);
void lcd_define_char(const lcd1602_descriptor_t * lcd, char c,
                     const uint8_t * bitmap);

inline void lcd_moveto(const lcd1602_descriptor_t * lcd, uint8_t line, uint8_t col);


/* Timing information for 5V:
 * RS + RW delay: 40ns                  <= 1 cycles@16MHz
 * ENABLE duration: 230ns               <= 4 cycles@16MHz
 * post-ENABLE: 10ns                    <= 1 cycles@16MHz
 * no more than 1 enable every 500ns    <= 8 cycles@16MHz
 *
 * Timing information for 3.3V
 * RS + RW delay: 60ns                  <=  1 cycles@16MHz
 * ENABLE duration: 450ns               <=  8 cycles@16MHz
 * post-ENABLE: 20ns                    <=  1 cycles@16MHz
 * no more than 1 enable every 1000ns   <= 16 cycles@16MHz
 *
 *  command delay:
 *     37us for all commands            <=   592 cycles@16MHz
 *   1520us for CLEAR and HOME          <= 24320 cycles@16MHz
 */
#if (370000/(10000000000/CLOCK) - 110) > 0
#define LCD1602_DELAY_CYCLES    (370000/(10000000000/CLOCK) - 110)
#else
#define LCD1602_DELAY_CYCLES    0
#endif

#define LCD1602_CMD_CLEAR   0x01
#define LCD1602_CMD_HOME    0x02

#define LCD1602_CMD_MODE    0x04
#define LCD1602_CMD_MODE_SHIFT      (1<<0)
#define LCD1602_CMD_MODE_LTR        (1<<1)

#define LCD1602_CMD_DISPLAY 0x08
#define LCD1602_CMD_DISPLAY_POS     (1<<0)
#define LCD1602_CMD_DISPLAY_CURSOR  (1<<1)
#define LCD1602_CMD_DISPLAY_POWER   (1<<2)

#define LCD1602_CMD_SHIFT   0x10
#define LCD1602_CMD_SHIFT_LEFT      (0<<2)
#define LCD1602_CMD_SHIFT_RIGHT     (1<<2)
#define LCD1602_CMD_SHIFT_CURSOR    (1<<3)

#define LCD1602_CMD_FN      0x20
#define LCD1602_CMD_FN_8BIT         (1<<4)
#define LCD1602_CMD_FN_2LINE        (1<<3)
#define LCD1602_CMD_FN_11DOTS       (1<<2)

#define LCD1602_CMD_MOVEC   0x40
#define LCD1602_CMD_MOVEC_ADDR      0x3f

#define LCD1602_CMD_MOVED   0x80
#define LCD1602_CMD_MOVED_ADDR      0x7f

inline void lcd_moveto(const lcd1602_descriptor_t * lcd, uint8_t line, uint8_t col) {
    lcd_send_command(lcd, LCD1602_CMD_MOVED | (line * 0x40 + col));
}

#endif
