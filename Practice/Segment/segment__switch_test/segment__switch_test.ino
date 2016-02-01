#include<Servo.h>
Servo myservo;

void setup() {
myservo.attach(10,1);
}

void loop () {
for (int i=0;i<180;i++)
{
  myservo.write(i,1);
  delay(500);
}
}
