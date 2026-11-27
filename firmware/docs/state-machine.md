# Vehicle State Machine

[Home](../../README.md) › [Firmware](../README.md) › [Docs](README.md) › **State machine**

*Draft. Firmware track to finalize with the electrical lead during Phase 1.*

```
            LV on
 [OFF] ───────────► [IDLE] ── HV switch + pre-charge confirmed ──► [HV_READY]
                      ▲                                                │
                      │ HV lost / mode→Charge                          │ Ready mode + brake pressed
                      │                                                ▼
 [CHARGE] ◄── Charge mode ── [IDLE]                               [DRIVE_ENABLED]
                                                                       │  gear N/D/R
 any state ── fault (thermal, HVIL, BMS, CAN timeout, pedal implausible) ──► [FAULT]
 [FAULT] ── fault cleared + LV cycle ──► [IDLE]
```

| State | Motor command | Notes |
|---|---|---|
| `OFF` | — | MCU not running |
| `IDLE` | 0 current | LV only; lights work |
| `HV_READY` | 0 current | HV active verified |
| `DRIVE_ENABLED` | From accel pedal, direction from gear | Neutral → 0 current |
| `CHARGE` | 0 current | Driving inhibited |
| `FAULT` | 0 current | Dash fault LED on; latched |

## Rules
- Entering `DRIVE_ENABLED` requires the brake pressed and accel ≈ 0 (no surprise launch).
- Changing gear D↔R only at ~0 velocity (from MC telemetry).
- Brake pressed → motor current 0 regardless of accel.
- Every transition is logged over UART.
- The transition function is pure (`state_next(state, inputs) → state`), so it can be unit-tested in `tests/`.
