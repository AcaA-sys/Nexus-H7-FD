# Nexus-CAN FD Protocol Specification (v1.2)

## 1. System Topology
The Nexus ecosystem operates on a dual-bus architecture managed by the **Nexus-H7-FD** (Master) running grblHAL.

### Bus A: CAN FD-1 (High-Priority Motion)
- **Master:** STM32H723
- **Nodes:** 2x Nexus-Drive-FD (Axes X and Y)
- **Transceiver:** TD541SCANFD (Limit: 5 Mbps)
- **Role:** Primary trajectory execution and real-time error correction.

### Bus B: CAN FD-2 (Toolhead, Sensing & Virtual Axes)
- **Master:** STM32H723
- **Nodes:** Nexus-Tower-G4 (Multi-axis hub), Nexus-Accel-Unit (ADXL355/345)
- **Transceiver:** TD541SCANFD (Limit: 5 Mbps)
- **Role:** Toolhead motion, 20-bit vibration analytics, and virtual axis coordination.

---

## 2. CAN ID Allocation (11-bit Standard)
Priority is ranked by ID value (Lower = Higher Priority).


| ID (Hex) | Name | Source | Description |
| :--- | :--- | :--- | :--- |
| **0x010** | **SYS_SYNC** | Master | Global timestamp sync pulse |
| **0x050** | **RT_CORRECTION** | Master | **Active Trajectory Offset** (Real-time compensation) |
| **0x120** | **ACCEL_DATA** | Accel | Vibration stream (X, Y, Z - 20 bit) |
| **0x201** | **DRIVE_X_CMD** | Master | X-Axis Target/Velocity |
| **0x202** | **DRIVE_Y_CMD** | Master | Y-Axis Target/Velocity |
| **0x310** | **TOWER_V_AXIS** | Master | **Virtual Axis Command** (Multi-motor macro) |
| **0x311** | **TOWER_STATUS** | Tower | Vacuum (ADS1115) & Axis feedback |
| **0x410** | **ENV_DATA** | Tower | Temperature (DS18B20) for Thermal Comp. |
| **0x720** | **SERVICE** | Master | Black Box (Flash) data retrieval |

---

## 3. Critical Frame Definitions

### 3.1 Active Trajectory Correction (ID: 0x050)
Real-time offset sent to Bus A to counteract mechanical inertia/vibrations.
- **Bytes 0-3:** Offset X (int32_t, nanometers/microsteps)
- **Bytes 4-7:** Offset Y (int32_t, nanometers/microsteps)
*Drive-FD must inject this offset into the current motion buffer instantly.*

### 3.2 High-Precision Acceleration (ID: 0x120)
- **Byte 0-3:** Timestamp (uint32_t, microseconds).
- **Byte 4-12:** Sample 1 (X, Y, Z - 20 bit each, packed).
- **Byte 13:** Status Flags (Data Ready, Collision Detect).

### 3.3 Virtual Axis Control (ID: 0x310)
Used to control multiple motors on Tower-G4 without overloading grblHAL core.
- **Byte 0:** Virtual Group ID (e.g., Nozzle_Rotate_All, Tool_Change_Seq).
- **Byte 1-4:** Target Value / Coordinate (int32_t).
- **Byte 5-6:** Speed/Parameter (uint16_t).
- **Byte 7:** Command Bitmask (Vacuum, Solenoids).

---

## 4. Operational Logic
1. **Motion Isolation:** Primary axes (X/Y) stay on Bus A. All sensing and toolhead actions stay on Bus B.
2. **Active Loop:** Master (H723) reads vibration from ID 0x120 (Bus B), processes the PID/Filter, and issues correction ID 0x050 (Bus A) within <1ms.
3. **Bandwidth Management:** Tower axes use Open-Loop Step/Dir. No encoder feedback is streamed back unless requested, saving 5 Mbps bandwidth for 20-bit Accel data.
4. **Black Box:** Full 4kHz 20-bit raw logs are saved to local **W25Q128 SPI Flash** and retrieved during machine idle via ID 0x720.

---
*Nexus Ecosystem Protocol - Designed for Micron-level Pick and Place accuracy.*



