# Hardware Onboarding

Hardware work happens in this order. **Don't skip ahead to the schematic.**

```
 Step 1                 Step 2                    Step 3              Step 4         Step 5
 Part selection   →     Current consumption  →    Schematic     →     Layout   →     Bring-up
 & availability         / power budget            design              & fab
 part-selection.md      power-budget.md           schematic-          layout-        bringup-
                                                  checklist.md        guidelines.md  procedure.md
```

## Setup

1. Install [KiCad 9](https://www.kicad.org/download/) and Git.
2. Make accounts on **Digi-Key**, **Mouser** and **LCSC** (free). You need them for Step 1.
3. Clone this repo.

## Your first tasks

### Task 1: Check part availability (Step 1)
Read [`part-selection.md`](part-selection.md). You'll be assigned one or two functions from its priority table (e.g. "CAN transceiver"). For each:
- Find candidate MPNs, check stock/lifecycle/price at 2+ distributors, find an alternate
- Fill in your rows in [`../bom/parts-tracker.csv`](../bom/parts-tracker.csv)
- Open a PR titled `hw: part check – <function>`

### Task 2: Calculate current consumption (Step 2)
Read [`power-budget.md`](power-budget.md). Using the datasheets from Task 1:
- Fill in the current numbers for your parts in [`../bom/power-budget.csv`](../bom/power-budget.csv)
- Once all rows are in, the team totals each rail and picks the regulator and fuse ratings

### Task 3: Learn KiCad, then start designing (Step 3)
- Work through the [KiCad Getting Started guide](https://docs.kicad.org/9.0/en/getting_started_in_kicad/getting_started_in_kicad.html)
- Read the 2026 schematic ([Sunstang-VCU-2026](https://github.com/hanjing06/Sunstang-VCU-2026), `DC.kicad_sch`) and trace one signal end to end, e.g. `LSignalLightIn`: connector → conditioning → MCU pin
- Read [`nucleo-to-chip-migration.md`](nucleo-to-chip-migration.md) and ST **AN4206**
- Claim a schematic sheet (see [`../README.md`](../README.md)) and start drawing, using parts from the approved tracker only

## Docs in this folder

| Step | Doc | What it's for |
|---|---|---|
| 1 | [`part-selection.md`](part-selection.md) | How to check availability; priority part list |
| 2 | [`power-budget.md`](power-budget.md) | How to calculate current per rail and size the regulator/fuse |
| — | [`design-requirements.md`](design-requirements.md) | What the board must do: electrical, mechanical, safety |
| 3 | [`nucleo-to-chip-migration.md`](nucleo-to-chip-migration.md) | Everything the Nucleo did that we now design ourselves |
| 3 | [`schematic-checklist.md`](schematic-checklist.md) | Use before every schematic review |
| 4 | [`layout-guidelines.md`](layout-guidelines.md) | Stackup, placement, routing rules |
| 5 | [`bringup-procedure.md`](bringup-procedure.md) | First power-on of an assembled board |
