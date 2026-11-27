# Task 2: Send Drive Commands to the Motor Controllers

[Home](../../../README.md) › [Firmware](../../README.md) › [Integration test](../README.md) › **02 Motor controller**

**Assigned to:**
**Read first:** [`../../research/motor-controller-can/`](../../research/motor-controller-can/), the [safety section](../README.md#safety)
**Needs:** task 1 working

## Goal

Prove the STM32 running VCU_2025 can make the motor controllers spin the motor, and read the motor's speed back.

## How it works in VCU_2025

`CAN_Transmit.c` sends **`0x401`** (motor drive command) over and over:

| Bytes | Field | Type | Meaning |
|---|---|---|---|
| 0–3 | Velocity | float, rpm | Target speed. A very large value (e.g. 20000) means "go as fast as the current allows" (torque control) |
| 4–7 | Current | float, 0.0–1.0 | Fraction of max motor current. From the pedal |

The motor controllers send velocity back on **`0x503`** (MC1) and **`0x603`** (MC2), which `CAN_Receive.c` decodes.

Check these against the motor controller's CAN manual. That's what the motor-controller research topic is for.

## Steps

1. **Without HV first.** With only LV on, confirm in SavvyCAN that `0x401` is being sent, and decode bytes 0–7 by hand. Do the values match what the pedal is doing?
2. **Check the motor controllers see it.** Most motor controllers broadcast a status/error message. Look for a "no drive command" or timeout error and confirm it clears when the VCU is on.
3. **With HV, on stands, electrical lead present:** set a very small current limit and press the pedal gently. The motor should turn.
4. **Read speed back.** Check the velocity frames (`0x503` / `0x603`) change with the motor and that VCU_2025 prints a sensible speed on the UART console.
5. **Test stopping.** Release the pedal: the motor should coast down. Unplug the VCU's CAN: what does the motor controller do? (It should stop after a timeout. Write down how long.)
6. **Test reverse** if the gear selector is wired, following the motor controller manual.

## Done when

- [ ] `0x401` decoded by hand and matches the pedal
- [ ] Motor spins on stands from the pedal, and stops when released
- [ ] Speed read back and printed correctly
- [ ] Timeout behaviour when the VCU stops sending is measured
- [ ] Results and any problems in [`../test-log.md`](../test-log.md)
