void setup() {
  Serial.begin(9600);//enable serial monitor
  pinMode(9,INPUT );//define LED pin
}
void loop() {
  int value = digitalRead(9);//read value
  Serial.print("Value : ");
  Serial.println(value);
  if (value < 300) {//check condition
    digitalWrite(8, LOW);
    Serial.print("Heavy rain  LED on ");
  } else {
    digitalWrite(8,HIGH);
  }
}
