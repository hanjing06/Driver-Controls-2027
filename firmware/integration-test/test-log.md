# Integration Test Log

[Home](../../README.md) › [Firmware](../README.md) › [Integration test](README.md) › **Test log**

**Owner (task 5):**

This file is the record of the integration test. The owner keeps it tidy; everyone adds their results. The goal is a procedure anyone can repeat, especially when the 2027 board arrives.

## Setup

| Item | Details |
|---|---|
| VCU | Nucleo-F302R8 + 2026 VCU board, VCU_2025 commit: |
| Motor controllers | Model: · Firmware: · CAN base addresses: |
| BMS | Model: · CAN IDs: |
| Pedal | Model: · Output range: |
| CAN adapter | Model: · Software: SavvyCAN |
| Bit rate | 500 kbit/s |
| Termination | Measured CAN_H–CAN_L (power off): Ω |

**Bus wiring diagram:** *(add a photo or sketch)*

## Procedure

*(Fill in the exact steps as they're worked out, so someone new can follow them.)*

1. LV only: power VCU, check `0x401` in SavvyCAN
2. …

## Results

| Date | Task | Test | Expected | Result | Pass? | Who |
|---|---|---|---|---|---|---|
| | 1 | All 3 devices visible in SavvyCAN | Frames from VCU, MC, BMS | | | |
| | 2 | Pedal spins motor on stands | Motor turns, stops on release | | | |
| | 2 | VCU stops sending | MC stops after timeout | | | |
| | 3 | BMS pack voltage on UART | Matches BMS display | | | |
| | 4 | Pedal at rest / floored | `0x401` current = 0 / max | | | |
| | 4 | Pedal unplugged | Command = 0 | | | |

## Problems found

| # | Problem | Task | Issue link | Status |
|---|---|---|---|---|
| | | | | |
