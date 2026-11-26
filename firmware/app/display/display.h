/**
 * display.h - Driver LCD (NHD-C0220BIZ, 2x20 characters, I2C).
 */
#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

/* Low-level LCD driver */
void lcd_init(void);
void lcd_clear(void);
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_print(const char *text);

/* Screens */
void display_update(void);   /* draw speed / pack voltage / state / faults from telemetry */

#endif /* DISPLAY_H */
