const int TRIG_PIN = 4;  // Pin for the Trigger
const int ECHO_PIN = 5; // Pin for the Echo

void setup() {
  Serial.begin(9600); // Start serial communication at 9600 baud
  pinMode(TRIG_PIN, OUTPUT); // Set TRIG_PIN as OUTPUT
  pinMode(ECHO_PIN, INPUT);  // Set ECHO_PIN as INPUT
  pinMode(8, OUTPUT);
}

void loop() {
  // Clear the trigger
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Send a 10µs pulse to trigger the sensor
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read the echo pulse duration in microseconds
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate the distance (duration / 2) * speed of sound
  int distance = duration * 0.034 / 2;

  // Print the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500); // Delay between measurements
  if (distance > 10)
  {
    Serial.println("Water level low! Turning on motor.");
    digitalWrite(8, LOW);
  }
  else
  {
    Serial.println("Water level sufficient. Turning off motor.");
    digitalWrite(8, HIGH);
  }
  delay(2000);
}
