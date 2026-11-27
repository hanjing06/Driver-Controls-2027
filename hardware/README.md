# Hardware: 2027 Driver Controls PCB

[Home](../README.md) › **Hardware**

> **New hardware member? This page is your onboarding.** Read it top to bottom, then open the README of the circuit block you've been assigned.

---

## 1. What the board does

The Driver Controls board (VCU) is the low-voltage brain of the car. It:

- **reads the driver's controls:** accelerator pedal, brake, gear selector (N/R/D), turn-signal and hazard buttons, Ready/Charge mode switch
- **drives the 12 V lights:** brake lights, turn signals, daytime running lights (DRLs)
- **shows the HV system's status:** pre-charge and main-contactor indicator LEDs, LV/HV/HVIL-active LEDs, dash fault light
- **talks to the rest of the car over CAN:** sends drive commands to the motor controllers, receives speed and battery data
- **shows information to the driver** on a small I²C LCD

There are two voltage worlds on the board. The **12 V side** has the car's switches, lights and LEDs. The **3.3 V side** has the microcontroller. A lot of the circuitry exists to move signals safely between them.

The full system description is in [`../docs/system-overview.md`](../docs/system-overview.md), and the pin list is in [`../docs/interface-control.md`](../docs/interface-control.md).

## 2. What's different this year: new design cycle, chip-down

