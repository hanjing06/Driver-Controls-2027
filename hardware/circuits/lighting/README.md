# Lighting 🟡

**Owner:** · **Members:**
**KiCad sheet:** `kicad/lighting.kicad_sch`

## What this circuit does

The microcontroller can only output 3.3 V at a few milliamps, but the car's lights run on **12 V at much higher current**. Each light circuit uses a **low-side N-channel MOSFET** as a switch: the MCU drives the gate, and the MOSFET connects the light to ground.

| Output | Load |
|---|---|
| `BrakeLightOut` | Brake lights ×3 |
| `LSignalLightOut` / `RSignalLightOut` | Turn signals ×3 per side |
| `DRLLeftOut` / `DRLRightOut` | Daytime running lights |

```
         +12 V (fused)
            │
          [Light]
            │
 MCU ──Rg──┤ N-MOSFET
       │    │
      Rpd  GND
```

## How it was done before

2026 board: **FQP30N06L** MOSFETs (TO-220 through-hole, logic-level) and lots of 0466-series fuses.

## What changes now (chip-down)

Same idea, but this is a chance to shrink: swap TO-220s for **SMD logic-level MOSFETs** if they handle the current. Re-check the fuse ratings against the real light currents.

## Your tasks

### Step 1: Parts & availability
- 🟢 Find out what light modules the car uses (ask the electrical/aerobody lead) and their **current at 12 V**.
- 🟢 Check FQP30N06L availability, and find 2 **SMD** logic-level N-MOSFETs (SOT-23 / SOT-223 / DPAK) fully on at **V_GS = 3.3 V** (look for R_DS(on) specified at 2.5 V or 3.3 V or 4.5 V).
- 🟢 Pick fuses per output channel.

### Step 2: Current consumption
- 🟢 Fill each light's current × quantity × duty (turn signals ≈ 50 %) into the 12 V section of `power-budget.csv`.
- 🟡 For each MOSFET: `P = I² × R_DS(on)`. Is it below what the package can dissipate without a heatsink?

### Step 3: Design
- 🟢 Draw one channel: MOSFET, gate resistor (~100 Ω), gate pull-down (~10–100 kΩ, keeps the light off while the MCU boots), fuse.
- 🟡 Add **flyback/TVS protection** if any load is inductive or the wiring is long.
- 🟢 Copy for every output, net names per the ICD.
- 🟡 *Optional:* should any outputs support PWM dimming (DRL)? Agree with firmware.

## Research questions (`notes.md`)
- What does "logic-level MOSFET" mean? Why does V_GS(th) not tell you the MOSFET is fully on?
- Why low-side switching instead of high-side? What's the downside?
- Why does a gate need a pull-down resistor?

## Done when
- [ ] MOSFETs and fuses approved
- [ ] 12 V light currents and MOSFET losses in `power-budget.csv`
- [ ] `lighting.kicad_sch` reviewed

## Resources
- Onsemi / Nexperia app notes on using MOSFETs as load switches
- MOSFET datasheets: look at the R_DS(on) vs. V_GS graph
- 2026 schematic lighting section
