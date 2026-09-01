#include <SPI.h>
#include <MFRC522.h>
#include <MsTimer2.h>
#include <SoftwareSerial.h>

// RFID Setup
#define SS_PIN 10
#define RST_PIN 8
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Motion Detection, Buzzer, and GSM Setup
#define INTERRUPT_PIN 2
#define LED_PIN 13
#define BUZZER_PIN 7
#define GSM_TX 3
#define GSM_RX 9

#define DEBOUNCE_DELAY 200
#define MOTION_THRESHOLD 2
#define MOTION_INTERVAL 1000

// Variables
SoftwareSerial SIM900(GSM_TX, GSM_RX);

String recipientNumber = "YOUR_PHONE_NUMBER"; // Replace with your number
String authorizedUID = "YOUR_RFID_UID";        // Replace with your RFID UID

volatile int motionCount = 0;
volatile unsigned long lastInterruptTime = 0;

bool motionDetected = false;
bool rfidAuthorized = false;

// Setup Function
void setup() {

  // Serial Monitor
  Serial.begin(9600);

  // GSM Module
  SIM900.begin(9600);

  // RFID Init
  SPI.begin();
  mfrc522.PCD_Init();

  // Pins
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  // Motion Sensor Interrupt
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), motionInterrupt, FALLING);

  // Motion Timer
  MsTimer2::set(MOTION_INTERVAL, handleMotionThreshold);
  MsTimer2::start();

  Serial.println("System initialized.");
}

// Main Loop
void loop() {

  // Check RFID
  checkRFID();

  // If motion detected and RFID not authorized
  if (motionDetected && !rfidAuthorized) {

    // Turn ON LED
    digitalWrite(LED_PIN, HIGH);

    // Continuous buzzer sound
    tone(BUZZER_PIN, 3000);

    // Send SMS
    sendSMS("Motion detected! Unauthorized access.");

    Serial.println("Unauthorized motion detected.");

    // Keep buzzer ON for 4 seconds
    delay(4000);

    // Stop buzzer
    noTone(BUZZER_PIN);

    // Turn OFF LED
    digitalWrite(LED_PIN, LOW);

    // Reset motion detection
    motionDetected = false;
  }
}

// RFID Function
void checkRFID() {

  // Check if card is present
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Read UID
  String content = "";

  for (byte i = 0; i < mfrc522.uid.size; i++) {

    content += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
    content += String(mfrc522.uid.uidByte[i], HEX);
  }

  // Convert to uppercase
  content.toUpperCase();

  Serial.print("RFID UID: ");
  Serial.println(content);

  // Check authorized UID
  if (content == authorizedUID) {

    Serial.println("RFID Authorized. Motion alerts disabled.");

    rfidAuthorized = true;

    // Short confirmation beep
    tone(BUZZER_PIN, 2000);
    delay(200);
    noTone(BUZZER_PIN);

  } 
  else {

    Serial.println("RFID Unauthorized. Motion alerts enabled.");

    rfidAuthorized = false;

    // Warning beep
    tone(BUZZER_PIN, 1000);
    delay(500);
    noTone(BUZZER_PIN);
  }

  // Halt RFID
  mfrc522.PICC_HaltA();
}

// Motion Interrupt Function
void motionInterrupt() {

  unsigned long currentTime = millis();

  if (currentTime - lastInterruptTime > DEBOUNCE_DELAY) {

    motionCount++;
    lastInterruptTime = currentTime;
  }
}

// Motion Threshold Function
void handleMotionThreshold() {

  if (motionCount > MOTION_THRESHOLD) {

    motionDetected = true;
  }

  motionCount = 0;
}

// GSM SMS Function
void sendSMS(String message) {

  Serial.println("Sending SMS...");

  SIM900.print("AT+CMGF=1\r");

  delay(500);

  SIM900.print("AT+CMGS=\"");
  SIM900.print(recipientNumber);
  SIM900.println("\"");

  delay(500);

  SIM900.println(message);

  delay(50);

  // CTRL + Z
  SIM900.write(26);

  delay(1000);

  Serial.println("SMS sent successfully.");
}
