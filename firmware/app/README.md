# app/: Our Application Code

[Home](../../README.md) › [Firmware](../README.md) › **App**

One folder per module. Each folder has:
- `<module>.h`: the interface (already drafted, so read this first)
- `<module>.c`: the implementation (**you write this**)
- `README.md`: what the module does, how VCU_2025 did it, your tasks

| Module | Priority |
|---|---|
| [`can_bus/`](can_bus/) | **This year's main project** |
| [`indicators/`](indicators/) | Later |
| [`gear/`](gear/) | Later |
| [`lighting/`](lighting/) | Later |
| [`pedals/`](pedals/) | Later |
| [`telemetry/`](telemetry/) | With can_bus |
| [`display/`](display/) | Later |
| [`faults/`](faults/) | Later |
| [`vehicle_state/`](vehicle_state/) | Later |
| [`common/`](common/) | Firmware lead |

## Adding app/ to the CubeIDE project
Project → Properties → C/C++ General → Paths and Symbols:
- **Includes:** add `app/common` and each module folder
- **Source Location:** link `app/` as a source folder

Modules only include each other's headers, never CubeMX headers (except `common/bsp.c` and `can_bus/can_bus.c`, which talk to HAL).
