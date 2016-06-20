#include<AltSoftSerial.h>

AltSoftSerial yourSerial;

struct Axis {
  double realN = 0;
  int integer = 0;
};


void Transmiter_init() {
  yourSerial.begin(19200);
  int8_t waitCheck = 1;
  while (1) {
    yourSerial.write('B');
    if (yourSerial.available()) {
      if (waitCheck) {
        Serial.println("Status_UART wait");
        waitCheck = 0;
      }
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
  roll = 20.1;
  pitch = 10.1;
  yaw = 0.1;
  
  X.realN = roll - (int)roll;
  X.integer = roll - X.realN;
  X.realN *= 100;
  //Serial.println((int)X.realN);

  Y.realN = pitch - (int)pitch;
  Y.integer = pitch - Y.realN;
  Y.realN *= 100;

  Z.realN = yaw - (int)yaw;
  Z.integer = yaw - Z.realN;
  Z.realN *= 100;

  //StatusPrint();

  yourSerial.write('S');
  delayMicroseconds(130);

  yourSerial.write('X');
  delayMicroseconds(130);
  yourSerial.write(X.integer);
  delayMicroseconds(130);
  yourSerial.write((int)X.realN);
  delayMicroseconds(130);

  yourSerial.write('Y');
  delayMicroseconds(130);
  yourSerial.write(Y.integer);
  delayMicroseconds(130);
  yourSerial.write((int)Y.realN);
  delayMicroseconds(130);

  yourSerial.write('Z');
  delayMicroseconds(130);
  yourSerial.write(Z.integer);
  delayMicroseconds(130);
  yourSerial.write((int)Z.realN);
  delayMicroseconds(130);

  yourSerial.write('F');
}

void StatusPrint() {
  Serial.print("X: ");
  Serial.print(X.integer); Serial.print(" "); Serial.print(X.realN/100); 
  Serial.print(" Y: ");
  Serial.print(Y.integer); Serial.print(" "); Serial.print(Y.realN/100);
  Serial.print(" Z: ");
  Serial.print(Z.integer); Serial.print(" "); Serial.println(Z.realN/100);
}


  
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

