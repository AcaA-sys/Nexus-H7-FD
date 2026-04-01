/*
 * PnP-Controller H723 v1.0 - grblHAL Pin Mapping
 * MCU: STM32H723VGT6
 */

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
// CAN FD2 (Aux)

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

#endif /* MAP_H_ */


/*Что нужно сделать дальше:
Проверка TIM1: В настройках grblHAL (или STM32Cube) убедитесь, что пины PE12-PE15 назначены на таймер TIM1. Это позволит управлять вакуумом и клапанами плавно через ШИМ.
Настройка CAN FD: Поскольку у вас 6 осей на CAN, в my_machine.h нужно будет добавить плагин canbus и прописать ID для каждого узла.
Логика PE10: В функции инициализации board_init() добавьте принудительную установку PE10 в HIGH сразу после сброса, чтобы ключи не «дернулись» до полной загрузки прошивки.
1. Полная совместимость (Drop-in Replacement)
Эти чипы имеют ту же распиновку и архитектуру, различаясь только объемом памяти или набором интерфейсов:
STM32H733VGT6: Почти идентичен. Основное отличие — встроенное аппаратное ускорение криптографии (Crypto/Hash). Если прошивка grblHAL его не использует, замена будет бесшовной.
STM32H725VGT6: Более продвинутая версия. Имеет интерфейс Octo-SPI (вместо Quad-SPI) и иногда больше оперативной памяти. Распиновка совпадает.
STM32H735VGT6: Топовый чип в этой подгруппе. Включает криптографию и расширенные интерфейсы памяти. Полностью совместим по пинам.
2. Частичная совместимость (Серия H743 / H753)
Это "классика" H7, но они работают на частоте 480 МГц (против 550 МГц у H723).
STM32H743VIT6 / VGT6: Популярные чипы. У них больше Flash (2 МБ), но меньше максимальная частота.
Нюанс: У них другая структура памяти (AxiSRAM) и настройки тактирования PLL. Придется пересобирать проект в STM32Cube с изменением типа МК.
CAN FD: Поддерживается так же, как в H723.
3. Бюджетная альтернатива (Серия H723 с меньшей памятью)
STM32H723VET6: Буква "E" означает 512 КБ Flash (вместо 1 МБ у "G"). Если ваш бинарный файл grblHAL со всеми плагинами умещается в 512 КБ, это самый дешевый способ сэкономить без переделки платы.

Рекомендация: Если H723VGT6 нет в наличии, ищите H733VGT6 или H725VGT6 — они потребуют минимум правок в коде.

Для замены STM32H723VGT6 существуют прямые аналоги от китайских производителей, таких как GigaDevice и Geehy. Они часто превосходят оригинал по тактовой частоте, но требуют внимательной проверки библиотек.
1. Прямые китайские аналоги (Pin-to-Pin)
Наиболее близкие варианты в корпусе LQFP100:
GD32H737VGT6 (GigaDevice): Самый мощный конкурент.
Частота: до 600 МГц (у STM32H723 — 550 МГц).
Память: сопоставимый объем Flash и SRAM.
Совместимость: физически полностью совпадает по пинам, но имеет свои регистры периферии. Потребуется адаптация драйверов CAN FD и USB в прошивке.
APM32F103VET6 (Geehy): Не является аналогом по производительности (это серия F1), но часто упоминается как доступная замена в том же корпусе для менее требовательных задач. Для PnP-контроллера с 8 осями не рекомендуется из-за отсутствия нужной мощности и CAN FD. 
GigaDevice
GigaDevice
 +3
2. Ключевые отличия китайских H7 (GD32H7)
При переходе на GigaDevice учитывайте следующие моменты:
Питание: GD32H7 обычно имеет более простую схему питания ядра, но при прямой замене на вашу плату это не должно вызвать проблем, если разведен стандартный LDO.
Периферия: Таймеры и ADC работают очень похоже, однако драйверы для FDCAN и USB в grblHAL придется переписывать под SDK от GigaDevice.
Кварц: Ваш резонатор 25 МГц полностью поддерживается GD32H7. 
GigaDevice
GigaDevice
 +1
3. Резюме по замене
Модель	Частота	Flash	SRAM	Совместимость
STM32H723VGT6	550 МГц	1 МБ	564 КБ	Оригинал
GD32H737VGT6	600 МГц	1-3 МБ	до 1 МБ	Высокая (нужна правка кода)
STM32H743VGT6	480 МГц	1-2 МБ	1 МБ	Полная (ST-на-ST)
 */