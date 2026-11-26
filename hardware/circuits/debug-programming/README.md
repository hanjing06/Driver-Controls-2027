# Debug & Programming 🟢🟡

**Owner:** · **Members:**
**KiCad sheet:** `kicad/debug.kicad_sch`

## What this circuit does

How we **load firmware onto the chip and see what it's doing**:

| Part | Purpose |
|---|---|
| **SWD connector** | Plug in an ST-LINK to flash and debug (pins SWDIO PA13, SWCLK PA14, NRST, GND, 3.3 V, optional SWO PB3) |
| **UART header** | Serial console. Firmware prints telemetry here (USART2, PA2/PA3) |
| **Status LEDs** | Power-on LED, plus 1–2 LEDs firmware can blink ("heartbeat") |
| **Test points** | Places to clip a multimeter/scope: 12 V, 3.3 V, GND, CAN_H/L, key signals |

During bring-up this block is how we find out what's wrong, so it's worth doing well.

## How it was done before

The Nucleo had a built-in ST-LINK and USB-serial port. You just plugged in a USB cable. Our board had none of this.

## What changes now (chip-down)

No USB on the chip-down board. We add a debug connector and use an external ST-LINK (STLINK-V3MINIE, or a Nucleo's ST-LINK with its jumpers removed).

## Your tasks

### Step 1: Parts & availability
- 🟢 Compare SWD connector options: **2×5 1.27 mm Cortex-Debug header** vs. **Tag-Connect TC2030** (no part on the board, needs a special cable). List pros/cons and stock in `notes.md` / `parts-tracker.csv`.
- 🟢 Pick a UART header (e.g. 1×3 or 1×6 2.54 mm to match a common USB-UART adapter), status LEDs, and test point parts.
- 🟢 Check which ST-LINK the team owns or needs to buy.

### Step 2: Current consumption
- 🟢 LED current: choose a resistor so each LED draws ~2–5 mA from 3.3 V: `R = (3.3 − V_f) / I`. Add to `power-budget.csv`.

### Step 3: Design
- 🟢 Draw the SWD connector with the **standard ARM Cortex-Debug 10-pin pinout** (or TC2030 pinout). Double-check against the ST-LINK manual.
- 🟢 UART header, LEDs with resistors, test points.
- 🟡 Make a list of which signals deserve test points (ask every other block for their one most useful test point).

## Research questions (`notes.md`)
- What is SWD and how is it different from JTAG?
- What does the ST-LINK's VTref pin do, and why must the board be powered itself?
- What's SWO and is it worth routing?

## Done when
- [ ] Connector/LED/test point parts approved
- [ ] LED currents in `power-budget.csv`
- [ ] `debug.kicad_sch` drawn, pinout double-checked by a firmware member

## Resources
- ARM *Cortex-Debug connector* pinout (10-pin, 0.05")
- STLINK-V3MINIE user manual (st.com)
- Tag-Connect TC2030 datasheet
- [`../../docs/bringup-procedure.md`](../../docs/bringup-procedure.md): how this block gets used
