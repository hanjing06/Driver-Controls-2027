# Flashing & Debugging

## On a Nucleo-F302R8 (prototyping, now)
Plug in USB → CubeIDE **Run** (green play) or **Debug** (bug). The on-board ST-LINK does everything. UART console = the Nucleo's virtual COM port (USART2, PA2/PA3) at 115200 baud (check the `.ioc`).

## On the 2027 board (after bring-up)
There's no USB. You need an external debugger on the board's **SWD header**:

| Option | Notes |
|---|---|
| STLINK-V3MINIE | Small, cheap, recommended |
| A Nucleo's ST-LINK | Remove the two **CN2** jumpers on the Nucleo, then wire CN4 SWD pins to our header |

SWD wiring: `SWDIO (PA13)`, `SWCLK (PA14)`, `NRST`, `GND`, `VTref (3.3 V)`, optional `SWO (PB3)`. The board must be powered from its own 12 V input.

UART console: connect a 3.3 V USB-UART adapter to the board's UART header (TX↔RX crossed, GND common).

## Clock note
The Nucleo build uses HSI (or ST-LINK MCO). The 2027 board uses an **8 MHz crystal (HSE, not bypass)**, so a Nucleo `.ioc` won't run CAN correctly on our board, and vice versa. Keep two build configurations, or a `BOARD_NUCLEO` / `BOARD_DC2027` define, until bring-up is done.

## Tools
- **STM32CubeProgrammer**: read device ID, erase, flash `.elf`/`.hex`
- **Live Expressions** (CubeIDE debug view): watch variables live
- **SavvyCAN** + a USB-CAN adapter: watch the bus
