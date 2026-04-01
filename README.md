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
