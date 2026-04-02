/*
 * Nexus-H7 FD Master Node - Configuration Map
 * MCU: STM32H723VGT6 (550MHz)
 * Target: grblHAL / OpenPnP
 * Features: 0.8 MHz Step/Dir, Dual CAN FD, Isolated RS485
 * 
 * Автор: AcaA-sys
 */

// --- СЕКЦИЯ STEP/DIR (РАЗГОН ДО 0.8 МГЦ) ---
// Используем Port E для минимизации задержек на шине AHB4

#ifndef MAP_H_
#define MAP_H_

// 1. ТАКТИРОВАНИЕ ( 25МГц)
#define HSE_VALUE 25000000UL

// 2. ШАГОВЫЕ ДВИГАТЕЛИ (X, Y) - Порт E
// Использование одного порта (GPIOE) обеспечивает поддержку скорости (1МГц)
#define X_STEP_PORT   GPIOE
#define X_STEP_PIN    1                 // X
#define Y_STEP_PORT   GPIOE
#define Y_STEP_PIN    3                  // Y
#define Z_STEP_PORT   GPIOE
#define Z_STEP_PIN    7                 // Z
#define STEP_OUTMODE  GPIO_SINGLE
//#define STEP_EN_PIN 4 // PE4
#define STEP_EN_INVERT // Инвертируем, если драйвер активен хорошего уровня

// Define step direction output pins.
#define X_DIRECTION_PORT            GPIOE
#define X_DIRECTION_PIN             0
#define Y_DIRECTION_PORT            GPIOE
#define Y_DIRECTION_PIN             2
#define Z_DIRECTION_PORT            GPIOE
#define Z_DIRECTION_PIN             8
#define DIRECTION_OUTMODE           GPIO_SINGLE
//#define DIRECTION_PINMODE           PINMODE_OD // Uncomment for open drain outputs

// Define stepper driver enable/disable output pin.
#define X_ENABLE_PORT               GPIOE
#define X_ENABLE_PIN                4
#define Y_ENABLE_PORT               GPIOE
#define Y_ENABLE_PIN                4
#define Z_ENABLE_PORT               GPIOE
#define Z_ENABLE_PIN                4
//#define STEPPERS_ENABLE_PINMODE   PINMODE_OD // Uncomment for open drain outputs

// Define homing/hard limit switch input pins.
#define X_LIMIT_PORT                GPIOC
#define X_LIMIT_PIN                 0                           // X- Limit
#define Y_LIMIT_PORT                GPIOC
#define Y_LIMIT_PIN                 4                           // Y- Limit
#define Z_LIMIT_PORT                GPIOC
#define Z_LIMIT_PIN                 5                           // Z- Limit
#define LIMIT_INMODE                GPIO_SINGLE

// 3. СИЛОВАЯ ПЕРИФЕРИЯ (PWM) - Порт E
#define AUX_PWM_PORT GPIOE
#define OUT1_PIN 12 // PE12 (TIM1_CH3N)
#define OUT2_PIN 13 // PE13 (TIM1_CH3)
#define OUT3_PIN 14 // PE14 (TIM1_CH4)
#define OUT4_PIN 15 // PE15 (TIM1_BKIN2)

//#define AUXOUTPUT5_PORT GPIOE // оптрон АТС
//#define AUXOUTPUT5_PIN 5
//#define AUXOUTPUT6_PORT GPIOE // оптрон АТС
//#define AUXOUTPUT6_PIN 6


// Блокировка драйверов (Безопасность)
#define UCC_DIS_PORT GPIOE
#define UCC_DIS_PIN 10 // PE10 (Высокий уровень = Отключено)

// 4. СВЯЗЬ И ИНТЕРФЕЙСЫ
// RS-485 (USART1 или UART4 — уточнение в HAL)
#define RS485_PORT GPIOA
#define RS485_TX_PIN 9 // PA9
#define RS485_RX_PIN 10 // PA10
#define RS485_DE_PIN 8 // PA8 (управление направлением)

// Nextion (USART2)
#define HMI_PORT GPIOD
#define HMI_TX_PIN 5 // PD5
#define HMI_RX_PIN 6 // PD6

// CAN FD 1 (Основной основной)
#define CAN1_PORT GPIOD
#define CAN1_TX_PIN 1 // PD1
#define CAN1_RX_PIN 0 // PD0
// CAN FD2
#define CAN2_PORT GPIOB
#define CAN2_TX_PIN 13 //
#define CAN2_RX_PIN 12 //

// 5. ВХОДЫ (Входы) - Порт C
#define IN_PORT GPIOC
#define ESTOP_PIN 14 // PC14
//#define RUN_PIN 15 // PC15
#define ALARM_PIN 13 // PC13
#define AUXINPUT1_PORT GPIOC  // Probe
#define AUXINPUT1_PIN  15

#if PROBE_ENABLE
#define PROBE_PORT  AUXINPUT1_PORT
#define PROBE_PIN   AUXINPUT1_PIN
#endif


// 6. АНАЛОГОВЫЕ ВХОДЫ (ADC)
#define ADC_PORT GPIOA
#define VACUUM1_PIN 2 // PA2 (ADC1_IN14)
#define VACUUM2_PIN 3 // PA3 (ADC1_IN15)
#define JOY_X_PIN 4 // PA4 (ADC1_IN18)
#define JOY_Y_PIN 5 // PA5 (ADC1_IN19)
#define JOY_BTN_PIN 6 // PA6 (Цифровой вход)
#define VBUS_DET_PIN 7 // PA7 (USB Sense)

// 7. ПАМЯТЬ И ИНДИКАЦИЯ
#define I2C1_PORT GPIOB
#define I2C1_SCL_PIN 8 // PB8
#define I2C1_SDA_PIN 9 // PB9

#define LED_PORT GPIOC
#define STATUS_LED_PIN 2 // PC2
#define ERROR_LED_PIN 3 // PC3

// 8. СПЕЦИАЛЬНЫЕ НАСТРОЙКИ (grblHAL)
// Отключение детекции VBUS на PA9 (конфликт с RS-485)
#define USB_VBUS_DETECTION_DISABLED

#endif
