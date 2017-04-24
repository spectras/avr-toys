#ifndef SEGMENTS_H
#define SEGMENTS_H

/****************************************************************************/

void segments_init();
void segments_stop();

inline void segments_set_figures(uint8_t values[4], int8_t decimals);
void segments_set_value(uint16_t value, int8_t decimals);
void segments_show_next();

/****************************************************************************/

extern uint8_t _segments_values[4];
extern int8_t _segments_decimals;

inline void segments_set_figures(uint8_t vals[4], int8_t decs)
{
    _segments_values[0] = vals[0];
    _segments_values[1] = vals[1];
    _segments_values[2] = vals[2];
    _segments_values[3] = vals[3];
    _segments_decimals = decs;
}

#endif
