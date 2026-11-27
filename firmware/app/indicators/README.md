# Indicators

[Home](../../../README.md) › [Firmware](../../README.md) › [App](../README.md) › **Indicators**

**Owner:** · **Members:**

## What it does
Drives the dash LEDs the MCU controls: a **heartbeat** LED (blinks while firmware is running, so you know it hasn't crashed) and the **dash fault indicator** (on when [`faults`](../faults/) reports anything).

## How VCU_2025 did it
`led.c`, a simple LED task.

## Tasks
- `indicators_update()`: toggle heartbeat every 500 ms, set fault LED from `faults_any()`
- Great first module: do [`../../examples/01-blinky`](../../examples/01-blinky/) first
