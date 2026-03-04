# ESP32 Tripper Navigation System 🚗

## 📌 Project Idea
I wanted to create a Tripper Navigation display like modern bikes.

Google Maps API is paid for advanced navigation features,
so I designed my own GUI-based navigation system using:

- ESP32
- OLED Display (SSD1306)
- WiFi Hotspot Mode
- Mobile Web Interface

## 🔧 Features

- Destination Distance Display
- Turn Distance in Meters
- Direction Input:
  - LEFT
  - RIGHT
  - STRAIGHT
  - U-TURN
- Arrow Graphics on OLED
- Arrival Detection
- Mobile Friendly Interface
- No Google API
- No Bluetooth
- No Router Required

## 🌐 How It Works

ESP32 creates its own WiFi hotspot.
Mobile connects to ESP32.
User manually inputs:

- Destination KM
- Turn distance (meters)
- Direction

OLED updates instantly.

## 🚀 Future Improvements

- Real GPS integration
- Speed display
- Buzzer alert
- Auto decreasing distance
- Turn-by-turn memory

---
![OLED](https://github.com/user-attachments/assets/fe9ceee1-5ca0-4184-9534-7bdda50041b4)


Made with ❤️ using ESP32
