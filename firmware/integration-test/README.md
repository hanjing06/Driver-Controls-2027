# Integration Test: VCU + Motor Controllers + BMS

[Home](../../README.md) › [Firmware](../README.md) › **Integration test**

**This year's main firmware project.** Owner: · Members:

## Why this comes first

Last year's firmware ([VCU_2025](https://github.com/uixt/VCU_2025)) already does the important things: it reads the accelerator pedal, sends the drive command to the motor controllers, and receives speed and BMS data over CAN. **The code is fine. What has never been proven is the whole system working together.**

So before anyone rewrites or adds features, we test what we have:

1. **All three devices on one CAN bus:** the VCU, the motor controllers and the BMS
2. **The VCU commands the motor controllers** (and reads their speed back)
3. **The VCU reads BMS telemetry** (pack voltage, current, temperatures)
4. **The real accelerator pedal** drives the command end to end

Everything else (new CAN code, state machine, LCD, faults, porting to the 2027 board) is for later.

```
  Accel pedal ──► [ Nucleo-F302R8 + 2026 VCU board ]
                        running VCU_2025
                              │ CAN (500 kbit/s)
     ┌────────────────────────┼────────────────────────┬──────────────────┐
     ▼                        ▼                        ▼                  ▼
 Motor controller 1    Motor controller 2             BMS          USB-CAN adapter
 (0x500 base)          (0x600 base)               (0x701–0x703)    + SavvyCAN laptop
                                                                     (watches everything)
```

## Hardware you need

| Item | Notes |
|---|---|
| Nucleo-F302R8 + the 2026 VCU board | The 2026 board has the CAN transceiver and connectors. Ask the lead where it is |
| VCU_2025 flashed onto the Nucleo | See [Before you start](#before-you-start) |
| USB-CAN adapter + [SavvyCAN](https://www.savvycan.com/) | Lets you see every frame on the bus. See [`../research/can-tools/`](../research/can-tools/) |
| Motor controllers and BMS | On the car or on a bench, **only with the electrical lead present** |
| The real accelerator pedal | From the car, or a spare |
| CAN cable(s) + two 120 Ω terminations | One at each end of the bus |

## Safety

The motor controllers and BMS are part of the **high-voltage system**.

- **Never** power the HV system without the electrical lead (or someone HV-trained) present.
- For motor tests, the car is **on stands with the wheels off the ground**, or the motor is otherwise unloaded.
- Start with a **tiny current command** (e.g. 0.05 = 5 %) and work up.
- Someone is always on the **e-stop / LV kill switch**.
- Tasks 1 and 3 (bus and BMS) can be done with the HV contactors open. Only task 2 needs the motor to actually spin.

## Before you start

Everyone on the project does this first (about a week):

1. Read [`../research/can-fundamentals/`](../research/can-fundamentals/)
2. Do [`../examples/01-blinky`](../examples/01-blinky/) so your toolchain works
3. Clone [VCU_2025](https://github.com/uixt/VCU_2025), open it in STM32CubeIDE, build it, and flash it onto a Nucleo. Open the UART console (115200 baud) and check it prints. Notes on the code: [`../../docs/reference/2025-firmware.md`](../../docs/reference/2025-firmware.md)

## Tasks

| # | Task | Folder | Assigned to |
|---|---|---|---|
| 1 | Wire up the bus and watch it with SavvyCAN | [`01-can-bus-setup/`](01-can-bus-setup/) | |
| 2 | Send drive commands to the motor controllers | [`02-motor-controller/`](02-motor-controller/) | |
| 3 | Read BMS telemetry | [`03-bms-telemetry/`](03-bms-telemetry/) | |
| 4 | Test the real accelerator pedal end to end | [`04-accel-pedal/`](04-accel-pedal/) | |
| 5 | Write the test procedure and record results | [`test-log.md`](test-log.md) | |

Task 1 comes first. Tasks 2, 3 and 4 can run in parallel once the bus works. Task 5 runs alongside all of them: one person owns the test log, and everyone adds their results to it.

**Suggested split for 5 people:** one person per task. Pair newer members with someone who has used a microcontroller before.

## Done when

- [ ] All three devices are on the bus, and SavvyCAN shows frames from each
- [ ] Pressing the pedal spins the motor (on stands) through VCU_2025, and releasing it stops it
- [ ] BMS pack voltage, current and temperatures print correctly on the VCU's UART console
- [ ] [`test-log.md`](test-log.md) has a repeatable procedure and the results, so we can run the same test on the 2027 board
- [ ] Anything wrong in VCU_2025 is written up as an issue (don't rewrite it yet)
