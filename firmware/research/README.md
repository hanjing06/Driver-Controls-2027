# Research

[Home](../../README.md) › [Firmware](../README.md) › **Research**

Research supports the integration test: learn what you need to run your task. Each topic folder has a README with **why it matters**, **questions to answer**, **where to look**, and **what to hand in**.

## How to do a research topic

1. Open an issue "Research: <topic>" and assign yourself (a topic can have 2 people).
2. Read the topic README and the resources. Take notes as you go.
3. Write `notes.md` in the topic folder:
   - Answer every question, **in your own words**
   - Add diagrams (draw.io, hand-drawn photo, ASCII, all fine)
   - List sources at the bottom
   - Add a "**What this means for our VCU**" section at the end. This is the most valuable part
4. Open a PR (`fw/research-<topic>`). Someone else on the team reviews it.
5. Present it at a team meeting (5–10 min).

## Topics

**Needed now** for the [integration test](../integration-test/):

| Topic | Depends on | Needed for |
|---|---|---|
| [`can-fundamentals/`](can-fundamentals/) | — (**everyone reads this**) | Everyone |
| [`can-tools/`](can-tools/) | can-fundamentals | Task 1: bus setup |
| [`motor-controller-can/`](motor-controller-can/) | can-fundamentals | Task 2: motor controller |
| [`bms-can/`](bms-can/) | can-fundamentals | Task 3: BMS telemetry |

**Later**, once the integration test passes:

| Topic | Depends on |
|---|---|
| [`stm32-bxcan/`](stm32-bxcan/) | can-fundamentals |
| [`freertos-queues/`](freertos-queues/) | — |

Good research notes from this year become the onboarding material for next year.
