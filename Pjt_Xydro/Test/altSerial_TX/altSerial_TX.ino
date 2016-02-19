#include<AltSoftSerial.h>
AltSoftSerial altSerial;

void setup() {
  Serial.begin(19200);
  altSerial.begin(19200);
}

double X = 1, Y = 2, Z = 3;
boolean value = false;

int rollTime = 0;
int pitchTime = 0;
int yawTime = 0;

boolean rollCheck = true;
boolean pitchCheck = false;
boolean yawCheck = false;


void loop() {

  if (Serial.available()) {
    int readData = Serial.read();
    if (readData == 'K') {
      while (1) {  //altSerial.write(Y);
        //altSerial.write(Z);
        if (Serial.available()) {
          int readData = Serial.read();
          if (readData == 'K')
            break;
        }

      }
    }
  }

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
