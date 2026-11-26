# Research: CAN Fundamentals 🟢

**Assigned to:** everyone (one or two people write the notes; everyone reads them)

## Why it matters

CAN (Controller Area Network) is how every board in the car talks: the VCU, motor controllers, BMS and more. The drive command that makes the car move is a CAN message. If CAN breaks, the car doesn't drive. Everything else in firmware builds on this topic.

## Questions to answer in `notes.md`

**The bus**
1. What problem does CAN solve compared with wiring every signal point-to-point?
2. What are CAN_H and CAN_L? What are **dominant** and **recessive** bits, and what voltages are they?
3. Why does the bus need a 120 Ω resistor at each end?

**The frame**
4. Draw a standard (11-bit ID) CAN data frame and label each field: SOF, ID, RTR, IDE, DLC, data, CRC, ACK, EOF.
5. What's the difference between standard (11-bit) and extended (29-bit) IDs? Which does our car use?
6. How many data bytes can a classic CAN frame carry?

**Arbitration and reliability**
7. Two boards start transmitting at the same time. What happens? Why does a **lower ID win**?
8. How does CAN detect errors (CRC, ACK, bit stuffing, ...)? What are error-active, error-passive and bus-off?
9. What happens if no other node ACKs your frame (e.g. you're alone on the bench)?

**Timing**
10. What is the **bit rate**, and what's a **time quantum (TQ)**? What are sync segment, BS1, BS2 and the sample point?
11. Why does CAN need an accurate clock on every node?

**What this means for our VCU**
12. Our car runs at 500 kbit/s with standard IDs. Which IDs does the VCU send/receive? (See [`../../docs/can-messages.md`](../../docs/can-messages.md).) Which message has the highest priority?

## Resources
- TI SLOA101: *Introduction to the Controller Area Network (CAN)*
- CSS Electronics: *CAN Bus Explained: A Simple Intro* (very beginner-friendly)
- Bosch CAN 2.0 specification (the original; skim, don't read cover to cover)
- Hardware's CAN block: [`../../../hardware/circuits/can/`](../../../hardware/circuits/can/), since they're researching the same physical layer

## Done when
- [ ] `notes.md` answers 1–12 with at least one frame diagram
- [ ] Presented at a team meeting
