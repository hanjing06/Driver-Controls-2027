# Layout Guidelines

*Starting rules. Adjust once the stackup and fab house are chosen.*

## Stackup
- Prefer **4 layers**: Signal / GND / 3V3+12V / Signal. If 2 layers, keep a solid bottom GND pour.

## Placement
1. Connectors first (fixed by the enclosure/harness)
2. MCU roughly central
3. Decoupling caps on the same side as the MCU, as close to each VDD pin as possible
4. Crystal within a few mm of OSC pins, no traces under it, guard with GND
5. Power stage at the board edge near the 12 V input. Keep the switching loop small
6. Separate 12 V power/lighting area from the 3.3 V logic/analog area

## Routing
- 12 V lighting traces sized for current (use a trace-width calculator, ≥ TBD mm for TBD A)
- CAN_H / CAN_L as a differential pair, short, to the connector
- Analog pedal input away from switching nodes and PWM lines
- No 90° corners on high-current traces; vias stitched around GND pours

## Fab & assembly
- Silkscreen: board name, rev, date, connector pin 1, test point labels, team logo
- Run DRC with the fab house's rules (JLCPCB / PCBWay design rules TBD)
- Export to `fabrication/revX/`: Gerbers, drill, pos file, BOM
