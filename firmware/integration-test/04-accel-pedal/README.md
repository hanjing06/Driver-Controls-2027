# Task 4: Accelerator Pedal End to End

[Home](../../../README.md) › [Firmware](../../README.md) › [Integration test](../README.md) › **04 Accel pedal**

**Assigned to:**
**Warm-up:** [`../../examples/02-adc-pedal/`](../../examples/02-adc-pedal/) (same idea with a potentiometer)

## Goal

Prove the **real** pedal produces the right drive command: pedal up → 0 %, pedal floored → 100 %, smooth in between, and safe if something goes wrong.

## How it works in VCU_2025

The pedal is read on **ADC1_IN1 (PA0)** with DMA into a 4-sample buffer. `CAN_Transmit.c` averages the buffer and turns it into the current field (bytes 4–7) of `0x401`.

## Steps

1. **Find the pedal's datasheet** (ask the mech/electrical lead what pedal the car uses). What voltage does it output at rest and fully pressed? What supply does it need?
2. **Check the voltage is safe for the STM32.** The ADC pin must never see more than **3.3 V**. Measure the pedal output (through the 2026 board) with a multimeter at rest and fully pressed.
3. **Read the raw ADC values.** In CubeIDE's **Live Expressions** (debug view), watch the ADC buffer as you press the pedal. Write down the raw value at rest and fully pressed.
4. **Check the command.** In SavvyCAN, decode the current field of `0x401` at rest, half and full. Does rest give exactly 0? Does full give 1.0 (or the intended maximum)?
5. **Check the failure cases** (with the motor *off*): unplug the pedal connector. What command does the VCU send? A floating input that reads as "full throttle" is a serious problem. Write down what happens.

## Done when

- [ ] Pedal voltage and raw ADC values at rest / full written down
- [ ] `0x401` current field reads 0 at rest and the expected maximum when floored
- [ ] Unplugged-pedal behaviour tested and written down
- [ ] Results and any needed fixes (deadband, calibration, unplugged detection) in [`../test-log.md`](../test-log.md)
