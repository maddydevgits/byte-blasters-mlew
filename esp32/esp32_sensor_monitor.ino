#define BLYNK_TEMPLATE_ID "TMPL3X_Gr1GlO"
#define BLYNK_TEMPLATE_NAME "IOT stethescope for basic health monitoring"
#define BLYNK_AUTH_TOKEN "7F_de_C-8cUo1ln3h_ygY1URkyib-EsF"

#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"
#include "spo2_algorithm.h"
#include <Adafruit_ADXL345_U.h>

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "suri";
char pass[] = "123456789";

// Pin definitions
#define LDR_PIN 2          // Digital pin for LDR sensor
#define SOUND_PIN A0       // Analog pin for sound sensor

// Sensor objects
MAX30105 particleSensor;
Adafruit_ADXL345_Unified accelerometer = Adafruit_ADXL345_Unified(12345);

const byte RATE_SIZE = 4;
byte rates[RATE_SIZE];
byte rateSpot = 0;
long lastBeat = 0;
float beatsPerMinute;
int beatAvg;

// SpO2 and Heart Rate buffers
uint32_t irBuffer[100];
uint32_t redBuffer[100];
int bufferLength = 100;

int32_t spo2;
int8_t validSPO2;
int32_t heartRate;
int8_t validHeartRate;

// Accelerometer variables
sensors_event_t event;
float accelX, accelY, accelZ;
float totalAcceleration;
float accelerationThreshold = 2.0; // g-force threshold (adjust as needed)

// Sensor thresholds
const int HEART_RATE_THRESHOLD_LOW = 50;   // BPM threshold low
const int HEART_RATE_THRESHOLD_HIGH = 120; // BPM threshold high
const int SPO2_THRESHOLD = 92;             // SpO2 threshold
const float TEMP_THRESHOLD_F = 100.4;     // Temperature threshold in Fahrenheit (38°C)
const int SOUND_THRESHOLD = 500;          // Sound threshold
const int LIGHT_THRESHOLD = 1;            // Light detection threshold (digital)
const float ACCEL_THRESHOLD = 2.0;        // Acceleration threshold in g

// Timing variables
unsigned long lastSensorRead = 0;
const unsigned long SENSOR_READ_INTERVAL = 5000; // Read sensors every 5 seconds

// Alert flags
bool heartRateAlert = false;
bool spo2Alert = false;
bool temperatureAlert = false;
bool soundAlert = false;
bool lightAlert = false;
bool accelerationAlert = false;

void setup() {
  Serial.begin(115200);

  // Initialize pins
  pinMode(LDR_PIN, INPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Serial.println("Initializing MAX30105...");
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("MAX30105 not found. Check wiring.");
    while (1);
  }

  particleSensor.setup();
  particleSensor.setPulseAmplitudeRed(0x1F);
  particleSensor.setPulseAmplitudeIR(0x1F);

  // Initialize ADXL345 accelerometer
  Serial.println("Initializing ADXL345...");
  if (!accelerometer.begin()) {
    Serial.println("ADXL345 not found. Check wiring.");
    while (1);
  }
  
  // Configure ADXL345
  accelerometer.setRange(ADXL345_RANGE_16_G);
  accelerometer.setDataRate(ADXL345_DATARATE_100_HZ);

  Serial.println("IoT Health Monitor with Blynk Started");
  Serial.println("Place your finger on the sensor.");
}

void loop() {
  Blynk.run();

  if (millis() - lastSensorRead >= SENSOR_READ_INTERVAL) {
    readAllSensors();
    lastSensorRead = millis();
  }

  delay(10);
}

