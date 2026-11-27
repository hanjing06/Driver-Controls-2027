# Gear

[Home](../../../README.md) › [Firmware](../../README.md) › [App](../README.md) › **Gear**

**Owner:** · **Members:**

## What it does
Reads the rotary gear selector's three inputs (`Neutral`, `Reverse`, `Drive`) and reports a clean, **debounced** gear. If zero or more than one input is active, it reports `GEAR_INVALID`.

## How VCU_2025 did it
A test file, `gearselecttest`, read the pins directly.

## Tasks
- `gear_update()`: read the 3 inputs through `bsp_read()`, accept a new gear only after it's stable for ~50 ms
- Unit test: bouncing input → no change until stable; two inputs → `GEAR_INVALID`
- Test on a Nucleo with three jumper wires to GND
