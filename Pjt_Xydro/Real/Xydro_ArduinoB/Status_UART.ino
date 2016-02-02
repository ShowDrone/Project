#include<AltSoftSerial.h>
AltSoftSerial altSerial;

void Transmiter_init() {
  altSerial.begin(19200);
}

int waitTime = 0;
boolean rollCheck = true;
boolean pitchCheck = false;
boolean yawCheck = false;


void Transmiter_Update() {
  if (rollCheck) {
    if (waitTime + 3 > millis()) {
      altSerial.write(roll);
      rollCheck = false;
      pitchCheck = true;
      Serial.print(" 1 ");
      waitTime = millis();
    }
  }
  else if (pitchCheck) {
    if (waitTime + 3 > millis()) {
      altSerial.write(pitch);
      pitchCheck = false;
      yawCheck = true;
      Serial.print(" 2 ");
      waitTime = millis();
    }
  }
  else if (yawCheck) {
    if (waitTime + 3 > millis()) {
      altSerial.write(yaw);
      yawCheck = false;
      rollCheck = true;
      waitTime = millis();
      Serial.println(" 3 ");
    }
  }
}
