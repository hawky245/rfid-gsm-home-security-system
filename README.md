# Smart Home E-Security System

## Overview

The Smart Home E-Security System is an IoT-based residential security solution built using Arduino Uno. The project combines RFID authentication, microwave motion detection, GSM communication, and automated gate control to provide a multi-layered home security framework.

The system consists of two independent security zones:

1. Indoor Motion Detection Alert System
2. Outdoor Garage Door Security System

## Features

- RFID-based access control
- Microwave motion detection
- GSM SMS intrusion alerts
- Servo-controlled garage gate automation
- Real-time intrusion monitoring
- Interrupt-driven motion detection
- Audible buzzer alerts
- Visual LED status indication

## Hardware Components

- Arduino Uno R3
- MFRC522 RFID Reader
- RFID Tags
- SIM900A GSM Module
- Microwave Motion Sensor
- SG90 Servo Motor
- Piezo Buzzer
- LED Indicator

## Working Principle

### Indoor Security

The microwave motion sensor continuously monitors indoor spaces. When unauthorized motion is detected:

- Buzzer activates
- LED turns ON
- SMS alert is sent using SIM900A GSM module

### Outdoor Security

The RFID reader scans user cards.

- Authorized UID → Garage door opens
- Unauthorized UID → Access denied and warning generated

## Technologies Used

- Arduino IDE
- Embedded C++
- SPI Communication
- SoftwareSerial
- RFID Authentication
- GSM Communication

## Future Improvements

- MQTT-based IoT dashboard
- Mobile application integration
- ESP32-CAM surveillance
- Multi-factor authentication
- Battery backup system

## Author

Abhay Surya R
