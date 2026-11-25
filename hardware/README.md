# Hardware

KiCad 9 design for the 2027 Driver Controls PCB, with the STM32 chip directly on the board.

## Workflow

**1. Part selection & availability** → **2. Current consumption / power budget** → 3. Schematic → 4. Layout & fab → 5. Bring-up

New members start at Step 1: see [`docs/onboarding.md`](docs/onboarding.md).

## Folder map

| Folder | Contents |
|---|---|
| [`docs/`](docs/) | Onboarding, requirements, Nucleo→chip migration, checklists, bring-up |
| [`kicad/`](kicad/) | KiCad project. Hierarchical schematic, one sheet per block |
| [`libraries/`](libraries/) | Project-local `symbols/`, `footprints/`, `3dmodels/` |
| [`datasheets/`](datasheets/) | Datasheet **links** for every part (don't commit PDFs) |
| [`simulation/`](simulation/) | LTspice / KiCad sims (input dividers, RC filters, power stage) |
| [`bom/`](bom/) | `parts-tracker.csv` (Step 1), `power-budget.csv` (Step 2), exported BOMs per revision |
| [`fabrication/`](fabrication/) | Gerbers, drill, pick-and-place per revision: `revA/` |

## Schematic sheets & owners

| Sheet | Contents | Owner |
|---|---|---|
| `power.kicad_sch` | 12 V input, reverse-polarity & TVS, fuse, 12 V→3.3 V regulator, (5 V if needed) | TBD |
| `mcu.kicad_sch` | STM32F302R8, decoupling, VDDA filter, HSE crystal, NRST, BOOT0 | TBD |
| `debug.kicad_sch` | SWD connector, UART header, status LEDs, test points | TBD |
| `can.kicad_sch` | CAN transceiver, ESD (NUP2105), termination jumper | TBD |
| `driver_inputs.kicad_sch` | Pedal ADC conditioning, 12 V digital input stages (gear, turn, hazard, mode) | TBD |
| `lighting.kicad_sch` | Low-side MOSFET drivers for brake/turn/DRL, flyback/protection | TBD |
| `hv_interface.kicad_sch` | LV/HV switch pass-through, pre-charge & contactor indicator LEDs, HVIL | TBD |
| `display.kicad_sch` | I²C LCD, pull-ups | TBD |
| `connectors.kicad_sch` | All off-board connectors | TBD |

Start in [`docs/onboarding.md`](docs/onboarding.md).
