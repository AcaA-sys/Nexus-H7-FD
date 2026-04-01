/*
 * Nexus-H7 FD Master Node - Configuration Map
 * MCU: STM32H723VGT6 (550MHz)
 * Target: grblHAL / OpenPnP
 * Features: 1MHz Step/Dir, Dual CAN FD, Isolated RS485
 * 
 * Автор: AcaA-sys
 */

// --- СЕКЦИЯ STEP/DIR (РАЗГОН ДО 1 МГЦ) ---
// Используем Port E для минимизации задержек на шине AHB4

#ifndef MAP_H_
#define MAP_H_

// 1. ТАКТИРОВАНИЕ (HSE 25MHz)
#define HSE_VALUE    25000000UL

// 2. ШАГОВЫЕ ДВИГАТЕЛИ (X, Y) - Port E
// Использование одного порта (GPIOE) обеспечивает максимальную скорость (1МГц)
#define STEP_PORT      GPIOE
#define STEPX_PIN      1   // PE1
#define DIRX_PIN       0   // PE0
#define STEPY_PIN      3   // PE3
#define DIRY_PIN       2   // PE2
#define STEP_EN_PIN    4   // PE4
#define STEP_EN_INVERT      // Инвертируем, если драйвер активен низким уровнем

// 3. СИЛОВАЯ ПЕРИФЕРИЯ (PWM) - Port E
#define AUX_PWM_PORT   GPIOE
#define OUT1_PIN       12  // PE12 (TIM1_CH3N)
#define OUT2_PIN       13  // PE13 (TIM1_CH3)
#define OUT3_PIN       14  // PE14 (TIM1_CH4)
#define OUT4_PIN       15  // PE15 (TIM1_BKIN2)

//#define AUXOUTPUT5_PORT  GPIOE // оптрон АТС
//#define AUXOUTPUT5_PIN   5
//#define AUXOUTPUT6_PORT  GPIOE // оптрон АТС
//#define AUXOUTPUT6_PIN   6


// Блокировка драйверов (Safety)
#define UCC_DIS_PORT   GPIOE
#define UCC_DIS_PIN    10  // PE10 (High = Disabled)

// 4. СВЯЗЬ И ИНТЕРФЕЙСЫ
// RS-485 (USART1 или UART4 - уточнить в HAL)
#define RS485_PORT     GPIOA
#define RS485_TX_PIN   9   // PA9
#define RS485_RX_PIN   10  // PA10
#define RS485_DE_PIN   8   // PA8 (Direction Control)

// Nextion (USART2)
#define HMI_PORT       GPIOD
#define HMI_TX_PIN     5   // PD5
#define HMI_RX_PIN     6   // PD6

// CAN FD 1 (Основной Main)
#define CAN1_PORT      GPIOD
#define CAN1_TX_PIN    1   // PD1
#define CAN1_RX_PIN    0   // PD0
// CAN FD2 
#define CAN2_PORT      GPIOB
#define CAN2_TX_PIN    13   // 
#define CAN2_RX_PIN    12   // 

// 5. ВХОДЫ (Inputs) - Port C
#define IN_PORT        GPIOC
#define ESTOP_PIN      14  // PC14
//#define RUN_PIN        0   // PC0
#define ALARM_PIN      13  // PC13
#define LIMIT_Y_PIN    4   // PC4
//#define LIMIT_X_PIN    5   // PC5 (Reserve)

// 6. АНАЛОГОВЫЕ ВХОДЫ (ADC)
#define ADC_PORT       GPIOA
#define VACUUM1_PIN    2   // PA2 (ADC1_IN14)
#define VACUUM2_PIN    3   // PA3 (ADC1_IN15)
#define JOY_X_PIN      4   // PA4 (ADC1_IN18)
#define JOY_Y_PIN      5   // PA5 (ADC1_IN19)
#define JOY_BTN_PIN    6   // PA6 (Digital In)
#define VBUS_DET_PIN   7   // PA7 (USB Sense)

// 7. ПАМЯТЬ И ИНДИКАЦИЯ
#define I2C1_PORT      GPIOB
#define I2C1_SCL_PIN   8   // PB8
#define I2C1_SDA_PIN   9   // PB9

#define LED_PORT       GPIOC
#define STATUS_LED_PIN 2   // PC2
#define ERROR_LED_PIN  3   // PC3

// 8. СПЕЦИАЛЬНЫЕ НАСТРОЙКИ (grblHAL)
// Отключение детекции VBUS на PA9 (конфликт с RS-485)
#define USB_VBUS_DETECTION_DISABLED 

#endif
