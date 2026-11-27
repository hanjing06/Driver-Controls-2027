# Research: FreeRTOS Tasks & Queues

[Home](../../../README.md) › [Firmware](../../README.md) › [Research](../README.md) › **FreeRTOS queues**

**Assigned to:**

## Why it matters

The VCU firmware runs on **FreeRTOS**. CAN frames arrive in an interrupt, but the work of decoding them happens in a task. The safe way to pass data between the two is a **queue**. This research is the other half of the CAN queues task.

## Questions to answer in `notes.md`

**Tasks**
1. What is a task? What does the scheduler do? What does **priority** mean in FreeRTOS?
2. What's the difference between `osDelay()` and `HAL_Delay()`, and why must tasks use `osDelay()`?
3. What are the task states (running, ready, blocked, suspended)?

**Queues**
4. What is a queue? What happens when a task reads from an empty queue (blocking with a timeout)?
5. What happens when you write to a full queue?
6. Why must you use `xQueueSendFromISR()` (not `xQueueSend()`) inside an interrupt? What is `pxHigherPriorityTaskWoken` for?
7. Queues copy data by value. What's the trade-off of queueing a whole CAN frame struct vs. a pointer?

**Sharing data**
8. What is a **race condition**? Give an example with two tasks and a global variable.
9. What is a **mutex**, and when would you use one instead of a queue?

**CMSIS-RTOS**
10. VCU_2025 uses the CMSIS-RTOS v1 wrapper (`osThreadDef`, `osMessageQId`, ...) that CubeMX generates. How do those map to native FreeRTOS calls (`xTaskCreate`, `xQueueCreate`)? Which should we use?

**What this means for our VCU**
11. Look at VCU_2025's `canRxTask` and how `CAN_Receive.c` passes frames to it. Is there anything unsafe (globals shared between tasks without protection)?
12. How big should the CAN RX queue be? (Hint: how many frames per second arrive, and how often does the RX task run?)

## Resources
- [FreeRTOS kernel docs](https://www.freertos.org/Documentation/02-Kernel/01-About-the-FreeRTOS-kernel/01-FreeRTOS-kernel), especially "Queues" and "Interrupt safe API"
- *Mastering the FreeRTOS Real Time Kernel* (free PDF from freertos.org): chapters on queues and interrupts
- Digi-Key YouTube: *Introduction to RTOS* series (parts on queues and mutexes)
- VCU_2025 `main.c` and `CAN_Receive.c`

## Done when
- [ ] `notes.md` answers 1–12
- [ ] A tiny demo on a Nucleo: one task sends a counter through a queue, another prints it over UART (commit to `../../examples/` on your branch)
- [ ] Presented at a team meeting
