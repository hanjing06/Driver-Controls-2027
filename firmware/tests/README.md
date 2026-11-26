# Host Unit Tests 🟢🟡

## What this is
Tests for the parts of `app/` that don't touch hardware (no HAL), compiled with plain `gcc` on your laptop. They catch bugs before anything is flashed, and are a great way for newer members to contribute.

## Tasks (in priority order)
1. 🟢 **CAN float encode/decode** ([`can_bus`](../app/can_bus/) task 1): `20000.0f` ↔ `00 40 9C 46`, `0.25f` ↔ `00 00 80 3E`, negative values, zero
2. 🟢 **Drive command encoding**: `can_encode_drive_cmd()` produces ID `0x401`, DLC 8, correct bytes
3. 🟡 **Gear debounce** and **pedal scaling/deadband**
4. 🟡 **State machine**: every transition in [`../docs/state-machine.md`](../docs/state-machine.md)

## Setup
- Framework: [Unity](https://github.com/ThrowTheSwitch/Unity) (vendor `unity.c`/`unity.h` into `tests/unity/`)
- One test file per module: `test_can_bus.c`, `test_gear.c`, …
- 🟡 Write a `Makefile` so `make -C firmware/tests` builds and runs everything (first person to set this up gets bragging rights)
