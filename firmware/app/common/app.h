/**
 * app.h - Entry point from CubeMX main.c into our application.
 *
 * main.c (USER CODE sections) should only:
 *   1. call app_init() after MX_*_Init()
 *   2. call app_create_tasks() before osKernelStart()
 */
#ifndef APP_H
#define APP_H

void app_init(void);         /* init all app modules */
void app_create_tasks(void); /* create RTOS tasks (see firmware/docs/architecture.md) */

#endif /* APP_H */
