# IoT Sensor Monitoring System with Blynk IoT

A comprehensive IoT health monitoring system using ESP32 with MAX30102 (heart rate, SpO2, temperature), ADXL345 (accelerometer), LDR (light detection), and Sound sensors, with real-time notifications and control through Blynk IoT Cloud platform.

## 🏗️ System Architecture

```
ESP32 (Sensors) → Blynk IoT Cloud → Blynk Mobile App
     ↓                ↓                    ↓
  MAX30102         Real-time Data      User Interface
  LDR Sensor       Push Notifications  Remote Control
  Sound Sensor     Data Visualization  Alert Management
```

## 📋 Components

### Hardware
- **ESP32 Development Board**
- **MAX30102** - Heart rate, SpO2 (blood oxygen), and temperature sensor
- **ADXL345** - 3-axis accelerometer for movement and fall detection
- **LDR Sensor** - Light detection (digital)
- **Sound Sensor** - Audio level detection (analog)
- **Breadboard and jumper wires**

### Software
- **ESP32 Firmware** - Arduino-based sensor monitoring with Blynk integration
- **Blynk IoT Cloud** - Cloud platform for data handling and notifications
- **Blynk Mobile App** - User interface and remote control

## 🔌 Hardware Wiring

### ESP32 Pin Connections

| Component | ESP32 Pin | Notes |
|-----------|-----------|-------|
| MAX30102 SDA | GPIO 21 | I2C Data |
| MAX30102 SCL | GPIO 22 | I2C Clock |
| MAX30102 VCC | 3.3V | Power |
| MAX30102 GND | GND | Ground |
| LDR Sensor | GPIO 2 | Digital input |
| Sound Sensor | GPIO 36 (A0) | Analog input |
| Sound Sensor VCC | 3.3V | Power |
| Sound Sensor GND | GND | Ground |

### Circuit Diagram
```
ESP32                    MAX30102
┌─────────┐             ┌─────────┐
│ GPIO 21 ├─────────────┤ SDA     │
│ GPIO 22 ├─────────────┤ SCL     │
│ 3.3V    ├─────────────┤ VCC     │
│ GND     ├─────────────┤ GND     │
└─────────┘             └─────────┘

ESP32                    LDR Sensor
┌─────────┐             ┌─────────┐
│ GPIO 2  ├─────────────┤ Signal  │
│ 3.3V    ├─────────────┤ VCC     │
│ GND     ├─────────────┤ GND     │
└─────────┘             └─────────┘

ESP32                    Sound Sensor
┌─────────┐             ┌─────────┐
│ GPIO 36 ├─────────────┤ Signal  │
│ 3.3V    ├─────────────┤ VCC     │
│ GND     ├─────────────┤ GND     │
└─────────┘             └─────────┘
```

## 🚀 Setup Instructions

### 1. ESP32 Setup

1. **Install Arduino IDE** with ESP32 support
2. **Install required libraries:**
   - SparkFun MAX3010x Pulse and Proximity Sensor Library
   - Blynk library
3. **Configure WiFi credentials** in `esp32_blynk_sensor_monitor.ino`
4. **Get Blynk Auth Token** from Blynk IoT Cloud
5. **Upload code** to ESP32

### 2. Blynk IoT Cloud Setup

1. **Create Blynk Account** at https://blynk.cloud
2. **Create New Template:**
   - Template name: "IoT Sensor Monitor"
   - Hardware: "ESP32"
   - Connection: "WiFi"
3. **Get Authentication Token** from template settings
4. **Configure Virtual Pins** as per configuration guide

### 3. Blynk Mobile App Setup

1. **Download Blynk IoT App** from App Store/Google Play
2. **Sign in** with your Blynk account
3. **Create New Device** from your template
4. **Configure Dashboard** with widgets for monitoring
5. **Set up Notifications** for alerts

## 📊 Sensor Thresholds

| Sensor | Normal Range | Alert Threshold | Action |
|--------|-------------|-----------------|---------|
| Heart Rate | 50-120 BPM | < 50 or > 120 BPM | Abnormal heart rate alert |
| SpO2 | 92-100% | < 92% | Low oxygen alert |
| Temperature | 90-100.4°F | > 100.4°F | High temperature alert |
| Sound Level | 0-500 | > 500 | High sound alert |
| Light Detection | 0 (Dark) | 1 (Light) | Sunlight detected alert |
| Acceleration | 0-2.0g | > 2.0g | High acceleration/fall alert |

## 🔧 Configuration

