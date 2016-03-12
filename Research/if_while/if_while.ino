#include<SoftwareSerial.h>
SoftwareSerial mySerial(8, 9);

void setup() {
  Serial.begin(19200);
  mySerial.begin(19200);
}

int pre_time = 0;
int sum = 0;
void loop() {
  int time = micros() - pre_time;
  while (mySerial.available()) {
    int check = mySerial.read();
  }
  Serial.println(time);

  if(time > 100) {
  }
  
  pre_time = micros();
}
