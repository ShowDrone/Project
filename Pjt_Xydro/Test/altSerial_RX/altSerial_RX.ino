#include<AltSoftSerial.h>
AltSoftSerial altSerial;

double pitch_B, roll_B, yaw_B;

void setup() {
  altSerial.begin(19200);
  Serial.begin(19200);
}

int time = 0;

void loop() {
  //if (time + 5 < millis()) {
  please();
  //  time = millis();
  //}
}

void please() {
  int i = 0;
  while (altSerial.available()) {
    if (i == 0) {
      roll_B = altSerial.read();
      Serial.print(" roll_B: "); Serial.print(roll_B);
      i++;
    }
    if (i == 1) {
      pitch_B = altSerial.read();
      i++;
      Serial.print(" pitch_B: "); Serial.print(pitch_B);
    }
    if (i == 2) {
      yaw_B = altSerial.read();
      Serial.print(" yaw_B: "); Serial.println(yaw_B);
      i++;
    }
    if ( i == 3) {
      //StatusPrint();
      Serial.print(altSerial.available()); Serial.print(" ");
      int a =  altSerial.readBytes(char a);
      Serial.print(a); Serial.print(" ");
      break;
    }
  }
}

void StatusPrint() {
  Serial.print(" roll_B: "); Serial.print(roll_B);
  Serial.print(" pitch_B: "); Serial.print(pitch_B);
  Serial.print(" yaw_B: "); Serial.println(yaw_B);
}
