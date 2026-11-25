# Firmware

STM32F302R8 firmware for the 2027 Driver Controls board. Built with **STM32CubeIDE**, HAL and **FreeRTOS** (CMSIS-RTOS), carried over from [VCU_2025](https://github.com/uixt/VCU_2025).

## Folder map

| Folder | Contents |
|---|---|
| [`docs/`](docs/) | Onboarding, architecture, state machine, CAN messages, coding standards, flashing |
| [`DriverControls/`](DriverControls/) | STM32CubeIDE project: `.ioc`, generated `Core/`, `Drivers/`, `Middlewares/` (FreeRTOS) |
| [`app/`](app/) | **Our code**: one module per feature (`inc/` + `src/`) |
| [`drivers/`](drivers/) | Drivers for external devices (LCD) |
| [`examples/`](examples/) | Onboarding exercises, run on a Nucleo-F302R8 |
| [`tests/`](tests/) | Host-side unit tests for app logic (state machine, pedal mapping) |
| [`tools/`](tools/) | Scripts: CAN log parsing, DBC, etc. |

## Why `app/` is separate from the CubeIDE project

In VCU_2025, our code lived in `Core/` next to generated code, and a lot of it ended up in `main.c`. For 2027, CubeMX owns `DriverControls/Core`, and we own `app/`. `main.c` only calls `app_init()` and creates the RTOS tasks. This means:
- Regenerating from the `.ioc` (which will happen a lot as the pin map changes) never clobbers our code
- Logic in `app/` can be unit-tested on a laptop without hardware

## Quick start

1. Install [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html).
2. **File → Import → Existing Projects into Workspace** → select `firmware/DriverControls`.
3. Build (hammer icon). Flash with a Nucleo or ST-LINK, see [`docs/flashing-and-debugging.md`](docs/flashing-and-debugging.md).

New member? → [`docs/onboarding.md`](docs/onboarding.md)
