# Design Requirements

*Fill in during Phase 1. `TBD` items are decisions the team still has to make.*

## Electrical

| ID | Requirement | Value | Status |
|---|---|---|---|
| E1 | Input supply | 12 V nominal from DC-DC; survive TBD V transients and reverse connection | TBD |
| E2 | Logic rail | 3.3 V ±3%, ≥ TBD mA | TBD |
| E3 | Digital inputs | Accept 0/12 V, logic threshold TBD V, debounce RC TBD | TBD |
| E4 | Analog inputs | Accel pedal range TBD V → 0–3.3 V ADC, RC filter fc TBD Hz | TBD |
| E5 | Lighting outputs | Per-channel current TBD A, fused | TBD |
| E6 | CAN | ISO 11898-2, 500 kbit/s (TBD), switchable 120 Ω termination | TBD |
| E7 | MCU | STM32F302R8T6, HSE 8 MHz | DRAFT |

## Mechanical

| ID | Requirement | Value | Status |
|---|---|---|---|
| M1 | Board outline | TBD × TBD mm, fits the dash/enclosure | TBD |
| M2 | Mounting | TBD × M3 holes | TBD |
| M3 | Connectors | Locking, automotive-grade (MX150 or equiv.) | TBD |
| M4 | Layers | 2 or 4 (4 recommended: solid GND plane) | TBD |

## Safety

| ID | Requirement |
|---|---|
| S1 | Main contactor must never close before pre-charge is confirmed (hardware interlock **and** firmware) |
| S2 | Thermal shutoff / HVIL fault must reach a safe state even if the MCU is hung (hardware path or watchdog) |
| S3 | No 12 V net connects directly to an MCU pin |
| S4 | Every off-board 12 V output is fused |
| S5 | Comply with current solar car race regulations for lighting and driver controls (check the regs doc) |
