# CAN Bus Module: RX/TX Queues

[Home](../../../README.md) › [Firmware](../../README.md) › [App](../README.md) › **CAN bus**

**This year's main firmware project.** Owner: · Members:
**Do your research first:** [`../../research/can-fundamentals/`](../../research/can-fundamentals/), [`stm32-bxcan/`](../../research/stm32-bxcan/), [`freertos-queues/`](../../research/freertos-queues/)

## What this module does

Every CAN frame the VCU sends or receives goes through this module.

```
                 RECEIVE                                         TRANSMIT
 CAN bus                                         any task (control, status, ...)
    │                                                       │ can_send(&frame)
    ▼                                                       ▼
 bxCAN RX FIFO0 (3 deep, hardware)                  ┌───────────────┐
    │ interrupt                                     │   TX queue    │  (FreeRTOS, 16 frames)
    ▼                                               └───────┬───────┘
 HAL_CAN_RxFifo0MsgPendingCallback()                        │ can_tx_task
    │ copy frame, xQueueSendFromISR()                       ▼ waits for a free mailbox
    ▼                                               bxCAN TX mailboxes (3, hardware)
 ┌───────────────┐                                          │
 │   RX queue    │  (FreeRTOS, 32 frames)                   ▼
 └───────┬───────┘                                       CAN bus
         │ can_rx_task: can_receive()
         ▼ switch (frame.id) → decode → telemetry
```

**Why queues?** The hardware only holds 3 received frames and 3 outgoing frames. If a task is busy for a few milliseconds, frames are lost. Software queues absorb bursts, keep the interrupt tiny, and mean any task can send a frame without worrying about mailboxes.

## How VCU_2025 did it

VCU_2025 already has a version of the RX side: an RX callback feeds a queue that `canRxTask` reads, and a `canTxTask` sends `0x401`. Read `Core/Src/CAN_Receive.c`, `CAN_Transmit.c` and `main.c` in [VCU_2025](https://github.com/uixt/VCU_2025). What's missing or messy:
- TX writes straight to the mailbox from one task. There's no TX queue, so other tasks can't send.
- Decoded values go into `extern` globals shared between tasks, with no protection.
- Filters, IDs and decode logic are spread across several files.
- No counters, so you can't tell if frames are dropped.

## What to build

The interface is already drafted in [`can_bus.h`](can_bus.h). Implement it in `can_bus.c` **on a Nucleo-F302R8**. It doesn't need the new board.

### Tasks

| # | Task | Done when |
|---|---|---|
| 1 | **Encode/decode helpers**: `can_encode_float`, `can_decode_float`, `can_encode_drive_cmd`. Pure C, no HAL | Unit tests in [`../../tests/`](../../tests/) pass on a laptop |
| 2 | **RX path**: `HAL_CAN_RxFifo0MsgPendingCallback` → `xQueueSendFromISR` into RX queue; count drops when full | Frames sent in loopback mode come out of `can_receive()` |
| 3 | **TX path**: `can_send()` pushes to TX queue (non-blocking); `can_tx_task` waits for a free mailbox (`HAL_CAN_GetTxMailboxesFreeLevel`) and sends | 100 frames queued at once all arrive in loopback, in order |
| 4 | **Filters**: accept only the IDs we care about (`0x5xx`, `0x6xx`, `0x70x`) | Frames with other IDs never reach the RX queue |
| 5 | **RX dispatch**: `can_rx_task` switches on ID, decodes, and updates [`../telemetry/`](../telemetry/) | Fake velocity frame → correct km/h printed over UART |
| 6 | **Stats & errors**: fill `can_stats_t`, handle `HAL_CAN_ErrorCallback`, print stats over UART every second | Unplugging the bus shows errors climbing |
| 7 | **Timeout detection**: record last-received time per source (MC, BMS) for [`../faults/`](../faults/) | Stop sending fake BMS frames → timeout flag set within 500 ms |
| 8 | **Bench test with a real second node**: USB-CAN adapter + SavvyCAN, or a second Nucleo | Drive command visible in SavvyCAN; fake MC/BMS frames decoded correctly |

Suggested split: newer members take 1 and 5 with a more experienced partner; members with some C / microcontroller experience take 2–4 and 6–7; task 8 is done together.

### Testing without a second board

Use bxCAN **loopback mode** (`CAN_MODE_LOOPBACK` in CubeMX). The chip receives its own frames, so no transceiver or bus is needed. Switch to **normal mode** only when there's a second node and termination on the bus.

## Rules for this module

- The ISR does **only**: read the frame, push to queue, count drops. No decoding, no `printf`.
- `can_send()` **never blocks**. If the queue is full, count it and return `false`.
- Floats on the bus are **little-endian IEEE-754**. Use the helpers, not unions, everywhere.

## Resources
- [`../../docs/can-messages.md`](../../docs/can-messages.md): IDs and layouts
- RM0365 bxCAN chapter; STM32F3 HAL manual (UM1786), CAN section
- FreeRTOS: `xQueueSendFromISR`, `xQueueReceive`
- VCU_2025 source
