#include<AltSoftSerial.h>

AltSoftSerial yourSerial;

void Transmiter_init() {
  yourSerial.begin(19200);

  while (1) {
    yourSerial.write('B');
    if (yourSerial.available()) {
      int check = yourSerial.read();
      if (check == 'O') {
        Serial.println("Status_UART OK");
        delay(500);
        break;
      }
    }
  }
}

boolean rollCheck = true;
boolean pitchCheck = false;
boolean yawCheck = false;

int rollTime = 0;
int pitchTime = 0;
int yawTime = 0;

void Transmiter_Update() {

  yourSerial.write('S');
  delayMicroseconds(500);
  yourSerial.write(roll);
  delayMicroseconds(500);
  yourSerial.write(pitch);
  delayMicroseconds(500);
  yourSerial.write(yaw);
  delayMicroseconds(500);
  yourSerial.write('F');
  delayMicroseconds(100);

  /*
  if(rollCheck) {
    yourSerial.write(roll);
    rollCheck = false;
    pitchCheck = true;
  }
  else if(pitchCheck) {
    yourSerial.write(pitch);
    pitchCheck = false;
    yawCheck = true;
  }
  else if(yawCheck) {
    yourSerial.write(yaw);
    yawCheck = false;
    rollCheck = true;
  }
  */
}
