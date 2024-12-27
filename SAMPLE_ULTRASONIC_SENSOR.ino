#define BLYNK_TEMPLATE_ID "TMPL3My8-MFwF"
#define BLYNK_DEVICE_NAME "dixon"
#define BLYNK_AUTH_TOKEN "phgZv_gKlqlVUXVC2OFXn8ioKC9zTQ9v"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define TRIG_PIN D1 // Ultrasonic sensor Trig pin
#define ECHO_PIN D2 // Ultrasonic sensor Echo pin

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "EDUREKA_5G";
char pass[] = "Edureka@123456";

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  Blynk.run();
  measureDistance();
  delay(1000); // Measure every 1 second
}

void measureDistance() {
  // Trigger the ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Read the echo response
  long duration = pulseIn(ECHO_PIN, HIGH);
  
  // Calculate the distance in cm
  int distance = duration * 0.034 / 2;
  
  // Display distance in Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Send distance to Blynk app on virtual pin V0
  Blynk.virtualWrite(V0, distance);
}
