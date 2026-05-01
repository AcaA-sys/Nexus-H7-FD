# Nexus-H7 FD: High-Performance  Controller

Nexus-H7 FD — это передовой контроллер движения на базе STM32H723 (550MHz)

🚀 Основные особенности
- 0.8 MHz Step/Dir: Стабильная генерация импульсов на осях X/Y. Реализовано через низкоуровневый доступ к таймерам TIM1/TIM8 и регистрам GPIO BSRR ("800 KHz Secret").
- Dual Isolated CAN FD: Две независимые шины для распределенного управления (Оси X/Y Servo + Tower/Feeders).
- Isolated RS-485: Выделенный интерфейс для умных питателей (Nexus-Feeder) по протоколу Modbus/Custom.
- Industrial Grade: Полная гальваническая развязка драйверов (UCC21520), CAN и RS-485 интерфейсов.
- OpenPnP Ready: Исправлены баги маппинга аналоговых входов в плагине OpenPnP (ADC PA0/PA1 теперь видны как E0/E1).

🛠 Технические характеристики (Hardware v1.0)
- MCU: STM32H723VGT6 (ARM Cortex-M7, 550MHz).
- Габариты: 100x75мм (крепление под алюминиевый профиль 20x80мм).
- Силовые ключи: Полная гальваническая развязка силовых драйверов 4 x NTMFS5C628 (2х0-24V,2х24V) для помп и освещения.
- Интерфейсы: Nextion Intelligent HMI (USART2), 2x CAN FD, RS-485.
- Сенсоры: Поддержка датчиков вакуума XGZP6847, аналоговый джойстик.
- Память: FRAM FM24CL16B для хранения координат и настроек + W25Q128.

📂 Структура репозитория
- /Firmware/nexus_h7_fd_map.h — Конфигурация пинов (Pinout).
- /Firmware/driver.h — Оптимизированный движок генерации импульсов (0.8 MHz Logic).
- /Plugins/pnp_pneumatics.c — Экспериментальный плагин управления вакуумом.

👨‍💻 Статус разработки
- Hardware: V1.0 Ready (в стадии завершения дизайна платы).
- Firmware: В активной разработке. Базовая поддержка STM32H723 подтверждена разработчиками grblHAL (fixes by dresco).
System Roadmap:
- Проектирование Nexus-Tower (Slave-модуль головы на STM32G431R).
- Проектирование Nexus-Drive FD (Slave-модуль High-Torque FOC Servo, Concept. 3-Phase Gate Driver (DRV8323H) with 6x High-current N-CH MOSFETs (PowerFLAT 5x6).)
- Разработка протокола Nexus-Feeder (RS-485).
🤝 Коллаборация
Проект открыт для энтузиастов и разработчиков. Если вы хотите поучаствовать в создании экосистемы CAN FD модулей или тестировании плагинов — добро пожаловать в Issues.

________________________
# Nexus-H7-FD (v1.2) — Universal Controller

**Nexus-H7-FD** — это высокопроизводительная промышленная платформа для систем автоматизации, ориентированная на использование в PnP-установщиках (OpenPnP). Построена на базе мощного МК **STM32H723VGT6** (550 МГц) с распределенной архитектурой управления по шине **CAN FD**.

## 🚀 Основные характеристики
- **Core:** STM32H723VGT6, 550 MHz, 32-bit Cortex-M7.
- **Bus:** 2x Isolated CAN FD (до 5 Мбит/с) для периферийных модулей.
- **Power:** 4x NTMFS5C628 (150A) с изолированными драйверами UCC21520 (5.7 кВ).
- **Vision:** Высокоскоростной порт (10 Мбит/с) на базе TLP2362 для стробоскопической подсветки (Vision-on-the-Fly).

---

## 📍 Распиновка (Pinout Map)

### 1. Управление движением (Motion)

