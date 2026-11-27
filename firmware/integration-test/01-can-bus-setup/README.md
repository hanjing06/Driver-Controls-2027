# Task 1: CAN Bus Setup

[Home](../../../README.md) › [Firmware](../../README.md) › [Integration test](../README.md) › **01 CAN bus setup**

**Assigned to:**
**Read first:** [`../../research/can-fundamentals/`](../../research/can-fundamentals/), [`../../research/can-tools/`](../../research/can-tools/)

## Goal

Get the VCU, the motor controllers and the BMS on **one working CAN bus**, and be able to see every frame on a laptop. Every other task depends on this.

## Steps

1. **Find out what's on the bus.** Ask the electrical lead which motor controllers and BMS the car uses, where their CAN connectors are, and whether a wiring harness already exists.
2. **Check they all use the same bit rate.** VCU_2025 runs at **500 kbit/s**. Check the motor controller and BMS settings match. If one is different, nothing will work.
3. **Check termination.** A CAN bus needs exactly **two 120 Ω resistors, one at each end**. With everything powered off, measure across CAN_H and CAN_L: you should read about **60 Ω**. 120 Ω means one is missing; 40 Ω means there's one too many.
4. **Connect the USB-CAN adapter** and open SavvyCAN at 500 kbit/s. Power on one device at a time and note which IDs appear.
5. **Bring the VCU on.** Power the Nucleo + 2026 board running VCU_2025. You should see `0x401` (the drive command) appear.

## What you should see

| ID | From | Should appear when |
|---|---|---|
| `0x401` | VCU | VCU powered |
| `0x500`–`0x5FF` | Motor controller 1 | MC1 powered |
| `0x600`–`0x6FF` | Motor controller 2 | MC2 powered |
| `0x701`, `0x702`, `0x703` | BMS | BMS powered |

Full list: [`../../docs/can-messages.md`](../../docs/can-messages.md).

## If it doesn't work

- **Nothing at all:** wrong bit rate in SavvyCAN, CAN_H/CAN_L swapped, or no termination.
- **Error frames / bus-off:** bit rates don't match, or termination is wrong (go back to step 3).
- **Only some devices show up:** check that device's connector and power. Unplug the others and test it alone.

## Done when

- [ ] Bus wiring drawn (photo of a sketch is fine) and added to [`../test-log.md`](../test-log.md)
- [ ] Termination measured and written down
- [ ] A SavvyCAN capture with frames from all three devices, saved in this folder (`.csv` or `.gvret` log)
