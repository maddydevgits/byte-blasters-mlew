# Installation Guide

## Prerequisites

### For ESP32 Development
- Arduino IDE (latest version)
- ESP32 board package
- Required Arduino libraries

### For Backend Development
- Node.js (version 16 or higher)
- MongoDB (local installation or MongoDB Atlas)
- Firebase project

### For Mobile App Development
- React Native CLI
- Android Studio (for Android development)
- Xcode (for iOS development, macOS only)

## Step-by-Step Installation

### 1. ESP32 Setup

#### Install Arduino IDE
1. Download Arduino IDE from https://www.arduino.cc/en/software
2. Install the IDE following the platform-specific instructions

#### Install ESP32 Board Package
1. Open Arduino IDE
2. Go to File → Preferences
3. Add this URL to "Additional Board Manager URLs":
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
4. Go to Tools → Board → Boards Manager
5. Search for "ESP32" and install "esp32 by Espressif Systems"

#### Install Required Libraries
1. Go to Tools → Manage Libraries
2. Install the following libraries:
   - **SparkFun MAX3010x Pulse and Proximity Sensor Library** by SparkFun Electronics
   - **Blynk** by Volodymyr Shymanskyy
   - **Adafruit ADXL345** by Adafruit
   - **ArduinoJson** by Benoit Blanchon

#### Configure Arduino IDE for ESP32
1. Select Board: "ESP32 Dev Module"
2. Select Port: Choose the correct COM port
3. Set Upload Speed: 115200
4. Set CPU Frequency: 240MHz (WiFi/BT)
5. Set Flash Frequency: 80MHz
6. Set Flash Mode: QIO
7. Set Flash Size: 4MB (32Mb)
8. Set Partition Scheme: Default 4MB with spiffs

### 2. Backend Setup

#### Install Node.js
1. Download Node.js from https://nodejs.org/
2. Install the LTS version (16.x or higher)
3. Verify installation:
   ```bash
   node --version
   npm --version
   ```

#### Install MongoDB
**Option A: Local Installation**
1. Download MongoDB Community Server from https://www.mongodb.com/try/download/community
2. Install following platform-specific instructions
3. Start MongoDB service

**Option B: MongoDB Atlas (Cloud)**
1. Create account at https://www.mongodb.com/atlas
2. Create a new cluster
3. Get connection string

#### Setup Backend Project
1. Navigate to backend directory:
   ```bash
   cd backend
   ```
2. Install dependencies:
   ```bash
   npm install
   ```
3. Create environment file:
   ```bash
   cp env.example .env
   ```
4. Edit `.env` file with your configuration
5. Start the server:
   ```bash
   npm start
   ```

### 3. Firebase Setup

#### Create Firebase Project
1. Go to https://console.firebase.google.com/
2. Click "Create a project"
3. Enter project name: "iot-sensor-monitor"
4. Enable Google Analytics (optional)
5. Create project

#### Enable Cloud Messaging
1. In Firebase Console, go to Project Settings
2. Click "Cloud Messaging" tab
3. Note down the Server Key (for backend)
4. Download configuration files

#### Backend Firebase Configuration
1. Go to Project Settings → Service Accounts
2. Click "Generate new private key"
3. Download the JSON file
4. Rename to `firebase-service-account.json`
5. Place in backend directory

#### Mobile App Firebase Configuration
1. Add Android app to Firebase project
2. Download `google-services.json`
3. Place in `mobile-app/android/app/` directory

### 4. Mobile App Setup

#### Install React Native CLI
```bash
npm install -g react-native-cli
```

#### Install React Native Firebase
```bash
cd mobile-app
npm install @react-native-firebase/app @react-native-firebase/messaging
```

#### Android Setup
1. Install Android Studio
2. Install Android SDK
3. Set up Android emulator or connect physical device
4. Enable Developer Options and USB Debugging

#### iOS Setup (macOS only)
1. Install Xcode from App Store
2. Install Xcode Command Line Tools:
   ```bash
   xcode-select --install
   ```
3. Install CocoaPods:
   ```bash
   sudo gem install cocoapods
   ```

#### Run Mobile App
```bash
# For Android
npm run android

# For iOS (macOS only)
npm run ios
```

## Configuration Files

### ESP32 Configuration
Update these values in `esp32_sensor_monitor.ino`:
```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* serverURL = "http://YOUR_SERVER_IP:3000/api/sensor-data";
```

### Backend Configuration
Update `.env` file:
```
PORT=3000
MONGODB_URI=mongodb://localhost:27017/iot-sensors
```

### Mobile App Configuration
Update `App.js`:
```javascript
const API_BASE_URL = 'http://YOUR_SERVER_IP:3000/api';
```

## Testing Installation

### Test ESP32
1. Upload the code to ESP32
2. Open Serial Monitor (115200 baud)
3. Check for WiFi connection and sensor readings

### Test Backend
1. Start the server: `npm start`
2. Visit: http://localhost:3000/health
3. Should see: `{"status":"OK","timestamp":"..."}`

### Test Mobile App
1. Run the app on device/emulator
2. Check if it connects to backend
3. Verify push notification permissions

## Troubleshooting

### Common Issues

**ESP32 won't upload:**
- Check USB cable (data cable, not just power)
- Try different USB port
- Press and hold BOOT button during upload

**Backend won't start:**
- Check if MongoDB is running
- Verify all dependencies installed
- Check port 3000 is not in use

**Mobile app build fails:**
- Clean build: `cd android && ./gradlew clean`
- Check Android SDK installation
- Verify Firebase configuration files

**Push notifications not working:**
- Check Firebase project configuration
- Verify device registration
- Check app permissions

## Next Steps

After successful installation:
1. Wire up the sensors according to wiring guide
2. Configure WiFi credentials
3. Test sensor readings
4. Set up push notifications
5. Customize alert thresholds

For detailed wiring instructions, see [WIRING_GUIDE.md](WIRING_GUIDE.md)
