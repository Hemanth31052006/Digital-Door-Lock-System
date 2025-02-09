#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 53
#define RST_PIN 11
#define RELAY_PIN 10 // Relay pin

// LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust address if needed

// Keypad setup
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5}; // Connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8, 9}; // Connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String correctPassword = "1234"; // Set your desired password here
String enteredPassword = ""; // Stores the entered password

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

bool lockState = true; // Initial lock state: locked
bool lastCardPresent = false; // Tracks if the card was previously present

void setup() {
  Serial.begin(9600);   // Initiate serial communication
  SPI.begin();          // Initiate SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Initial state: locked

  lcd.init();            // Initialize the LCD
  lcd.backlight();       // Turn on backlight
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
  lcd.setCursor(0, 1);
  lcd.print("Locked        "); // Initial state on LCD
}

void loop() {
  // Keypad handling
  char key = keypad.getKey(); // Get the pressed key

  if (key) { // Check if a key is pressed
    if (lockState) {
      // Handle password entry
      if (key == '#') { // Submit password
        lcd.setCursor(0, 0);
        lcd.print("                "); // Clear first line
        lcd.setCursor(0, 1);
        lcd.print("                "); // Clear second line
        if (enteredPassword == correctPassword) {
          lockState = false; // Unlock
          digitalWrite(RELAY_PIN, HIGH); // Unlock relay
          lcd.setCursor(0, 0);
          lcd.print("Unlocked       "); // Display unlocked
        } else {
          lcd.setCursor(0, 0);
          lcd.print("Wrong Password "); // Display error message
          delay(1000); // Show error for a moment
        }
        enteredPassword = ""; // Clear entered password after submission
      } else if (key == '*') { // Clear input
        enteredPassword = ""; // Clear input
        lcd.setCursor(0, 0);
        lcd.print("Enter Password:"); // Reset prompt
        lcd.setCursor(0, 1);
        lcd.print("                "); // Clear second line
      } else {
        enteredPassword += key; // Append key to entered password
        lcd.setCursor(0, 1);
        lcd.print("                "); // Clear previous content
        lcd.setCursor(0, 1);
        lcd.print(enteredPassword); // Display current input
      }
    } else {
      // Handle unlocked state options
      if (key == '#') { // Lock the system
        lockState = true; // Lock
        digitalWrite(RELAY_PIN, LOW); // Lock relay
        lcd.setCursor(0, 0);
        lcd.print("Enter Password:"); // Reset prompt
        lcd.setCursor(0, 1);
        lcd.print("Locked        "); // Display locked
      }
    }
  }

  // RFID handling
  bool cardPresent = mfrc522.PICC_IsNewCardPresent();
  bool readCard = mfrc522.PICC_ReadCardSerial();

  if (cardPresent && readCard) {
    // Show UID on serial monitor
    String uidString = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      uidString += String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      uidString += String(mfrc522.uid.uidByte[i], HEX);
    }
    uidString.toUpperCase(); // Convert to uppercase for readability

    Serial.print("UID tag: ");
    Serial.println(uidString); // Print UID to Serial Monitor

    if (!lastCardPresent) {
      // Card was not present previously, toggle relay state
      lockState = !lockState; // Toggle state
      digitalWrite(RELAY_PIN, lockState ? LOW : HIGH); // Update relay

      // Update LCD with relay state
      lcd.setCursor(0, 0);
      lcd.print("RFID Detected ");
      lcd.setCursor(0, 1);
      lcd.print(lockState ? "Locked        " : "Unlocked      ");
    }

    lastCardPresent = true; // Update last card present status
  } else {
    // No new card present
    lastCardPresent = false; // Update last card present status
  }

  // Halt PICC
  mfrc522.PICC_HaltA();

  // Stop encryption on PCD
  mfrc522.PCD_StopCrypto1();
}
