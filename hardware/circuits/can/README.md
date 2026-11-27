# CAN

[Home](../../../README.md) › [Hardware](../../README.md) › **CAN**

**Owner:** · **Members:**
**KiCad sheet:** `kicad/can.kicad_sch`

## What this circuit does

**CAN** is the two-wire network (CAN_H, CAN_L) that connects the boards in the car. Through it, the VCU sends drive commands to the motor controllers and receives speed and battery data from the motor controllers and BMS.

The STM32 has a CAN *controller* built in, but it only outputs logic-level TX/RX. A **CAN transceiver** chip converts those to the differential bus signals.

```
STM32 CAN_TX/RX (PA12/PA11) ─► Transceiver ─► ESD protection ─► 120 Ω termination (jumper) ─► Connector CAN_H/CAN_L
```

## How it was done before

2026 board: **MCP2551** transceiver (5 V, through-hole) + **NUP2105** ESD diode. But the STM32 runs at 3.3 V, so a 5 V transceiver is a mismatch.

## What changes now (chip-down)

We generate our own rails, so we choose: **switch to a 3.3 V transceiver** (no 5 V rail needed) or keep a 5 V part and ask the Power block for a 5 V rail. Most teams pick 3.3 V. Also decide whether this board is at the **end of the bus** (needs termination) or in the middle.

## Your tasks

### Step 1: Parts & availability
- Compare 3.3 V transceivers: **SN65HVD230**, **TCAN334**, **MCP2562 (with VIO = 3.3 V)**, and others. Record supply voltage, standby mode, ESD rating, package and stock.
- Check that **NUP2105LT1G** (ESD) is still available, and find an alternate.
- Pick a jumper or solder bridge for the termination resistor.

### Step 2: Current consumption
- From the transceiver datasheet, find supply current in **dominant** state (worst case) → `power-budget.csv`.

### Step 3: Design
- Draw the transceiver from the datasheet's typical application.
- Decide on termination: plain 120 Ω, or **split termination** (2 × 60 Ω + cap to GND) for less noise. Justify in `notes.md`.
- Standby/silent pin: tie it, or give it to an MCU GPIO? Agree with firmware.

## Research questions (`notes.md`)
These are important. CAN is central to the whole car, and firmware members are researching the same topic.
- What are dominant and recessive bits? What voltages do CAN_H/CAN_L sit at in each state?
- Why does a CAN bus need 120 Ω at **each end**, and what happens without it?
- Where does this board sit on the car's CAN bus? (Ask the electrical lead.)
- What bit rate does the car use? (VCU_2025: 500 kbit/s.)

## Done when
- [ ] Transceiver + ESD approved
- [ ] Current in `power-budget.csv`
- [ ] `notes.md` answering the research questions
- [ ] `can.kicad_sch` drawn and reviewed

## Resources
- TI *"Introduction to the Controller Area Network (CAN)"* (SLOA101)
- TI *"Overview of 3.3V CAN Transceivers"* (SLLA337)
- Transceiver datasheets above
- [`../../../firmware/research/can-fundamentals/`](../../../firmware/research/can-fundamentals/): the firmware CAN research, worth reading
