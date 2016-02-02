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
      waitTime = millis();
      rollCheck = false;
      pitchCheck = true;
    }
  }
  else if (pitchCheck) {
    if (waitTime + 3 > millis()) {
      altSerial.write(pitch);
      waitTime = millis();
      pitchCheck = false;
      yawCheck = true;
    }
  }
  else if (yawCheck) {
    if (waitTime + 3 > millis()) {
      altSerial.write(yaw);
      waitTime = millis();
      yawCheck = false;
      rollCheck = true;
    }
  }
}
