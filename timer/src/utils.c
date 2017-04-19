#include "config.h"
#include "utils.h"

void bin2bcd(uint16_t val, uint8_t buffer[4])
{
    for (uint8_t i = 0; i < 4; i += 1) {
        buffer[i] = val % 10; val = val / 10;
    }
}
