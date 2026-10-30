#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "message.h"

// HC-SR04 pins: change these GPIO numbers to match your wiring.
#define TRIG_PIN 25
#define ECHO_PIN 26

// Receiver's MAC address. Replace this with yours (print it with the "mac" environment).
uint8_t receiverMac[] = {0x88, 0x57, 0x21, 0x6D, 0x9E, 0x08};

Message message;
uint32_t messageCounter = 0;

// Measure distance in centimeters; return -1 if the sensor gets no echo.
float measureDistanceCm() {
  // Start a measurement with a 10-microsecond trigger pulse.
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Wait up to 30 ms for an echo; increase this timeout for more range.
  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000UL);
  if (duration == 0) return -1.0;
  // I divide by two because the sound makes a round trip.
  return duration * 0.0343 / 2.0;
}

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // ESP-NOW uses Wi-Fi station mode; a router connection isn't needed.
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW initialization failed");
    return;
  }

  esp_now_peer_info_t peer = {};
  memcpy(peer.peer_addr, receiverMac, 6);
  peer.channel = 0;  // 0 uses the current channel; set a fixed one if both boards need it.
  peer.encrypt = false;

  if (esp_now_add_peer(&peer) != ESP_OK) {
    Serial.println("Failed to add receiver");
    return;
  }
  Serial.println("Transmitter ready");
}

void loop() {
  // Send the latest reading with a sequence number to track messages on the receiver.
  message.sequence = messageCounter++;
  message.distanceCm = measureDistanceCm();

  esp_err_t result = esp_now_send(receiverMac, (uint8_t *)&message, sizeof(message));

  Serial.print("Message #");
  Serial.print(message.sequence);
  Serial.print(" | Distance: ");
  Serial.print(message.distanceCm, 1);
  Serial.println(result == ESP_OK ? " cm | Sent" : " cm | Send failed");

  delay(100);  // Wait 100 ms between readings; adjust this to change the send rate.
}
