# Research: Motor Controller CAN Protocol 🟡

**Assigned to:**
**Read first:** [`../can-fundamentals/`](../can-fundamentals/)

## Why it matters

The VCU makes the car move by sending a **drive command** to the motor controllers over CAN, and it reads speed back from them. We need to know exactly what the motor controllers expect: wrong byte order or units can mean the car doesn't move, or moves unexpectedly.

VCU_2025 uses IDs that follow the **Prohelion (formerly Tritium) WaveSculptor**-style layout: driver controls base `0x400`, motor controller 1 base `0x500`, motor controller 2 base `0x600`. **Confirm with the electrical lead which motor controllers the 2027 car uses.**

## Questions to answer in `notes.md`

1. Which motor controller(s) does the 2027 car use? Find the **CAN communications manual** for it.
2. What is the **base address** concept? How do `0x401`, `0x503`, `0x603` relate to their base addresses?
3. **Drive command (`0x401`):** what are the two fields, their units and data types (float? byte order?)? What does a velocity of e.g. 20000 rpm combined with a current of 0.3 mean (torque control vs. velocity control)?
4. How do you command **reverse**? How do you command **zero torque / coast**? How do you do **regen braking** (if supported)?
5. How often must the drive command be sent? What does the motor controller do if it stops receiving it (timeout)?
6. **Velocity (`0x503`, `0x603`):** what fields does it contain? How do you convert to km/h?
7. List the other broadcast messages (status/errors, bus voltage/current, heatsink temperature, ...) that might be useful for the dash or for fault detection.
8. Compare with what VCU_2025 actually sends/decodes (`CAN_Transmit.c`, `CAN_Receive.c`). Anything wrong or missing?

**What this means for our VCU**
9. Update the table in [`../../docs/can-messages.md`](../../docs/can-messages.md) with exact byte layouts for every motor controller message we use.

## Resources
- The motor controller's CAN communications manual (Prohelion publishes theirs online)
- VCU_2025 source
- Ask: electrical lead / last year's firmware members

## Done when
- [ ] `notes.md` answers 1–8
- [ ] `can-messages.md` updated with byte layouts (PR)
- [ ] Presented at a team meeting
