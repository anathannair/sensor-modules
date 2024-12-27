#include <Servo.h>
const int SERVO_PIN = 12;
Servo myservo;
void setup(){
    Serial.begin(9600);
     myservo.attach(SERVO_PIN);
  myservo.write(0);  // Center position
  delay(2000);

}
void loop()
{
   Serial.println("moving forward");
    myservo.write(90);
    delay(1000);
    Serial.println("moving right");
    myservo.write(45);
    delay(1000);
     Serial.println("moving left");
    myservo.write(0);
    delay(1000);
}
