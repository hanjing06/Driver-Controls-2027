# Firmware Architecture

## Layers

```
┌──────────────────────────────────────────────────────────────┐
│ app/  (our logic, testable on a PC where possible)           │
│  vehicle_state · pedals · gear · lighting · indicators       │
│  can_bus · telemetry · display · faults                      │
├──────────────────────────────────────────────────────────────┤
│ app/common: pinmap.h + bsp (read input, set output, ADC)     │  ← only place that knows pins
├──────────────────────────────────────────────────────────────┤
│ DriverControls/  (CubeMX generated: HAL, FreeRTOS, startup)  │
└──────────────────────────────────────────────────────────────┘
```

Rule: modules in `app/` never call `HAL_GPIO_*` with a raw pin. They go through `bsp_*` functions that use names from `pinmap.h`. When the pin map changes, only `pinmap.h` changes.

## Modules

| Module | Responsibility | 2025 equivalent |
|---|---|---|
| `pinmap.h` | Signal name → port/pin, generated from the [ICD](../../docs/interface-control.md) | `initialize_pins.h` |
| `bsp` | `bsp_read(SIGNAL)`, `bsp_write(SIGNAL, on)`, ADC access | (inline in `main.c`) |
| `pedals` | ADC DMA buffer → filtered accel 0–1, brake pressed, plausibility check | ADC DMA in `main.c`, averaging in `CAN_Transmit.c` |
| `gear` | Debounced Neutral / Drive / Reverse | `gearselecttest` |
| `vehicle_state` | State machine ([state-machine.md](state-machine.md)) | — (new) |
| `lighting` | Brake light, turn signals, hazard blink, DRL | `ButtonManaging.c` (`brake_light`, …) |
| `indicators` | Dash LEDs, fault LED, heartbeat | `led.c` |
| `can_bus` | RX/TX queues on bxCAN; decode MC/BMS frames into telemetry; send drive command ([details](../app/can_bus/README.md)) | `CAN_Receive.c`, `CAN_Transmit.c` |
| `telemetry` | Shared struct of latest values (mutex-protected); UART console print | `telem_to_console()` + globals |
| `display` | LCD driver (I²C) + speed, pack V, faults screens | — (new) |
| `faults` | Collect faults (thermal, HVIL, CAN timeout, pedal implausible), latch, report | — (new) |

## RTOS tasks (starting point)

| Task | Period | Priority | Does |
|---|---|---|---|
| `can_rx_task` | event (RX queue from ISR) | High | Decode frames → `telemetry` |
| `can_tx_task` | event (TX queue) | High | Move queued frames into free bxCAN mailboxes |
| `control_task` | 10 ms | High | Read pedals & gear → `vehicle_state` → `can_send()` drive command |
| `io_task` | 20 ms | Normal | Debounce buttons, run `lighting`, `indicators` |
| `ui_task` | 200–500 ms | Low | `display` update, UART telemetry |
| `watchdog` | — | — | IWDG refreshed only if all tasks checked in |

VCU_2025 had `can_tx`, `can_rx`, `buttons_100ms` and `buttons_500ms` tasks. The split above keeps the same idea but separates control from UI.

## Data flow

```
ADC/DMA ─► pedals ─┐
GPIO ───► gear ────┼─► vehicle_state ─► can_bus (TX queue) ─► Motor controller
GPIO ───► buttons ─┘         │
                             ├─► lighting / indicators ─► MOSFETs, LEDs
CAN RX ─► can_bus (RX queue) ─► telemetry ─► display, UART
                     └─► faults ─► vehicle_state
```

## Changes from 2025 to make

- **Clock:** VCU_2025 runs from **HSI** (internal RC, PLL ×16 → 64 MHz). The 2027 board gets an 8 MHz crystal, so switch to **HSE + PLL** and re-check CAN bit timing (currently prescaler 8, BS1 2 TQ, BS2 5 TQ → 500 kbit/s at APB1 32 MHz).
- **Pin map:** regenerate the `.ioc` from the ICD instead of the Nucleo default.
- **Shared data:** replace `extern union Data` globals with the `telemetry` module + mutex.
- **Don't commit `Debug/`** (build output, `.elf`, `.o`). It's in `.gitignore` now.
