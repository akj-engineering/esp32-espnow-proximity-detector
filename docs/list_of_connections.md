# HC-SR04 to ESP32 Connections

I used this wiring for the ESP32 transmitter and its HC-SR04 ultrasonic sensor:

| HC-SR04 pin | ESP32 connection | Notes |
|---|---|---|
| VCC | VIN (5 V) | The standard HC-SR04 needs 5 V. On the ESP32 development board, VIN provides the USB 5 V supply when powered over USB. |
| GND | GND | Connect the grounds to provide a common reference. |
| TRIG | GPIO 25 | The ESP32's 3.3 V output is sufficient to trigger the sensor. |
| ECHO | GPIO 26 through a voltage divider | Do not connect ECHO directly to the ESP32. The sensor can output 5 V, while ESP32 GPIO pins are 3.3 V. |

## ECHO voltage divider

Use a1k and a 2k ohm resistors to reduce the ECHO signal to a safe level:

```text
HC-SR04 ECHO --- 1 kOhm ------ ESP32 GPIO 26
                           |
                         2 kOhm
                           |
                          GND
```

The divider lowers the 5 V ECHO signal to approximately 3.3 V. Connect the divider's GND to the same GND used by the sensor and ESP32.

The GPIO numbers match the variable `TRIG_PIN` and `ECHO_PIN` in `src/transmitter.cpp`. If you use different pins, you should update those definitions to match your wiring.