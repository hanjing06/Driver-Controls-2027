# Interface Control Document (ICD): Pin Map

This is the **contract between hardware and firmware**. Hardware assigns each signal to an MCU pin and a connector pin. Firmware configures the `.ioc` and writes `app/inc/pinmap.h` from this table.

**Rules**
- This table is the single source of truth. If the schematic and this table disagree, that's a bug: open an issue.
- Every change needs a PR approved by **one hardware and one firmware member**.
- Signal names match the KiCad net labels exactly (carried over from the 2026 schematic where possible).

Status key: `TBD` = not assigned yet · `DRAFT` = proposed · `FROZEN` = in the released schematic

## MCU: STM32F302R8T6 (LQFP-64), planned

### Driver inputs (12 V or sensor → conditioned → MCU)

| Signal (net) | Dir | Type | Source / connector | Conditioning | MCU pin | Peripheral | Status |
|---|---|---|---|---|---|---|---|
| `AccelIn` | In | Analog | Accel pedal | Divider + RC filter, clamp to 3.3 V | PA0 | ADC1_IN1 + DMA | DRAFT (VCU_2025) |
| `BrakePedalIn` | In | Analog/Digital | Brake pedal | TBD | TBD | ADC / GPIO | TBD |
| `Neutral` | In | Digital | Gear selector | 12 V → 3.3 V | TBD | GPIO | TBD |
| `Reverse` | In | Digital | Gear selector | 12 V → 3.3 V | TBD | GPIO | TBD |
| `Drive` | In | Digital | Gear selector | 12 V → 3.3 V | TBD | GPIO | TBD |
| `LSignalLightIn` | In | Digital | L turn button (latching) | 12 V → 3.3 V | TBD | GPIO/EXTI | TBD |
| `RSignalLightIn` | In | Digital | R turn button (latching) | 12 V → 3.3 V | TBD | GPIO/EXTI | TBD |
| `HazardIn` | In | Digital | Hazard button (latching) | 12 V → 3.3 V | TBD | GPIO/EXTI | TBD |
| `ReadyMode` | In | Digital | Mode select (SPDT) | 12 V → 3.3 V | TBD | GPIO | TBD |
| `ChargeMode` | In | Digital | Mode select (SPDT) | 12 V → 3.3 V | TBD | GPIO | TBD |
| `ThermalShutoff` | In | Digital | Thermal sensor / BMS | 12 V → 3.3 V | TBD | GPIO/EXTI | TBD |
| `SupBattMonitor` | In | Analog | 12 V supplemental battery | Divider + filter | TBD | ADC1_INx | TBD |

### Outputs (MCU → MOSFET gate → 12 V load)

| Signal (net) | Dir | Load | Driver | MCU pin | Peripheral | Status |
|---|---|---|---|---|---|---|
| `BrakeLightOut` | Out | Brake lights ×3 | Low-side N-MOSFET | TBD | GPIO | TBD |
| `LSignalLightOut` | Out | L turn signals ×3 | Low-side N-MOSFET | TBD | GPIO / TIM PWM | TBD |
| `RSignalLightOut` | Out | R turn signals ×3 | Low-side N-MOSFET | TBD | GPIO / TIM PWM | TBD |
| `DRLLeftOut` | Out | Left DRL | Low-side N-MOSFET | TBD | GPIO / TIM PWM | TBD |
| `DRLRightOut` | Out | Right DRL | Low-side N-MOSFET | TBD | GPIO / TIM PWM | TBD |
| `DashFaultIndicator` | Out | Dash fault LED | TBD | TBD | GPIO | TBD |
| `DOExtra1` | Out | Spare | TBD | TBD | GPIO | TBD |

### Pure-hardware 12 V paths (no MCU pin, listed for completeness)

`LVSwitch±`, `HVSwitch±`, `To/From_PreChargeBtn`, `To_ModeSelect`, `LVActive`, `HVActive`, `HVILActive`, pre-charge (blue) and main-contactor (green) indicator LEDs. *Decide this year whether any of these should also be read by the MCU (e.g. `HVActive` for the state machine).*

### Communication

| Signal | Peripheral | MCU pins | Notes | Status |
|---|---|---|---|---|
| `CAN_TX` / `CAN_RX` | bxCAN, 500 kbit/s | PA12 / PA11 | Transceiver TBD (3.3 V part preferred) | DRAFT (VCU_2025) |
| `I2C1_CLK` / `I2C1_SDA` | I2C1 | TBD | Character LCD; pull-ups on board | TBD |
| `UART_TX` / `UART_RX` | USART2 | PA2 / PA3 | Debug header (UART telemetry console) | DRAFT (VCU_2025) |
| SWDIO / SWCLK / NRST / SWO | SWD | PA13 / PA14 / NRST / PB3 | Fixed by the chip | DRAFT |

### Clock & boot

| Function | MCU pins | Notes |
|---|---|---|
| HSE 8 MHz crystal | PF0-OSC_IN / PF1-OSC_OUT | Needed for accurate CAN timing |
| BOOT0 | BOOT0 | 10 kΩ pull-down |
| NRST | NRST | 100 nF to GND + optional reset button |

### Spares

`DIExtra1`, `DIExtra2`: spare conditioned digital inputs. Keep a few spare GPIOs broken out to test points.
