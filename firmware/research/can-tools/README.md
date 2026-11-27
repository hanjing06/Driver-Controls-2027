# Research: CAN Tools & DBC Files

[Home](../../../README.md) › [Firmware](../../README.md) › [Research](../README.md) › **CAN tools**

**Assigned to:**
**Read first:** [`../can-fundamentals/`](../can-fundamentals/)

## Why it matters

You can't debug a CAN bus by staring at code. We need to **see** the frames on the wire. Tools also let us **fake** other boards (e.g. pretend to be the BMS) so we can test the VCU on a bench without the whole car. A **DBC file** describes every message and signal so tools can decode frames into readable values automatically.

## Questions to answer in `notes.md`

1. What USB-CAN adapters does the team own? If none, compare 2–3 cheap options (CANable / candleLight, PCAN-USB, CANtact, ...): price, software support, Windows/Mac/Linux.
2. What is **SavvyCAN**? How do you connect it to an adapter, view live frames, filter by ID, and **send** a frame?
3. How would you use the adapter + SavvyCAN to **pretend to be the motor controller** and send fake velocity frames to the VCU?
4. What is a **DBC file**? Explain messages, signals, start bit, length, byte order, factor/offset.
5. *(Optional)* What can the Python **`cantools`** and **`python-can`** libraries do with a DBC file?

## Hands-on deliverable

- [ ] Write `tools/driver_controls.dbc` with every message in [`../../docs/can-messages.md`](../../docs/can-messages.md) (start with `0x401`, `0x503`, `0x701–0x703`). Coordinate with the motor-controller and BMS research people for exact layouts.
- [ ] If the team has an adapter: capture a log of a Nucleo running [`../../examples/03-can-loopback`](../../examples/03-can-loopback/) in normal mode, and decode it with the DBC.

## Resources
- [SavvyCAN](https://www.savvycan.com/)
- CSS Electronics: *DBC File Explained*
- [cantools docs](https://cantools.readthedocs.io/)
- canable.io

## Done when
- [ ] `notes.md` answers 1–4
- [ ] `tools/driver_controls.dbc` committed (PR)
- [ ] Short demo at a team meeting
