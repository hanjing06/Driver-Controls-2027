# KiCad Project

[Home](../../README.md) › [Hardware](../README.md) › **KiCad**

Project: `kicad/DriverControls/` (KiCad). **One editor per sheet at a time.** Claim it in the issue before you start.

## Schematic hierarchy

| Sheet | File | Purpose |
|---|---|---|
| Root | `Sunstang_DriverControls.kicad_sch` | Top-level project sheet. Currently holds the imported reference design; it will hold only the hierarchy once sheets are populated |
| `dc2027` | `dc2027.kicad_sch` | Hierarchy sheet: block diagram that ties the four sub-sheets together (inter-sheet labels and nets) |
| `PowerSupply` | `PowerSupply.kicad_sch` | 12 V input, fuse/PPTC, reverse-polarity and TVS protection, 3.3 V regulator |
| `STM32` | `STM32.kicad_sch` | STM32F302R8 chip: decoupling, HSE crystal, reset, boot, SWD, status LEDs, CAN transceiver and protection |
| `USB` | `USB.kicad_sch` | USB connector, ESD protection and USB-UART bridge for the serial/debug console |
| `User_IO` | `User_IO.kicad_sch` | Driver-facing I/O: pedal and button conditioning, lighting MOSFETs, HV/pre-charge LEDs, LCD, off-board connectors |
| (stub) | `DriverControls.kicad_sch/.kicad_pcb` | Empty project stub; the PCB will live here |

These four sub-sheets replace the older per-block file plan; the block READMEs in [`../circuits/`](../circuits/) map onto them (power → PowerSupply; mcu-core, debug-programming, can → STM32; driver-inputs, lighting, hv-interface, display, connectors → User_IO).

**Library tables** should use `${KIPRJMOD}` relative paths, e.g. `${KIPRJMOD}/../../libraries/symbols/Sunstang.kicad_sym`.
