<div align="center">

# Sunstang Driver Controls 2027

Driver Controls / Vehicle Control Unit (VCU) PCB for **Western Sunstang**, 2027 car.

</div>

This repo is used to help and guide members throughout the school year to ease onboarding to the team. This team has two subsections: hardware and firmware. To navigate through this repo, start here and follow through the README which explains what each part of the system does and what you'd like to work on.

| Track | Start here | First tasks |
|---|---|---|
| **Hardware** | [`hardware/README.md`](hardware/README.md) | Join a **circuit block** → check part availability → calculate current consumption → design |
| **Firmware** | [`firmware/README.md`](firmware/README.md) | **Integration test** of last year's firmware: VCU, motor controllers and BMS on one CAN bus, drive commands, BMS telemetry, accelerator pedal |

---

## New to GitHub? How to find your way around

You don't need to know Git to read this repo. Everything is clickable in your browser.

- **Every folder has a README.** When you open a folder on GitHub, its README shows up underneath the list of files. That's your instructions for that folder.
- **Click the links**, not the file list. Each page links to the next place you should go.
- **Lost? Look at the line under the page title** (e.g. `Home › Firmware › Research › CAN fundamentals`). Click any part of it to go back up. *Home* always brings you back to this page.
- **Use the page outline.** On any README, click the ☰ list icon at the top right of the file to jump between sections.
- **Search for a file:** press `t` anywhere in the repo and start typing a name (e.g. `can_bus`).

### Where do I go?

