# Firmware: 2027 Driver Controls

[Home](../README.md) › **Firmware**

> **New firmware member? This page is your onboarding.** Read it top to bottom, then go to the [integration test](integration-test/), this year's main project.

---

## 1. What the system does

The Driver Controls board (VCU) runs C code on an **STM32F302R8** microcontroller. The firmware:

1. **Reads the driver:** accelerator pedal (ADC), brake, gear selector (N/R/D), turn-signal/hazard buttons, Ready/Charge switch
2. **Decides what the car should do:** a vehicle state machine (idle → HV ready → drive enabled, or fault)
3. **Commands the motor:** sends a *drive command* (velocity + current) over **CAN** to the motor controllers, every few milliseconds
4. **Listens to the car:** receives speed from the motor controllers and voltage/current/temperature from the BMS over **CAN**
5. **Controls the lights:** brake lights, blinking turn signals and hazards, DRLs
6. **Informs the driver:** LCD and dash LEDs; prints telemetry over UART for debugging

It runs on **FreeRTOS**, a small real-time operating system that lets us split the work into tasks (e.g. one task receives CAN, one sends the drive command, one handles buttons).

```
 Pedals, buttons ─► [ read inputs ] ─► [ vehicle state machine ] ─► [ CAN TX ] ─► Motor controllers
                                              ▲         │
 Motor ctrl, BMS ─► [ CAN RX ] ─► telemetry ──┘         └─► lights, LEDs, LCD
```

**CAN is the backbone.** Almost everything the VCU does involves sending or receiving CAN messages. That's why this year's firmware work is about proving CAN works with the rest of the car.

More detail: [`docs/architecture.md`](docs/architecture.md), [`docs/can-messages.md`](docs/can-messages.md), [`docs/state-machine.md`](docs/state-machine.md).

## 2. Where we're starting from

- **Last year's firmware:** [VCU_2025](https://github.com/uixt/VCU_2025). It already sends the drive command, receives motor-controller and BMS frames, reads the pedal, and prints telemetry. Notes on it: [`../docs/reference/2025-firmware.md`](../docs/reference/2025-firmware.md).
- **What's changing:** the hardware team is replacing the Nucleo dev board with the STM32 chip on our own PCB. For firmware that means a new clock source (crystal), a new pin map, and flashing through a debug header. The board won't exist for a while, so that port comes later.
- **The priority:** VCU_2025 works, but it has never been tested with **all three devices on one CAN bus**: the VCU, the motor controllers and the BMS. Proving that is what matters most this year. The rest can wait.

## 3. What I'd like you to do

### Main project: integration test

**Test last year's firmware with the real car hardware.** Everything happens in [`integration-test/`](integration-test/):

| # | Task | Folder | Assigned to |
|---|---|---|---|
| 1 | Wire all three devices on one CAN bus and watch it with SavvyCAN | [`integration-test/01-can-bus-setup/`](integration-test/01-can-bus-setup/) | |
| 2 | Send drive commands from the STM32 to the motor controllers | [`integration-test/02-motor-controller/`](integration-test/02-motor-controller/) | |
| 3 | Read BMS telemetry | [`integration-test/03-bms-telemetry/`](integration-test/03-bms-telemetry/) | |
| 4 | Test the real accelerator pedal end to end | [`integration-test/04-accel-pedal/`](integration-test/04-accel-pedal/) | |
| 5 | Write the test procedure and record results | [`integration-test/test-log.md`](integration-test/test-log.md) | |

Five tasks, one per person. Pair newer members with someone who has used a microcontroller before. Motor and BMS tests involve the high-voltage system, so **read the [safety section](integration-test/README.md#safety) first**.

### Research that supports the test

Each topic folder in [`research/`](research/) has a README with the questions to answer and where to look. These four are needed now:

| Topic | Folder | Needed for |
|---|---|---|
| CAN fundamentals | [`research/can-fundamentals/`](research/can-fundamentals/) | Everyone |
| CAN tools (USB-CAN, SavvyCAN, DBC files) | [`research/can-tools/`](research/can-tools/) | Task 1 |
| Motor controller CAN protocol | [`research/motor-controller-can/`](research/motor-controller-can/) | Task 2 |
| BMS CAN protocol | [`research/bms-can/`](research/bms-can/) | Task 3 |

**Deliverable:** a `notes.md` in the topic folder (your own words, diagrams welcome). Keep it short and practical: what you need to run the test.

### Later

Only once the integration test passes:

| Work | Folder |
|---|---|
| Rewrite CAN with RX/TX queues | [`app/can_bus/`](app/can_bus/) |
| Other modules: state machine, faults, lighting, LCD, gear, indicators, telemetry | [`app/`](app/) |
| Deeper research: STM32 bxCAN, FreeRTOS queues | [`research/stm32-bxcan/`](research/stm32-bxcan/), [`research/freertos-queues/`](research/freertos-queues/) |
| Port to the 2027 board (crystal clock, new pin map, SWD flashing) | [`DriverControls/`](DriverControls/), [`docs/flashing-and-debugging.md`](docs/flashing-and-debugging.md) |

## 4. Your first week

1. **Set up**
   - Install [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) and Git, and clone this repo
   - Sign out a **Nucleo-F302R8** from the team bin
2. **Read**
   - This page, then [`research/can-fundamentals/`](research/can-fundamentals/)
3. **Do** [`examples/01-blinky`](examples/01-blinky/) to prove your toolchain works.
4. **Build and flash [VCU_2025](https://github.com/uixt/VCU_2025)** onto your Nucleo and check it prints on the UART console. Notes on the code: [`../docs/reference/2025-firmware.md`](../docs/reference/2025-firmware.md).
5. **Get an integration test task** from the firmware lead and open an issue for it (use the **Task** template).

## 5. Folder map

| Folder | Contents |
|---|---|
| [`integration-test/`](integration-test/) | **Main project**: one folder per test task, plus the shared test log |
| [`research/`](research/) | One folder per research topic, with questions + your `notes.md` |
| [`examples/`](examples/) | Warm-up exercises on a Nucleo |
| [`app/`](app/) | Later: our new code, one folder per module (each with `.h`, `.c` and a README) |
| [`DriverControls/`](DriverControls/) | Later: STM32CubeIDE project for the 2027 board. Created by the firmware lead |
| [`tests/`](tests/) | Unit tests that run on a laptop |
| [`tools/`](tools/) | Scripts, `.dbc` file |
| [`docs/`](docs/) | Reference: architecture, CAN message list, state machine, coding standards, flashing |

## 6. Rules

- Our code goes in `app/`. In CubeMX-generated files, only write between `/* USER CODE BEGIN */` and `/* USER CODE END */`.
- Follow [`docs/coding-standards.md`](docs/coding-standards.md).
- Branch `fw/<topic>`, open a PR, get one review. See [`../CONTRIBUTING.md`](../CONTRIBUTING.md).
- Stuck for more than ~30 minutes? Ask. Everyone on this team started somewhere.
