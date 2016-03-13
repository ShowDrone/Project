#include<SoftwareSerial.h>

SoftwareSerial mySerial(8, 9);

void setup() {

  Serial.begin(19200);
  mySerial.begin(19200);
}

void loop() {
    int a = 5;
    mySerial.write(a);
    
}
