// #include "MPU6050.h"
#include <Wire.h>
// MPU6050 mpu;
// int16_t ax, ay, az;
// int16_t gx, gy, gz;

// unsigned long lastTime = 0;
// float deltaTime;
// float angleZ = 0.0;
// float gz_deg_per_s;
// int16_t gz_offset = 0;
// int final_angle=0;




// Ultrasonic sensors pins
int trig1 = 22, echo1 = 23, trig2 = 24, echo2 = 25, trig3 = 26, echo3 = 27;
int trig4 = 28, echo4 = 29, trig5 = 30, echo5 = 31, trig6 = 32, echo6 = 33;

float duration1,duration2,duration3,duration4,duration5,duration6;
float distance1, distance2, distance3,distance4, distance5, distance6;
// Threashold distances for all three sensors 
const float set_distance1 = 35, set_distance2 = 35, set_distance3 = 35;




#define IN1 9   // PWM Motor Control
#define IN2 10  // PWM Motor Control
#define IN3 11  // PWM Motor Control
#define IN4 12  // PWM Motor Control

#define ENCODER_A 2  // Encoder A Pin
#define ENCODER_B 3  // Encoder B Pin
#define ENCODER_C 20  // Encoder A Pin
#define ENCODER_D 21 // Encoder B Pin

int x_coordinate =3, y_coordinate =3;
int speed1=120,speed2=120;

// Constants (converted to feet)
const float ticksPerRevolution = 448.0; // Encoder ticks per full revolution
const float wheelRadius = 0.03;  // Wheel radius in meters (3 inches = 0.0762 meters)
const float wheelbase = 0.17;    // Distance between left and right wheels in meters (17 inches = 0.4320 meters)

// Variables to store encoder ticks
volatile long encoderCount1 = 0; 
volatile long encoderCount2 = 0;

// Position and Orientation Variables
float x = 0.0; // X position in feet
float y = 0.0; // Y position in feet
float theta = 0.0; // Orientation in radians
float D;
float deltaTheta;



void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENCODER_A, INPUT_PULLUP);
  pinMode(ENCODER_B, INPUT_PULLUP);
  pinMode(ENCODER_C, INPUT_PULLUP);
  pinMode(ENCODER_D, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENCODER_A), encoderISR1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_C), encoderISR2, CHANGE);

  // Set ultrasonic sensor pins
  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);
  pinMode(trig3, OUTPUT);
  pinMode(trig4, OUTPUT);
  pinMode(trig5, OUTPUT);
  pinMode(trig6, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);
  pinMode(echo3, INPUT);
  pinMode(echo4, INPUT);
  pinMode(echo5, INPUT);
  pinMode(echo6, INPUT);
  Serial.begin(9600);
  Serial.begin(9600);

  // mpu.initialize();

  // // Calibrate MPU
  // calibrateMPU();
}

void loop() {


if(x < x_coordinate)
  moveForward();


// // for the straight movement of the robot.
// // if (encoderCount1 > encoderCount2) {
// //     if (speed2 < 120) {
// //         speed2++;
// //     } 
// //     else{
// //         speed1--;
// //     }
// // } 
// // else if (encoderCount2 > encoderCount1) {
// //     if (speed1 < 120) {
// //         speed1++;
// //     } 
// //     else{
// //         speed2--;
// //     }
// // }
// }


// else if(abs(theta) * 57.296 < 90){
//   moveRight();
// }

else
  stopMotors();

// else if(y < y_coordinate){
//   moveForward();
//   // to adjust the slip factor of the wheels.
//   if(encoderCount1/encoderCount2 > 500){
//     encoderCount1 = encoderCount2;
//   }
//   else if(encoderCount2/encoderCount1 > 500){
//     encoderCount2 = encoderCount1;
//   }
// }

// else if(final_angle < 180){
//   moveRight();
// }

// else if(x>0){
//   moveForward();
//   // to adjust the slip factor of the wheels.
//   if(encoderCount1/encoderCount2 > 500){
//     encoderCount1 = encoderCount2;
//   }
//   else if(encoderCount2/encoderCount1 > 500){
//     encoderCount2 = encoderCount1;
//   }
// }
  //angle_measure_mpu();
  encoder_ticks();
  delay(100); // Small delay for stability
}


// void angle_measure_mpu(){
//   unsigned long currentTime = micros();
//   deltaTime = (currentTime - lastTime) / 1000000.0; // Convert to seconds
//   lastTime = currentTime;

//   mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
//   gz -= gz_offset; // Apply offset correction
//   gz_deg_per_s = gz / 131.0;

//   angleZ += gz_deg_per_s * deltaTime;
//   final_angle = abs(int(angleZ));
//   // Serial.print("Angle Z = ");
//   // Serial.println(final_angle);
// }

