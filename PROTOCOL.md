# Nexus-CAN FD Protocol Specification (v1.1)

## 1. System Topology
The Nexus ecosystem operates on a dual-bus architecture managed by the **Nexus-H7-FD** (Master) running grblHAL.

### Bus A: CAN FD-1 (High-Priority Motion)
- **Master:** STM32H723
- **Nodes:** 2x Nexus-Drive-FD (Axes X and Y)
- **Transceiver:** TD541SCANFD (Limit: 5 Mbps)
- **Role:** Critical trajectory execution and real-time error correction.

### Bus B: CAN FD-2 (Toolhead & Sensing)
- **Master:** STM32H723
- **Nodes:** Nexus-Tower-G4 (6-axis hub), Nexus-Accel-Unit (ADXL355/345)
- **Transceiver:** TD541SCANFD (Limit: 5 Mbps)
- **Role:** Toolhead motion, vacuum control, and 20-bit vibration analytics.

---

## 2. CAN ID Allocation (11-bit Standard)
IDs are ranked by priority. Lower hex values have higher bus priority.


| ID (Hex) | Name | Source | Description |
| :--- | :--- | :--- | :--- |
| **0x010** | **SYS_SYNC** | Master | Global timestamp sync pulse |
| **0x050** | **RT_CORRECTION** | Master | **Active Trajectory Offset** (Real-time) |
| **0x120** | **ACCEL_DATA** | Accel | Vibration stream (X, Y, Z - 20 bit) |
| **0x201** | **DRIVE_X_CMD** | Master | X-Axis Target/Velocity |
| **0x202** | **DRIVE_Y_CMD** | Master | Y-Axis Target/Velocity |
| **0x310** | **TOWER_CMD** | Master | 6-axis Control (Z, N1, N2, Tool, Aux1/2) |
| **0x311** | **TOWER_STATUS**| Tower | Vacuum (ADS1115) & Limit switches |
| **0x410** | **ENV_DATA** | Tower | Temperature (DS18B20) for Thermal Comp. |
| **0x720** | **SERVICE** | Master | Black Box (Flash) data retrieval |

---

## 3. Critical Frame Definitions

### 3.1 Active Trajectory Correction (ID: 0x050)
Sent by Master to Bus A to compensate for mechanical inertia detected by the accelerometer.
- **Bytes 0-3:** Offset X (int32_t, nanometers or microsteps)
- **Bytes 4-7:** Offset Y (int32_t, nanometers or microsteps)
*Note: Nexus-Drive-FD must apply this offset instantly to the current motion buffer.*

### 3.2 High-Precision Acceleration (ID: 0x120)
Packs 20-bit raw data. 
- **Byte 0-3:** Timestamp (uint32_t, microseconds).
- **Byte 4-12:** Sample 1 (X, Y, Z - 20 bit each, packed).
- **Byte 13:** Status Flags (Data Ready, Trigger, Tap).

### 3.3 Multi-Axis Tower Control (ID: 0x310)
- **Byte 0:** Target Axis Index (0=Z, 1=N1, 2=N2, 3=Tool, 4=Aux1, 5=Aux2).
- **Byte 1-4:** Target Position (int32_t).
- **Byte 5-6:** Velocity (uint16_t).
- **Byte 7:** Actuator Mask (Vacuum, Solenoids, LED).

---

## 4. Bandwidth & Performance Strategy
Due to the **5 Mbps** physical limit of the transceivers:

1. **Dual-Bus Isolation:** High-speed streaming from the Accelerometer on Bus B does not jitter the step-generation on Bus A.
2. **Black Box Bypass:** For 4000Hz analysis, data is logged to the **W25Q128 SPI Flash** on the Tower/Accel node and retrieved via ID 0x720 during idle states.
3. **Active Loop:** The Master (H723) processes ID 0x120 from Bus B and generates ID 0x050 for Bus A to minimize settling time and vibration blur.

---

### Bandwidth Management"
Bus Load Optimization: Since Tower-G4 axes (Z, N1, N2, etc.) operate without encoders, communication is strictly "Command-Response". This prevents bus congestion and ensures jitter-free streaming of 20-bit accelerometer data (ID 0x120) even during multi-axis moves.

---

*Nexus Ecosystem Protocol - Designed for Micron-level Pick and Place accuracy.*


