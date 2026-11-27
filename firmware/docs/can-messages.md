# CAN Messages

[Home](../../README.md) › [Firmware](../README.md) › [Docs](README.md) › **CAN messages**

Bus: **500 kbit/s**, standard 11-bit IDs (from VCU_2025 `.ioc`).
The IDs below are from VCU_2025 `CAN_Receive.c` / `CAN_Transmit.c`. They follow the Prohelion motor-controller base-address layout (driver controls base `0x400`, MC1 base `0x500`, MC2 base `0x600`). **Confirm against the 2027 motor controller and BMS configs.**

## Transmitted by VCU

| ID | Name | Period | Data | Status |
|---|---|---|---|---|
| `0x401` | Motor drive command | 10 ms (TBD) | bytes 0–3: velocity (float, rpm) · bytes 4–7: current (float, 0–1) | From 2025 |
| `0x4xx` | VCU status (state, faults) | 100 ms | TBD | New |

## Received by VCU

| ID | Source | Name | Used for | Status |
|---|---|---|---|---|
| `0x500` | MC1 | Identification | — | 2025 (commented out) |
| `0x503` | MC1 | Velocity | Speed display, gear-change interlock | 2025 |
| `0x50B` | MC1 | Heatsink temp | Display / faults | 2025 (commented out) |
| `0x603` | MC2 | Velocity | Averaged with MC1 | 2025 |
| `0x60B` | MC2 | Heatsink temp | Display / faults | 2025 (commented out) |
| `0x701` | BMS | Temperatures (high/low) | Display / faults | 2025 |
| `0x702` | BMS | Pack & cell voltages | Display | 2025 |
| `0x703` | BMS | Pack current | Display | 2025 |

Bytes are little-endian. Floats are IEEE-754 (VCU_2025 decodes via `union Data { float f; int i; uint8_t byte[4]; }`).

**TODO:** move this into a `.dbc` file in `../tools/` so SavvyCAN/cantools can decode logs.
