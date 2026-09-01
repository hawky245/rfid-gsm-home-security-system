# Wiring Instructions

## RFID MFRC522
SDA -> D10
SCK -> D13
MOSI -> D11
MISO -> D12
RST -> D8
3.3V -> 3.3V
GND -> GND

## SIM900 GSM Module
TX -> D9
RX -> D3
GND -> GND

## Motion Sensor
OUT -> D2
VCC -> 5V
GND -> GND

## Buzzer
Positive -> D7
Negative -> GND

## LED Indicator
Connected to D13 (or Arduino built-in LED)

NOTE:The project was implemented using Arduino Uno, MFRC522 RFID reader, SIM900 GSM module, microwave motion sensor, buzzer, and LED indicator.
