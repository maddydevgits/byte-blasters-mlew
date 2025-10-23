# ESP32 Sensor Wiring Guide

## Required Components
- ESP32 Development Board
- MAX30102 Heart Rate & Temperature Sensor
- ADXL345 Accelerometer Sensor
- LDR (Light Dependent Resistor) Sensor
- Sound Sensor (Analog)
- Breadboard
- Jumper wires
- Resistors (10kΩ for LDR)

## Detailed Wiring Instructions

### MAX30102 Sensor
The MAX30102 is an I2C sensor that measures heart rate and temperature.

**Connections:**
- VCC → ESP32 3.3V
- GND → ESP32 GND
- SDA → ESP32 GPIO 21
- SCL → ESP32 GPIO 22

**Notes:**
- The MAX30102 operates at 3.3V
- Pull-up resistors are usually built into the sensor module
- Place finger on sensor for accurate readings

### ADXL345 Accelerometer Sensor
The ADXL345 is an I2C sensor that measures acceleration in 3 axes. Uses Adafruit ADXL345 library.

**Connections:**
- VCC → ESP32 3.3V
- GND → ESP32 GND
- SDA → ESP32 GPIO 21 (shared with MAX30102)
- SCL → ESP32 GPIO 22 (shared with MAX30102)

**Notes:**
- The ADXL345 operates at 3.3V
- Can share I2C bus with MAX30102 (different addresses)
- Measures acceleration in X, Y, Z axes
- Range: ±16g (configurable)
- Used for fall detection and movement monitoring
- Uses Adafruit ADXL345 library for easy integration

### LDR (Light Dependent Resistor) Sensor
Digital light detection sensor.

**Connections:**
- Signal → ESP32 GPIO 2
- VCC → ESP32 3.3V
- GND → ESP32 GND

**Circuit:**
```
3.3V ──┬── 10kΩ Resistor ──┬── GPIO 2
       │                   │
       └── LDR ───────────┘
       │
       GND
```

### Sound Sensor
Analog sound level detection.

**Connections:**
- Signal → ESP32 GPIO 36 (A0)
- VCC → ESP32 3.3V
- GND → ESP32 GND

**Notes:**
- GPIO 36 is an analog input pin
- Adjust sensitivity using the potentiometer on the sensor module
- Values range from 0-4095 (12-bit ADC)

## Power Supply
- ESP32 can be powered via USB (5V) or external power supply
- All sensors use 3.3V logic level
- Ensure stable power supply for accurate readings

## Testing Connections
1. Upload a simple test sketch to verify connections
2. Use serial monitor to check sensor readings
3. Test each sensor individually before integrating

## Safety Notes
- Double-check all connections before powering on
- Use appropriate resistors to prevent damage
- Keep sensors away from moisture
- Handle MAX30102 sensor carefully (optical components)
