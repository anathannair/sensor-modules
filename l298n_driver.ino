// Define motor control pins
const int IN1 = 9;  // Input 1 on L298N
const int IN2 = 10; // Input 2 on L298N
const int ENA = 11; // Enable A on L298N

void setup() {
  // Set motor control pins as outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  
  // Start with motor off
  digitalWrite(ENA, LOW);
}

void loop() {
  // Run motor forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(ENA, HIGH); // Enable motor
  delay(2000); // Run for 2 seconds

  // Stop the motor
  digitalWrite(ENA, LOW);
  delay(1000); // Stop for 1 second

  // Run motor backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(ENA, HIGH); // Enable motor
  delay(2000); // Run for 2 seconds

  // Stop the motor
  digitalWrite(ENA, LOW);
  delay(1000); // Stop for 1 second
}
