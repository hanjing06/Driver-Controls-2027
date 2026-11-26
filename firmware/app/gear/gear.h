/**
 * gear.h - Debounced gear selector.
 */
#ifndef GEAR_H
#define GEAR_H

typedef enum { GEAR_NEUTRAL, GEAR_DRIVE, GEAR_REVERSE, GEAR_INVALID } gear_t;

void   gear_update(void);
gear_t gear_get(void);

#endif /* GEAR_H */
