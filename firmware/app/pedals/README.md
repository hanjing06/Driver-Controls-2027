# Pedals

[Home](../../../README.md) › [Firmware](../../README.md) › [App](../README.md) › **Pedals**

**Owner:** · **Members:**

## What it does
Turns the accelerator pedal's analog voltage into a 0.0–1.0 value for the drive command, and reports whether the brake is pressed. Also detects an **implausible** pedal reading (e.g. wire unplugged → reads 0 V or 3.3 V), which must never be treated as full throttle.

## How VCU_2025 did it
ADC1 on PA0 with DMA into a 4-sample buffer; `CAN_Transmit.c` averaged it and used it as the motor current.

## Tasks
- Do [`../../examples/02-adc-pedal`](../../examples/02-adc-pedal/) first
- `pedals_update()`: average the DMA buffer, scale with min/max calibration, apply a deadband near 0
- `pedals_implausible()`: out-of-range detection; agree thresholds with the hardware Driver Inputs block
- Unit tests for scaling and deadband in [`../../tests/`](../../tests/)
