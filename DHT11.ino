#include "DHT.h"

// Pin connected to the DATA pin of DHT11
#define DHTPIN 2  // Use GPIO2 (D4 on NodeMCU)

// Define sensor type
#define DHTTYPE DHT11

// Initialize the DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);  // Start Serial Monitor
  Serial.println("DHT11 Sensor Test");
  dht.begin();           // Initialize DHT sensor
}

void loop() {
  delay(2000);  // Wait for 2 seconds between readings

  // Read temperature in Celsius
  float temperature = dht.readTemperature();
  // Read humidity
  float humidity = dht.readHumidity();

  // Check if any reading failed
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print values to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
}
