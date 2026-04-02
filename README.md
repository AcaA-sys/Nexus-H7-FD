# Nexus-H7 FD: High-Performance Motion Controller

**Nexus-H7 FD** — это передовой контроллер движения на базе **STM32H723** (550MHz), спроектированный специально для профессиональных SMT-установщиков (**OpenPnP**) и высокоскоростных систем ЧПУ под управлением **grblHAL**.

## 🚀 Основные особенности

*   **1.0 MHz Step/Dir:** Стабильная генерация импульсов на осях X/Y. Реализовано через низкоуровневый доступ к таймерам TIM1/TIM8 и регистрам GPIO BSRR (**"1MHz Secret"**).
*   **Dual Isolated CAN FD:** Две независимые шины для распределенного управления (Оси X/Y Servo + Tower/Feeders).
*   **Isolated RS-485:** Выделенный интерфейс для умных питателей (**Nexus-Feeder**) по протоколу Modbus/Custom.
*   **Industrial Grade:** Полная гальваническая развязка драйверов (UCC21520), CAN и RS-485 интерфейсов.
*   **OpenPnP Ready:** Исправлены баги маппинга аналоговых входов в плагине OpenPnP (ADC PA0/PA1 теперь видны как E0/E1).

## 🛠 Технические характеристики (Hardware v1.0)

*   **MCU:** STM32H723VGT6 (ARM Cortex-M7, 550MHz).
*   **Габариты:** 100x75мм (крепление под алюминиевый профиль 20x80мм).
*   **Силовые ключи:** Полная гальваническая развязка силовых драйверов 4 x NTMFS5C628 (12-24V) для помп и освещения.
*   **Интерфейсы:** Nextion Intelligent HMI (USART2), 2x CAN FD, RS-485.
*   **Сенсоры:** Поддержка датчиков вакуума XGZP6847, аналоговый джойстик.
*   **Память:** FRAM FM24CL16B для хранения координат и настроек.

## 📂 Структура репозитория

*   `/Firmware/nexus_h7_fd_map.h` — Конфигурация пинов (Pinout).
*   `/Firmware/driver.h` — Оптимизированный движок генерации импульсов (1MHz Logic).
*   `/Plugins/pnp_pneumatics.c` — Экспериментальный плагин управления вакуумом.

## 👨‍💻 Статус разработки

*   **Hardware:** V1.0 Ready (в стадии завершения дизайна платы).
*   **Firmware:** В активной разработке. Базовая поддержка STM32H723 подтверждена разработчиками grblHAL (fixes by **dresco**).
*   **System Roadmap:** 
    *   Проектирование **Nexus-Tower** (Slave-модуль головы на G431).
    *   Проектирование  **Nexus-Drive FD** (Slave-модуль High-Torque FOC Servo, Concept. 3-Phase Gate Driver (DRV8301 or DRV8323) with 6x High-current N-CH MOSFETs (PowerFLAT 5x6).)
    *   Разработка протокола **Nexus-Feeder** (RS-485).
 

## 🤝 Коллаборация

Проект открыт для энтузиастов и разработчиков. Если вы хотите поучаствовать в создании экосистемы CAN FD модулей или тестировании плагинов — добро пожаловать в Issues.

---
*Developed by AcaA-sys*
*Special thanks to **dresco** and **Terje Io** for grblHAL support.*

