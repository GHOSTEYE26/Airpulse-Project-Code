# 🌬️ AirPulse - Smart Air Quality Monitor

[![ESP32](https://img.shields.io/badge/ESP32-Enabled-brightgreen.svg)](https://www.espressif.com/en/products/socs/esp32)
[![DHT11](https://img.shields.io/badge/DHT11-Sensor-blue.svg)](https://github.com/adafruit/DHT-sensor-library)
[![Google Sheets](https://img.shields.io/badge/Google%20Sheets-Integration-orange.svg)](https://workspace.google.com/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

**Real-time IoT Air Quality Monitoring System** built with **ESP32**. Measures temperature, humidity, and dust (PM) levels and automatically logs data to **Google Sheets** for remote monitoring and analysis.

---

## 📸 Sneak Peek

![AirPulse Project](https://github.com/GHOSTEYE26/Airpulse-Project-Code/blob/main/Air%20Pulse.jpeg?raw=true)

> *Live environmental monitoring at your fingertips!*

---

## ✨ Features

- 🌡️ **Accurate Temperature & Humidity** sensing with DHT11
- 🌫️ **Dust / PM Detection** using Sharp optical dust sensor
- ☁️ **Seamless Google Sheets Integration** — data logs automatically
- 📡 **WiFi Enabled** — works over your local network
- 📊 **Real-time Data Logging** every 10 seconds
- 🔋 **Low-power friendly** design for long-term deployment
- 📱 **Remote Access** — view your air quality from anywhere

---

## 🧰 Hardware Components

- **ESP32 Development Board**
- **DHT11** Temperature & Humidity Sensor
- **Sharp GP2Y1010AU0F** Optical Dust Sensor
- Breadboard + Jumper Wires
- USB Cable for programming/power

---

## 🔌 Circuit Connections

### DHT11 Sensor
| DHT11 Pin | ESP32 Pin |
|-----------|-----------|
| VCC       | 3.3V      |
| GND       | GND       |
| DATA      | GPIO 4    |

### Sharp GP2Y1010AU0F Dust Sensor
| Dust Sensor Pin | ESP32 Pin | Notes |
|-----------------|-----------|-------|
| VCC             | 5V        | - |
| GND             | GND       | - |
| LED             | GPIO 5    | Controls internal IR LED |
| Vo (Output)     | GPIO 34   | Analog reading (ADC1_CH6) |

> **Tip**: The dust sensor needs precise LED pulsing timing for accurate readings (handled in code).

---

## ⚙️ How It Works

1. **Sensors** collect real-time environmental data (Temp, Humidity, Dust).
2. **ESP32** processes the raw values.
3. Data is sent over **WiFi** using HTTP GET to a **Google Apps Script** web app.
4. The script appends a new row to your **Google Sheet** with timestamp + readings.
5. You can view live trends, create charts, or analyze historical data directly in Google Sheets.

---

## 📥 Setup Instructions

### 1. Google Sheets Setup (One-time)

1. Create a new Google Sheet.
2. Go to **Extensions → Apps Script**.
3. Paste the following script (replace `SHEET_NAME` if needed):

```javascript
const SHEET_ID = "YOUR_SHEET_ID_HERE";   // Copy from your sheet URL
const SHEET_NAME = "AirPulse_Data";

function doGet(e) {
  const ss = SpreadsheetApp.openById(SHEET_ID);
  const sheet = ss.getSheetByName(SHEET_NAME) || ss.insertSheet(SHEET_NAME);
  
  const temp = e.parameter.temp;
  const hum = e.parameter.hum;
  const dust = e.parameter.dust;
  const timestamp = new Date();

  sheet.appendRow([timestamp, temp, hum, dust]);
  
  return ContentService.createTextOutput("Data logged successfully!");
}
