# Task 3: Read BMS Telemetry

[Home](../../../README.md) › [Firmware](../../README.md) › [Integration test](../README.md) › **03 BMS telemetry**

**Assigned to:**
**Read first:** [`../../research/bms-can/`](../../research/bms-can/)
**Needs:** task 1 working

## Goal

Prove the VCU correctly reads the battery's data from the BMS: pack voltage, current and temperatures.

## How it works in VCU_2025

`CAN_Receive.c` decodes three BMS messages and the telemetry is printed over UART:

| ID | Contents |
|---|---|
| `0x701` | Temperatures (high / low) |
| `0x702` | Pack and cell voltages |
| `0x703` | Pack current |

Byte layouts are in [`../../docs/can-messages.md`](../../docs/can-messages.md). Confirm them against the BMS documentation (that's the BMS research topic).

## Steps

1. **Find the BMS documentation** or the battery sub-team member who owns it. Find out what it sends and how often.
2. **Capture the BMS frames** in SavvyCAN with only the BMS and the adapter on the bus.
3. **Decode one frame of each ID by hand** and compare with what the BMS's own software or display shows. Pay attention to byte order and scaling.
4. **Add the VCU** and check its UART console prints the same values.
5. **Compare with a multimeter / known value** where safe: e.g. pack voltage against the BMS's display, temperature at room temperature.
6. **Unplug the BMS's CAN.** What does the VCU print? (It probably keeps the last value, which is a problem worth writing down for later.)

## Done when

- [ ] Each of `0x701`–`0x703` decoded by hand and matching the BMS's own readout
- [ ] VCU_2025 prints the same values on the UART console
- [ ] Any wrong decoding (byte order, units, scaling) written up as an issue
- [ ] Results in [`../test-log.md`](../test-log.md)
