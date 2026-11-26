# Coding Standards

Short on purpose. Consistency over cleverness.

## Naming
- Files & functions: `snake_case`, prefixed by module: `lighting_update()`, `pedals_get_accel()`
- Types: `snake_case_t`: `vehicle_state_t`
- Macros/constants/enums: `UPPER_SNAKE`: `PEDAL_DEADBAND_PCT`
- Signal names match the ICD/KiCad net names: `PIN_BRAKE_LIGHT_OUT` ↔ `BrakeLightOut`

## Rules
1. Our code lives in `app/<module>/`. In generated files, only write between `USER CODE BEGIN/END`.
2. No raw `HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, …)` in `app/`; use `pinmap.h` names via `bsp`.
3. No new `extern` globals; expose getters from the owning module.
4. Data shared between tasks goes through a queue or a mutex.
5. Never block in an ISR. ISRs push to a queue and return.
6. No `HAL_Delay()` inside RTOS tasks; use `osDelay()`.
7. Use fixed-width types (`uint8_t`, `int32_t`). Mark ISR-shared variables `volatile`.
8. Every module has a header with a one-line comment per public function.
9. Don't leave large blocks of commented-out code. Git remembers it.
10. Units in names when not obvious: `velocity_mps`, `pack_voltage_v`.

## Formatting
4-space indent, braces on the same line, 100-column limit. A `.clang-format` will be added in `tools/`.
