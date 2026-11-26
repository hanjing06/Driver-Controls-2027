# Vehicle State Machine 🔴

**Owner:** · **Members:**

## What it does
Decides what the car is allowed to do: idle, HV ready, drive enabled, charging, or fault. It is the safety core. For example, the motor gets zero current unless the car is in `VS_DRIVE_ENABLED`, and you can only get there with the brake pressed. Full spec: [`../../docs/state-machine.md`](../../docs/state-machine.md).

## How VCU_2025 did it
There was no explicit state machine. The drive command was sent whenever the pedal was pressed.

## Tasks
- 🔴 Finalize the state diagram with the electrical lead (startup sequence, which faults matter)
- 🔴 Implement `vs_next()` as a **pure function** (no HAL), so it's fully testable
- 🟡 Unit tests for every transition in [`../../tests/`](../../tests/). 🟢 members can write test cases from the diagram
- 🟡 `vehicle_state_update()`: gather inputs from pedals/gear/faults, call `vs_next`, log transitions over UART
