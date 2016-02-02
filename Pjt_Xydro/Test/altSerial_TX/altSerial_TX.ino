#include<AltSoftSerial.h>
AltSoftSerial altSerial;

void setup() {
  Serial.begin(19200);
  altSerial.begin(19200);
}

double X, Y, Z;
boolean value = false;

int rollTime = 0;
int pitchTime = 0;
int yawTime = 0;

boolean rollCheck = true;
boolean pitchCheck = false;
boolean yawCheck = false;


void loop() {

  if (value == false) {
    X = 1.55;
    Y = 2.55;
    Z = 3.55;
    value = true;
  }
  else if (value == true) {
    X = 1.05;
    Y = 2.05;
    Z = 3.05;
    value = false;
  }
  
  altSerial.write(X);
  delay(3);
  altSerial.write(Y);
  delay(3);
  altSerial.write(Z);
  delay(3);
  
  /*
  if (rollCheck) {
    if (rollTime + 3 < millis()) {
      altSerial.write(X);
      rollCheck = false;
      pitchCheck = true;
      Serial.print("1: "); Serial.print(rollTime+3);
      rollTime = millis();
    }
  }
  else if (pitchCheck) {
    if (pitchTime + 3 < millis()) {
      altSerial.write(Y);
      pitchCheck = false;
      yawCheck = true;
      Serial.print("2: "); Serial.print(pitchTime+3);
      pitchTime = millis();
    }
  }
  else if (yawCheck) {
    if (yawTime + 3 < millis()) {
      altSerial.write(Z);
      yawCheck = false;
      rollCheck = true;
      Serial.print("3: "); Serial.println(yawTime+3);
      yawTime = millis();
    }
  }
  */
}
