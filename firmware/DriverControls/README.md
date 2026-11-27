# DriverControls: STM32CubeIDE Project

[Home](../../README.md) › [Firmware](../README.md) › **CubeIDE project**

Generated project for the STM32F302R8T6. **CubeMX owns this folder**: only write code between `/* USER CODE BEGIN */ … /* USER CODE END */`.

## Creating it (one-time, firmware lead)
1. Start from VCU_2025's `VCU_2025.ioc` (keeps FreeRTOS, CAN 500k, ADC DMA, USART2), *or* a new project for STM32F302R8Tx.
2. Rename to `DriverControls.ioc`.
3. RCC → HSE **Crystal/Ceramic Resonator**, 8 MHz → PLL → 64 MHz SYSCLK. Re-check CAN bit timing.
4. Assign pins from [`docs/interface-control.md`](../../docs/interface-control.md), with labels = net names.
5. Generate code, add `app/` include + source paths, call `app_init()` / `app_create_tasks()` in `main.c`.

Expected contents after generation: `DriverControls.ioc`, `Core/`, `Drivers/`, `Middlewares/`, `STM32F302R8TX_FLASH.ld`, `.project`, `.cproject`. `Debug/` and `Release/` are git-ignored.