| Обозначение | Пин | Функция | Примечание |
| :--- | :---| :---  | :--- |
| **X_STEP** | `PE1` | TIM1_CH1 | Step Local X |
| **X_DIR**  | `PE0` | GPIO | Dir Local X |
| **Y_STEP** | `PE3` | TIM1_CH2 | Step Local Y |
| **Y_DIR**  | `PE2` | GPIO | Dir Local Y |
| **ENABLE** | `PE4` | GPIO | Общий сигнал Enable |


### 2. Память (Storage)

| Чип | Пин | Функция | Описание |
| :--- | :--- | :--- | :--- |
| **W25Q128** 
| |  PB2` | QSPI_CLK | 16MB Flash (Clock < 10mm) |
| | `PB10`| QSPI_NCS | Chip Select (10k Pull-up) |
| | `PD11`| QSPI_IO0 | Data Line 0 |
| | `PD13`| QSPI_IO1 | Data Line 1 |
| | `PE7` | QSPI_IO2 | Data Line 2 |
| | `PD12`| QSPI_IO3 | Data Line 3 |
| **FM24C256**
| |`PB8`| I2C1_SCL | 32KB FRAM (Non-volatile) |
| |`PB9`| I2C1_SDA | Fast Mode Plus |
| |`PB7`| WP| защита от записи |

### 3. Силовая часть (Power & High Speed)

| Канал | Пин | Драйвер / Оптика | Назначение |
| :--- | :--- | :--- | :--- |
| **PWM_1** | `PE12`| UCC21520DW | Вспышка камеры  |
| **PWM_2** | `PE13`| UCC21520DW | Вибро двигатель |
| **PWM_3** | `PE14`| UCC21520DW | Вакуумный насос |
| **PWM_4** | `PE15`| UCC21520DW | Насос давления  |
|**DISABLE**| `PE10`| UCC21520DW | DISABLE |
| **PWM_5** | `PE11`| TLP2362    | Управление лазером (Aux), камера(Sync-on-the-Fly) |
| **OUT_6** | `PB6`| TLP290 | Оптоизолятор |
| **OUT_7** | `PB5`| TLP290 | Оптоизолятор |
| **OUT_8** | `PE6`| TLP290 | Оптоизолятор |
| **OUT_9** | `PE5`| TLP290 | Оптоизолятор | 

### 4. Интерфейсы

| Интерфейс | Пины | Индикация (LED) | Примечание |
| :--- | :--- | :--- | :--- |
| **CAN FD 1** | `PD0`(RX), `PD1`(TX) | `PD14`(T), `PD15`(E) | Isolated Bus |
| **CAN FD 2** | `PB12`(RX), `PB13`(TX)| `PB14`(T), `PB15`(E) | Isolated Bus |
| **RS-485**   | `PA9`, `PA10`, `PA8` | `PD9`(TX), `PD12`(RX) | Isolated |
| **DS18B20**  | `PC6`(Data), `PC8`(Pwr)| — | ID & Temp Sensor |
| **NEXTION**  | `PD5`(TX), `PD6`(RX) | — | USART2 HMI |

### 5. Аналоговый блок и Входы
- **Джойстик:** `PA4`(X), `PA5`(Y), `PA6`(Key)
- **Вакуум-сенсор:** `PA2`, `PA3` (Analog XGZP6847)
- **Audio/Scope:** `PA0`(DAC), `PA1`(Sync Out)
- **Концевики:** `PC0`(Y), `PC4`(X), `PC5`(Res), `(PC13, PC15` резерв)
- **E-Stop:** `PC14` (Hardware Buffer)
- **Кнопка:** `PD7` (выбор режима)

---

## 🛠 Технологические особенности
- **Разделение земель:** Цифровая и силовая части гальванически развязаны.
- **Сигнальные линии:** Все линии QSPI выровнены по длине для работы на частотах до 133 МГц.
- **Периферия:** Совместимость с модулями на базе **STM32G431** через Raw CAN / CAN FD.

---
© 2026 Nexus-H7 Project

---
*Developed by AcaA-sys*
*Special thanks to **dresco** and **Terje Io** for grblHAL support.*

