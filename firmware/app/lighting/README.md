# Lighting

[Home](../../../README.md) › [Firmware](../../README.md) › [App](../README.md) › **Lighting**

**Owner:** · **Members:**

## What it does
Controls the 12 V lights through the MOSFET outputs:
- **Brake lights:** on while the brake is pressed
- **Turn signals:** blink ~1.5 Hz while the left/right button is latched
- **Hazard:** both sides blink together, overrides turn signals
- **DRLs:** on whenever the car is on (maybe PWM-dimmed, TBD with hardware)

## How VCU_2025 did it
`ButtonManaging.c` (`brake_light`, button tasks at 100 ms / 500 ms).

## Tasks
- Implement the logic with LEDs on a Nucleo + buttons/jumpers standing in for the real inputs
- Blink timing from a tick counter (no `osDelay` per light), and left/right blink in sync with hazard
- Check the race regulations for required blink rate / brake light rules
