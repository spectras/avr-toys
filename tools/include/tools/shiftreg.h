#ifndef TOOLS_SHIFTREG_H
#define TOOLS_SHIFTREG_H

#include <stdint.h>

typedef struct shiftreg_descriptor {
    volatile uint8_t * port;    /**< Port address */
    uint8_t     data_bit;       /**< Data bit, as mask */
    uint8_t     strobe_bit;     /**< Strobe bit, as mask */
    uint8_t     output_bit;     /**< Output bit, as mask */
} shiftreg_descriptor_t;


void shiftreg_send(const shiftreg_descriptor_t * reg, uint8_t value);

inline void shiftreg_commit(const shiftreg_descriptor_t * reg) {
    uint8_t out_mask = reg->output_bit;
    uint8_t port_val = *reg->port | out_mask;
    *reg->port = port_val;
    port_val &= ~out_mask;
    *reg->port = port_val;
}

#endif
