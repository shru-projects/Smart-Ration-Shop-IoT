# 🛒 Smart Ration Shop IoT System

An IoT-based inventory monitoring system using ESP8266, OLED display, keypad input, and Google Sheets as a cloud database.

---

## 📌 Project Overview

This project demonstrates a smart grocery/ration shop system where stock levels of essential items are displayed in real-time and updated through user interaction.

The system uses:
- ESP8266 NodeMCU for processing and Wi-Fi connectivity
- OLED display for output
- Keypad for user interaction
- Google Sheets as a cloud-based database

---

## ⚙️ Features

- 📡 Real-time inventory display from cloud
- 🔢 Keypad-based stock reduction (simulation of sales)
- ☁️ Automatic update to Google Sheets
- 📟 Compact OLED interface
- 🌐 Wi-Fi enabled IoT system

---

## 🧱 System Architecture

Keypad Input → NodeMCU ESP8266 → Wi-Fi → Google Apps Script → Google Sheets
↓
OLED Display

---

## 🧰 Components Used

### Hardware
- NodeMCU ESP8266
- 0.96" OLED Display (SSD1306)
- 4×3 Matrix Keypad
- Breadboard
- Jumper wires

### Software
- Arduino IDE
- Google Apps Script
- Google Sheets

---

## 🔌 Wiring Details

### OLED → NodeMCU
- VCC → 3V
- GND → G
- SDA → D2
- SCL → D1

### Keypad → NodeMCU
- Pin 2 → D3
- Pin 3 → D4
- Pin 4 → TX
- Pin 5 → D5
- Pin 6 → D6
- Pin 7 → D7
- Pin 8 → RX

---

## 🚀 How It Works

1. ESP8266 connects to Wi-Fi
2. Fetches inventory data from Google Sheets
3. Displays data on OLED
4. User presses keypad to simulate sales
5. Stock is reduced locally
6. Updated data is sent back to Google Sheets

---

## 📊 Output

- OLED displays:
  - Rice stock
  - Wheat stock
  - Sugar stock
- Updates reflect instantly on cloud

---

## 👨‍💻 Team Members

- **D. S. Anushruthi**
- **Bindu Singh M J**
- **Gagana B**
- **Kruthika M**

---

## 🔮 Future Scope

- Mobile app integration
- Automatic billing system
- Multi-shop cloud synchronization
- SMS/email alerts for low stock
- Real-time analytics dashboard

---

## 📚 References

- Arduino Documentation
- ESP8266 Wi-Fi Library
- Google Apps Script Documentation
- Adafruit SSD1306 Library

---

## ⭐ Acknowledgment

This project was developed as part of an academic mini-project to explore IoT-based solutions for real-world problems.
