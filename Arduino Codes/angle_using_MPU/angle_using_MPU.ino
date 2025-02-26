/*
   Arduino and MPU6050 Accelerometer and Gyroscope Sensor Tutorial
   Updated to calculate ax, ay, and az in m/s²
*/
#include <Wire.h>
const int MPU = 0x68; // MPU6050 I2C address
float AccX, AccY, AccZ;
float ax, ay, az; // Acceleration in m/s²
float GyroX, GyroY, GyroZ;
float accAngleX, accAngleY, gyroAngleX, gyroAngleY, gyroAngleZ;
float roll, pitch, yaw;
float elapsedTime, currentTime, previousTime;

void setup() {
  Serial.begin(19200);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);
  delay(20);
}

void loop() {
  // Read accelerometer data
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true);
  
  AccX = (Wire.read() << 8 | Wire.read()) / 16384.0;
  AccY = (Wire.read() << 8 | Wire.read()) / 16384.0;
  AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0;
  
  // Convert to m/s²
  ax = AccX * 9.81;
  ay = AccY * 9.81;
  az = AccZ * 9.81;
  
// ax -= ax_offset;
// ay -= ay_offset;

float vx = 0, vy = 0;  // Initial velocity
float dt = 0.01;  // Time step (assume 10ms loop)

vx += ax * dt;
vy += ay * dt;


float x = 0, y = 0;  // Initial position

x += vx * dt;
y += vy * dt;

// Print position values
    Serial.print("X: ");
    Serial.print(x);
    Serial.print(" m, Y: ");
    Serial.println(y);
  // // Print values
  // Serial.print("ax: "); Serial.print(ax);
  // Serial.print(" m/s², ay: "); Serial.print(ay);
  // Serial.print(" m/s², az: "); Serial.println(az);
  
  delay(500); // Slow down the loop for readability
}
