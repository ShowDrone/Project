#include<AltSoftSerial.h>

AltSoftSerial yourSerial;

struct Axis {
  int realN = 0;
  double integer = 0;
};


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

struct Axis X;
struct Axis Y;
struct Axis Z;

void Transmiter_Update() {

  roll = 1.45;
  pitch = 2.45;
  yaw = 3.45;


  X.integer = roll - (int)roll;
  X.realN = roll - X.integer;
  X.integer *= 100;
  Serial.println((int)X.integer);

  Y.integer = pitch - (int)pitch;
  Y.realN = pitch - Y.integer;
  Y.integer *= 100;

  Z.integer = yaw - (int)yaw;
  Z.realN = yaw - Z.integer;
  Z.integer *= 100;

  yourSerial.write('S');
  delayMicroseconds(100);

  yourSerial.write('X');
  delayMicroseconds(100);
  yourSerial.write(X.realN);
  delayMicroseconds(100);
  yourSerial.write((int)X.integer);
  delayMicroseconds(100);

  yourSerial.write('Y');
  delayMicroseconds(100);
  yourSerial.write(Y.realN);
  delayMicroseconds(100);
  yourSerial.write((int)Y.integer);
  delayMicroseconds(100);

  yourSerial.write('Z');
  delayMicroseconds(100);
  yourSerial.write(Z.realN);
  delayMicroseconds(100);
  yourSerial.write((int)Z.integer);
  delayMicroseconds(100);

  yourSerial.write('F');

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
