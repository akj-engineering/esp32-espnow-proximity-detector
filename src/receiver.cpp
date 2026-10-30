#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "message.h"
 
// Change LED_PIN to match your LED wiring, and set the alert distance you want.
#define LED_PIN 2
#define ALERT_THRESHOLD_CM 100.0

Message receivedMessage;

// This callback signature depends on your Arduino-ESP32 version.
#if ESP_ARDUINO_VERSION_MAJOR >= 3
void onReceive(const esp_now_recv_info_t *info, const uint8_t *data, int length) {
#else
void onReceive(const uint8_t *senderMac, const uint8_t *data, int length) {
#endif
  // Keep the receiver and transmitter message formats in sync (see message.h).
  if (length != sizeof(receivedMessage)) return;
  memcpy(&receivedMessage, data, sizeof(receivedMessage));

  // Change this condition if you want the LED to react differently.
  bool alert = receivedMessage.distanceCm > 0 && receivedMessage.distanceCm < ALERT_THRESHOLD_CM;
  digitalWrite(LED_PIN, alert ? HIGH : LOW);

  Serial.print("Message #");
  Serial.print(receivedMessage.sequence);
  Serial.print(" | Distance: ");
  if (receivedMessage.distanceCm < 0) {
    Serial.print("out of range");
  } else {
    Serial.print(receivedMessage.distanceCm, 1);
    Serial.print(" cm");
  }
  Serial.print(" | LED: ");
  Serial.println(alert ? "ON" : "OFF");
}
 
void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
 
  // Start ESP-NOW and tell it to pass incoming messages to onReceive().
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW initialization failed");
    return;
  }
  esp_now_register_recv_cb(onReceive);
  Serial.println("Receiver ready, waiting for messages...");
}
 
void loop() {}  // onReceive() handles messages as they arrive.
