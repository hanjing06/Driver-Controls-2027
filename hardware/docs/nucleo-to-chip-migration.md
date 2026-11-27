# Nucleo → Chip-Down Migration

[Home](../../README.md) › [Hardware](../README.md) › [Docs](README.md) › **Nucleo-to-chip migration**

In 2026 the Nucleo-F302R8 gave us these blocks for free. In 2027 each one becomes a section of **our** schematic. Reference: ST AN4206 and the Nucleo-64 schematic (MB1136), which is a known-good design to copy from.

| # | Block | What we need | Notes / decisions |
|---|---|---|---|
| 1 | **Power input & protection** | Fuse/PPTC, reverse-polarity protection (P-FET or diode), TVS on 12 V | Automotive 12 V has load-dump and cranking transients. Size the TVS accordingly |
| 2 | **3.3 V regulation** | 12 V → 3.3 V. Options: buck straight to 3.3 V, or buck → 5 V → LDO 3.3 V | Budget current (MCU + LEDs + LCD + transceiver). A buck saves heat |
| 3 | **5 V rail?** | Only if we keep a 5 V CAN transceiver (MCP2551) | Prefer a 3.3 V transceiver → no 5 V rail |
| 4 | **Decoupling** | 100 nF per VDD pin (close to the pin) + 4.7 µF bulk | VBAT → VDD if RTC unused |
| 5 | **VDDA** | Ferrite bead + 1 µF + 10 nF | ADC accuracy matters for the accel pedal |
| 6 | **Clock** | 8 MHz HSE crystal + load caps (calculate from CL and stray C) | HSI is ±1%: too loose for reliable CAN. Nucleo used ST-LINK MCO, which we don't have |
| 7 | **Reset** | NRST: 100 nF to GND, optional tactile button | Internal pull-up already present |
| 8 | **BOOT0** | 10 kΩ to GND (optionally a jumper/pad to 3.3 V for the system bootloader) | |
| 9 | **Programming/debug** | SWD connector: 2×5 1.27 mm Cortex-Debug or Tag-Connect TC2030 | Need an STLINK-V3MINIE, or use a Nucleo's ST-LINK with jumpers removed |
| 10 | **Serial console** | UART header (TX/RX/GND), 3.3 V logic | Replaces the Nucleo's USB virtual COM port |
| 11 | **Status LEDs** | Power LED, 1–2 MCU heartbeat LEDs | Massive help during bring-up |
| 12 | **Test points** | 12 V, 3.3 V, GND, CAN_H/L, key signals | Label on silkscreen |

## Things that do NOT change

- The STM32F302R8's peripherals and pin capabilities (if we stay on this part)
- 12 V input conditioning and MOSFET light drivers (re-check values, but same topology)
- Off-board signal list (see the ICD)

## Firmware impact

- Clock config: HSE 8 MHz crystal (`RCC_HSE_ON`, not `BYPASS` like the Nucleo)
- Pinout regenerated from the ICD, not the Nucleo default `.ioc`
- Flashing over our SWD header instead of the Nucleo's USB
