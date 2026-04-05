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
String scriptURL = "https://script.google.com/macros/s/AKfycbx5IKCTw2cm7V_UEMaJDgkCofyyTubFinCT69hXWJzsSg6AxZcZ0uAg0igGcYVSX3zl/exec";

void connectWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  int timeout = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    timeout++;

    // Retry if failed
    if (timeout > 30) {
      Serial.println("\nRetrying WiFi...");
      WiFi.disconnect();
      WiFi.begin(ssid, password);
      timeout = 0;
    }
  }

  Serial.println("\n✅ Connected to WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);

  dht.begin();
  pinMode(ledPin, OUTPUT);

  connectWiFi();
}

void loop() {

  // Reconnect WiFi if disconnected
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi Lost! Reconnecting...");
    connectWiFi();
  }

  // -------- Read DHT11 --------
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  // -------- Read Dust Sensor --------
  digitalWrite(ledPin, LOW);
  delayMicroseconds(280);

  int dustValue = analogRead(dustPin);

  delayMicroseconds(40);
  digitalWrite(ledPin, HIGH);
  delayMicroseconds(9680);

  // -------- Error Check --------
  if (isnan(temp) || isnan(hum)) {
    Serial.println("❌ DHT Error");
    delay(2000);
    return;
  }

  // -------- Print Data --------
  Serial.println("------ Sensor Data ------");
  Serial.print("Temp: "); Serial.print(temp); Serial.println(" °C");
  Serial.print("Humidity: "); Serial.print(hum); Serial.println(" %");
  Serial.print("Dust: "); Serial.println(dustValue);

  // -------- Send Data --------
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String url = scriptURL + "?temp=" + String(temp) +
                 "&hum=" + String(hum) +
                 "&dust=" + String(dustValue);

    http.begin(url);
    int httpCode = http.GET();

    Serial.print("HTTP Response: ");
    Serial.println(httpCode);

    http.end();
  }

  Serial.println("--------------------------\n");

  delay(10000); // 10 sec
}