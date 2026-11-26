# HV Interface & Indicators 🟡

**Owner:** · **Members:**
**KiCad sheet:** `kicad/hv_interface.kicad_sch`

## What this circuit does

The VCU board is part of the **startup and safety chain** for the high-voltage battery. This block carries those 12 V signals and shows their status to the driver:

| Signals | What they are |
|---|---|
| `LVSwitch±`, `HVSwitch±` | Driver's LV and HV switches, passed through to the power distribution board |
| `To/From_PreChargeBtn` | Pre-charge button, to the pre-charge board |
| `To_ModeSelect` | Ready/Charge mode line |
| `LVActive`, `HVActive`, `HVILActive` | Status lines from the power distribution board |
| Pre-charge LEDs (blue ×5), main contactor LEDs (green ×5) | Tell the driver the HV startup state |
| `DashFaultIndicator` | Fault light |

**Startup sequence it supports:** LV on → HV switch → pre-charge button → pre-charge confirmed → main contactor closes → HV active → Ready mode → drive. See [`../../../docs/system-overview.md`](../../../docs/system-overview.md).

## How it was done before

On the 2026 board these were mostly pure 12 V paths (no MCU involvement), with LEDs and resistors driven directly from the status lines.

## What changes now (chip-down)

Mostly the same, but it's a new design cycle, so question everything:
- Should the MCU **read** `HVActive` / `HVILActive` (via a driver-inputs-style stage) so firmware can block driving if HV isn't ready?
- Are the 12 V LED resistor values right for the LEDs we'll buy this year?

## Your tasks

### Step 1: Parts & availability
- 🟢 Pick indicator LEDs (blue, green, red/amber) and check stock. 2026 used LiteOn LTST 1206/0603.
- 🟢 Confirm connector pinouts with the pre-charge and power distribution board teams (who sends what, at what voltage?).

### Step 2: Current consumption
- 🟢 LED resistor at 12 V: `R = (12 − V_f) / I_LED`, and resistor power `P = I² × R` (check the resistor's power rating!). Fill `power-budget.csv`.

### Step 3: Design
- 🟢 Draw the LED indicator circuits.
- 🟡 Draw the switch pass-through paths and confirm with the electrical lead.
- 🟡 If the MCU should read any HV status lines, add them to the ICD (`icd/` PR) and coordinate with the Driver Inputs block.

## Research questions (`notes.md`)
- What is pre-charge and why must it finish before the main contactor closes?
- What is an HVIL (high-voltage interlock loop)?
- Which parts of the startup sequence should be enforced in hardware, and which in firmware?

## Done when
- [ ] LEDs approved, LED/resistor currents and power in `power-budget.csv`
- [ ] Interfaces confirmed with the other board teams (write it in `notes.md`)
- [ ] `hv_interface.kicad_sch` reviewed

## Resources
- [`../../../docs/images/VCU_System_2026.png`](../../../docs/images/VCU_System_2026.png): system integration diagram
- Current solar car race regulations (electrical / HV sections)
