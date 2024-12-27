#include <SimpleDHT.h>
#include <NewPing.h>
#include <BlynkSimpleEsp8266.h>  // Include Blynk library

// Blynk Auth Token from the Blynk app
char auth[] = "Sc6sFxYOrDTe_OQ2BcFNmQN2RDNkpcVi";  // Replace with your Blynk Auth Token

// Your WiFi credentials
char ssid[] = "EDUREKA";  // Replace with your WiFi SSID
char pass[] = "Edureka@123456";  // Replace with your WiFi password

// Define pins for HC-SR04
#define TRIG_PIN D5  // Trigger pin for HC-SR04
#define ECHO_PIN D6  // Echo pin for HC-SR04
#define MAX_DISTANCE 400  // Maximum distance to measure (in cm)

#define rainsensorPin A0

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);  // Initialize NewPing object

// Define pin for DHT11
int pinDHT11 = D4;  // GPIO 2 (D4 pin)
SimpleDHT11 dht11(pinDHT11);

const int flowSensorPin = D7; // GPIO pin connected to the flow sensor (D1)
volatile int pulseCount = 0;
float flowRate;              // Flow rate in liters/min
float totalVolume = 0;       // Total volume in liters
unsigned long oldTime = 0;

const int soilMoisturePin = D2; // Digital pin connected to soil moisture sensor

int loops, i, j, k, l, m;

// Interrupt function to count pulses
void IRAM_ATTR pulseCounter() {
  pulseCount++;
}

void setup() {
  // Start serial communication
  Serial.begin(115200);
  
  pinMode(soilMoisturePin, INPUT);
  
  pinMode(flowSensorPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(flowSensorPin), pulseCounter, FALLING);
  
  // Connect to Blynk server
  Blynk.begin(auth, ssid, pass);
  
  delay(2000);
}

void loop() {
  // Loop counter for data reset
  Serial.print("loops :");
  Serial.println(loops);
  Serial.print("i :");
  Serial.println(i);
  Serial.print("j :");
  Serial.println(j);
  Serial.print("k :");
  Serial.println(k);
  Serial.print("l :");
  Serial.println(l);
  Serial.print("m :");
  Serial.println(m);
  
  loops++;
  if (loops > 3) {
    i = 0;
    j = 0;
    k = 0;
    l = 0;
    m = 0;
    loops = 0;
    Blynk.virtualWrite(V0, 0);      //we use vitual pins in the Blynk IoT platform
    Blynk.virtualWrite(V1, 0);
    Blynk.virtualWrite(V2, 0);
    Blynk.virtualWrite(V3, 0);
    Blynk.virtualWrite(V4, 0);
  }

  // Write to Blynk based on counters
  if (i == 3) Blynk.virtualWrite(V0, 100);
  if (j == 3) Blynk.virtualWrite(V1, 100);
  if (k == 3) Blynk.virtualWrite(V2, 100);
  if (l == 3) Blynk.virtualWrite(V3, 100);
  if (m == 3) Blynk.virtualWrite(V4, 100);
  
  // Start Blynk functionality
  Blynk.run();
  
  // Read data from DHT11 sensor**************************
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err=");
    Serial.println(SimpleDHTErrCode(err));
    return;
  }
  // Print temperature and humidity to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print((int)temperature);
  Serial.println(" *C");
  Serial.print("Humidity: ");
  Serial.print((int)humidity);
  Serial.println(" H");
  // Send temperature and humidity data to Blynk
  
  // Measure distance using HC-SR04**********************
  unsigned int distance = sonar.ping_cm();  // Send ping and get distance in cm
  Serial.print("Distance: ");
  Serial.println(distance);
  // Send distance data to Blynk

  // Read the analog value from Rain sensor**************************
  int sensorValue = analogRead(rainsensorPin);  // Read the analog value from sensor
  Serial.print("rain sensor output: ");
  Serial.println(sensorValue);

  //Read water flow using Flow sensor****************************
  // Calculate flow rate every second
  if (millis() - oldTime > 1000) {  // Calculate flow rate every 1 second
    detachInterrupt(flowSensorPin);

    // Calculate flow rate in L/min
    flowRate = (pulseCount / 7.5);  // YF-S201 provides 7.5 pulses per liter
    
    // Calculate the total volume of water in liters
    totalVolume += (flowRate / 60.0); // Since we're calculating every second

    // Print the flow rate and total volume to the Serial Monitor
    Serial.print("Flow rate (L/min): ");
    Serial.print(flowRate);
    Serial.print("\tTotal Volume (L): ");
    Serial.println(totalVolume);

    // Reset pulse count and time
    pulseCount = 0;
    oldTime = millis();
    
    attachInterrupt(digitalPinToInterrupt(flowSensorPin), pulseCounter, FALLING);
  }
  
  //Read water flow using soil moisture sensor****************************
  int soilMoistureStatus = digitalRead(soilMoisturePin);
  Serial.print("soil moisture value: ");
  Serial.println(soilMoistureStatus);

  // Check conditions based on the sensor values
  checkConditions(temperature, humidity, distance, sensorValue, soilMoistureStatus, flowRate);
  delay(2000);
}

// Function to check if sensor values meet conditions
void checkConditions(int temperature, int humidity, int distance, int rainSensorValue, int soilMoistureStatus, float flowRate) {
  int tempThreshold = 21;         // Example temperature threshold
  int humidityThreshold = 55;     // Example humidity threshold
  int distanceThreshold = 50;    // Example distance threshold
  int rainThreshold = 600;        // Example rain sensor threshold
  int flowRateThreshold = 20;      // Example flow rate threshold

  if (temperature < tempThreshold && humidity > humidityThreshold) {
    Serial.println("Weather forecast Alert: There may be Heavy Rain!");
    i++;
  }
  if (soilMoistureStatus == LOW) { // Assuming LOW means wet
    Serial.println("Alert: Soil is wet.");
    j++;
  }

  if (distance < distanceThreshold) {
    Serial.println("Alert: Object too close.");
    k++;
  }
  
  if (rainSensorValue < rainThreshold) {
    Serial.println("Alert: Rain detected.");
    l++;
  }
  if (flowRate > flowRateThreshold) {
    Serial.println("Alert: Rain detected.");
    m++;
  }
}
