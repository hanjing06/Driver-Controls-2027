# Example 01: Blinky + UART

[Home](../../../README.md) › [Firmware](../../README.md) › [Examples](../README.md) › **01 Blinky**

**Goal:** prove your toolchain works, and learn CubeMX, GPIO, UART and flashing.

## Steps
1. CubeIDE → **File → New → STM32 Project** → Board Selector → **NUCLEO-F302R8** → initialize peripherals with default mode: *Yes*.
2. In the `.ioc`, check **PB13 = LD2** (green LED) and **USART2 = Asynchronous** (PA2/PA3, connected to the ST-LINK virtual COM port).
3. Generate code. In `main.c`'s `while (1)` loop (inside `USER CODE` comments!):
   - toggle LD2 with `HAL_GPIO_TogglePin`
   - print `hello sunstang\r\n` with `HAL_UART_Transmit`
   - `HAL_Delay(500)`
4. Build, then **Run**. Open a serial terminal (CubeIDE console, PuTTY or `screen`) at 115200 baud.

## Done when
- LD2 blinks at 1 Hz and the message prints every 500 ms
- *Stretch:* make the blue button (B1, PC13) change the blink speed

Save your project in this folder on your branch `fw/onboarding-<yourname>`.
