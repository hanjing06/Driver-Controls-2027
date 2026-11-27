# Display

[Home](../../../README.md) › [Firmware](../../README.md) › [App](../README.md) › **Display**

**Owner:** · **Members:**

## What it does
Shows the driver key information on the 2×20 character LCD over I²C: speed, pack voltage, vehicle state, and any active fault.

## How VCU_2025 did it
Not implemented. This module is new.

## Tasks
- Research: read the NHD-C0220BIZ datasheet. What's the I²C address, and what init commands does it need? Write it in `notes.md` here
- LCD driver: `lcd_init`, `lcd_clear`, `lcd_set_cursor`, `lcd_print` using `HAL_I2C_Master_Transmit`
- Screen layout: design what goes on the 2 lines (mock it up in `notes.md` first)
- `display_update()` reading from [`telemetry`](../telemetry/), called from the low-priority UI task

Works with the hardware [Display block](../../../hardware/circuits/display/).
