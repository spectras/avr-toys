#ifndef TOOLS_SHIFTREG_H
#define TOOLS_SHIFTREG_H

#include <stdint.h>

typedef struct shiftreg_descriptor {
    volatile void * port;       /**< Port address */
    uint8_t     data_bit;       /**< Data bit, as mask */
    uint8_t     strobe_bit;     /**< Strobe bit, as mask */
    uint8_t     output_bit;     /**< Output bit, as mask */
} shiftreg_descriptor_t;


void shiftreg_send(const shiftreg_descriptor_t * reg, uint8_t value);

#endif
