# Host Unit Tests

Tests for hardware-independent logic in `app/` (no HAL), compiled with plain `gcc` on your laptop.

First targets:
- `vs_next()` in `vehicle_state.c`: every transition in [`state-machine.md`](../docs/state-machine.md), plus "can't enter DRIVE without brake"
- Pedal scaling, deadband and implausibility thresholds
- CAN float decode/encode (byte order)

Framework: [Unity](https://github.com/ThrowTheSwitch/Unity) (single C file, easy to vendor). Run: `make -C firmware/tests`. *(Makefile TBD.)*
