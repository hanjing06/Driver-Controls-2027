/**
 * can_bus.h - CAN RX/TX queues on top of the STM32 bxCAN peripheral.
 * See README.md in this folder for the design and task breakdown.
 * Message IDs and layouts: firmware/docs/can-messages.md
 */
#ifndef CAN_BUS_H
#define CAN_BUS_H

#include <stdbool.h>
#include <stdint.h>

/* ---- Message IDs (from VCU_2025, confirm in research/) ---- */
#define CAN_ID_DRIVE_CMD      0x401u
#define CAN_ID_MC1_VELOCITY   0x503u
#define CAN_ID_MC1_HEATSINK   0x50Bu
#define CAN_ID_MC2_VELOCITY   0x603u
#define CAN_ID_MC2_HEATSINK   0x60Bu
#define CAN_ID_BMS_TEMP       0x701u
#define CAN_ID_BMS_VOLTAGE    0x702u
#define CAN_ID_BMS_CURRENT    0x703u

/* ---- Queue sizes (tune after research/freertos-queues Q12) ---- */
#define CAN_RX_QUEUE_LEN      32u
#define CAN_TX_QUEUE_LEN      16u

/* One CAN frame, as it travels through our queues */
typedef struct {
    uint32_t id;        /* 11-bit standard ID */
    uint8_t  dlc;       /* 0-8 */
    uint8_t  data[8];
    uint32_t timestamp_ms;
} can_frame_t;

/* Statistics: useful for debugging dropped frames */
typedef struct {
    uint32_t rx_count;
    uint32_t tx_count;
    uint32_t rx_queue_full_drops;
    uint32_t tx_queue_full_drops;
    uint32_t bus_errors;
} can_stats_t;

/* ---- Setup ---- */
void can_bus_init(void);                 /* create queues, set filters, start CAN, enable RX IRQ */

/* ---- Queue API ---- */
bool can_send(const can_frame_t *frame); /* push to TX queue; false if full (never blocks) */
bool can_receive(can_frame_t *out, uint32_t timeout_ms); /* pop from RX queue */
void can_get_stats(can_stats_t *out);

/* ---- RTOS tasks ---- */
void can_rx_task(void *arg);  /* pops RX queue -> decodes -> telemetry */
void can_tx_task(void *arg);  /* pops TX queue -> bxCAN mailbox */

/* ---- Encode / decode helpers (pure: unit-testable on a PC) ---- */
void  can_encode_drive_cmd(can_frame_t *out, float velocity_rpm, float current);
float can_decode_float(const uint8_t *bytes);   /* 4 bytes, little-endian IEEE-754 */
void  can_encode_float(uint8_t *bytes, float value);

#endif /* CAN_BUS_H */
