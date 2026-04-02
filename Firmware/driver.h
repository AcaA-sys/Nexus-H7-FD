/*

  driver.h - driver code for STM32H7xx ARM processors

  Part of grblHAL

  Copyright (c) 2021-2026 Terje Io

// Minimum pulse off time.
// Минимальное время паузы между импульсами (Off time)
// Установка в 0.5f позволит поднять частоту до ~1 МГц при $0=0.5
#ifndef STEP_PULSE_TOFF_MIN
#define STEP_PULSE_TOFF_MIN 0.5f//2.0f
#endif
// Time from main stepper interrupt to pulse output, must be less than STEP_PULSE_TOFF_MIN.
// Adjust for correct pulse off time after configuring and running at a step rate > max possible.
#ifndef STEP_PULSE_TON_LATENCY
#if SPINDLE_SYNC_ENABLE
#define STEP_PULSE_TON_LATENCY 0.5f//1.35f
#else
#define STEP_PULSE_TON_LATENCY 0.2f//0.65f
#endif
#endif
// Time from step out to step reset.
// Adjust for correct step pulse time
// Задержка от прерывания до физического импульса
#ifndef STEP_PULSE_TOFF_LATENCY
#define STEP_PULSE_TOFF_LATENCY 0.2f//0.35f
#endif
// Only used when step injection is enabled (stepper spindle and plasma THC)
// Задержка сброса (выключения) импульса
#ifndef STEP_PULSE_LATENCY
#define STEP_PULSE_LATENCY 0.1f//1.0f // microseconds
#endif



#endif // __DRIVER_H__
