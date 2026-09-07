# FloodGuard: Smart Water Detection for Smart Cities

An IoT flood-monitoring device built on Arduino that combines an ultrasonic sensor and a water-level sensor to detect rising flood risk in real time, pushing live status and alerts to the Blynk app over WiFi.


## What It Does

Iligan City has a history of severe flooding — most notably Typhoon Washi in 2011 — with limited real-time early-warning infrastructure for residents. FloodGuard is a low-cost prototype that continuously measures water distance and depth, classifies flood risk into four levels (Normal, Low, Moderate, High), and sends live updates and push notifications to connected devices through the Blynk IoT platform — so residents get advance warning without needing to monitor the site in person.

## Tech Stack

- **MCU:** Arduino UNO
- **Connectivity:** ESP8266-01S WiFi module → Blynk IoT platform (web + mobile)
- **Sensors:** HC-SR04 ultrasonic sensor (water distance), HW-038 water level sensor (depth via variable resistance)
- **Power:** 5V supply for Arduino/sensors, 3.3V for the ESP8266
- **Passive components:** 1kΩ and 10kΩ resistors for voltage division/current limiting on the WiFi module

## How It Works

**Ultrasonic sensor (flood risk classification):** measures distance from the sensor to the water surface. Based on how close the water gets (as a percentage of a 10cm range), the system classifies risk:

| Water proximity | Status |
|---|---|
| ~15% (far) | NORMAL |
| ~50% | LOW FLOOD RISK |
| ~70% | MODERATE FLOOD RISK |
| >70% | HIGH FLOOD RISK |

**Water level sensor:** acts like a variable resistor whose resistance changes based on water exposure, producing an analog output proportional to depth. The analog range was manually capped at 700 (instead of the default 1023) for measurement accuracy.

**Data flow:** sensors → Arduino UNO (reads ultrasonic digital pins 10/12, water level analog pin A0) → ESP8266-01S over UART (digital pins 2/3) → Blynk cloud via virtual pins → live display + push notifications on any connected device.

## Hardware Setup

- **Ultrasonic sensor (HC-SR04):** trigger/echo pins → Arduino digital pins 10 and 12
- **Water level sensor (HW-038):** analog output → Arduino pin A0
- **ESP8266-01S:** powered at 3.3V (not 5V), RX/TX → Arduino digital pins 2 and 3, with 1kΩ/10kΩ resistors for voltage division since the module isn't breadboard-friendly
- All sensors share 5V VCC and common GND with the Arduino


## Repository Structure

```
├── src/                 # Arduino sketch(es) — sensor reading, Blynk integration
├── docs/                # Circuit diagram, block diagrams, images
└── README.md
```

## How to Build & Flash

<!-- Fill in with your actual setup -->
```bash
# Requires the Blynk library and ESP8266 board support in Arduino IDE
# 1. Set your Blynk auth token in the sketch
# 2. Select board: Arduino Uno
# 3. Upload
```

## Results

The system correctly reported the four risk levels based on sensor readings and successfully pushed live water level data and notifications to the Blynk app during testing, confirming the sensor-to-cloud pipeline worked end to end.

<!-- Add specific numbers if available: response latency, sensor accuracy, etc. -->

## What I'd Improve

- Move beyond Blynk's subscription-gated data export for longer-term historical logging
- Add a battery/solar power option for deployment away from fixed power sources
- Field-test calibration thresholds (10cm range, 700 analog cap) against real flood conditions rather than a bench setup

## Team

- Harold T. Cañas
- Ricardo Jose G. Vicente

Department of Computer Engineering and Mechatronics, MSU-IIT

## License

MIT