The previous board ([Sunstang-VCU-2026](https://github.com/hanjing06/Sunstang-VCU-2026)) plugged in an **STM32 Nucleo dev board**. The Nucleo quietly handled power regulation, the clock, reset and programming for us.

**This year we start a fresh design and put the STM32F302R8T6 chip directly on our PCB.** Everything the Nucleo did, we now design ourselves. That's why the board is split into **circuit blocks** below, and each new member gets one.

You can use the 2026 schematic as a reference for *what* the board needs to do. Don't copy it as-is: every block gets re-checked and redesigned.

## 3. How we work: the three steps (in this order)

Every block goes through the same steps. **Nobody starts in KiCad.** We find out what's buyable and how much current it needs first.

| Step | What you do | Where it goes | How-to |
|---|---|---|---|
| **1. Parts & availability** | Pick the real parts for your block. Check stock at 2+ distributors, check that they're still in production, and find a backup part | Your rows in [`bom/parts-tracker.csv`](bom/parts-tracker.csv) | [`docs/part-selection.md`](docs/part-selection.md) |
| **2. Current consumption** | From the datasheets, write down how much current your block draws (or passes through) on each rail | Your rows in [`bom/power-budget.csv`](bom/power-budget.csv) | [`docs/power-budget.md`](docs/power-budget.md) |
| **3. Design** | Calculate component values, simulate if useful, then draw your block's schematic sheet | Calcs/sims in your block folder; schematic in [`kicad/`](kicad/) | Your block's README + [`docs/schematic-checklist.md`](docs/schematic-checklist.md) |

After all blocks pass schematic review, the experienced members lead **layout** ([`docs/layout-guidelines.md`](docs/layout-guidelines.md)) and **bring-up** ([`docs/bringup-procedure.md`](docs/bringup-procedure.md)). Everyone is welcome to help.

## 4. Circuit blocks and assignments

Each block has **one owner** (someone with some experience) and **one to three members**. To help you pick one that fits you:

- **Beginner-friendly** (Connectors, Display, Debug & programming). Good if this is your first circuit. Mostly part research and simple, well-documented circuits.
- **Intermediate** (HV interface, Driver inputs, Lighting, CAN). You've done a circuits course or a small project. Involves some calculations.
- **Advanced** (Power, MCU core). Critical to the board working at all. Best owned by someone experienced, with a beginner pairing in.

| Block | Folder | What it is | Owner | Members |
|---|---|---|---|---|
| Connectors | [`circuits/connectors/`](circuits/connectors/) | Every wire that enters or leaves the board | |Cindy|
| Display | [`circuits/display/`](circuits/display/) | Driver LCD over I²C | | |
| Debug & programming | [`circuits/debug-programming/`](circuits/debug-programming/) | SWD header, UART header, status LEDs, test points | | |
| HV interface & indicators | [`circuits/hv-interface/`](circuits/hv-interface/) | LV/HV switches, pre-charge & contactor LEDs, status LEDs | | |
| Driver inputs | [`circuits/driver-inputs/`](circuits/driver-inputs/) | Pedal + buttons/switches: 12 V → 3.3 V conditioning | |Samarth|
| Lighting | [`circuits/lighting/`](circuits/lighting/) | MOSFETs that switch the 12 V lights | | |
| CAN | [`circuits/can/`](circuits/can/) | CAN transceiver, protection, termination | | |
| Power | [`circuits/power/`](circuits/power/) | 12 V input protection → 3.3 V regulator | | |
| MCU core | [`circuits/mcu-core/`](circuits/mcu-core/) | The STM32 chip, decoupling, crystal, reset, boot | |Owen, Sahil|

*The Driver Controls Lead fills in names at the first meeting. If you're not sure where you fit, pick a beginner-friendly block, or ask to pair into an advanced one. Pairing is the fastest way to learn.*

Each block README has the same sections:
1. **What this circuit does**
2. **How it was done before** (2026 board)
3. **What changes now that we're chip-down**
4. **Your tasks**, split by Step so everyone in the block has something to do
5. **Done when**: what to hand in
6. **Resources**

## 5. Your first week

1. **Set up**
   - Install [KiCad 9](https://www.kicad.org/download/) and Git, and clone this repo
   - Make free accounts on **Digi-Key**, **Mouser** and **LCSC** (you need them for Step 1)
2. **Read**
   - This page, then [`../docs/system-overview.md`](../docs/system-overview.md)
   - Your block's README
3. **Look at the old board.** Open `DC.kicad_sch` from [Sunstang-VCU-2026](https://github.com/hanjing06/Sunstang-VCU-2026) and find your block in it. Notes on the old parts are in [`../docs/reference/2026-vcu.md`](../docs/reference/2026-vcu.md).
4. **Start Step 1 for your block.** Open an issue using the **"Part check"** template, assign yourself, and work on a branch `hw/<block>-parts`.

**New to KiCad?** Do the [KiCad Getting Started guide](https://docs.kicad.org/9.0/en/getting_started_in_kicad/getting_started_in_kicad.html) during Steps 1–2. You'll need it for Step 3.

## 6. Folder map

| Folder | Contents |
|---|---|
| [`circuits/`](circuits/) | **One folder per block**, with its README (your instructions), calculations, sims, notes |
| [`bom/`](bom/) | `parts-tracker.csv` (Step 1), `power-budget.csv` (Step 2), exported BOMs per revision |
| [`docs/`](docs/) | How-to guides shared by every block: part selection, power budget, chip-down migration, checklists, layout, bring-up |
| [`kicad/`](kicad/) | The KiCad project. One hierarchical sheet per block |
| [`libraries/`](libraries/) | Project-local symbols / footprints / 3D models |
| [`datasheets/`](datasheets/) | Datasheet **links** for every chosen part |
| [`simulation/`](simulation/) | Board-level sims (block-level sims can live in the block folder) |
| [`fabrication/`](fabrication/) | Gerbers, drill, pick-and-place per revision |

## 7. Rules

- **Only use parts that are approved in `parts-tracker.csv`** in the schematic.
- **One person edits a KiCad sheet at a time.** Say so in your issue before you open it.
- Net names must match [`../docs/interface-control.md`](../docs/interface-control.md). If you need to change a pin, open an `icd/` PR (a firmware member has to approve it).
- Stuck for more than ~30 minutes? Ask your block owner or the team channel. That's expected, not a failure.

Branching and PR rules: [`../CONTRIBUTING.md`](../CONTRIBUTING.md).
