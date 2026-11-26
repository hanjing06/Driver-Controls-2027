# Common: App Entry, Pin Map, Board Support 🔴

**Owner:** firmware lead

## What this does
- `app.h`: the only two calls `main.c` makes into our code: `app_init()` and `app_create_tasks()`
- `pinmap.h`: every signal name → MCU pin, copied from [`../../../docs/interface-control.md`](../../../docs/interface-control.md)
- `bsp.h`: board support: `bsp_read()`, `bsp_write()`, `bsp_adc_raw()`. **The only place outside `can_bus` that calls HAL.** Swapping between the Nucleo and the 2027 board only changes `bsp.c` and `pinmap.h`

## Tasks
- 🔴 Create the `DriverControls` CubeIDE project (see [`../../DriverControls/README.md`](../../DriverControls/README.md))
- 🔴 Write `app.c` (task creation) and `bsp.c` for the **Nucleo** first, with a `BOARD_NUCLEO` / `BOARD_DC2027` switch
- 🟡 Keep `pinmap.h` in sync with the ICD as hardware assigns pins
