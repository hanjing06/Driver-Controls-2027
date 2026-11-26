/**
 * bsp.h - Board support: the only module that touches HAL GPIO/ADC directly.
 * Swap the implementation (Nucleo vs. 2027 board) without touching app logic.
 */
#ifndef BSP_H
#define BSP_H

#include <stdbool.h>
#include <stdint.h>
#include "pinmap.h"

void     bsp_init(void);
bool     bsp_read(signal_t sig);            /* true = active (polarity handled here) */
void     bsp_write(signal_t sig, bool on);
uint16_t bsp_adc_raw(adc_channel_t ch);     /* latest averaged raw ADC value, 0-4095 */

#endif /* BSP_H */
