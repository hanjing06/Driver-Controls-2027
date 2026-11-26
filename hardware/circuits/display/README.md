# Display 🟢

**Owner:** · **Members:**
**KiCad sheet:** `kicad/display.kicad_sch`

## What this circuit does

A small character **LCD** on the dash that shows the driver things like speed, battery voltage and faults. The MCU talks to it over **I²C**, a two-wire bus (SCL clock, SDA data) that needs **pull-up resistors**.

```
STM32 I2C1 SCL/SDA ──┬── pull-ups to 3.3 V ──► LCD connector (3.3 V, GND, SCL, SDA, backlight)
```

## How it was done before

2026 board: **NHD-C0220BIZ-FSW-FBW-3V3M** (Newhaven, 2×20 characters, I²C, 3.3 V).

## What changes now (chip-down)

The LCD itself can stay. Now the pull-ups and LCD power come from our board, and the I²C pins must be assigned on our chip (MCU Core block / ICD).

## Your tasks

### Step 1: Parts & availability
- 🟢 Check the NHD-C0220BIZ is still available. Find 1–2 alternatives (bigger? backlit? still I²C, 3.3 V).
- 🟢 Find the connector/cable the LCD needs and whether it mounts on the board or on the dash.

### Step 2: Current consumption
- 🟢 LCD logic current + **backlight current** from the datasheet → `power-budget.csv` (3.3 V).

### Step 3: Design
- 🟢 Draw the LCD connector and any caps the LCD datasheet requires.
- 🟢 Pick I²C pull-up values (typically 2.2 kΩ–10 kΩ at 3.3 V). Explain your choice in `notes.md`.
- 🟢 Backlight resistor if needed.

## Research questions (`notes.md`)
- How does I²C work: addresses, start/stop, ACK?
- Why does I²C need pull-ups, and what happens if they're too big or too small?
- What's the LCD's I²C address?

## Done when
- [ ] LCD + connector approved, current in `power-budget.csv`
- [ ] `display.kicad_sch` drawn, I²C pins match the ICD

## Resources
- NHD-C0220BIZ datasheet (Newhaven Display)
- TI SLVA689: *I²C Bus Pullup Resistor Calculation*
- SparkFun: *I²C tutorial*
