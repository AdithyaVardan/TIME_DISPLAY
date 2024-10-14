

---

# **ESP32 LED Matrix Clock Project**

This project displays the current time on a 32x8 LED matrix display connected to an ESP32 DEV MODULE using the I2C protocol. The ESP32 microcontroller retrieves the time and date from the internet via Wi-Fi and displays it using the `MD_MAX72XX` and `MD_PAROLA` libraries to control the LED matrix.

## **Table of Contents**
- [Overview](#overview)
- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Wiring Diagram](#wiring-diagram)
- [Installation](#installation)
- [Usage](#usage)
- [Libraries Used](#libraries-used)
- [License](#license)

---

## **Overview**

The project uses an **ESP32** microcontroller, which features two Xtensa 32-bit LX6 processors, along with built-in Wi-Fi capabilities. By connecting to a Wi-Fi network, the ESP32 fetches the current time and date from the internet using the `WiFi.h` library. This data is then displayed on a 32x8 LED matrix display.

The **MD_MAX72XX** and **MD_PAROLA** libraries are used to interface with and control the LED matrix display, enabling scrolling text and animations for displaying the time.

---

## **Features**

- **Wi-Fi Connectivity**: Connects to a Wi-Fi network to fetch real-time date and time from the internet.
- **LED Matrix Display**: Displays the time on a 32x8 LED matrix using scrolling animations.
- **I2C Protocol**: The communication between the ESP32 and the LED matrix uses the I2C protocol.
- **Customizable Display**: Easy to customize scrolling effects and update frequency.

---

## **Hardware Requirements**

- **ESP32 DEV MODULE**: The core microcontroller used for Wi-Fi connectivity and processing.
- **32x8 LED Matrix Display**: The display unit where the time will be shown.
- **Connecting Wires**: Jumper wires for connecting the ESP32 to the LED matrix.
- **Power Supply**: A power source for the ESP32 (typically USB or a battery pack).

### **Optional**
- Breadboard for easier connections.

---

## **Software Requirements**

- **Arduino IDE**: The development environment used to upload code to the ESP32.
- **ESP32 Board Support Package**: Make sure you install the ESP32 board support via the Arduino Board Manager.
  
---

## **Wiring Diagram**

| ESP32 Pin | LED Matrix Pin |
|-----------|----------------|
| 3.3V      | VCC            |
| GND       | GND            |
| D21 (SCL) | CLK            |
| D22 (SDA) | DIN            |
| D23 (CS)  | CS             |

Connect the ESP32 to the 32x8 LED matrix according to this pinout to enable I2C communication.

---

## **Installation**

### **Step 1: Set Up Arduino IDE**
- Download and install the Arduino IDE from [here](https://www.arduino.cc/en/software).
- In the Arduino IDE, install the **ESP32 board package** by navigating to:
  - `File` > `Preferences` > Add this URL to the "Additional Board Manager URLs" field:
    ```
    https://dl.espressif.com/dl/package_esp32_index.json
    ```
  - Go to `Tools` > `Board` > `Boards Manager`, search for "ESP32", and install the ESP32 board package.

### **Step 2: Install Required Libraries**
- In the Arduino IDE, install the following libraries:
  - **WiFi.h** (comes with the ESP32 package)
  - **MD_MAX72XX**: For controlling the LED matrix.
  - **MD_PAROLA**: For handling text animations and scrolling on the display.

To install these, go to `Sketch` > `Include Library` > `Manage Libraries`, search for `MD_MAX72XX` and `MD_PAROLA`, and install them.

### **Step 3: Upload the Code**
- Open the provided `.ino` file in the Arduino IDE.
- Modify the Wi-Fi credentials in the code to connect to your local network:
  ```cpp
  const char* ssid     = "your-SSID";
  const char* password = "your-PASSWORD";
  ```
- Connect the ESP32 to your computer and select the correct board and port:
  - Go to `Tools` > `Board` > Select "ESP32 Dev Module".
  - Go to `Tools` > `Port` > Select the correct port for your ESP32.
- Upload the code by clicking the upload button (right arrow) in the Arduino IDE.

---

## **Usage**

Once the code is uploaded, the ESP32 will:
1. Connect to the specified Wi-Fi network.
2. Retrieve the current time from an online NTP (Network Time Protocol) server.
3. Display the time on the 32x8 LED matrix with scrolling animations.

You can modify the text effects, display updates, or time formatting by adjusting the settings in the code.

---

## **Libraries Used**

### 1. **WiFi.h**
   - Used to connect the ESP32 to a Wi-Fi network and get internet access for fetching the time.
   
### 2. **MD_MAX72XX**
   - A library for controlling LED matrix displays with the MAX7219 driver.
   
### 3. **MD_PAROLA**
   - A library built on top of MD_MAX72XX, allowing easy control over scrolling and animated text for LED displays.

---

## **License**

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## **Contact**

If you have any questions or need further assistance with the project, feel free to contact:

- **ADITHYA VARDAN**
- [a.adithyavardan1@gmaial.com]
- GitHub: [AdithyaVardan](https://github.com/AdithyaVardan)

---


