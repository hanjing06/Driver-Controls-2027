# MCU Core

[Home](../../../README.md) › [Hardware](../../README.md) › **MCU core**

**Owner:** · **Members:**
**KiCad sheet:** `kicad/mcu.kicad_sch`

## What this circuit does

This is the **STM32F302R8T6** (LQFP-64) and the minimum circuitry it needs to run:

| Part of the block | Why it's needed |
|---|---|
| Decoupling caps (100 nF per VDD pin + bulk) | Supply clean, instant current to the chip; without them it resets randomly |
| VDDA filter (ferrite + caps) | Clean supply for the ADC, so the accelerator pedal reading is stable |
| 8 MHz HSE crystal + load caps | Accurate clock. CAN communication fails with a sloppy clock |
| NRST circuit | Clean reset at power-up, plus an optional reset button |
| BOOT0 pull-down | Makes the chip run our program instead of the factory bootloader |

## How it was done before

All of this was on the **Nucleo dev board**. The 2026 schematic only shows the Nucleo's headers, not the chip. VCU_2025 firmware ran on the chip's internal oscillator (HSI) because there was no crystal.

## What changes now (chip-down)

Everything above is new for us. The good news: ST publishes a known-good reference (the Nucleo-64 schematic) and an application note (AN4206) that walk through each piece.

## Your tasks

### Step 1: Parts & availability
- Check availability of **STM32F302R8T6** (and a backup: e.g. another F302/F303 in LQFP-64 with the same pinout). Fill `parts-tracker.csv`.
- Find an **8 MHz crystal** in stock. Write down its **load capacitance (CL)** and ESR. You'll need them in Step 3.
- Pick the decoupling capacitor and ferrite bead parts (size, voltage rating, dielectric X7R).

### Step 2: Current consumption
- From the STM32F302R8 datasheet, find **run-mode current at 64 MHz with peripherals on** (typ and max) → `power-budget.csv`.
- Add I/O current: how many LEDs/pins does the MCU drive directly? Ask the other blocks.

### Step 3: Design
- Count the VDD/VSS pins on the LQFP-64 and place one 100 nF cap per VDD pin.
- Calculate the **crystal load caps**: `C = 2 × (CL − C_stray)`, assume C_stray ≈ 3–5 pF. Show your work in `calcs.md`.
- VDDA filter, NRST and BOOT0 circuits from AN4206.
- Pin assignment: with the firmware lead, assign every signal in [`../../../docs/interface-control.md`](../../../docs/interface-control.md) to a real pin. Check alternate functions in the **datasheet pinout table**, not just CubeMX.

## Research questions (`notes.md`)
- Why does every VDD pin need its own capacitor, placed as close as possible?
- Why is the internal HSI oscillator not good enough for CAN? (Hint: look up the HSI accuracy in the datasheet and CAN's clock tolerance.)
- What happens at power-up if BOOT0 is floating?

## Done when
- [ ] MCU, crystal, caps, ferrite approved in `parts-tracker.csv`
- [ ] MCU current in `power-budget.csv`
- [ ] `calcs.md` with crystal load cap calculation
- [ ] ICD pins all assigned (status DRAFT → FROZEN after review)
- [ ] `mcu.kicad_sch` passes the MCU section of the schematic checklist

## Resources
- [STM32F302R8 datasheet & RM0365](https://www.st.com/en/microcontrollers-microprocessors/stm32f302r8.html)
- **ST AN4206**: Getting started with STM32F3 hardware development (read this first)
- **ST AN2867**: Oscillator design guide for STM32
- Nucleo-64 schematic (MB1136)
- Phil's Lab: "STM32 PCB design" videos
- [`../../docs/nucleo-to-chip-migration.md`](../../docs/nucleo-to-chip-migration.md)
