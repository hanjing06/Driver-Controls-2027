/**
 * faults.h - Collect and latch faults; drives the dash fault indicator.
 */
#ifndef FAULTS_H
#define FAULTS_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    FAULT_THERMAL_SHUTOFF  = 1u << 0,
    FAULT_HVIL_OPEN        = 1u << 1,
    FAULT_BMS              = 1u << 2,
    FAULT_CAN_TIMEOUT_MC   = 1u << 3,
    FAULT_CAN_TIMEOUT_BMS  = 1u << 4,
    FAULT_PEDAL_IMPLAUSIBLE= 1u << 5,
} fault_t;

void     faults_update(void);
void     faults_set(fault_t f);
bool     faults_any(void);
uint32_t faults_get_mask(void);

#endif /* FAULTS_H */
