/**
 * telemetry.h - Latest values from the bus, shared between tasks (mutex-protected).
 * Replaces the extern union Data globals from VCU_2025.
 */
#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <stdint.h>

typedef struct {
    float   velocity_mps;        /* average of MC1 / MC2 */
    float   mc_heatsink_c;
    float   pack_voltage_v;
    float   pack_current_a;
    float   cell_v_max;
    float   cell_v_min;
    int32_t bms_temp_max_c;
    int32_t bms_temp_min_c;
    uint32_t last_mc_rx_ms;      /* for CAN timeout faults */
    uint32_t last_bms_rx_ms;
} telemetry_t;

void telemetry_init(void);
void telemetry_get(telemetry_t *out);           /* copy out under mutex */
void telemetry_set(const telemetry_t *in);
void telemetry_print_uart(void);                /* console output */

#endif /* TELEMETRY_H */