// void calibrateMPU() {
//   long gz_sum = 0;
//   for (int i = 0; i < 1000; i++) {
//     mpu.getRotation(&gx, &gy, &gz);
//     gz_sum += gz;
//     delay(2);
//   }
//   gz_offset = gz_sum / 1000;
// }

void encoder_ticks(){
   // Calculate distance traveled by each wheel in **feet**
  float dL = (encoderCount1 / ticksPerRevolution) * (2 * PI * wheelRadius); // Left wheel
  float dR = (encoderCount2 / ticksPerRevolution) * (2 * PI * wheelRadius); // Right wheel

  // Calculate the average distance traveled by the robot
  D = (dL + dR) / 2.0;

  // Calculate the change in orientation (theta) based on wheel distance difference
  deltaTheta = (dR - dL) / wheelbase; // Change in radians

  // Update orientation (remains in radians for correct calculations)
  theta = deltaTheta;

  // Update X and Y position in **feet**
  x = D * cos(theta);
  y = D * sin(theta);

  //Print data
  Serial.print("Right: ");
  Serial.print(dR);
  Serial.print("Left: ");
  Serial.print(dL);
  Serial.print("X: ");
  Serial.print(x);
  Serial.print("Y: ");
  Serial.print(y);
  Serial.print("Theta: ");
  Serial.print(theta * 57.296); // Convert to degrees for readability
  Serial.println(" deg");
}

void encoderISR1() {
  if (digitalRead(ENCODER_A) == digitalRead(ENCODER_B)) {
    encoderCount1++;  // Clockwise
  } else {
    encoderCount1--;  // Counterclockwise
  }
}

void encoderISR2() {
  if (digitalRead(ENCODER_C) == digitalRead(ENCODER_D)) {
    encoderCount2++;  // Clockwise
  } else {
    encoderCount2--;  // Counterclockwise
  }
}

void dist_measure() {

    // Send a pulse to the trigger pin
    digitalWrite(trig1, LOW);
    digitalWrite(trig2, LOW);
    digitalWrite(trig3, LOW);
    digitalWrite(trig4, LOW);
    digitalWrite(trig5, LOW);
    digitalWrite(trig6, LOW);
    delayMicroseconds(2);
    digitalWrite(trig1, HIGH);
    digitalWrite(trig2, HIGH);
    digitalWrite(trig3, HIGH);
    digitalWrite(trig4, HIGH);
    digitalWrite(trig5, HIGH);
    digitalWrite(trig6, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig1, LOW);
    digitalWrite(trig2, LOW);
    digitalWrite(trig3, LOW);
    digitalWrite(trig4, LOW);
    digitalWrite(trig5, LOW);
    digitalWrite(trig6, LOW);

    // Measure the duration of the pulse on the echo pin
    duration1 = pulseIn(echo1, HIGH,50000);
    duration2 = pulseIn(echo2, HIGH,50000);
    duration3 = pulseIn(echo3, HIGH,50000);
    duration4 = pulseIn(echo4, HIGH,50000);
    duration5 = pulseIn(echo5, HIGH,50000);
    duration6 = pulseIn(echo6, HIGH,50000);
    // Calculate the distance based on the duration of the pulse
    distance1 = (duration1 * 0.034) / 2;
    distance2 = (duration2 * 0.034) / 2;
    distance3 = (duration3 * 0.034) / 2;
    distance4 = (duration4 * 0.034) / 2;
    distance5 = (duration5 * 0.034) / 2;
    distance6 = (duration6 * 0.034) / 2;
}

// 🛠 Forward Movement
void moveForward() {
    analogWrite(IN1, speed2);
    analogWrite(IN2, 0);
    analogWrite(IN3, speed1);
    analogWrite(IN4, 0);
}

// 🔄 Reverse Movement
void moveReverse() {
    analogWrite(IN1, 0);
    analogWrite(IN2, speed2);
    analogWrite(IN3, 0);
    analogWrite(IN4, speed1);
}

// ⬅️ Turn Left (Slow down left motor or stop it)
void moveRight() {
    analogWrite(IN1, 0);
    analogWrite(IN2, speed2);
    analogWrite(IN3, speed1);
    analogWrite(IN4, 0);
}

//Turn Right (Slow down right motor or stop it)
void moveLeft() {
    analogWrite(IN1, speed2);
    analogWrite(IN2, 0);
    analogWrite(IN3, 0);
    analogWrite(IN4, speed1);
}

//Stop Motors
void stopMotors() {
    analogWrite(IN1, 0);
    analogWrite(IN2, 0);
    analogWrite(IN3, 0);
    analogWrite(IN4, 0);
}

