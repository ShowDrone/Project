#include<TextFinder.h>
String Remote = "201502131274";
void setup() {
 Serial.begin(9600);
 Serial.println("c"+ Remote + "\r");
 delay(100);
 Serial.println("SM,0"); // 0 = slave , 1 = master
 delay(100);
 Serial.println("--"+ Remote + "\r");
 delay(100);
}

void loop() {
  if(Serial.available() > 0)
  {
    char ch = Serial.read();
    if(ch == 'L')
    {
    digitalWrite(13,HIGH);
    delay(100);
    }
    else if(ch == 'H')
    {
      digitalWrite(13,LOW);
      delay(100);
    }
  }
}
