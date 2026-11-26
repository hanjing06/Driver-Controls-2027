# Driver Inputs 🟡

**Owner:** · **Members:**
**KiCad sheet:** `kicad/driver_inputs.kicad_sch`

## What this circuit does

Everything the driver touches comes in through here, and must be converted so the 3.3 V microcontroller can read it **without being damaged**.

| Signal | Type | Comes from |
|---|---|---|
| `AccelIn` | Analog | Accelerator pedal |
| `BrakePedalIn` | Analog or digital (TBD) | Brake pedal |
| `Neutral`, `Reverse`, `Drive` | 12 V digital | Gear selector (rotary switch) |
| `LSignalLightIn`, `RSignalLightIn`, `HazardIn` | 12 V digital | Dash buttons (latching) |
| `ReadyMode`, `ChargeMode` | 12 V digital | Mode switch (SPDT) |
| `ThermalShutoff` | 12 V digital | Thermal sensor / BMS |
| `SupBattMonitor` | Analog | 12 V supplemental battery voltage |

Two kinds of circuit:
1. **12 V digital → 3.3 V digital:** a voltage divider + clamp, or a transistor/optocoupler stage, plus an RC filter to remove switch bounce and noise.
2. **Analog → ADC (0–3.3 V):** a divider so the max input becomes ≤ 3.3 V, plus an RC low-pass filter.

**This block is repeated ~10 times, so it's great for a team with several beginners.** Once one stage is designed, others can copy and check it.

## How it was done before

The 2026 board had input stages from the connectors to the Nucleo pins. Open `DC.kicad_sch` from [Sunstang-VCU-2026](https://github.com/hanjing06/Sunstang-VCU-2026) and trace `LSignalLightIn`.

## What changes now (chip-down)

The topology can stay similar. Re-check every value, because the pins are now on our own chip. Decide if any 12 V HV-status signals (e.g. `HVActive`) should also be read by the MCU.

## Your tasks

### Step 1: Parts & availability
- 🟢 Find the accelerator and brake pedal sensors' datasheets (ask the mech/electrical lead what pedals the car uses). Write down output voltage range.
- 🟢 Pick resistor/capacitor sizes (0805 or 0603), clamp diodes (e.g. BAT54S), and check stock.
- 🟡 If using transistor or opto stages: compare 2 parts each.

### Step 2: Current consumption
- 🟢 For each 12 V input stage: current through the divider at 12 V (`I = 12 / (R1 + R2)`) × number of inputs → `power-budget.csv`.

### Step 3: Design
- 🟢 **Digital stage:** pick R1/R2 so 12 V → ~3.0 V. Check the *worst case* (e.g. 14.4 V when charging, or a spike) stays ≤ 3.6 V with the clamp. Show calcs in `calcs.md`.
- 🟢 **RC filter:** pick R and C for a cutoff around TBD Hz (`fc = 1 / (2πRC)`). Agree with firmware on what's done in hardware vs. software debounce.
- 🟡 **Pedal ADC stage:** scale the pedal's range to 0–3.3 V, add the filter, and check the ADC input impedance requirement in the datasheet.
- 🟡 **Simulate** one digital stage and the pedal stage in LTspice → save `.asc` files here.
- 🟢 Copy the approved stage for every input and label the nets exactly as in the ICD.

## Research questions (`notes.md`)
- What is switch bounce, and should we filter it in hardware, software, or both?
- Divider + clamp vs. transistor vs. optocoupler: which is safest, and which is cheapest?
- Why does the ADC care about source impedance?

## Done when
- [ ] Parts approved, input currents in `power-budget.csv`
- [ ] `calcs.md` + LTspice sims in this folder
- [ ] `driver_inputs.kicad_sch` with every input from the ICD, reviewed by a firmware member (thresholds and polarity)

## Resources
- [`../../../docs/interface-control.md`](../../../docs/interface-control.md): full input list
- TI *"Voltage Divider Circuit"* and ST AN2834 *"How to get the best ADC accuracy in STM32"*
- LTspice: [analog.com/ltspice](https://www.analog.com/en/resources/design-tools-and-calculators/ltspice-simulator.html)
