# Power

[Home](../../../README.md) › [Hardware](../../README.md) › **Power**

**Owner:** · **Members:**
**KiCad sheet:** `kicad/power.kicad_sch`

## What this circuit does

Takes the car's **12 V** low-voltage supply and turns it into a clean **3.3 V** rail for the microcontroller, CAN transceiver and LCD. It also **protects the board** from what a car's 12 V system can throw at it: wiring backwards (reverse polarity), voltage spikes (transients), and shorts (overcurrent).

```
12 V in ─► Fuse/PPTC ─► Reverse-polarity protection ─► TVS clamp ─► Regulator ─► 3.3 V rail
                                                                     (buck and/or LDO)
```

If this block doesn't work, nothing on the board works. That's why it's one of the most critical blocks.

## How it was done before

The 2026 board fed 12 V into the **Nucleo**, and the Nucleo's own regulator made 3.3 V. Our board only had fuses/PPTC (PPTC021LFBN-RC) on the input.

## What changes now (chip-down)

We design the 3.3 V regulator ourselves. Key decision: **LDO, buck, or buck → LDO?**
An LDO dropping 12 V → 3.3 V burns `(12 − 3.3) × I` as heat: at 100 mA that's ~0.9 W, which is a lot for a small part. A buck converter is efficient but noisier and harder to lay out.

Also decide: **do we need a 5 V rail?** Only if the CAN block keeps a 5 V transceiver. Coordinate with the CAN block.

## Your tasks

### Step 1: Parts & availability
- Find 2–3 candidate **fuses/PPTCs** and **TVS diodes** rated for automotive 12 V. Fill in `parts-tracker.csv`.
- Find a **reverse-polarity** part: a Schottky diode (simple) or P-MOSFET (lower loss). List one of each.
- Find 2–3 candidate **3.3 V regulators** (at least one buck, one LDO). Record input voltage range, output current, quiescent current, package, stock.
- Pick the regulator once Step 2 numbers are in.

### Step 2: Current consumption
- Collect the 3.3 V current from every other block (MCU, CAN, LCD, LEDs, pull-ups) into the 3.3 V section of `power-budget.csv`.
- Add 25 % margin → required regulator current.
- Calculate regulator heat (LDO) or efficiency/input current (buck), and the temperature rise `ΔT = P × θJA`.
- Size the **input fuse** from the total 12 V current (this block + lights + LEDs).

### Step 3: Design
- Draw the fuse + reverse-polarity + TVS section from the datasheets' typical application circuits.
- Design the regulator: input/output caps, inductor (buck), feedback resistors, per the datasheet. Write the calcs in `calcs.md`.
- Add a power-good LED and test points on 12 V, 3.3 V and GND.
- *Optional:* simulate the regulator in LTspice (many TI/ADI parts have models) → save in this folder.

## Research questions (write answers in `notes.md`)
- What transients can a 12 V vehicle system see (load dump, cranking)? What does our DC-DC from the battery box actually output?
- Diode vs. P-MOSFET reverse protection: what are the trade-offs?
- LDO vs. buck: efficiency, noise, cost, layout difficulty. Which would you pick and why?

## Done when
- [ ] All power parts approved in `parts-tracker.csv`
- [ ] 3.3 V and 12 V totals filled in `power-budget.csv`, with regulator and fuse choice written at the top
- [ ] `calcs.md` with component value calculations
- [ ] `power.kicad_sch` passes [`../../docs/schematic-checklist.md`](../../docs/schematic-checklist.md) (Power section)

## Resources
- ST AN4206, section on power supply schemes
- TI *"Understanding the Basics of LDO Regulators"* / *"Basic Calculation of a Buck Converter's Power Stage"* (SLVA477)
- Nucleo-64 schematic (MB1136): see how ST did it
- [`../../docs/power-budget.md`](../../docs/power-budget.md)
