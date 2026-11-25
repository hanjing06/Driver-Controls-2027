/**
 * can_bus.h - CAN receive/transmit. IDs in firmware/docs/can-messages.md.
 */
#ifndef CAN_BUS_H
#define CAN_BUS_H

#include <stdint.h>

#define CAN_ID_DRIVE_CMD      0x401u
#define CAN_ID_MC1_VELOCITY   0x503u
#define CAN_ID_MC1_HEATSINK   0x50Bu
#define CAN_ID_MC2_VELOCITY   0x603u
#define CAN_ID_MC2_HEATSINK   0x60Bu
#define CAN_ID_BMS_TEMP       0x701u
#define CAN_ID_BMS_VOLTAGE    0x702u
#define CAN_ID_BMS_CURRENT    0x703u

void can_bus_init(void);                                    /* filters, start, enable RX IRQ */
void can_rx_task(void *arg);                                /* decodes frames -> telemetry */
void can_send_drive_cmd(float velocity_rpm, float current); /* current 0.0 - 1.0 */

#endif /* CAN_BUS_H */
