# Connectors

[Home](../../../README.md) › [Hardware](../../README.md) › **Connectors**

**Owner:** · **Members:**
**KiCad sheet:** `kicad/connectors.kicad_sch`

## What this circuit does

Every wire that enters or leaves the board goes through a connector: 12 V power, pedals, gear selector, dash buttons, lights, the HV-interface lines, CAN, and the LCD. This block decides **which connectors we use and what goes on every pin**. Every other block depends on it, and the wiring harness team builds their cables from it.

## How it was done before

2026 board: **Molex MX150** (348302001) sealed automotive connectors.

## What changes now (chip-down)

The board will likely be smaller, so connector count and placement matter more. Group signals sensibly (e.g. one connector for the dash, one for lights, one for power/HV interface).

## Your tasks

### Step 1: Parts & availability
- Check MX150 availability (headers **and** mating housings + crimp terminals, since the harness team needs those too).
- Find one alternative family (e.g. Molex Micro-Fit 3.0, TE Deutsch DTM) and compare: current per pin, locking, sealing, cost, crimp tool needed.

### Step 2: Current consumption
- For every connector pin, write the max current it carries (from the other blocks' numbers in `power-budget.csv`). Make sure it's below the pin rating. Power and lighting pins especially.

### Step 3: Design
- Make a **pinout table** for each connector in `pinout.md`: pin #, net name (from the ICD), direction, max current, wire gauge.
- Draw `connectors.kicad_sch` with net labels matching the ICD exactly.
- Review the pinout with the harness/electrical team and the people who own the boards on the other end.

## Research questions (`notes.md`)
- What makes a connector "automotive-grade" (vibration, locking, sealing)?
- How do you choose wire gauge for a current?
- Why put GND pins next to signal pins?

## Done when
- [ ] Connector parts (board side + mating side) approved
- [ ] `pinout.md` complete, with current per pin checked
- [ ] `connectors.kicad_sch` drawn, reviewed by the harness/electrical lead

## Resources
- Molex MX150 product family page and datasheets
- [`../../../docs/interface-control.md`](../../../docs/interface-control.md)
- [`../../../docs/images/VCU_System_2026.png`](../../../docs/images/VCU_System_2026.png)
