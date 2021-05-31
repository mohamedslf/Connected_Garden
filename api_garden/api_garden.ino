#include <dht.h>
#include <SPI.h>
#include <WiFi101.h>

dht DHT;
char ssid[] = "HUAWEI-B310-5F52";
char pass[] = "RD5LJL6N2FE";

int status = WL_IDLE_STATUS;

WiFiClient client;

char server[] = "api.thingspeak.com";
String writeAPIKey = "5Y10MHG8P4TE38N3";

unsigned long lastConnectionTime = 0;
const unsigned long postingInterval = 20L * 1000L;

void setup() {
  Serial.begin(9600);
  
  while (status != WL_CONNECTED) {
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }
}

void loop() {
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  delay(1000);
  if (millis() - lastConnectionTime > postingInterval) {
    httpRequest();
  }
}

void httpRequest() {
  int sensorValue = analogRead(0);
  long rssi = WiFi.RSSI();
  float temp = DHT.temperature;
  float humi = DHT.humidity;
  String data = String("field1=" + String(sensorValue, DEC) + "&field2=" + String(rssi, DEC) + "&field3=" + String(temp, DEC)); 
  
  client.stop();
  if (client.connect(server, 80)) {
    client.println("POST /update HTTP/1.1");
    client.println("Host: api.thingspeak.com");
    client.println("Connection: close");
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("X-THINGSPEAKAPIKEY: "+writeAPIKey);
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.print(data.length());
    client.print("\n\n");
    client.print(data);
    
    lastConnectionTime = millis();
  }
}
