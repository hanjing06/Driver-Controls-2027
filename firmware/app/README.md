# app/: Our Application Code

`inc/` holds the module interfaces (already drafted). `src/` is where implementations go. **Pick a module, open an issue, write `src/<module>.c`.**

| Header | Implement in | Port from VCU_2025 |
|---|---|---|
| `app.h` | `src/app.c` | task creation from `main.c` |
| `pinmap.h` | (header only) | `initialize_pins.h` |
| `bsp.h` | `src/bsp.c` | GPIO/ADC calls in `main.c` |
| `pedals.h` | `src/pedals.c` | ADC averaging in `CAN_Transmit.c` |
| `gear.h` | `src/gear.c` | `gearselecttest` |
| `vehicle_state.h` | `src/vehicle_state.c` | new |
| `lighting.h` | `src/lighting.c` | `ButtonManaging.c` |
| `can_bus.h` | `src/can_bus.c` | `CAN_Receive.c`, `CAN_Transmit.c` |
| `telemetry.h` | `src/telemetry.c` | `telem_to_console()` + globals |
| `faults.h` | `src/faults.c` | new |

In CubeIDE, add `../../app/inc` to **Include paths** and `../../app/src` as a **linked source folder** (Project → Properties → C/C++ General → Paths and Symbols).
