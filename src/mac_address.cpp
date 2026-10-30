#include <Arduino.h>
#include <WiFi.h>
 
void setup() {
  Serial.begin(115200);
  // Flash this environment to the receiver, then copy its address into receiverMac in transmitter.cpp.
  WiFi.mode(WIFI_STA);
  delay(500);
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());
}
 
void loop() {}  // The address is printed once when the ESP32 starts.
