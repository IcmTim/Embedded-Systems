#include <WiFi.h>
#include "DHT.h"
#include "secrets.h"

#define DHTPIN 15
#define DHTTYPE DHT22

const char* server = "api.thingspeak.com";

const char* server_ip = "192.168.0.101";
const int server_port = 3000;

DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;

// LED bar
int ledPins[] = {16, 17, 18, 19, 20, 21, 22, 26, 27, 28};
int ledCount = 5;

void setup() {
  Serial1.begin(115200);
  dht.begin();

  for (int i = 0; i < ledCount; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  //Wi-Fi
  Serial1.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial1.print(".");
  }
  Serial1.println("\n✅ WiFi connected!");
}

void displayTemperature(float temp) {
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(ledPins[i], LOW);
  }

  int level = 0;
  if (temp < 20) level = 1;
  else if (temp < 25) level = 2;
  else if (temp < 30) level = 3;
  else if (temp < 35) level = 4;
  else level = 5;

  for (int i = 0; i < level; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial1.println("❌ Failed to read from DHT22 sensor!");
    delay(2000);
    return;
  }

  Serial1.print("Temperature: ");
  Serial1.print(temperature);
  Serial1.print(" °C, Humidity: ");
  Serial1.print(humidity);
  Serial1.println(" %");

  displayTemperature(temperature);

  if (client.connect(server, 80)) {
    String url = "/update?api_key=" + apiKey +
                 "&field1=" + String(temperature) +
                 "&field2=" + String(humidity);

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + server + "\r\n" +
                 "Connection: close\r\n\r\n");

    Serial1.println("📡 Sending data to ThingSpeak...");
    Serial1.println("URL: " + url);
    client.stop();
  }

  delay(20000);
}