### ESP32 Configuration
```cpp
// Blynk authentication token
char auth[] = "YOUR_BLYNK_AUTH_TOKEN";

// WiFi credentials
char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";

// Sensor thresholds
const int HEART_RATE_THRESHOLD_LOW = 50;
const int HEART_RATE_THRESHOLD_HIGH = 120;
const int SPO2_THRESHOLD = 92;
const float TEMP_THRESHOLD_F = 100.4;
const int SOUND_THRESHOLD = 500;
const float ACCEL_THRESHOLD = 2.0;
```

### Blynk Virtual Pins
```cpp
// Data pins
Blynk.virtualWrite(V0, heartRate);      // Heart Rate
Blynk.virtualWrite(V1, spo2);           // SpO2 Level
Blynk.virtualWrite(V2, tempF);           // Temperature (°F)
Blynk.virtualWrite(V3, soundValue);      // Sound Level
Blynk.virtualWrite(V4, lightValue);      // Light Detection
Blynk.virtualWrite(V5, totalAcceleration); // Total Acceleration
Blynk.virtualWrite(V6, accelX);          // Acceleration X
Blynk.virtualWrite(V7, accelY);          // Acceleration Y
Blynk.virtualWrite(V8, accelZ);          // Acceleration Z

// Alert pins
Blynk.virtualWrite(V10, heartRateAlert);    // Heart Rate Alert
Blynk.virtualWrite(V11, spo2Alert);         // SpO2 Alert
Blynk.virtualWrite(V12, temperatureAlert);  // Temperature Alert
Blynk.virtualWrite(V13, soundAlert);        // Sound Alert
Blynk.virtualWrite(V14, lightAlert);        // Light Alert
Blynk.virtualWrite(V15, accelerationAlert); // Acceleration Alert

// Control pins
BLYNK_WRITE(V20) { /* Heart Rate Threshold */ }
BLYNK_WRITE(V21) { /* SpO2 Threshold */ }
BLYNK_WRITE(V22) { /* Temperature Threshold */ }
BLYNK_WRITE(V23) { /* Sound Threshold */ }
BLYNK_WRITE(V24) { /* Acceleration Threshold */ }
BLYNK_WRITE(V30) { /* Emergency Stop */ }
```

## 📱 Blynk Features

### Real-time Monitoring
- **Live sensor readings** displayed on mobile app
- **Instant push notifications** for alerts
- **Remote threshold adjustment** via sliders
- **Emergency stop** functionality

### Data Visualization
- **Value displays** for sensor readings
- **LED indicators** for alert status
- **Historical charts** for trend analysis
- **Customizable dashboard** layout

### Remote Control
- **Threshold adjustment** sliders
- **Alert enable/disable** toggles
- **Emergency stop** button
- **Device status** monitoring

## 🔔 Notification System

The system sends push notifications via Blynk IoT Cloud when:
- **Heart rate < 50 or > 120 BPM** ❤️
- **SpO2 < 92%** 🫁
- **Body temperature > 100.4°F** 🌡️
- **Sound level > 500** 🔊
- **Sunlight is detected** ☀️
- **Acceleration > 2.0g** 📱 (fall detection)

Notifications are automatically handled by Blynk IoT Cloud and delivered to the Blynk mobile app.

## 🛠️ Troubleshooting

### Common Issues

1. **ESP32 not connecting to WiFi**
   - Check WiFi credentials
   - Ensure WiFi network is 2.4GHz (ESP32 doesn't support 5GHz)

2. **Sensors not reading correctly**
   - Check wiring connections
   - Verify power supply (3.3V)
   - Calibrate sensor thresholds

3. **Blynk connection issues**
   - Verify auth token is correct
   - Check Blynk server status
   - Ensure stable internet connection

4. **Mobile app not receiving notifications**
   - Enable notifications in Blynk app
   - Check device notification permissions
   - Verify virtual pin configuration

### Debug Mode

Enable serial monitoring on ESP32 to see debug output:
```cpp
Serial.begin(115200);
```

## 📈 Future Enhancements

- [ ] Multiple device support
- [ ] Custom alert thresholds
- [ ] Historical data analysis
- [ ] Machine learning for anomaly detection
- [ ] Integration with health platforms
- [ ] Voice alerts and commands
- [ ] Automated reporting
- [ ] Multi-user access control

## 📄 License

This project is licensed under the MIT License - see the LICENSE file for details.

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Push to the branch
5. Create a Pull Request

## 📞 Support

For support and questions:
- Create an issue in the repository
- Contact: your.email@example.com

## 📚 Additional Documentation

- [Blynk Configuration Guide](docs/BLYNK_CONFIGURATION.md) - Detailed Blynk app setup
- [Installation Guide](docs/INSTALLATION_GUIDE.md) - Step-by-step setup instructions
- [Wiring Guide](docs/WIRING_GUIDE.md) - Hardware connection details

---

**Note:** This system uses Blynk IoT Cloud for simplified IoT development. For production use, consider implementing additional security measures and data validation.
