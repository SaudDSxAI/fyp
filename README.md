Agrobot – Autonomous Weed Removal Robot (Code Module)

This repository contains the Arduino/ESP32 code modules for the Agrobot, an autonomous agricultural robot designed for weed detection, removal, and crop monitoring. These code modules handle motor control, sensor data acquisition, and IoT integration, forming the backbone for the robot’s mobility and real-time monitoring capabilities.

Overview

The provided code modules implement the following core functionalities:

Bluetooth-Controlled Mobility

Motor control via Bluetooth commands.

Adjustable speed control for forward, backward, and turning movements.

Smooth directional transitions, including diagonal movements.

MPU6050 Motion Tracking

Real-time acceleration (ax, ay, az) in m/s².

Approximate velocity and position calculation.

Supports integration with navigation and path-planning algorithms.

Blynk IoT Dashboard Integration

Sends sensor data to a remote dashboard for monitoring.

Includes environmental sensors: DHT11 (temperature and humidity), soil moisture, light intensity, and X/Y positional values.

Provides remote control for an LED actuator via Blynk virtual pins.

Ultrasonic Sensor-Based Obstacle Detection

Measures distance using up to six ultrasonic sensors.

Enables obstacle avoidance and safe navigation in agricultural fields.

Encoder-Based Odometry

Tracks wheel rotation to calculate X, Y coordinates and robot orientation (theta).

Supports precise navigation across uneven terrain.

Code Modules
1. Bluetooth Motor Control

Purpose: Receives commands from a Bluetooth device to control motor direction and speed.

Key Features:

Commands: F (forward), B (backward), L (left), R (right), S (stop), G, I, H, J (diagonal motions).

Speed adjustments via numeric inputs 0–9.

Smooth motor operation using analogWrite() for PWM control.

2. MPU6050 Sensor Module

Purpose: Reads accelerometer and gyroscope data for motion tracking.

Key Features:

Converts raw data to acceleration in m/s².

Calculates velocity and approximate displacement.

Outputs real-time X and Y positions to Serial Monitor.

3. Blynk IoT Integration

Purpose: Transmits environmental sensor readings to a Blynk dashboard.

Sensors Integrated:

DHT11: Temperature and humidity

Soil Moisture Sensor

Light Sensor

X/Y positional values

Features:

Remote LED control via Blynk.

Data sent every 2 seconds for real-time monitoring.

4. Ultrasonic Distance Measurement

Purpose: Measures distances around the robot for obstacle detection.

Features:

Supports up to six sensors.

Calculates distance using the pulse duration from trigger/echo pins.

Outputs distances to Serial Monitor for debugging.

5. Encoder-Based Motion Tracking

Purpose: Tracks wheel rotations for accurate position and orientation calculations.

Features:

Converts encoder ticks into distance traveled.

Calculates X, Y coordinates and heading angle (theta).

Supports straight-line motion, turning, and odometry correction.

Hardware Pin Configuration
Module	Pins
Motor Driver	IN1, IN2, IN3, IN4
Motor Encoders	ENCODER_A, ENCODER_B, ENCODER_C, ENCODER_D
Ultrasonic Sensors	Trig1–6, Echo1–6
MPU6050	I2C (SDA, SCL)
DHT11	Pin 4
Soil Moisture	Analog Pin 34
Light Sensor	Analog Pin 35
LED	Pin 4 (digital output)
Bluetooth	Serial2 (ESP32 default)
