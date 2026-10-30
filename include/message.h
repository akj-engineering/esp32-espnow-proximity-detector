#pragma once
#include <Arduino.h>
 
// This is the packet shared by both ESP32s. If you add or change a field here, update the transmitter and receiver to use the same format.
typedef struct {
  uint32_t sequence;  // Message number, useful for following readings.
  float distanceCm;   // Latest distance in centimeters, getting the value -1 means no echo was received.
} Message;
