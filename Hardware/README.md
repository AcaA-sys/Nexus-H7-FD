    Nexus-H7 FD Master Node
High-Performance Motion Controller for OpenPnP / grblHAL
Overview
Nexus-H7 FD is a high-speed motion control platform designed for professional SMT placement machines. Based on the STM32H723 (550MHz), it implements a distributed control architecture via Dual CAN FD buses, eliminating complex wiring and maximizing step-generation frequency.
Technical Specifications
MCU: STM32H723VGT6, ARM Cortex-M7 @ 550MHz.
Firmware: Fully compatible with grblHAL (H7 driver fixes by dresco).
Step/Dir Performance: Up to 1MHz pulse frequency for X/Y axes (local).
Communication Interfaces (Isolated):
Dual CAN FD: 2x Isolated ports (TD541SCANFD) for distributed axis nodes (Feeders, Head, Actuators).
RS-485: 1x Isolated port (TDH541S485H) for Modbus/Nextion HMI.
On-board Peripherals:
External axes: 2 Local (X/Y) + 6 via CAN FD.
Memory: FRAM FM24CL16B (I2C) for non-volatile parameter storage.
Inputs: 6x Buffered inputs (74LVC) for E-Stop, Run, Alarm, Limits.
Power Outputs: 4x High-current PWM MOSFETs (NTMFS5C628) with isolated UCC21520 drivers.
Analog: 2x ADC channels for Vacuum sensors (XGZP6847), 2x ADC for Joystick.
Software Integration Status
Core: grblHAL STM32H7xx driver verified.
Plugin: OpenPnP plugin integration fixed.
Key Fix: ADC mapping for PA0/PA1 now correctly identified as Aux analog in 0/1 (E0/E1), enabling direct sensor feedback in OpenPnP actuators.
Distributed Architecture (The Nexus Ecosystem)
The system is designed to work with Nexus-Tower and Nexus-Drive Slave nodes:
Protocol: Custom high-speed CAN FD message set.
Slave MCU: STM32G431 (FDCAN, FOC-capable).
Functions: Local motor control (Servo/Stepper), vacuum sensing, and valve actuation at the point of use.
Contact / Collaboration
Looking for developers and early adopters to define the standard CAN FD message set for PnP peripherals.
Hardware: Nexus-H7 FD v1.0 (100x75mm, DIN-rail / 20x80 profile mount).

