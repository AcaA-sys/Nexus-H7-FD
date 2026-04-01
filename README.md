# Nexus-H7-FD
High-performance grblHAL motion controller based on STM32H723 (550MHz) with Dual CAN FD for OpenPnP.

High-Speed Step Generation (1MHz Secret)
The 1MHz Challenge on STM32H7
Most grblHAL controllers operate at 100-400kHz. Nexus-H7 FD is designed to push the boundaries of SMT placement speed:
Target: Stable 1.0 MHz pulse frequency on X/Y axes.
Implementation: Leverages TIM1 / TIM8 high-speed timers in Toggle Mode with direct register access (GPIO BSRR).
Signal Integrity: PCB layout optimized for fast edge rates. All Step/Dir lines are routed with impedance considerations to prevent ringing and ghost pulses at 1MHz frequencies.
Driver Support: Optimized for high-speed optocouplers and digital drivers (ClearPath, Delta, Leadshine).

