# Example 02: ADC Pedal

[Home](../../../README.md) › [Firmware](../../README.md) › [Examples](../README.md) › **02 ADC pedal**

**Goal:** read an analog voltage like the accelerator pedal does, using DMA.

## Setup
A 10 kΩ potentiometer: ends to **3.3 V** and **GND** (never 5 V!), wiper to **PA0** (A0 on the Nucleo header).

## Steps
1. New project (or copy 01). In the `.ioc`: **ADC1 → IN1** (PA0), continuous conversion, **DMA circular**, 12-bit.
2. Start with `HAL_ADC_Start_DMA(&hadc1, buf, 4)` into a 4-sample buffer (same as VCU_2025).
3. Every 100 ms: average the buffer, convert to percent (`raw * 100 / 4095`), print it.
4. Add a **deadband**: anything below 5 % reads 0 %.

## Done when
- Turning the pot prints 0 → 100 % smoothly, with a solid 0 at rest

## Questions (answer in a comment in your PR)
- Why use DMA instead of polling the ADC?
- What happens to the reading if the pot's wiper wire falls off? Why does that matter for a car pedal?
