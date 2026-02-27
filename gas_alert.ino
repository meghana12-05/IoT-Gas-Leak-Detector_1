#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Add your Wi-Fi";         // <-- Add your Wi-Fi
const char* password = "Add your Password"; // <-- Add your Password
const char* mqtt_server = "test.mosquitto.org";

WiFiClient espClient;
PubSubClient client(espClient);
const int gasPin = 34; 

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to Wi-Fi: ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500); 
    Serial.print("."); 
  }
  Serial.println("\nWi-Fi Connected!");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT Cloud... ");
    String clientId = "ESP32Client-" + String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str())) { 
      Serial.println("Connected!"); 
    } else { 
      Serial.println("Failed. Retrying in 5 seconds...");
      delay(5000); 
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) { reconnect(); }
  client.loop();

  int gasValue = analogRead(gasPin); // Read A0 pin
  
  // Print to the Serial Monitor so you can see it!
  Serial.print("Current Gas Level: ");
  Serial.println(gasValue);

  // Send to Cloud
  char msg[10];
  snprintf(msg, 10, "%d", gasValue);
  client.publish("home/kitchen/gas", msg); 
  
  delay(2000); 
}