void readAllSensors() {
  // Read LDR sensor (light detection)
  int lightValue = digitalRead(LDR_PIN);
  
  // Read sound sensor
  int soundValue = analogRead(SOUND_PIN);

  // Read accelerometer data
  accelerometer.getEvent(&event);
  accelX = event.acceleration.x;
  accelY = event.acceleration.y;
  accelZ = event.acceleration.z;
  
  // Calculate total acceleration magnitude
  totalAcceleration = sqrt(accelX * accelX + accelY * accelY + accelZ * accelZ);

  // Read MAX30105 sensor data
  for (int i = 0; i < bufferLength; i++) {
    while (!particleSensor.available()) {
      particleSensor.check();
    }
    redBuffer[i] = particleSensor.getRed();
    irBuffer[i] = particleSensor.getIR();
    particleSensor.nextSample();
  }

  // Calculate SpO2 and Heart Rate
  maxim_heart_rate_and_oxygen_saturation(
    irBuffer, bufferLength, redBuffer,
    &spo2, &validSPO2,
    &heartRate, &validHeartRate
  );

  // Read internal temperature in °C and convert to °F
  float tempC = particleSensor.readTemperature();
  float tempF = (tempC * 1.8) + 32.0;

  // Print to Serial
  Serial.print("Heart Rate: ");
  Serial.print(validHeartRate ? String(heartRate) + " bpm" : "Invalid");

  Serial.print(", SpO2: ");
  Serial.print(validSPO2 ? String(spo2) + " %" : "Invalid");

  Serial.print(", Temp: ");
  Serial.print(tempF);
  Serial.print(" °F");

  Serial.print(", Sound: ");
  Serial.print(soundValue);

  Serial.print(", Light: ");
  Serial.print(lightValue ? "Detected" : "None");
  
  Serial.print(", Accel: ");
  Serial.print(totalAcceleration);
  Serial.print(" g");
  Serial.println();

  // Send data to Blynk
  if (validHeartRate) {
    Blynk.virtualWrite(V0, heartRate);
    checkHeartRateAlert(heartRate);
  }

  if (validSPO2) {
    Blynk.virtualWrite(V1, spo2);
    checkSpO2Alert(spo2);
  }

  // Send Fahrenheit to V2
  Blynk.virtualWrite(V2, tempF);
  checkTemperatureAlert(tempF);

  // Send sound and light data
  Blynk.virtualWrite(V3, soundValue);
  Blynk.virtualWrite(V4, lightValue);
  
  // Send accelerometer data
  Blynk.virtualWrite(V5, totalAcceleration);
  Blynk.virtualWrite(V6, accelX);
  Blynk.virtualWrite(V7, accelY);
  Blynk.virtualWrite(V8, accelZ);
  
  checkSoundAlert(soundValue);
  checkLightAlert(lightValue);
  checkAccelerationAlert(totalAcceleration);
}

void checkHeartRateAlert(int heartRate) {
  if ((heartRate < HEART_RATE_THRESHOLD_LOW || heartRate > HEART_RATE_THRESHOLD_HIGH) && !heartRateAlert) {
    String alertMsg = "Heart Rate Abnormal: " + String(heartRate) + " bpm";
    Blynk.logEvent("heart_rate_alert", alertMsg);
    Blynk.virtualWrite(V10, 1); // Alert LED
    heartRateAlert = true;
    Serial.println("ALERT: " + alertMsg);
  } else if (heartRate >= HEART_RATE_THRESHOLD_LOW && heartRate <= HEART_RATE_THRESHOLD_HIGH && heartRateAlert) {
    heartRateAlert = false;
    Blynk.virtualWrite(V10, 0); // Clear Alert LED
  }
}

void checkSpO2Alert(int spo2) {
  if (spo2 < SPO2_THRESHOLD && !spo2Alert) {
    String alertMsg = "SpO₂ Low: " + String(spo2) + "%";
    Blynk.logEvent("spo2_alert", alertMsg);
    Blynk.virtualWrite(V11, 1); // Alert LED
    spo2Alert = true;
    Serial.println("ALERT: " + alertMsg);
  } else if (spo2 >= SPO2_THRESHOLD && spo2Alert) {
    spo2Alert = false;
    Blynk.virtualWrite(V11, 0); // Clear Alert LED
  }
}

