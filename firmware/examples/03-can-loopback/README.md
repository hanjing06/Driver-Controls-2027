# Example 03: CAN Loopback 🟡

**Goal:** send and receive a CAN frame on a single Nucleo, with no transceiver or bus, using loopback mode.
**Read first:** [`../../research/can-fundamentals/`](../../research/can-fundamentals/)

## Steps
1. In the `.ioc`: enable **CAN** on PA11/PA12, **Operating mode: Loopback**, bit timing for **500 kbit/s** (VCU_2025: prescaler 8, BS1 = 2 TQ, BS2 = 5 TQ, with the clock at 64 MHz / APB1 32 MHz). Enable **CAN RX0 interrupt**.
2. Configure a filter that accepts everything (mask 0), then `HAL_CAN_Start` and `HAL_CAN_ActivateNotification(..., CAN_IT_RX_FIFO0_MSG_PENDING)`.
3. Every second, send ID `0x401` with 8 bytes: velocity `20000.0f` + current `0.25f` as little-endian floats.
4. In `HAL_CAN_RxFifo0MsgPendingCallback`, read the frame and set a flag; in the main loop, print the ID and 8 bytes, and decode the two floats back.

## Done when
- UART shows `RX 0x401: 00 40 9C 46 00 00 80 3E → v=20000.0 I=0.25` every second

## Stretch (leads into the real task)
- Move sending into a FreeRTOS task, and pass received frames through a **queue** to a print task. That's [`app/can_bus/`](../../app/can_bus/) in miniature.
- Switch to normal mode with a USB-CAN adapter and see the frame in SavvyCAN ([`research/can-tools`](../../research/can-tools/)).
