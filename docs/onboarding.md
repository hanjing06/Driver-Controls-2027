# Onboarding: Start Here

Welcome to Driver Controls! This page is for **everyone**. When you're done, continue to your track's guide.

## Week 1 checklist

- [ ] Get added to the GitHub repo and team channel (ask the Driver Controls Lead)
- [ ] Install Git and clone this repo: `git clone <repo-url>`
- [ ] Read [`system-overview.md`](system-overview.md)
- [ ] Skim [`interface-control.md`](interface-control.md). Don't memorize it, just know it exists
- [ ] Look at last year's work:
  - Board: [Sunstang-VCU-2026](https://github.com/hanjing06/Sunstang-VCU-2026) → notes in [`reference/2026-vcu.md`](reference/2026-vcu.md)
  - Firmware: [VCU_2025](https://github.com/uixt/VCU_2025) → notes in [`reference/2025-firmware.md`](reference/2025-firmware.md)
- [ ] Read [`../CONTRIBUTING.md`](../CONTRIBUTING.md)
- [ ] Pick a track and open its onboarding guide:
  - [Hardware onboarding](../hardware/docs/onboarding.md)
  - [Firmware onboarding](../firmware/docs/onboarding.md)

## Git in 5 commands

```bash
git pull                         # get the latest
git checkout -b fw/lighting-turn # make a branch for your task
git add <files>                  # stage your changes
git commit -m "fw: add turn signal blink timer"
git push -u origin fw/lighting-turn   # then open a PR on GitHub
```

New to Git? Try [learngitbranching.js.org](https://learngitbranching.js.org/). It's about an hour.

## Glossary

| Term | Meaning |
|---|---|
| VCU | Vehicle Control Unit, this board |
| LV / HV | Low voltage (12 V system) / High voltage (traction battery) |
| Pre-charge | Slowly charging the motor controller caps through a resistor before closing the main contactor |
| HVIL | High-Voltage Interlock Loop, a safety loop that opens if an HV connector is unplugged |
| BMS | Battery Management System |
| DRL | Daytime Running Light |
| ICD | Interface Control Document, our pin map |
| HAL | ST's Hardware Abstraction Layer library |
| `.ioc` | STM32CubeMX config file (pins, clocks, peripherals) |
| SWD | Serial Wire Debug, how we flash and debug the chip |
| Nucleo | ST's dev board, which we used in 2026 and still use for prototyping |
