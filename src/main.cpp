#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Q7A-5G";
const char* pass = "iiitbbsr";

ESP8266WebServer server(80);

#define RELAY D1

void onLight() {
  digitalWrite(RELAY, LOW);
  server.send(200, "text/plain", "ON");
}

void offLight() {
  digitalWrite(RELAY, HIGH);
  server.send(200, "text/plain", "OFF");
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, HIGH);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  server.on("/on", onLight);
  server.on("/off", offLight);
  server.begin();
}

void loop() {
  server.handleClient();
}