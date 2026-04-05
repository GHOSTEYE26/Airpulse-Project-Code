# 🌬️ AirPulse-Project-Code

## 📌 Overview
**AirPulse** is an IoT-based Air Quality Monitoring System built using ESP32. It measures temperature, humidity, and dust levels in real time and sends the data to Google Sheets for remote monitoring and analysis.

---

## 🖼️ Project Image
![Project Image](Airpulse-Project-Code/Air Pulse.jpeg)

> 📁 Place your image inside an `images` folder and name it `project.jpg`

---

## 🚀 Features
- 📡 Real-time air quality monitoring  
- 🌡️ Temperature & humidity sensing  
- 🌫️ Dust (pollution) detection  
- ☁️ Google Sheets cloud integration  
- 📶 WiFi-enabled system  
- 📊 Data logging for analysis  

---

## 🧰 Components Used
- ESP32 Development Board  
- DHT11 Temperature & Humidity Sensor  
- Sharp GP2Y1010AU0F Dust Sensor  
- Breadboard  
- Jumper Wires  
- USB Cable  

---

## ⚙️ Working Principle
1. Sensors collect environmental data  
2. ESP32 processes the data  
3. Data is sent via WiFi  
4. Google Apps Script receives data  
5. Google Sheets stores the data  

---

## 🔌 Circuit Connections

### 🔹 DHT11
- VCC → 3.3V  
- GND → GND  
- DATA → GPIO 4  

### 🔹 Dust Sensor
- Vo → GPIO 34  
- LED → GPIO 5  
- VCC → 5V  
- GND → GND  

---

## 💻 ESP32 Code

```cpp
#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

// -------- DHT11 --------
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// -------- Dust Sensor --------
int dustPin = 34;
int ledPin = 5;

// -------- WiFi --------
const char* ssid = "ESP32";
const char* password = "12345678";

// -------- Google Script URL --------
String scriptURL = "YOUR_GOOGLE_SCRIPT_URL";

void connectWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(ledPin, OUTPUT);

  connectWiFi();
}

void loop() {

  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  digitalWrite(ledPin, LOW);
  delayMicroseconds(280);

  int dustValue = analogRead(dustPin);

  delayMicroseconds(40);
  digitalWrite(ledPin, HIGH);
  delayMicroseconds(9680);

  if (isnan(temp) || isnan(hum)) {
    Serial.println("DHT Error");
    return;
  }

  Serial.print("Temp: "); Serial.println(temp);
  Serial.print("Humidity: "); Serial.println(hum);
  Serial.print("Dust: "); Serial.println(dustValue);

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String url = scriptURL + "?temp=" + String(temp) +
                 "&hum=" + String(hum) +
                 "&dust=" + String(dustValue);

    http.begin(url);
    int httpCode = http.GET();

    Serial.print("Response: ");
    Serial.println(httpCode);

    http.end();
  }

  delay(10000);
}
