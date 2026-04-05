# 🌬️ AirPulse - IoT Smart Air Quality Monitor

[![ESP32](https://img.shields.io/badge/ESP32-Enabled-brightgreen.svg)](https://www.espressif.com/)
[![DHT11](https://img.shields.io/badge/DHT11-Sensor-blue.svg)](https://github.com/adafruit/DHT-sensor-library)
[![Google Sheets](https://img.shields.io/badge/Google%20Sheets-Integration-orange.svg)](https://workspace.google.com/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

**AirPulse** is a real-time IoT-based Air Quality Monitoring System using **ESP32**. It measures **Temperature**, **Humidity**, and **Dust (PM2.5)** levels and automatically logs the data to **Google Sheets** for remote monitoring and analysis.

---

## 📸 Project Preview

![AirPulse Project](Air%20Pulse.jpeg)

> Real-time environmental monitoring with cloud data logging.

---

## 🚀 Live Demo

🔗 **View Live Data (Google Sheets / API):**  
👉 [Click Here](YOUR_LIVE_DEMO_LINK)

> Replace `YOUR_LIVE_DEMO_LINK` with your deployed Google Script or Sheet link.

---

## ✨ Features

- 🌡️ Temperature & Humidity sensing (DHT11)
- 🌫️ Dust / PM2.5 detection (Sharp GP2Y1010AU0F)
- ☁️ Google Sheets cloud logging
- 📡 WiFi enabled with auto-reconnect
- 📊 Timestamp-based data logging
- 🔄 Ready for dashboard integration

---

## 🧰 Hardware Components

- ESP32 Development Board  
- DHT11 Temperature & Humidity Sensor  
- Sharp GP2Y1010AU0F Dust Sensor  
- Breadboard  
- Jumper Wires  
- USB Cable  

---

## 🔌 Circuit Connections

### 🔹 DHT11
| Pin  | ESP32 |
|------|------|
| VCC  | 3.3V |
| GND  | GND  |
| DATA | GPIO 4 |

### 🔹 Dust Sensor
| Pin | ESP32 | Description |
|-----|------|------------|
| VCC | 5V   | Power |
| GND | GND  | Ground |
| LED | GPIO 5 | LED control |
| Vo  | GPIO 34 | Analog output |

---

## ⚙️ How It Works

1. Sensors collect environmental data  
2. ESP32 processes the readings  
3. Data is sent via WiFi  
4. Google Apps Script stores the data  
5. Google Sheets displays real-time logs  

---

## 📥 Setup Instructions

### 🔹 1. Google Sheets + Apps Script

1. Create a new Google Sheet  
2. Go to **Extensions → Apps Script**  
3. Replace code with:

```javascript
function doGet(e) {
  const ss = SpreadsheetApp.getActiveSpreadsheet();
  let sheet = ss.getSheetByName("AirPulse_Data");

  if (!sheet) {
    sheet = ss.insertSheet("AirPulse_Data");
    sheet.appendRow(["Timestamp", "Temperature", "Humidity", "Dust"]);
  }

  if (e.parameter.temp && e.parameter.hum && e.parameter.dust) {
    sheet.appendRow([
      new Date(),
      e.parameter.temp,
      e.parameter.hum,
      e.parameter.dust
    ]);
    return ContentService.createTextOutput("Success");
  }
}
