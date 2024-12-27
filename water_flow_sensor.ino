volatile int flow_frequency = 0; // Measures flow sensor pulses
unsigned int l_hour;            // Calculated litres/hour
unsigned char flowsensor =D5;          // Sensor Input (D5 corresponds to GPIO14)
unsigned long currentTime;
unsigned long cloopTime;

void flow() { // Interrupt function
  flow_frequency++;
}

void setup() {
  pinMode(flowsensor, INPUT_PULLUP); // Enable internal pull-up resistor
  Serial.begin(9600);               // Initialize Serial Monitor
  attachInterrupt(digitalPinToInterrupt(flowsensor), flow, RISING); // Setup interrupt for D5 (GPIO14)
  currentTime = millis();
  cloopTime = currentTime;
}

void loop() {
  currentTime = millis();
  // Every second, calculate and print litres/hour
  if (currentTime >= (cloopTime + 1000)) {
    cloopTime = currentTime; // Update cloopTime
    // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
    l_hour = (flow_frequency * 60 / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
    flow_frequency = 0; // Reset Counter
    Serial.print(l_hour, DEC); // Print litres/hour
    Serial.println(" L/hour");
  }
}
