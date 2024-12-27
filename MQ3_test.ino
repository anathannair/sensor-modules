const int mq3Pin = A0;
const int threshold = 180;
void setup() {
  Serial.begin(9600);
  pinMode(2,OUTPUT);  
}

void loop() {
  int sensorValue = analogRead(mq3Pin);
  Serial.print("MQ-3 Sensor Value: ");
  Serial.println(sensorValue); 
  delay(1000);
  if (sensorValue > threshold) {
    digitalWrite(2, HIGH);  
  } else {
    digitalWrite(2, LOW); 
  }
}
