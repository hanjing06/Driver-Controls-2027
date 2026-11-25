# KiCad Project

Create the project here with **KiCad 9** as `DriverControls.kicad_pro`, then add hierarchical sheets (see the table in [`../README.md`](../README.md)):

```
kicad/
├── DriverControls.kicad_pro
├── DriverControls.kicad_sch      ← root sheet: block diagram of hierarchical sheets only
├── DriverControls.kicad_pcb
├── power.kicad_sch
├── mcu.kicad_sch
├── debug.kicad_sch
├── can.kicad_sch
├── driver_inputs.kicad_sch
├── lighting.kicad_sch
├── hv_interface.kicad_sch
├── display.kicad_sch
├── connectors.kicad_sch
├── sym-lib-table                 ← points to ../libraries/symbols
└── fp-lib-table                  ← points to ../libraries/footprints
```

**Library tables** should use `${KIPRJMOD}` relative paths so they work on everyone's machine, e.g.
`${KIPRJMOD}/../libraries/symbols/Sunstang.kicad_sym`.

**One editor per sheet at a time.** Claim it in the issue before you start.
