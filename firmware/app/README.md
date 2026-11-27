# app/: Our Application Code

[Home](../../README.md) › [Firmware](../README.md) › **App**

> **Later.** VCU_2025's code works, so new modules wait until the [integration test](../integration-test/) passes.

One folder per module. Each folder has:
- `<module>.h`: the interface (already drafted, so read this first)
- `<module>.c`: the implementation (**you write this**)
- `README.md`: what the module does, how VCU_2025 did it, your tasks

| Module | Priority |
|---|---|
| [`can_bus/`](can_bus/) | Later (first after the integration test) |
| [`indicators/`](indicators/) | Later |
| [`gear/`](gear/) | Later |
| [`lighting/`](lighting/) | Later |
| [`pedals/`](pedals/) | Later |
| [`telemetry/`](telemetry/) | Later |
| [`display/`](display/) | Later |
| [`faults/`](faults/) | Later |
| [`vehicle_state/`](vehicle_state/) | Later |
| [`common/`](common/) | Firmware lead |

## Adding app/ to the CubeIDE project
Project → Properties → C/C++ General → Paths and Symbols:
- **Includes:** add `app/common` and each module folder
- **Source Location:** link `app/` as a source folder

Modules only include each other's headers, never CubeMX headers (except `common/bsp.c` and `can_bus/can_bus.c`, which talk to HAL).
