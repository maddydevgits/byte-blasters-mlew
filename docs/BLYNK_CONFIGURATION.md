# Blynk IoT App Configuration Guide

This guide will help you set up the Blynk IoT mobile app to monitor your ESP32 sensor system.

## 📱 Blynk App Setup

### 1. Download Blynk IoT App
- **Android**: Download from Google Play Store
- **iOS**: Download from App Store
- **Web**: Access via https://blynk.cloud

### 2. Create Blynk Account
1. Open Blynk IoT app
2. Sign up with email or social login
3. Verify your email address

### 3. Create New Template
1. In Blynk app, tap "Create New Template"
2. Template name: "IoT Sensor Monitor"
3. Hardware: "ESP32"
4. Connection type: "WiFi"
5. Note down the **Template ID** and **Template Name**

### 4. Get Authentication Token
1. Go to your template settings
2. Copy the **Auth Token**
3. Update the token in your ESP32 code:
   ```cpp
   char auth[] = "YOUR_BLYNK_AUTH_TOKEN";
   ```

## 🎛️ Blynk Dashboard Configuration

### Virtual Pins Mapping

| Virtual Pin | Function | Widget Type | Description |
|-------------|----------|-------------|-------------|
| V0 | Heart Rate | Value Display | Shows current heart rate in BPM |
| V1 | SpO2 Level | Value Display | Shows blood oxygen saturation in % |
| V2 | Temperature | Value Display | Shows body temperature in °F |
| V3 | Sound Level | Value Display | Shows sound sensor reading |
| V4 | Light Detection | LED | Shows light detection status |
| V5 | Total Acceleration | Value Display | Shows total acceleration magnitude |
| V6 | Acceleration X | Value Display | Shows X-axis acceleration |
| V7 | Acceleration Y | Value Display | Shows Y-axis acceleration |
| V8 | Acceleration Z | Value Display | Shows Z-axis acceleration |
| V10 | Heart Rate Alert | LED | Red LED for heart rate alerts |
| V11 | SpO2 Alert | LED | Red LED for low oxygen alerts |
| V12 | Temperature Alert | LED | Red LED for temperature alerts |
| V13 | Sound Alert | LED | Red LED for sound alerts |
| V14 | Light Alert | LED | Red LED for light alerts |
| V15 | Acceleration Alert | LED | Red LED for acceleration alerts |
| V20 | Heart Rate Threshold | Slider | Adjust heart rate threshold |
| V21 | SpO2 Threshold | Slider | Adjust SpO2 threshold |
| V22 | Temperature Threshold | Slider | Adjust temperature threshold |
| V23 | Sound Threshold | Slider | Adjust sound threshold |
| V24 | Acceleration Threshold | Slider | Adjust acceleration threshold |
| V30 | Emergency Stop | Button | Emergency stop all alerts |

### Widget Configuration

#### 1. Heart Rate Display (V0)
- **Widget**: Value Display
- **Label**: "Heart Rate"
- **Unit**: "BPM"
- **Color**: Green (normal), Red (alert)
- **Min**: 0, **Max**: 200
- **Update frequency**: 1 second

#### 2. SpO2 Display (V1)
- **Widget**: Value Display
- **Label**: "Blood Oxygen (SpO2)"
- **Unit**: "%"
- **Color**: Green (normal), Red (alert)
- **Min**: 70, **Max**: 100
- **Update frequency**: 5 seconds

#### 3. Temperature Display (V2)
- **Widget**: Value Display
- **Label**: "Body Temperature"
- **Unit**: "°F"
- **Color**: Blue (normal), Red (alert)
- **Min**: 90, **Max**: 110
- **Update frequency**: 5 seconds

#### 4. Sound Level Display (V3)
- **Widget**: Value Display
- **Label**: "Sound Level"
- **Unit**: "dB"
- **Color**: Green (normal), Red (alert)
- **Min**: 0, **Max**: 1000
- **Update frequency**: 5 seconds

#### 5. Light Detection LED (V4)
- **Widget**: LED
- **Label**: "Light Detection"
- **Color**: Yellow (detected), Gray (none)
- **Update frequency**: 1 second

#### 6. Acceleration Displays (V5-V8)
- **Widget**: Value Display
- **Label**: "Total Accel", "Accel X", "Accel Y", "Accel Z"
- **Unit**: "g"
- **Color**: Green (normal), Red (alert)
- **Min**: -16, **Max**: 16
- **Update frequency**: 5 seconds

#### 7. Alert LEDs (V10-V15)
- **Widget**: LED
- **Label**: "Heart Rate Alert", "SpO2 Alert", "Temperature Alert", "Sound Alert", "Light Alert", "Acceleration Alert"
- **Color**: Red (alert active), Gray (normal)
- **Update frequency**: Real-time

#### 8. Threshold Controls (V20-V24)
- **Widget**: Slider
- **Label**: "Heart Rate Threshold", "SpO2 Threshold", "Temperature Threshold", "Sound Threshold", "Acceleration Threshold"
- **Min**: 0, **Max**: 200 (heart rate), 100 (SpO2), 110 (temperature), 1000 (sound), 5.0 (acceleration)
- **Default**: 100, 92, 100.4, 500, 2.0

