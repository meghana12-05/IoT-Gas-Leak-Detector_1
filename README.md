# IoT-Gas-Leak-Detector_1
An IoT-based gas detection system using ESP32, MQTT, Python, and Twilio for real-time SMS alerts.

🚨 IoT Real-Time Gas Leak Detector
Overview: A smart home safety device that monitors gas levels and sends an emergency SMS to your phone if a leak is detected.
Tech Stack: > * Hardware: ESP32, MQ Sensor (Flying-Fish)

Backend: Python, Paho-MQTT

Cloud/API: Eclipse Mosquitto (MQTT Broker), Twilio SMS API

How it works: > 1. The ESP32 reads analog data from the MQ sensor.
2. Data is published to an MQTT cloud broker every 2 seconds.
3. A Python backend listens to the broker. If the gas level crosses the safety threshold (>2000), it triggers the Twilio API to send an SMS alert.
