# Firmware: 2027 Driver Controls

[Home](../README.md) › **Firmware**

> **New firmware member? This page is your onboarding.** Read it top to bottom, then go to your assigned research topic or module folder.

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

**CAN is the backbone.** Almost everything the VCU does involves sending or receiving CAN messages. That's why this year's firmware work starts with CAN.

More detail: [`docs/architecture.md`](docs/architecture.md), [`docs/can-messages.md`](docs/can-messages.md), [`docs/state-machine.md`](docs/state-machine.md).

## 2. Where we're starting from

- **Last year's firmware:** [VCU_2025](https://github.com/uixt/VCU_2025). It already sends the drive command, receives motor-controller and BMS frames, reads the pedal, and prints telemetry. Notes on it: [`../docs/reference/2025-firmware.md`](../docs/reference/2025-firmware.md).
- **What's changing:** the hardware team is replacing the Nucleo dev board with the STM32 chip on our own PCB. For firmware that means a new clock source (crystal), a new pin map, and flashing through a debug header. The board won't exist for a while, so **this year's firmware work is mostly research and prototyping on a Nucleo**, so we're ready when the board arrives.

## 3. What I'd like you to do

Work happens in three tracks, in this order. Everyone does Track A first.

### Track A: Research (everyone, first) 📚

Research is a big part of this design cycle. Before we write production code, every member should understand **how CAN works, how the STM32 does CAN, and how our car uses it**. Each topic folder in [`research/`](research/) has a README with the questions to answer and where to look.

| Topic | Folder | Assigned to |
|---|---|---|
| CAN fundamentals | [`research/can-fundamentals/`](research/can-fundamentals/) | all |
| STM32 bxCAN peripheral | [`research/stm32-bxcan/`](research/stm32-bxcan/) | |
| FreeRTOS tasks & queues | [`research/freertos-queues/`](research/freertos-queues/) | |
| Motor controller CAN protocol | [`research/motor-controller-can/`](research/motor-controller-can/) | |
| BMS CAN protocol | [`research/bms-can/`](research/bms-can/) | |
| CAN tools (USB-CAN, SavvyCAN, DBC files) | [`research/can-tools/`](research/can-tools/) | |

**Deliverable:** a `notes.md` in the topic folder (your own words, diagrams welcome) and a **5–10 minute explanation at a team meeting**. Teaching it is how we know you understand it, and the notes become the team's documentation.

### Track B: Hands-on with CAN (after your research) 🔧

| Task | Folder |
|---|---|
| Warm-up exercises on a Nucleo (blinky → ADC → CAN loopback) | [`examples/`](examples/) |
| **Implement CAN RX and TX queues** | [`app/can_bus/`](app/can_bus/) |
| Decode/encode functions for each message + unit tests | [`app/can_bus/`](app/can_bus/), [`tests/`](tests/) |
| CAN message definitions as a `.dbc` file | [`research/can-tools/`](research/can-tools/) |

The **CAN queues** task is this year's main firmware project. It replaces VCU_2025's ad-hoc CAN code with a clean design: interrupts put frames in a queue, tasks process them, and every frame we send goes through a TX queue.

### Track C: Port the rest of the app (later, as people are ready) 🧩

Each module has its own folder in [`app/`](app/) with a README explaining what it does and what to build. These are lower priority than Tracks A and B.

| Module | What it does |
|---|---|
| [`app/indicators/`](app/indicators/) | Dash LEDs, heartbeat |
| [`app/gear/`](app/gear/) | Debounced gear selector |
| [`app/lighting/`](app/lighting/) | Brake, turn, hazard, DRL logic |
| [`app/pedals/`](app/pedals/) | Pedal ADC → 0–100 % |
| [`app/telemetry/`](app/telemetry/) | Shared data from CAN, UART print |
| [`app/display/`](app/display/) | LCD driver + screens |
| [`app/faults/`](app/faults/) | Collect and latch faults |
| [`app/vehicle_state/`](app/vehicle_state/) | The state machine |
| [`app/common/`](app/common/) | Pin map, board support, app entry |

Mixed-experience pairs are encouraged: a newer member pairing with someone more experienced is how most people level up.

## 4. Your first week

1. **Set up**
   - Install [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) and Git, and clone this repo
   - Sign out a **Nucleo-F302R8** from the team bin
2. **Read**
   - This page, then [`research/can-fundamentals/`](research/can-fundamentals/)
3. **Do** [`examples/01-blinky`](examples/01-blinky/) to prove your toolchain works.
4. **Get a research topic** from the firmware lead and open an issue for it (use the **Task** template).

## 5. Folder map

| Folder | Contents |
|---|---|
| [`research/`](research/) | **Track A**: one folder per research topic, with questions + your `notes.md` |
| [`examples/`](examples/) | Warm-up exercises on a Nucleo |
| [`app/`](app/) | **Our code**, one folder per module (each with `.h`, `.c` and a README) |
| [`DriverControls/`](DriverControls/) | STM32CubeIDE project (generated HAL + FreeRTOS, `.ioc`). Created by the firmware lead |
| [`tests/`](tests/) | Unit tests that run on a laptop |
| [`tools/`](tools/) | Scripts, `.dbc` file |
| [`docs/`](docs/) | Reference: architecture, CAN message list, state machine, coding standards, flashing |

## 6. Rules

- Our code goes in `app/`. In CubeMX-generated files, only write between `/* USER CODE BEGIN */` and `/* USER CODE END */`.
- Follow [`docs/coding-standards.md`](docs/coding-standards.md).
- Branch `fw/<topic>`, open a PR, get one review. See [`../CONTRIBUTING.md`](../CONTRIBUTING.md).
- Stuck for more than ~30 minutes? Ask. Everyone on this team started somewhere.
