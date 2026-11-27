# Step 1: Part Selection & Availability Check

[Home](../../README.md) › [Hardware](../README.md) › [Docs](README.md) › **Part selection**

**This is the first task for every new hardware member.** Before anyone draws a schematic, we confirm that every part on the board can actually be bought, and in quantity, for the whole build season.

Work goes into [`../bom/parts-tracker.csv`](../bom/parts-tracker.csv). One row per part.

## Why this comes first

- A part that's out of stock or end-of-life forces a redesign later, after the footprint is already on the PCB.
- Chip-down means new parts we've never bought (MCU, regulator, crystal, SWD connector).
- The current numbers you find in datasheets here feed straight into **Step 2: [power budget](power-budget.md)**.

## Procedure (per part)

1. **Start from the function.** Use the subsystem list in the [ICD](../../docs/interface-control.md) and the 2026 parts in [`docs/reference/2026-vcu.md`](../../docs/reference/2026-vcu.md).
2. **Find the exact MPN.** Package and suffix matter: `STM32F302R8T6` ≠ `STM32F302R8T7`.
3. **Check stock at ≥ 2 distributors.** Digi-Key, Mouser, LCSC (needed if JLCPCB assembles). Record the stock qty and unit price @ 10 pcs.
4. **Check lifecycle status.** "Active" only. Avoid NRND / EOL / Obsolete.
5. **Find an alternate.** A drop-in second source, or at least a same-footprint equivalent.
6. **Grab the datasheet link**, and note the **supply current** (typ/max) and any **load current** for the power budget.
7. **Check the footprint exists**, either in the KiCad standard library, on SnapEDA/Ultra Librarian, or marked "need to draw".

## Pass/fail rule

A part is ✅ **approved** when: Active, stock ≥ 100× our qty (or ≥ 500 pcs) at 2 distributors, alternate identified, datasheet linked.

Otherwise mark it ⚠️ and raise it at the next meeting.

## Parts to check first (priority order)

| Priority | Function | 2026 part / starting point | Owner |
|---|---|---|---|
| 1 | MCU | STM32F302R8T6 (LQFP-64) | |
| 2 | 12 V → 3.3 V regulator | TBD: buck or LDO (see power budget) | |
| 3 | CAN transceiver | MCP2551 (5 V) → evaluate 3.3 V parts (SN65HVD230, TCAN334, MCP2562 w/ VIO) | |
| 4 | 8 MHz HSE crystal | TBD | |
| 5 | SWD connector | 2×5 1.27 mm or Tag-Connect TC2030 | |
| 6 | Lighting MOSFETs | FQP30N06L (TO-220) → SMD logic-level alternative | |
| 7 | Off-board connectors | Molex MX150 | |
| 8 | Input protection | TVS, reverse-polarity FET/diode, fuses/PPTC | |
| 9 | LCD | NHD-C0220BIZ-FSW-FBW-3V3M | |
| 10 | Passives, LEDs | 1206 (2026) → decide on 0805/0603 | |
