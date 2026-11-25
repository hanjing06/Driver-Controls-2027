# VCU_2025 Firmware: Reference Notes

Repo: [uixt/VCU_2025](https://github.com/uixt/VCU_2025) · STM32CubeIDE · STM32F302R8 (Nucleo) · FreeRTOS (CMSIS-RTOS v1)

## What's in it

| File (`Core/Src`) | Does |
|---|---|
| `main.c` | Peripheral init, ADC DMA start, creates tasks `canTxTask`, `canRxTask`, `buttons_task_100ms`, `buttons_task_500ms` |
| `CAN_Receive.c` | RX FIFO0 callback → queue → `can_rx` task, decodes MC velocity (`0x503`, `0x603`) and BMS (`0x701–0x703`) |
| `CAN_Transmit.c` | `can_tx` task: averages the ADC buffer and sends motor drive command `0x401` |
| `ButtonManaging.c` | `buttons_100ms` / `buttons_500ms`, brake light, telemetry printed to UART |
| `led.c` | LED task |
| `initialize_pins.h` | Pin defines (Nucleo defaults: LD2, B1, USART2, SWD) |

## Configuration
- SYSCLK 64 MHz from **HSI** /2 × 16 (no crystal)
- CAN 500 kbit/s on PA11/PA12 (prescaler 8, BS1 2 TQ, BS2 5 TQ)
- ADC1_IN1 on PA0 (accel pedal) with DMA, 4-sample buffer
- USART2 on PA2/PA3 for console; SWD + SWO

## What to keep
- Task structure, CAN ID set, ADC-DMA pedal approach, UART telemetry

## What to change for 2027
- HSI → **HSE crystal** (board has no ST-LINK MCO; CAN wants an accurate clock)
- Move app logic out of `Core/` / `main.c` into `firmware/app/` modules
- Replace `extern union Data` globals with a mutex-protected `telemetry` module
- Pins from the ICD instead of Nucleo defaults; most I/O (lights, gear, turn signals) still to be wired up
- Add: vehicle state machine, fault handling, watchdog, LCD
- Stop committing `Debug/` build output
