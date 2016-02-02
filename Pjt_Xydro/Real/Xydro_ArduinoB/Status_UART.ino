#include<AltSoftSerial.h>
AltSoftSerial altSerial;

void Transmiter_init() {
  altSerial.begin(19200);
}

boolean rollCheck = true;
boolean pitchCheck = false;
boolean yawCheck = false;

int rollTime = 0;
int pithcTime = 0;
int yawTime = 0;

void Transmiter_Update() {
  if (rollCheck) {
    if (rollTime + 3 < millis()) {
      altSerial.write(roll);
      rollCheck = false;
      pitchCheck = true;
      Serial.print(" 1 ");
      rollTime = millis();
    }
  }
  else if (pitchCheck) {
    if (pitchTime + 3 < millis()) {
      altSerial.write(pitch);
      pitchCheck = false;
      yawCheck = true;
      Serial.print(" 2 ");
      pitchTime = millis();
    }
  }
  else if (yawCheck) {
    if (yawTime + 3 < millis()) {
      altSerial.write(yaw);
      yawCheck = false;
      rollCheck = true;
      Serial.println(" 3 ");
      yawTime = millis();
    }
  }
}
