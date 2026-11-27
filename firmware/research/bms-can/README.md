# Research: BMS CAN Protocol

[Home](../../../README.md) › [Firmware](../../README.md) › [Research](../README.md) › **BMS CAN**

**Assigned to:**
**Read first:** [`../can-fundamentals/`](../can-fundamentals/)

## Why it matters

The **Battery Management System** watches every cell in the pack. The VCU reads its CAN messages to show pack voltage, current and temperature on the dash, and, more importantly, to **know when the battery is in trouble** so the VCU can stop driving or raise the fault light.

VCU_2025 receives `0x701` (temperatures), `0x702` (pack & cell voltages) and `0x703` (pack current).

## Questions to answer in `notes.md`

1. What BMS does the 2027 car use (commercial like Orion/Elithion, or in-house)? Find its CAN documentation, or the team member who owns it.
2. For each of `0x701`, `0x702`, `0x703`: byte layout, data types, units, scaling, send rate.
3. What fault/warning information does the BMS broadcast? Which faults should make the VCU **stop the car** vs. just **show a warning**?
4. Does the BMS expect anything **from** the VCU (e.g. a heartbeat, charge/drive mode)?
5. How does VCU_2025 decode these (`union Data` trick)? Is the byte order right? What would go wrong on a big-endian sender?
6. If BMS messages stop arriving (cable unplugged), how quickly should the VCU notice, and what should it do?

**What this means for our VCU**
7. Update [`../../docs/can-messages.md`](../../docs/can-messages.md) with exact layouts, and propose the list of BMS-related faults for [`../../app/faults/`](../../app/faults/).

## Resources
- BMS documentation / the battery sub-team
- VCU_2025 `CAN_Receive.c`
- [`../../docs/state-machine.md`](../../docs/state-machine.md)

## Done when
- [ ] `notes.md` answers 1–6
- [ ] `can-messages.md` and a fault list proposal updated (PR)
- [ ] Presented at a team meeting
