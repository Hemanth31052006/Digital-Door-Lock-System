# Digital Door Lock System with RFID, Password security and Facial Recognition

## Overview

This project integrates Arduino with RFID and keypad-based authentication to create a secure and versatile door lock system. It leverages real-time feedback via an LCD screen and controls a solenoid lock upon successful authentication. The system ensures enhanced security for homes, offices, and sensitive areas by providing a cost-effective and customizable access control solution.

# Secure RFID & Password-Based Door Lock System

## Overview
This project leverages the power of Arduino to create a secure and versatile door lock system that combines RFID and password authentication for enhanced security. The system integrates an RFID reader, a keypad, and an LCD screen to provide a comprehensive access control solution. Users can unlock the door by either scanning an authorized RFID tag or by entering a pre-defined password on the keypad. The LCD provides real-time feedback, displaying prompts and status updates to the user. Upon successful authentication, the Arduino controls a solenoid lock to grant access.

This dual-layer security approach ensures that unauthorized access is minimized, making it ideal for securing homes, offices, and other sensitive areas. By utilizing Arduino, the system is both cost-effective and highly customizable, allowing for easy updates and modifications to the authentication methods and user interface.

## Features
- Dual authentication (RFID & Password)
- Real-time feedback via LCD screen
- Secure solenoid lock control
- Easy-to-use 4x4 keypad for password entry
- ESP32 integration for additional functionality
- Customizable and expandable security features

## Components Required
- **Arduino Uno**
- **RFID Reader (MFRC522)**
- **RFID Tags**
- **4x4 Keypad**
- **16x2 LCD Screen**
- **I2C LCD Module** (optional for easier connections)
- **Solenoid Lock**
- **Relay Module**
- **Resistors (1kΩ, 220Ω)**
- **Breadboard**
- **Jumper Wires**
- **Power Supply** (for Arduino and Solenoid Lock)
- **ESP32**
- **ESP32 Camera Module**

## Circuit Assembly
1. Connect the RFID reader, keypad, LCD, and solenoid lock to the Arduino.
2. Use an I2C module for the LCD to simplify wiring.
3. Interface the relay module with the solenoid lock for controlled access.
4. Power the system using an appropriate power supply.

## Software & Programming
1. **Initialize Components**: Set up RFID reader, keypad, LCD, and solenoid lock.
2. **Read Inputs**: Capture RFID scans and keypad entries.
3. **Authentication Logic**:
   - Validate RFID tag or password.
   - Trigger solenoid lock upon successful authentication.
4. **Feedback System**: Display messages on LCD screen.
5. **ESP32 Integration**: Extend functionality for remote monitoring or logging.

## Installation & Testing
1. Verify RFID and keypad inputs.
2. Ensure proper solenoid lock activation.
3. Troubleshoot any wiring or software issues.
4. Securely mount the system and perform real-world tests.

## Future Enhancements
- **Mobile App Integration** for remote access control.
- **Biometric Authentication** for enhanced security.
- **Cloud Storage** for access logs and monitoring.
- **Wi-Fi/Bluetooth Connectivity** for smart home integration.

## Documentation
- **Circuit Diagram** (to be included in the repo)
- **Source Code** (to be uploaded in the repository)
- **User Manual** for setup and operation

## Contributing
Contributions are welcome! If you have any suggestions, feel free to submit a pull request or open an issue.

---
## Author
Developed by Hemanth.S

## References

### Multifactor Door Locking Systems: A Review
Emphasizes the transition from traditional locks to password-based and RFID systems for enhanced security.
Highlights the importance of regularly changing passwords to maintain security.
Discusses the integration of various authentication methods to create more robust access control systems.
Link : https://www.sciencedirect.com/science/article/pii/S2352146518303604

### An RFID-Based Access Control System Using Electromagnetic Door Lock and Password
Describes the use of RFID technology in combination with electromagnetic locks for secure access.
Explores the benefits of using RFID over traditional key-based systems, including convenience and security.
Suggests the integration of additional security measures like passwords to further enhance system reliability.
Link : https://www.researchgate.net/publication/330872586

### Real-Time Object Detection and Identification Using ESP32 CAM and Python OpenCV
This research paper delves into the integration of the ESP32 camera module with Python and OpenCV to perform real-time object detection and identification. The paper outlines the setup process, including uploading the program to the ESP32 module, configuring image resolution, and utilizing YOLO V3 for object detection. The system's performance is tested on various devices, including Raspberry Pi, Core i3, and Core i7 laptops, demonstrating varying levels of efficiency and speed. This implementation allows for customized object detection applications, such as a bird and gate detection system for security purposes.
Link : https://www.toolify.ai/







