# Step 2: Current Consumption / Power Budget

[Home](../../README.md) › [Hardware](../README.md) › [Docs](README.md) › **Power budget**

Once parts are picked ([Step 1](part-selection.md)), we add up how much current each rail must supply. **This decides the regulator** (buck vs. LDO, current rating), the input fuse, trace widths and connector ratings. Do it before the schematic.

Fill in [`../bom/power-budget.csv`](../bom/power-budget.csv).

## How to calculate

For each load, from its datasheet:

| Column | Meaning |
|---|---|
| Rail | 3.3 V, 5 V (if any), 12 V |
| Qty | How many on the board |
| I_typ / I_max (mA) | Per unit, from the datasheet's electrical characteristics |
| Duty | Fraction of time it's on (e.g. turn signal ≈ 0.5, MCU = 1) |
| Total I_max | `Qty × I_max` (design to **max**, not typical) |

Then for each rail: **sum of Total I_max × 1.25 margin** = required regulator output current.

## Regulator power check

- **LDO:** `P_loss = (V_in − V_out) × I_out`. From 12 V to 3.3 V at 100 mA that's **0.87 W**, which is too hot for a small LDO. This is why a buck (or buck → LDO) is likely.
- **Buck:** `P_in = (V_out × I_out) / efficiency`; `I_in = P_in / V_in`.
- Check package thermal resistance: `ΔT = P_loss × θ_JA`.

## 12 V side

12 V loads (lights, LEDs on 12 V) don't go through our regulator but **do** go through our connectors, fuses, MOSFETs and traces. Sum them separately to size:
- Input fuse and connector pins
- MOSFET `P = I² × R_DS(on)` at 3.3 V gate drive
- Trace widths ([layout guidelines](layout-guidelines.md))

## Loads to include

**3.3 V:** STM32 (run mode @ 64 MHz, all peripherals on, see datasheet table "Typical and maximum current consumption"), CAN transceiver (dominant state is worst case), LCD + backlight, status/indicator LEDs, I²C pull-ups, input-stage pull-ups, debugger target power (if any)

**12 V:** brake lights ×3, turn signals ×3 per side, DRLs, pre-charge (blue ×5) and main-contactor (green ×5) LEDs, HV/LV/HVIL/fault LEDs, MOSFET gate pull-downs, input dividers

## Output of this step

A short summary at the top of the CSV / PR:
- 3.3 V rail: ___ mA max → regulator choice: ___
- 12 V total through board: ___ A → input fuse: ___ A
- Worst-case board power: ___ W
