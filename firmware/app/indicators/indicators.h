/**
 * indicators.h - Dash LEDs driven by the MCU (fault, heartbeat).
 */
#ifndef INDICATORS_H
#define INDICATORS_H

void indicators_update(void);   /* call every io period: heartbeat blink, fault LED from faults module */

#endif /* INDICATORS_H */
