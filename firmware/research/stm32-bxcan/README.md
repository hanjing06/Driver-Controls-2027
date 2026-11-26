# Research: STM32 bxCAN Peripheral 🟡

**Assigned to:**
**Read first:** [`../can-fundamentals/`](../can-fundamentals/)

## Why it matters

The STM32F302R8 has a built-in CAN controller called **bxCAN**. The CAN queues task ([`../../app/can_bus/`](../../app/can_bus/)) is built directly on it, so whoever implements it needs to know how its mailboxes, FIFOs, filters and interrupts work.

## Questions to answer in `notes.md`

**Transmit**
1. bxCAN has **3 TX mailboxes**. What happens when all three are full and we call `HAL_CAN_AddTxMessage()`?
2. How does bxCAN decide which mailbox to send first?

**Receive**
3. bxCAN has **2 RX FIFOs, each 3 messages deep**. What happens if a 4th frame arrives before we read them (FIFO overrun)?
4. Which interrupt fires when a frame arrives (`HAL_CAN_RxFifo0MsgPendingCallback`)? Why should the callback be as short as possible?

**Filters**
5. Explain **mask mode** vs. **list mode** filters. Write a filter config that accepts only IDs `0x500–0x5FF`.
6. What does VCU_2025's filter config accept? (Look at `CAN_Receive.c` / `main.c` in [VCU_2025](https://github.com/uixt/VCU_2025).)

**Modes & timing**
7. What are **loopback** and **silent** mode, and why are they useful for testing on a bench with no other nodes?
8. VCU_2025 uses prescaler 8, BS1 = 2 TQ, BS2 = 5 TQ at APB1 = 32 MHz. Show that this gives 500 kbit/s. Where is the sample point? Is that a good sample point (look up the CiA recommendation)?
9. What changes in the bit timing when we switch from HSI to an 8 MHz HSE crystal (if APB1 stays 32 MHz)?

**What this means for our VCU**
10. Given 3 mailboxes and 3-deep FIFOs, why do we need **software queues** on top? Sketch how the ISR, queues and tasks fit together.

## Resources
- **RM0365** reference manual: the bxCAN chapter (the authority)
- STM32F3 HAL user manual (UM1786): CAN driver section
- [bittiming.can-wiki.info](http://www.bittiming.can-wiki.info/): CAN bit-timing calculator
- VCU_2025 `CAN_Receive.c`, `CAN_Transmit.c`

## Done when
- [ ] `notes.md` answers 1–10, including the bit-timing math
- [ ] Presented at a team meeting
