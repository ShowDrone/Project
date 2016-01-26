#include<SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX

int buf[8] = {0, 1, 2, 3, 4, 5, 6, 7};

void setup() {
  Serial.begin(19200);
  mySerial.begin(19200);
}

void loop() {
  int sw = Serial.read();
  if (sw == 'K') {
    for(int i=0;i<8;i++) {
      mySerial.write(buf[i]);
      delay(1);
    }
    Serial.println("Send Succesful");
  }
}
