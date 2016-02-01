//Maker : Seunghyun Lee http://dkwltmdgus.blog.me
//공유하실 땐 출처 남겨주세요~

#include "Wire.h"
#include "I2Cdev.h"
#include "MPU9150.h"
#include <AltSoftSerial.h>
AltSoftSerial altSerial;

MPU9150 accelGyroMag;

int16_t AcX, AcY, AcZ;
int16_t GyX, GyY, GyZ;
int16_t MgX, MgY, MgZ;

double rollGyro, pitchGyro, yawGyro;
double rollAcc, pitchAcc, yawAcc;
double pitch = 0, roll = 0, yaw = 0;
float DT = 0.01;

void setup() {
  Serial.begin(19200);
  altSerial.begin(115200);
  Wire.begin();
  accelGyroMag.initialize();
}
int time_pre = 0;
void loop() {
  int time1 = millis() - time_pre;
  time_pre = millis();
  Serial.println(time1);

  accelGyroMag.getMotion6(&AcX, &AcY, &AcZ, &GyX, &GyY, &GyZ);
  //가속도 계산
  pitchAcc = atan2(AcY, AcZ) * 180 / PI; // 라디안 to 각도값
  rollAcc = -atan2(AcX, AcZ) * 180 / PI;
  yawAcc = atan2(AcX, AcY) * 180 / PI;

  //자이로 계산
  pitchGyro = GyX / 131.07; // 16비트 값 to 250'/sec
  rollGyro = GyY / 131.07;
  yawGyro = GyZ / 131.07;

  //상보필터
  pitch = (0.98 * (pitch + (pitchGyro * DT))) + (0.02 * pitchAcc);
  roll = (0.98 * (roll + (rollGyro * DT))) + (0.02 * rollAcc);
  yaw = (0.98 * (yaw + (yawGyro * DT))) + (0.02 * rollAcc);

  char check = Serial.read();
  if (check == 'K') {
    while (1) {
      char incheck = Serial.read();
      altSerial.(1.0);
      altSerial.write(1.0);
      delayMicroseconds(2);
      altSerial.write(2.0);
      delayMicroseconds(2);
      altSerial.write(3.0);
      
      delay(100);
      if (incheck == 'K')
        break;
      
    }
  }
}