#### 9. Emergency Stop (V30)
- **Widget**: Button
- **Label**: "Emergency Stop"
- **Color**: Red
- **Action**: Momentary

## 📊 Dashboard Layout

### Recommended Layout:
```
┌─────────────────────────────────────┐
│        IoT Health Monitor           │
├─────────────────────────────────────┤
│ Heart Rate: 85 BPM        [Normal]  │
│ SpO2: 98%                [Normal]   │
│ Temperature: 98.6°F      [Normal]   │
│ Sound Level: 250          [Normal]  │
│ Light Detection: [LED]              │
│ Total Accel: 1.2g         [Normal]  │
│ Accel X: 0.1g, Y: 0.8g, Z: 0.9g    │
├─────────────────────────────────────┤
│ ALERTS:                             │
│ ❤️ Heart Rate Alert: [LED]          │
│ 🫁 SpO2 Alert: [LED]                │
│ 🌡️ Temperature Alert: [LED]        │
│ 🔊 Sound Alert: [LED]              │
│ ☀️ Light Alert: [LED]               │
│ 📱 Acceleration Alert: [LED]        │
├─────────────────────────────────────┤
│ CONTROLS:                           │
│ Heart Rate Threshold: [Slider]      │
│ SpO2 Threshold: [Slider]          │
│ Temperature Threshold: [Slider]     │
│ Sound Threshold: [Slider]          │
│ Acceleration Threshold: [Slider]    │
│ [Emergency Stop Button]            │
└─────────────────────────────────────┘
```

## 🔔 Notification Setup

### 1. Enable Notifications
1. Go to Template Settings
2. Enable "Push Notifications"
3. Configure notification preferences

### 2. Event Configuration
The ESP32 code automatically sends these events:
- `heart_rate_alert`: When heart rate < 50 or > 120 BPM
- `spo2_alert`: When SpO2 < 92%
- `temp_alert`: When temperature > 100.4°F (38°C)
- `sound_alert`: When sound level > threshold
- `acceleration_alert`: When acceleration > threshold (fall detection)

### 3. Notification Settings
- **Alert Level**: High priority
- **Sound**: Default notification sound
- **Vibration**: Enabled
- **LED**: Device LED notification

## 🎨 Customization Options

### Themes
- **Light Theme**: Clean, minimal design
- **Dark Theme**: Easy on the eyes
- **Custom Colors**: Match your preferences

### Widget Styling
- **Colors**: Customize widget colors
- **Sizes**: Adjust widget sizes
- **Layout**: Drag and drop to rearrange

### Data Visualization
- **Charts**: Add historical data charts
- **Graphs**: Real-time sensor data graphs
- **Gauges**: Analog-style displays

## 📱 Mobile App Features

### Real-time Monitoring
- Live sensor readings
- Instant alert notifications
- Remote threshold adjustment
- Emergency stop functionality

### Historical Data
- View past sensor readings
- Export data for analysis
- Trend analysis charts

### Remote Control
- Adjust sensor thresholds
- Enable/disable alerts
- Emergency stop button
- Device status monitoring

## 🔧 Advanced Configuration

### Data Logging
1. Enable "Data Export" in template settings
2. Set logging interval (1 second recommended)
3. Choose data format (CSV, JSON)

### Multiple Devices
1. Create device instances from template
2. Each device gets unique auth token
3. Monitor multiple sensors simultaneously

### Web Dashboard
1. Access via https://blynk.cloud
2. Same functionality as mobile app
3. Larger screen for better visualization

## 🚨 Troubleshooting

### Common Issues

**Device not connecting:**
- Check WiFi credentials
- Verify auth token
- Ensure ESP32 is powered

**Data not updating:**
- Check virtual pin mapping
- Verify widget configuration
- Check ESP32 serial output

**Notifications not working:**
- Enable notifications in app settings
- Check device notification permissions
- Verify event names in code

**Widgets not responding:**
- Check virtual pin assignments
- Verify widget types match code
- Test with simple values first

### Debug Tips
1. Monitor ESP32 serial output
2. Check Blynk app connection status
3. Verify virtual pin values in app
4. Test individual widgets

## 📈 Next Steps

1. **Test Basic Connection**: Upload code and verify connection
2. **Configure Widgets**: Set up all virtual pins and widgets
3. **Test Alerts**: Trigger alerts and verify notifications
4. **Customize Layout**: Arrange widgets to your preference
5. **Add Charts**: Include historical data visualization
6. **Share Access**: Invite others to monitor your system

## 💡 Pro Tips

- Use **Value Display** widgets for sensor readings
- Use **LED** widgets for alert status
- Use **Slider** widgets for threshold controls
- Use **Button** widgets for manual controls
- Enable **Data Export** for historical analysis
- Set appropriate **update frequencies** to save energy
- Use **color coding** for quick status recognition

This configuration provides a complete IoT monitoring solution with real-time alerts, remote control, and data visualization - all through the Blynk IoT platform!
