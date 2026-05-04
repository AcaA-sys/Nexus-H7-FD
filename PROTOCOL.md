# Nexus-CAN FD Protocol Specification (v1.0)

## 1. System Architecture
The Nexus system uses a dual-bus CAN FD topology managed by a Master controller (STM32H723) running grblHAL.

### Bus A: CAN FD-1 (Primary Motion)
- **Focus:** Low-latency control for main Gantry axes (X and Y).
- **Nodes:** 2x Nexus-Drive-FD.
- **Speed:** 1 Mbps (Nominal) / 5 Mbps (Data).

### Bus B: CAN FD-2 (Toolhead & Analytics)
- **Focus:** Auxiliary motion, toolhead peripherals, and high-precision sensing.
- **Nodes:** 1x Nexus-Tower-G4 (6-axis controller), 1x Nexus-Accel-Unit (ADXL355).
- **Speed:** 1 Mbps (Nominal) / 5 Mbps (Data).

---

## 2. CAN ID Allocation (11-bit Standard)
Priority is given to motion and high-speed sensing.


| ID (Hex) | Source | Function | Description |
| :--- | :--- | :--- | :--- |
| **0x010** | Master | **SYNC** | Global time synchronization pulse |
| **0x120** | Accel | **ACCEL_DATA** | Real-time ADXL355 stream (X, Y, Z) |
| **0x201** | Master | **DRIVE_X_CMD** | Nexus-Drive-FD (Axis X) commands |
| **0x202** | Master | **DRIVE_Y_CMD** | Nexus-Drive-FD (Axis Y) commands |
| **0x310** | Master | **TOWER_CMD** | 6-axis control & Peripherals for Tower-G4 |
| **0x311** | Tower | **TOWER_STATUS**| Vacuum (ADS1115) & Axis feedback |
| **0x410** | Tower/Acc| **ENV_DATA** | Temperature (DS18B20) & Diagnostics |
| **0x720** | Master | **SERVICE** | Flash Memory (Black Box) data retrieval |

---

## 3. Data Frames Definition

### 3.1 Precision Acceleration (ID: 0x120)
Packs 20-bit raw data from ADXL355.
- **Byte 0-3:** Timestamp (uint32_t, microseconds).
- **Byte 4-11:** Sample 1 (X, Y, Z - 20 bit each, packed).
- **Byte 12-19:** Sample 2 (X, Y, Z - 20 bit each, packed).
- **Status:** Integrated into the last 4 bits of Sample 2 (Data Ready, Tap, Activity).

### 3.2 Tower Multi-Axis Control (ID: 0x310)
Optimized frame to control 6 axes (Z, N1, N2, Tool, Aux1, Aux2).
- **Byte 0:** Target Axis ID (0-5).
- **Byte 1-4:** Target Position (int32_t).
- **Byte 5-6:** Velocity (uint16_t).
- **Byte 7:** Actuator Mask (Vacuum, Solenoids, LED).

### 3.3 Environmental & Thermal (ID: 0x410)
- **Byte 0-1:** Temperature (°C * 100).
- **Byte 2-3:** Vacuum Level (Raw ADC).

---

## 4. Bandwidth & Storage Management
Due to the **5 Mbps physical limit** of the TD541SCANFD transceiver:

1. **Real-time Mode:** ADXL355 streams at 1000Hz to Bus B. 
2. **Black Box Mode:** High-speed 4000Hz (20-bit) data is stored locally on the **W25Q128 SPI Flash**.
3. **Retrieval:** Logged data is transferred via Service ID (0x720) only when the machine is idle to prevent motion interference.
4. **Thermal Compensation:** Master (H723) applies offset corrections to coordinates based on ID 0x410 data.

---
*Developed by AcaA-sys for the Nexus OpenPnP Ecosystem.*

