/**
 * pedals.h - Accelerator (ADC) and brake pedal processing.
 */
#ifndef PEDALS_H
#define PEDALS_H

#include <stdbool.h>

void  pedals_update(void);          /* call every control period */
float pedals_get_accel(void);       /* 0.0 - 1.0 after deadband + filtering */
bool  pedals_brake_pressed(void);
bool  pedals_implausible(void);     /* out-of-range reading / open wire */

#endif /* PEDALS_H */
