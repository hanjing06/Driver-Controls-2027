# Onboarding Examples

Run these on a **Nucleo-F302R8**. Each folder gets its own small CubeIDE project made by you (don't copy someone else's: making the `.ioc` is the lesson).

| # | Folder | Goal | Done when |
|---|---|---|---|
| 1 | `01-blinky/` | GPIO + UART + flashing | LD2 blinks at 2 Hz and `hello sunstang` prints every second |
| 2 | `02-adc-pedal/` | ADC with DMA, scaling | Turning a pot on PA0 prints 0–100 % smoothly, with a deadband at 0 |
| 3 | `03-can-loopback/` | bxCAN 500 kbit/s, filters | Send `0x401` in loopback mode, receive it, print the 8 bytes |

Bonus: after 03, port it to a FreeRTOS task that sends every 100 ms and a second task that prints received frames from a queue. That's the VCU_2025 structure in miniature.

Commit your finished example to a branch `fw/onboarding-<yourname>` and open a PR. A reviewer will give feedback. These PRs are for learning and don't get merged to `main`.
