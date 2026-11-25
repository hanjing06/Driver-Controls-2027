# Firmware Onboarding

You don't need the 2027 board to start. Everything begins on a **Nucleo-F302R8** (same MCU), and we port to our PCB at bring-up.

## Setup

1. Install [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) and Git.
2. Borrow a Nucleo-F302R8 from the team bin (sign it out).
3. Clone this repo and import `firmware/DriverControls` into CubeIDE.

## Learn the basics

- Embedded C refresher: pointers, `volatile`, bit masks, `struct`/`union`
- ST's [STM32 MOOC / STM32CubeIDE basics](https://www.st.com/content/st_com/en/support/learning/stm32-education.html)
- FreeRTOS concepts: tasks, delays, queues, mutexes ([FreeRTOS docs](https://www.freertos.org/Documentation/02-Kernel/01-About-the-FreeRTOS-kernel/01-FreeRTOS-kernel))
- CAN basics: frames, IDs, bit timing

## Your first tasks

Do these in order, each one in [`../examples/`](../examples/):

1. **`01-blinky`**: make a CubeIDE project from scratch, blink LD2, print over UART. *Teaches: CubeMX, GPIO, UART, flashing.*
2. **`02-adc-pedal`**: read a potentiometer on an ADC pin with DMA, map it to 0–100 %. *Teaches: ADC, DMA, scaling. This is how the accel pedal works.*
3. **`03-can-loopback`**: send and receive a CAN frame in loopback mode at 500 kbit/s. *Teaches: bxCAN, filters, bit timing.*

Then:
4. Read [VCU_2025](https://github.com/uixt/VCU_2025) with [`../../docs/reference/2025-firmware.md`](../../docs/reference/2025-firmware.md) open, and explain to someone how a velocity frame from the motor controller gets to the UART console.
5. Pick up a `fw` + `good first issue` issue (usually a module in [`architecture.md`](architecture.md)).

## Docs in this folder

| Doc | What it's for |
|---|---|
| [`architecture.md`](architecture.md) | Modules, tasks, data flow |
| [`state-machine.md`](state-machine.md) | Vehicle states and transitions |
| [`can-messages.md`](can-messages.md) | CAN IDs we send/receive |
| [`coding-standards.md`](coding-standards.md) | Naming, style, rules |
| [`flashing-and-debugging.md`](flashing-and-debugging.md) | Nucleo vs. our board, SWD, UART |
