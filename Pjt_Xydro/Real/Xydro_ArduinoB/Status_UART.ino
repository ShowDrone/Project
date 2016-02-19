#include<AltSoftSerial.h>
AltSoftSerial altSerial;

void Transmiter_init() {
  altSerial.begin(19200);
}

boolean rollCheck = true;
boolean pitchCheck = false;
boolean yawCheck = false;

int rollTime = 0;
int pitchTime = 0;
int yawTime = 0;

void Transmiter_Update() {
  altSerial.write(roll);
  altSerial.write(pitch);
  altSerial.write(yaw);
  /*
  if (rollCheck) {
    if (rollTime + 1 < millis()) {
      altSerial.write(roll);
      rollCheck = false;
      pitchCheck = true;
      Serial.print(" 1 ");
      rollTime = millis();
    }
  }
  else if (pitchCheck) {
    if (pitchTime + 1 < millis()) {
      altSerial.write(pitch);
      pitchCheck = false;
      yawCheck = true;
      Serial.print(" 2 ");
      pitchTime = millis();
    }
  }
  else if (yawCheck) {
    if (yawTime + 1 < millis()) {
      altSerial.write(yaw);
      yawCheck = false;
      rollCheck = true;
      Serial.println(" 3 ");
      yawTime = millis();
    }
  }*/
}
