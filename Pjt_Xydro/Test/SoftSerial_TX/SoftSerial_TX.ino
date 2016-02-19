#include <SoftwareSerial.h>

SoftwareSerial Serial_one(9, 8);
SoftwareSerial Serial_two(11, 10);

void setup()  
{
  Serial_one.begin(19200);
  Serial_two.begin(19200);
  Serial.begin(19200);
}

void loop()
{
  Serial_one.write(1);
  delayMicroseconds(500);
  Serial_one.write(2);
  delayMicroseconds(500);
  Serial_one.write(3);
  delayMicroseconds(500);
  Serial_two.write(4);
  delayMicroseconds(500);
  Serial_two.write(5);
  delayMicroseconds(500);
  Serial_two.write(6);
  delayMicroseconds(500);
}
