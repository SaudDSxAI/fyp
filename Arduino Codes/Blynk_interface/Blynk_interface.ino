#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// Blynk Credentials
#define BLYNK_TEMPLATE_ID "TMPL6JOZyBnPl"
#define BLYNK_TEMPLATE_NAME "FYP Dashboard"
char auth[] = "RQ92h3pT0gXCT1s5bJUSr756ZLy2puxB"; // Blynk Auth Token
char ssid[] = "192.168.216.79";  // WiFi SSID
char pass[] = "192168100113";     // WiFi Password

// Sensor & Pin Definitions
#define DHTPIN 4      // DHT11 Sensor Data Pin
#define DHTTYPE DHT11 // DHT Type
DHT dht(DHTPIN, DHTTYPE);

#define SOIL_MOISTURE_PIN 34   // Soil Moisture Sensor (Analog)
#define LIGHT_SENSOR_PIN 35    // Light Intensity Sensor (Analog)
#define X_SENSOR_PIN 13        // X Values (Analog)
#define Y_SENSOR_PIN 2         // Y Values (Analog)
#define LED_PIN 4              // On/Off Control (Digital Output)

// Virtual Pins for Blynk
#define TEMP_VPIN V1    // Temperature Data
#define HUM_VPIN V2     // Humidity Data
#define SOIL_VPIN V3    // Soil Moisture Data
#define LIGHT_VPIN V4   // Light Intensity Data
#define X_VPIN V5       // X Sensor Data
#define Y_VPIN V6       // Y Sensor Data
#define LED_VPIN V7     // LED Control

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Ensure LED starts OFF
  dht.begin();

  Blynk.begin(auth, ssid, pass);
}

// Function to Send Sensor Data to Blynk
void sendSensorData() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  int soilMoisture = analogRead(SOIL_MOISTURE_PIN);
  int lightIntensity = analogRead(LIGHT_SENSOR_PIN);
  int xValue = analogRead(X_SENSOR_PIN);
  int yValue = analogRead(Y_SENSOR_PIN);

  if (isnan(temp) || isnan(hum)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Send Data to Blynk App
  Blynk.virtualWrite(TEMP_VPIN, temp);
  Blynk.virtualWrite(HUM_VPIN, hum);
  Blynk.virtualWrite(SOIL_VPIN, soilMoisture);
  Blynk.virtualWrite(LIGHT_VPIN, lightIntensity);
  Blynk.virtualWrite(X_VPIN, xValue);
  Blynk.virtualWrite(Y_VPIN, yValue);

  // Print values to Serial Monitor
  Serial.print("Temp: "); Serial.print(temp); Serial.print("°C, ");
  Serial.print("Hum: "); Serial.print(hum); Serial.print("%, ");
  Serial.print("Soil: "); Serial.print(soilMoisture); Serial.print(", ");
  Serial.print("Light: "); Serial.print(lightIntensity); Serial.print(", ");
  Serial.print("X: "); Serial.print(xValue); Serial.print(", ");
  Serial.print("Y: "); Serial.println(yValue);
}

// Blynk Function to Control LED via Virtual Pin 7
BLYNK_WRITE(LED_VPIN) {
  int ledState = param.asInt();
  digitalWrite(LED_PIN, ledState);
}

void loop() {
  Blynk.run();
  sendSensorData();
  delay(2000); // Send data every 2 seconds
}
