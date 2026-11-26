# Faults 🟡

**Owner:** · **Members:**

## What it does
Collects every reason the car should not drive (thermal shutoff, HVIL open, BMS fault, lost CAN contact with the motor controller or BMS, implausible pedal) into one bitmask. Faults are **latched**: they stay set until the car is restarted, so an intermittent problem can't be missed.

## How VCU_2025 did it
Not implemented. This module is new.

## Tasks
- 🟡 Get the fault list from the [`bms-can`](../../research/bms-can/) research
- 🟡 `faults_update()`: check inputs + CAN timeouts (from [`can_bus`](../can_bus/) task 7), latch the bits
- 🟢 Print active faults by name over UART
- 🔴 Agree with [`vehicle_state`](../vehicle_state/) on which faults force `VS_FAULT`
