volatile int pulseCount = 0;
float flowRate = 0.0;
unsigned long oldTime = 0;

void setup() {
  pinMode(D5, INPUT_PULLUP); // Signal pin connected to D5 (GPIO14 on NodeMCU)
  attachInterrupt(digitalPinToInterrupt(D5), pulseCounter, RISING);
  Serial.begin(115200); // Use 115200 for NodeMCU Serial Monitor
}

void loop() {
  // Calculate the flow rate every second
  if ((millis() - oldTime) >= 1000) {
    detachInterrupt(digitalPinToInterrupt(D5)); // Stop counting pulses temporarily

    // Flow rate in liters/minute
    flowRate = (pulseCount / 7.5); // Adjust based on your sensor's calibration factor
    oldTime = millis();
    pulseCount = 0;

    Serial.print("Flow Rate: ");
    Serial.print(flowRate);
    Serial.println(" L/min");

    attachInterrupt(digitalPinToInterrupt(D5), pulseCounter, RISING); // Restart counting
  }
}

// Interrupt service routine to count pulses
void pulseCounter() {
  pulseCount++;
}
