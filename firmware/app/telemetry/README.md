# Telemetry

[Home](../../../README.md) › [Firmware](../../README.md) › [App](../README.md) › **Telemetry**

**Owner:** · **Members:**

## What it does
Holds the **latest values received over CAN** (speed, pack voltage/current, temperatures, last-received times) in one struct, protected by a mutex so any task can read it safely. It also prints a telemetry line over UART.

## How VCU_2025 did it
Decoded values went into `extern union Data` globals, read by other tasks without protection. Printing was `telem_to_console()` in `ButtonManaging.c`.

## Tasks
- Implement `telemetry.c`: mutex create, `telemetry_get` / `telemetry_set` copy under the mutex
- `telemetry_print_uart()`: one readable line, e.g. `v=42.1km/h Vpack=101.3V I=12.4A Tmax=31C`
- Work with the [`can_bus`](../can_bus/) team: `can_rx_task` calls `telemetry_set`

**Read first:** [`../../research/freertos-queues/`](../../research/freertos-queues/) (mutex questions)