void checkTemperatureAlert(float tempF) {
  if (tempF > TEMP_THRESHOLD_F && !temperatureAlert) {
    String alertMsg = "Body Temp High: " + String(tempF) + " °F";
    Blynk.logEvent("temp_alert", alertMsg);
    Blynk.virtualWrite(V12, 1); // Alert LED
    temperatureAlert = true;
    Serial.println("ALERT: " + alertMsg);
  } else if (tempF <= TEMP_THRESHOLD_F && temperatureAlert) {
    temperatureAlert = false;
    Blynk.virtualWrite(V12, 0); // Clear Alert LED
  }
}

void checkSoundAlert(int soundValue) {
  if (soundValue > SOUND_THRESHOLD && !soundAlert) {
    String alertMsg = "High Sound Level: " + String(soundValue);
    Blynk.logEvent("sound_alert", alertMsg);
    Blynk.virtualWrite(V13, 1); // Alert LED
    soundAlert = true;
    Serial.println("ALERT: " + alertMsg);
  } else if (soundValue <= SOUND_THRESHOLD && soundAlert) {
    soundAlert = false;
    Blynk.virtualWrite(V13, 0); // Clear Alert LED
  }
}

void checkLightAlert(int lightValue) {
  if (lightValue == HIGH && !lightAlert) {
    String alertMsg = "Sunlight Detected!";
    Blynk.logEvent("light_alert", alertMsg);
    Blynk.virtualWrite(V14, 1); // Alert LED
    lightAlert = true;
    Serial.println("ALERT: " + alertMsg);
  } else if (lightValue == LOW && lightAlert) {
    lightAlert = false;
    Blynk.virtualWrite(V14, 0); // Clear Alert LED
  }
}

void checkAccelerationAlert(float acceleration) {
  if (acceleration > ACCEL_THRESHOLD && !accelerationAlert) {
    String alertMsg = "High Acceleration Detected: " + String(acceleration, 2) + " g";
    Blynk.logEvent("acceleration_alert", alertMsg);
    Blynk.virtualWrite(V15, 1); // Alert LED
    accelerationAlert = true;
    Serial.println("ALERT: " + alertMsg);
  } else if (acceleration <= ACCEL_THRESHOLD && accelerationAlert) {
    accelerationAlert = false;
    Blynk.virtualWrite(V15, 0); // Clear Alert LED
  }
}

// Blynk virtual pin handlers for manual controls
BLYNK_WRITE(V20) {
  int threshold = param.asInt();
  Serial.println("Heart rate threshold updated to: " + String(threshold));
}

BLYNK_WRITE(V21) {
  int threshold = param.asInt();
  Serial.println("SpO2 threshold updated to: " + String(threshold));
}

BLYNK_WRITE(V22) {
  int threshold = param.asInt();
  Serial.println("Temperature threshold updated to: " + String(threshold));
}

BLYNK_WRITE(V24) {
  float threshold = param.asFloat();
  Serial.println("Acceleration threshold updated to: " + String(threshold, 2) + " g");
}

// Blynk connection status
BLYNK_CONNECTED() {
  Serial.println("Connected to Blynk IoT Cloud");
  Blynk.syncVirtual(V20, V21, V22, V23, V24); // Sync threshold values
}

BLYNK_DISCONNECTED() {
  Serial.println("Disconnected from Blynk IoT Cloud");
}

// Emergency stop function
BLYNK_WRITE(V30) {
  if (param.asInt() == 1) {
    Serial.println("Emergency stop activated!");
    // Reset all alert flags
    heartRateAlert = false;
    spo2Alert = false;
    temperatureAlert = false;
    soundAlert = false;
    lightAlert = false;
    accelerationAlert = false;
    
    // Clear all alert LEDs
    Blynk.virtualWrite(V10, 0);
    Blynk.virtualWrite(V11, 0);
    Blynk.virtualWrite(V12, 0);
    Blynk.virtualWrite(V13, 0);
    Blynk.virtualWrite(V14, 0);
    Blynk.virtualWrite(V15, 0);
  }
}
