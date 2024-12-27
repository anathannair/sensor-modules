#include <DFRobot_DHT11.h>

int a=A0;

void setup() {
pinMode(a,OUTPUT);

}

void loop() {
analogWrite(a,255);
delay(1000);
analogWrite(a,0);
delay(1000);
}
