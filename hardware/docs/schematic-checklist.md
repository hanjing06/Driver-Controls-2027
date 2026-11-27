# Schematic Review Checklist

[Home](../../README.md) › [Hardware](../README.md) › [Docs](README.md) › **Schematic checklist**

Copy this into the PR description and tick each item.

## General
- [ ] ERC passes (or every waiver is explained)
- [ ] Net names match [`docs/interface-control.md`](../../docs/interface-control.md)
- [ ] Every part has MPN, manufacturer, datasheet link, footprint
- [ ] Parts are in stock (Digi-Key / Mouser / LCSC), with alternates noted

## Power
- [ ] Reverse polarity, TVS and fuse on 12 V input
- [ ] Regulator: input/output caps per datasheet, thermal check done
- [ ] Power-good / power LED

## MCU
- [ ] 100 nF on every VDD pin + bulk cap
- [ ] VDDA filtered; VREF+ handled (if exposed on package)
- [ ] HSE crystal load caps calculated
- [ ] NRST cap, BOOT0 pull-down
- [ ] SWD header pinout matches the debugger
- [ ] Pin functions verified against the datasheet alternate-function table (not just CubeMX)

## I/O
- [ ] Every 12 V input divided/clamped to ≤ 3.3 V (check worst-case input voltage)
- [ ] Input RC values give the intended debounce/filter
- [ ] MOSFET gates: series resistor + pull-down; FET is logic-level at 3.3 V V_GS
- [ ] Inductive loads have flyback protection
- [ ] CAN: ESD protection, termination option, split termination if used
- [ ] I²C pull-ups present (once, not on every device)
