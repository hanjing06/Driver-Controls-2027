# Contributing

## Branches

`main` is protected: no direct pushes. Work on a branch named after your track:

| Prefix | Use |
|---|---|
| `hw/` | Hardware: `hw/power-stage`, `hw/can-transceiver` |
| `fw/` | Firmware: `fw/pedal-adc`, `fw/state-machine` |
| `docs/` | Docs only |
| `icd/` | Changes to `docs/interface-control.md` (needs HW + FW review) |

## Commits

Short, present tense, prefixed: `hw: add 3V3 buck`, `fw: debounce gear selector`, `docs: update ICD for CAN pins`.

## Pull requests

- Link the issue (`Closes #12`)
- **Hardware PRs:** include a screenshot/PDF of changed sheets, and confirm ERC/DRC pass
- **Firmware PRs:** confirm it builds in CubeIDE, and say what you tested on (Nucleo / real board / host test)
- At least **1 approval** (2 for ICD changes: one HW, one FW)

## Hardware-specific

- One person edits a KiCad sheet at a time. KiCad files don't merge well. Claim the sheet in the issue first.
- New symbols/footprints go in `hardware/libraries/`, not your personal KiCad library.
- Every part needs MPN + datasheet link in its fields.

## Firmware-specific

- Our code goes in `firmware/app/` and `firmware/drivers/`. Only edit generated CubeMX files between `/* USER CODE BEGIN */` / `/* USER CODE END */`.
- Follow [`firmware/docs/coding-standards.md`](firmware/docs/coding-standards.md).
