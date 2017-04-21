#include <avr/io.h>
#include <tools/math.h>
#include "config.h"
#include "io.h"
#include "segments.h"

// Externally-demuliplexed segments
//  => use 4 ports for data
//  => use 4 ports as strobes
//  => use 1 port for dot (optional)

static uint8_t values[4];
static int8_t decimals = -1;
static uint8_t showing;

void segments_init()
{
    DDR(SEGMENTS_DATA)      |= 0x0f << SEGMENTS_DATA_BIT;
    DDR(SEGMENTS_STROBE)    |= 0x0f << SEGMENTS_STROBE_BIT;
    PORT(SEGMENTS_STROBE)   &= ~(0x0f << SEGMENTS_STROBE_BIT);
#ifdef SEGMENTS_DOT
    DDR(SEGMENTS_DOT)       |= 1 << SEGMENTS_DOT_BIT;
#endif
}

void segments_stop()
{
    PORT(SEGMENTS_STROBE)   &= ~(0x0f << SEGMENTS_STROBE_BIT);
}

void segments_set_value(uint16_t value, int8_t decs)
{
    bin2bcd4(value, values);
    decimals = decs;
}

void segments_show_next()
{
    if (++showing >= sizeof(values) / sizeof(values[0])) { showing = 0; }
    PORT(SEGMENTS_DATA)     = (PORT(SEGMENTS_DATA)
                            & ~(0x0f << SEGMENTS_DATA_BIT))
                            | (values[showing] << SEGMENTS_DATA_BIT);
    PORT(SEGMENTS_STROBE)   = (PORT(SEGMENTS_STROBE)
                            & ~(0x0f << SEGMENTS_STROBE_BIT))
                            | (1 << (SEGMENTS_STROBE_BIT + showing));
#ifdef SEGMENTS_DOT
    PORT(SEGMENTS_DOT)      = (PORT(SEGMENTS_DOT)
                            & ~(1<< SEGMENTS_DOT_BIT))
                            | (decimals == showing ? (1 << SEGMENTS_DOT_BIT) : 0);
#endif
}
