#include<SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX

int buf[8] = {0, };

void setup() {
  Serial.begin(19200);
  mySerial.begin(19200);
}

boolean check = false;

void loop() {
  if (mySerial.available()) {
    for (int i = 0; i < 8; i++) {
      buf[i] = mySerial.read();
      delay(1);
    }
    check = true;
  }
  if (check) {
    for (int i = 0; i < 8; i++) {
      Serial.print(" "); Serial.print(buf[i]);
      Serial.print(" ");
    }
    Serial.println();
    check = false;
  }
}
