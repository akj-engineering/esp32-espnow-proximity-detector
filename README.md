# ESP32 Wireless Proximity Detector | ESP-NOW

**Wireless proximity detection system using two ESP32 microcontrollers, an HC-SR04 ultrasonic sensor and ESP-NOW communication.**

**Système de détection de proximité sans fil utilisant deux microcontrôleurs ESP32, un capteur ultrasonique HC-SR04 et le protocole ESP-NOW.**

---

## English

### Overview

This project implements a wireless proximity detection system using two ESP32 boards communicating through ESP-NOW, without requiring a Wi-Fi router or Internet connection.

The transmitter measures distances using an HC-SR04 ultrasonic sensor and sends the measurements to the receiver. The receiver displays real-time readings through the Serial Monitor and activates its onboard LED when an object is detected within 100 cm.

### Features

- Ultrasonic distance measurement (HC-SR04).
- Wireless communication using ESP-NOW.
- Real-time distance monitoring.
- LED-based proximity alert (100 cm threshold).

### Technologies

- **Programming:** C++
- **Microcontrollers:** ESP32
- **Communication:** ESP-NOW
- **Development Environment:** PlatformIO
- **Sensor:** HC-SR04

### Wiring

| HC-SR04 | ESP32 |
|---|---|
| VCC | VIN (5V) |
| GND | GND |
| TRIG | GPIO25 |
| ECHO | GPIO26 (voltage divider: 1 kohm / 2 kohm) |

**Note:** A voltage divider is required on ECHO to reduce the 5V signal to approximately 3.3V, protecting the ESP32.

### Usage

1. Upload `mac_address.cpp` to the receiver and retrieve its MAC address.
2. Replace the receiver's MAC address in `transmitter.cpp`.
3. Upload `receiver.cpp` to the receiver.
4. Upload `transmitter.cpp` to the transmitter.
5. Open the receiver's Serial Monitor at 115200 baud.

---

## Français

### Présentation

Ce projet consiste à concevoir un système de détection de proximité sans fil à l'aide de deux cartes ESP32 communiquant par ESP-NOW, sans nécessiter de routeur Wi-Fi ni de connexion Internet.

L'émetteur mesure la distance des objets environnants à l'aide d'un capteur ultrasonique HC-SR04 et transmet les données au récepteur. Ce dernier affiche les mesures en temps réel dans le moniteur série et active sa LED intégrée lorsqu'un objet est détecté à moins de 100 cm.

### Fonctionnalités

- Mesure de distance par ultrasons (HC-SR04).
- Communication sans fil via ESP-NOW.
- Surveillance des distances en temps réel.
- Alerte de proximité par LED (seuil de 100 cm).

### Technologies

- **Programmation :** C++
- **Microcontrôleurs :** ESP32
- **Communication :** ESP-NOW
- **Environnement de développement :** PlatformIO
- **Capteur :** HC-SR04

### Branchement

| HC-SR04 | ESP32 |
|---|---|
| VCC | VIN (5V) |
| GND | GND |
| TRIG | GPIO25 |
| ECHO | GPIO26 (pont diviseur : 1 kohm / 2 kohm) |

**Remarque :** Un pont diviseur de tension est nécessaire sur ECHO afin de réduire le signal de 5V à environ 3,3V et protéger l'ESP32.

### Utilisation

1. Branchez le capteur HC-SR04 à l'ESP32 émetteur en suivant le tableau ci-dessus.
2. Dans PlatformIO, téléversez l'environnement `mac` sur l'ESP32 qui servira de récepteur, puis ouvrez le moniteur série à 115200 bauds pour récupérer son adresse MAC.
3. Remplacez `receiverMac` dans `transmitter.cpp` par l'adresse MAC du récepteur.
4. Téléversez l'environnement `receiver` sur le récepteur, puis l'environnement `transmitter` sur l'émetteur.
5. Ouvrez le moniteur série du récepteur à 115200 bauds pour suivre les mesures et l'état de la LED.

Adaptez les ports série `COM6` et `COM7` dans `platformio.ini` aux ports utilisés par vos cartes. Vous pouvez également modifier les broches du capteur dans `transmitter.cpp` et le seuil d'alerte dans `receiver.cpp`.