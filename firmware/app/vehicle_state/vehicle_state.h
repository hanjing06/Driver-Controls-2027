/**
 * vehicle_state.h - Vehicle state machine. See firmware/docs/state-machine.md.
 */
#ifndef VEHICLE_STATE_H
#define VEHICLE_STATE_H

#include <stdbool.h>
#include "gear.h"

typedef enum {
    VS_IDLE,
    VS_HV_READY,
    VS_DRIVE_ENABLED,
    VS_CHARGE,
    VS_FAULT
} vehicle_state_t;

typedef struct {
    bool   hv_active;
    bool   ready_mode;
    bool   charge_mode;
    bool   brake_pressed;
    float  accel;          /* 0.0 - 1.0 */
    gear_t gear;
    bool   fault_active;
} vs_inputs_t;

/* Pure function: no HAL calls, so it can be unit-tested in firmware/tests. */
vehicle_state_t vs_next(vehicle_state_t current, const vs_inputs_t *in);

void            vehicle_state_update(void);  /* gathers inputs, calls vs_next */
vehicle_state_t vehicle_state_get(void);

#endif /* VEHICLE_STATE_H */
