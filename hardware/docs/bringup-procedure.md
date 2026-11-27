# Board Bring-Up Procedure

[Home](../../README.md) › [Hardware](../README.md) › [Docs](README.md) › **Bring-up procedure**

Do these **in order**. Record results in a GitHub issue per board (`Bring-up: revA #1`).

## 0. Before power
- [ ] Visual inspection: solder bridges on the MCU, part orientation (diodes, LEDs, ICs)
- [ ] Resistance 12 V→GND and 3V3→GND is not a short

## 1. Power (bench supply, current limit ~100 mA)
- [ ] Apply 12 V. Current draw is sensible
- [ ] 3.3 V rail within spec at test point
- [ ] Power LED on
- [ ] Reverse-polarity test (if the protection is designed for it)

## 2. MCU alive (with firmware track)
- [ ] ST-LINK connects over SWD (STM32CubeProgrammer sees the device ID)
- [ ] Flash `examples/01-blinky` with pins changed to the board's status LED
- [ ] HSE starts (toggle MCO or check the clock config in debugger)
- [ ] UART prints a boot message

## 3. Per-I/O validation
For every row in the ICD: apply the input / command the output, and confirm. Tick the row in the bring-up issue.

## 4. Comms
- [ ] CAN loopback, then CAN to a USB-CAN adapter
- [ ] LCD shows text over I²C

## 5. Load test
- [ ] All lights on simultaneously at 12 V for 10 min; check FET and trace temperatures
