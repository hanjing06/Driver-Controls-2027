# System Overview

[Home](../README.md) › [Docs](README.md) › **System overview**

## Where the VCU sits in the car

The Driver Controls board (VCU) sits between the **driver** and the rest of the **low-voltage system**. It connects to:

- **Pre-charge board**: pre-charge button, pre-charge/main contactor status
- **Power distribution board**: LV/HV switches, mode select, LV/HV/HVIL active status
- **Battery box / BMS**: 12 V DC-DC supply, BMS signals, thermal shutoff
- **Pedals**: accelerator (analog), brake
- **Aerobody lighting**: brake lights, DRLs, turn signals
- **Dash**: gear selector, turn/hazard buttons, LCD, indicator LEDs
- **CAN bus**: motor controller and other boards (message set TBD, see `firmware/docs/can-messages.md`)

Off-board connections go through Molex MX150 connectors (2026). Re-evaluate for 2027.

## Voltage domains

| Domain | Voltage | What lives there |
|---|---|---|
| Automotive LV | 12 V (nominal; design for transients) | Switches, lights, contactor indicators, MOSFET loads |
| Logic | 3.3 V (generated on board in 2027) | STM32, CAN transceiver*, LCD, input conditioning outputs |

\*The 2026 board used an MCP2551, which is a **5 V** transceiver. For 2027, either add a 5 V rail or switch to a 3.3 V transceiver (e.g. SN65HVD230 / TCAN334). This is a hardware decision to make in Phase 1.

**Rule:** no 12 V signal touches an MCU pin directly. Inputs go through a divider/clamp or opto/transistor stage, and outputs drive a MOSFET gate.

## Startup sequence

1. LV switch on → board powers up, MCU boots
2. HV switch engaged
3. Driver presses pre-charge → pre-charge contactor closes
4. Pre-charge confirmed
5. Main contactor closes
6. HV active verified
7. Driver selects Ready mode
8. Gear selector out of Neutral → vehicle operational

Fault at any step (thermal shutoff, HVIL open, BMS fault) → dash fault indicator on, and the vehicle state drops to a safe state. Firmware formalizes this in `firmware/docs/state-machine.md`.

## Ownership split

| Area | Hardware | Firmware |
|---|---|---|
| Power, protection, clock, debug header | ✅ owns | reviews |
| Input conditioning, MOSFET drivers | ✅ owns | reviews thresholds/polarity |
| Pin assignment ([ICD](interface-control.md)) | ✅ proposes | ✅ approves |
| `.ioc` / clock config | reviews | ✅ owns |
| State machine, lighting logic, CAN, LCD | reviews | ✅ owns |
| Bring-up | ✅ power & rails | ✅ flash & per-I/O tests |
