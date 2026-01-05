# Embedded JSON Serializer for w-M-Bus–Related Firmware

## Project Overview
This project implements an embedded-friendly software library that serializes structured
smart meter data into a predefined JSON format.

The library is designed to represent a realistic firmware component in a smart-meter /
w-M-Bus data pipeline:

Measurement data → internal data structures → JSON serialization → gateway/backend interface

Radio communication, OMS, encryption, and real meter interaction are intentionally out of scope.
The focus is on clean software architecture, deterministic memory usage, and correct JSON output.

---

## Platform & Programming Language

**Chosen Platform:** Arduino-compatible environment (portable C/C++)

**Programming Language:** C / C++

### Justification
The Arduino-compatible environment provides a minimal embedded runtime and simple
console/serial output for demonstration purposes. This allows the focus to remain on
firmware-level data modeling, API design, and serialization logic rather than hardware
configuration.

The code itself is platform-agnostic and can be reused in STM32CubeIDE, ESP-IDF,
or other embedded toolchains with minimal adaptation.

---

## Project Structure


---

## Data Model

The internal data model is implemented using simple C structures without dynamic memory
allocation.

### Gateway Data
- `gatewayId` (string)
- `date` (YYYY-MM-DD)
- `deviceType` (string)
- `interval_minutes` (integer)
- `total_readings` (integer)

### Measurement Data
- Number of devices
- List of device readings
- Each device contains:
  - Media type
  - Meter type
  - Device ID
  - Unit
  - One or more meter data points

Each meter data point contains:
- Timestamp
- Meter timestamp
- Total meter value
- Status

---

## Public API

```c
int serialize_to_json(const GatewayData* input,
                      char* output,
                      size_t buffer_size);