| I want to… | Go to |
|---|---|
| Start as a **hardware** member | [Hardware onboarding](hardware/README.md) |
| Start as a **firmware** member | [Firmware onboarding](firmware/README.md) |
| Understand the whole system | [System overview](docs/system-overview.md) |
| See which pin does what | [Pin map (ICD)](docs/interface-control.md) |
| Find my circuit block | [Hardware › circuit blocks](hardware/README.md#4-circuit-blocks-and-assignments) |
| Find my firmware task | [Firmware › integration test](firmware/integration-test/README.md) |
| Find my research topic | [Firmware › research topics](firmware/research/README.md) |
| Learn how to branch, commit and open a PR | [Contributing guide](CONTRIBUTING.md) |
| See what last year's team did | [2026 board notes](docs/reference/2026-vcu.md) · [2025 firmware notes](docs/reference/2025-firmware.md) |

---

## Scope for this year

2026, we designed the ([Sunstang-VCU-2026](https://github.com/hanjing06/Sunstang-VCU-2026)) board using the **STM32 Nucleo-F302R8** dev board, running the [VCU_2025](https://github.com/uixt/VCU_2025) firmware.

**For 2027 we're starting a fresh design and replacing the dev board with the STM32 chip itself (STM32F302R8T6) on our own PCB.** The Nucleo used to give us power regulation, a clock, reset and a programmer. Now we design all of that ourselves.

Because members have a mix of experience, the work is split into small pieces, so there's something for everyone. Pairing a newer member with an experienced one is encouraged everywhere.

## What the board does

The VCU is the low-voltage brain of the car. It reads the driver's controls, decides what the car is allowed to do, commands the motor controllers over CAN, and drives the 12 V lights and indicators.

<p align="center">
  <img src="docs/images/VCU_System_2026.png" width="800" alt="2026 VCU system integration diagram">
  <br><em>2026 system diagram (reference)</em>
</p>

| Subsystem | Hardware block | Firmware module |
|---|---|---|
| 12 V in → 3.3 V, protection | [`power`](hardware/circuits/power/) | — |
| The STM32 chip + clock/reset | [`mcu-core`](hardware/circuits/mcu-core/) | [`common`](firmware/app/common/) |
| Programming & debug | [`debug-programming`](hardware/circuits/debug-programming/) | [flashing guide](firmware/docs/flashing-and-debugging.md) |
| CAN bus | [`can`](hardware/circuits/can/) | [`can_bus`](firmware/app/can_bus/) (tested first in the [integration test](firmware/integration-test/)) |
| Pedals, gear, buttons, mode switch | [`driver-inputs`](hardware/circuits/driver-inputs/) | [`pedals`](firmware/app/pedals/), [`gear`](firmware/app/gear/) |
| Brake / turn / hazard / DRL lights | [`lighting`](hardware/circuits/lighting/) | [`lighting`](firmware/app/lighting/) |
| HV startup chain & indicators | [`hv-interface`](hardware/circuits/hv-interface/) | [`indicators`](firmware/app/indicators/), [`vehicle_state`](firmware/app/vehicle_state/) |
| Driver LCD | [`display`](hardware/circuits/display/) | [`display`](firmware/app/display/) |
| Off-board wiring | [`connectors`](hardware/circuits/connectors/) | — |

Full description: [`docs/system-overview.md`](docs/system-overview.md). Pin map (the contract between hardware and firmware): [`docs/interface-control.md`](docs/interface-control.md).

## Repository layout

```
Driver-Controls-2027/
├── README.md, CONTRIBUTING.md
├── .github/                      issue + PR templates (part-check, task)
├── docs/                         system overview, ICD (pin map), notes on 2025/2026
├── hardware/
│   ├── README.md                 hardware onboarding
│   ├── bom/                      parts-tracker.csv, power-budget.csv, current-calculations.xlsx
│   ├── circuits/                 one folder + README per block:
│   │   ├── power/  mcu-core/  debug-programming/  can/
│   │   └── driver-inputs/  lighting/  hv-interface/  display/  connectors/
│   ├── datasheets/  docs/  fabrication/  libraries/  simulation/
│   └── kicad/DriverControls/     KiCad project (see schematic hierarchy in hardware/kicad/README.md)
│       ├── Sunstang_DriverControls.kicad_pro / .kicad_sch   (root project)
│       ├── DriverControls.kicad_pro / .kicad_sch / .kicad_pcb
│       ├── dc2027.kicad_sch      hierarchy sheet
│       └── STM32 / USB / PowerSupply / User_IO .kicad_sch
└── firmware/
    ├── README.md, DriverControls/ (CubeMX project)
    ├── integration-test/         main project: 01-can-bus-setup, 02-motor-controller,
    │                             03-bms-telemetry, 04-accel-pedal, test-log.md
    ├── research/                 CAN, bxCAN, FreeRTOS, MC & BMS protocols, tools
    ├── examples/                 01-blinky, 02-adc-pedal, 03-can-loopback
    ├── app/                      can_bus, pedals, gear, lighting, indicators, display,
    │                             faults, telemetry, vehicle_state, common
    ├── tests/  tools/  docs/
```

| Folder | What's in it |
|---|---|
| [`docs/`](docs/) | Shared by both tracks: system overview, pin map (ICD), notes on last year's work |
| [`hardware/`](hardware/README.md) | **Hardware onboarding** and everything for the PCB |
| ↳ [`hardware/circuits/`](hardware/README.md#4-circuit-blocks-and-assignments) | One folder per circuit block, each with its own README |
| ↳ [`hardware/bom/`](hardware/bom/) | `parts-tracker.csv` (step 1), `power-budget.csv` + `current-calculations.xlsx` (step 2) |
| ↳ [`hardware/docs/`](hardware/docs/) | How-to guides: part selection, power budget, checklists, layout, bring-up |
| ↳ [`hardware/kicad/`](hardware/kicad/) | KiCad project and schematic hierarchy |
| [`firmware/`](firmware/README.md) | **Firmware onboarding** and all the code |
| ↳ [`firmware/integration-test/`](firmware/integration-test/) | **This year's main project**: one folder per test task, plus the shared test log |
| ↳ [`firmware/research/`](firmware/research/) | One folder per research topic |
| ↳ [`firmware/examples/`](firmware/examples/) | Warm-up exercises on a Nucleo |
| ↳ [`firmware/app/`](firmware/app/) | Later: one folder per new code module |
| ↳ [`firmware/tests/`](firmware/tests/) · [`firmware/docs/`](firmware/docs/) | Laptop unit tests · reference docs |
| [`CONTRIBUTING.md`](CONTRIBUTING.md) | Branching, PRs, commit style |

## TODO

- [ ] **Check availability of all major parts** (stock at 2+ distributors, lifecycle, backup part) and record in [`hardware/bom/parts-tracker.csv`](hardware/bom/parts-tracker.csv): MCU, regulator, CAN transceiver, CAN ESD, crystal, SWD connector, lighting MOSFETs, LCD, MX150 connectors
- [ ] **Update the 20-pin headers** to use the same footprint as the Nucleo board headers
- [ ] **Recalculate current consumption** using [`hardware/bom/current-calculations.xlsx`](hardware/bom/current-calculations.xlsx) (fill the blue cells from datasheets), then pick regulator, fuse and MOSFETs
- [ ] Populate the schematic hierarchy sheets (see [`hardware/kicad/README.md`](hardware/kicad/README.md))
- [ ] **Run the firmware integration test**: VCU, motor controllers and BMS on one CAN bus, drive commands, BMS telemetry and the accelerator pedal (see [`firmware/integration-test/`](firmware/integration-test/))

## Getting started (everyone)

1. **Get access:** ask the Driver Controls Lead to add you to the GitHub repo and the team channel.
2. **Install Git** and clone this repo. New to Git? Try [learngitbranching.js.org](https://learngitbranching.js.org/) (about an hour).
3. **Read** this page and [`docs/system-overview.md`](docs/system-overview.md).
4. **Open your track's README** ([hardware](hardware/README.md) / [firmware](firmware/README.md)) and follow its "first week" section.
5. **Read** [`CONTRIBUTING.md`](CONTRIBUTING.md) before your first PR.

```bash
git pull                              # get the latest
git checkout -b fw/research-can       # branch for your task (hw/... or fw/...)
git add <files>
git commit -m "fw: CAN fundamentals notes"
git push -u origin fw/research-can    # then open a PR on GitHub
```

## Roadmap

| Phase | Hardware | Firmware |
|---|---|---|
| **0. Onboarding** | Join a block, read last year's schematic | Toolchain, warm-up examples, build and flash VCU_2025 on a Nucleo |
| **1. Research & parts** | Part selection & availability per block | CAN, motor controller and BMS research; wire all three devices on one bus |
| **2. Numbers** | Current consumption → regulator, fuse, MOSFET choices | Integration test: drive commands, BMS telemetry, accelerator pedal; record results |
| **3. Schematic** | Each block draws its sheet, design review, pin map frozen | Fix issues the test found; start CAN RX/TX queues and other modules |
| **4. Layout & fab** | Placement, routing, order PCB & parts | Port app modules to the `.ioc` for our pin map (HSE clock) |
| **5. Bring-up** | Power-on checklist | Flash over SWD, validate each I/O |
| **6. Integration** | In-car testing | Full startup sequence and CAN with the rest of the car |

## Glossary

| Term | Meaning |
|---|---|
| VCU | Vehicle Control Unit, this board |
| LV / HV | Low voltage (12 V system) / High voltage (traction battery) |
| Chip-down | Putting the bare microcontroller on our PCB instead of plugging in a dev board |
| CAN | Controller Area Network, the bus all the car's boards talk on |
| Pre-charge | Slowly charging the motor controller's capacitors before closing the main contactor |
| HVIL | High-Voltage Interlock Loop, a safety loop that opens if an HV connector is unplugged |
| BMS | Battery Management System |
| DRL | Daytime Running Light |
| ICD | Interface Control Document, our pin map |
| SWD | Serial Wire Debug, how we flash the chip |
| HAL / `.ioc` | ST's driver library / the CubeMX config file |


## References

- Previous board: [hanjing06/Sunstang-VCU-2026](https://github.com/hanjing06/Sunstang-VCU-2026) · notes: [`docs/reference/2026-vcu.md`](docs/reference/2026-vcu.md)
- Previous firmware: [uixt/VCU_2025](https://github.com/uixt/VCU_2025) · notes: [`docs/reference/2025-firmware.md`](docs/reference/2025-firmware.md)
- [STM32F302R8 product page](https://www.st.com/en/microcontrollers-microprocessors/stm32f302r8.html): datasheet, RM0365 reference manual
- ST AN4206: *Getting started with STM32F3 hardware development*
