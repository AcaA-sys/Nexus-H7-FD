# Nexus-H7-FD
                High-performance grblHAL motion controller based on STM32H723 (550MHz) with Dual CAN FD for OpenPnP.

Hardware: V1.0 Ready (PCB Designed). Firmware: In development (Core driver fixes for H723 verified by dresco). Support for 1MHz Step/Dir generation via TIM1/TIM8 high-speed timers.

High-Speed Step Generation (1MHz Secret)
The 1MHz Challenge on STM32H7
Most grblHAL controllers operate at 100-400kHz. Nexus-H7 FD is designed to push the boundaries of SMT placement speed:
Target: Stable 1.0 MHz pulse frequency on X/Y axes.
Implementation: Leverages TIM1 / TIM8 high-speed timers in Toggle Mode with direct register access (GPIO BSRR).
Signal Integrity: PCB layout optimized for fast edge rates. All Step/Dir lines are routed with impedance considerations to prevent ringing and ghost pulses at 1MHz frequencies.
Driver Support: Optimized for high-speed optocouplers and digital drivers (ClearPath, Delta, Leadshine).

Bug fixed Aux analog https://github.com/dresco/STM32H7xx/issues/61#issuecomment-3804045790


The printed circuit board Nexus-H7 FD Master contains:
- Motion Control (1 MHz Step/Dir) X and Y Axis.
- Communication interfaces (isolated) RS-485 TDH541S485H, 2*CAN FD TD541SCANFD.
- UCC21520DW drivers (isolated), keys 4 x NTMFS5C628.
- Nextion Intelligen HMI.
- XGZP6847 vacuum, joystick + button.
- +5V power supply (separate power supply).
- 100x75mm printed circuit board, board mounting adapted for 20x80mm aluminum profile.

Nexus-Tower Slave (Pluggable PCB Concept)
Status: Architecture Design / In Progress
The Nexus-Tower is a specialized point-of-use controller designed to be mounted directly on the PnP head. Its "Pluggable" nature allows for rapid maintenance and re-configuration of the head's peripherals.
Key Hardware Features:
MCU: STM32G431 (Advanced Mixed-Signal MCU, 170MHz).
Hybrid Motion Control:
- 1x Z-Axis: Dedicated High-Precision Servo/Stepper control.
- 2x C-Axis (Nozzles): Dual TMC2209 (UART Mode) for quiet and precise rotation (C1/C2).
- Integrated Pneumatics Hub:
- 4x Valve Outputs: PWM-capable MOSFETs for pick-and-place cycles.
- 2x Analog Vacuum Channels: Direct connection for XGZP6847 sensors (real-time ADC feedback over CAN FD).
Lighting & Sensing:
- 1x PWM Light Control: Dedicated channel for nozzle/camera illumination.
- 3x Endstop Inputs: Z-min, C1-home, C2-home.

Nexus-Drive FD: High-Performance Servo Node
Status: Advanced Concept / Research Phase
The Nexus-Drive FD is an intelligent FOC (Field Oriented Control) servo controller designed to drive X and Y axes with industrial-grade dynamics. It offloads real-time motor physics from the Master H7, communicating via high-speed CAN FD.
Key Hardware Features:
- MCU: STM32G431 (170MHz, Cordic math accelerator for FOC).
- Power Stage: 3-Phase Gate Driver (DRV8301 or DRV8323) with 6x High-current N-CH MOSFETs (PowerFLAT 5x6).
- Current Sensing: Dual or Triple shunt resistors with G431 internal OPAMPs for precise torque control.
- Feedback: AS5047P / AS5048 Magnetic Absolute Encoder (14-bit SPI) for closed-loop position control.
- Safety: Hardware Overcurrent, Overtemperature, and Stall Detection reporting back to Nexus-H7 via CAN FD.
- Performance: Silent operation (Stealth), Zero step loss, and "Soft Collision" detection through real-time torque monitoring.

Concept: Nexus-Feeder FD (Smart Actuator)
This is a tiny module that fits into each feeder (or a bank of 10 feeders).
Key Hardware Features:
- MCU: STM32G0B1 (the cheapest chip with CAN FD and an integrated oscillator) or similar.
- Driver: Integrated microstepper driver (e.g., TMC2300 – operates from 2V, tiny, and silent).
- Sensing: Optical end-of-ribbon sensor + component presence sensor (IR reflectance).
- Interface: Pass-through CAN FD + Power connector. Feeders are connected to each other in a "train-like" fashion in the base slots.
