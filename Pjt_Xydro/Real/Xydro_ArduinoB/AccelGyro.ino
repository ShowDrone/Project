#include "Wire.h"
#include "I2Cdev.h"
#include "MPU9150.h"

MPU9150 accelGyroMag;

int16_t AcX, AcY, AcZ;
int16_t GyX, GyY, GyZ;
int16_t MgX, MgY, MgZ;

double rollGyro, pitchGyro, yawGyro;
double rollAcc, pitchAcc, yawAcc;
double pitch = 0, roll = 0, yaw = 0;
float DT = 0.01;

void AccelGyro_init() {
  Wire.begin();
  accelGyroMag.initialize();
}

void AccelGyro_Update() {
  accelGyroMag.getMotion9(&AcX, &AcY, &AcZ, &GyX, &GyY, &GyZ, &MgX, &MgY, &MgZ);

  //Serial.print(MgX); Serial.print(" ");
  //Serial.print(MgY); Serial.print(" ");
  //Serial.print(MgZ); Serial.println(" ");

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
  yaw = (0.98 * (yaw + (yawGyro * DT))) + (0.02 * yawAcc);

  //yaw 계산
  //yawXY = atan2(MgY,MgX)*180/PI;

  //double XH = MgX*cos(pitch)+MgY*sin(roll)*sin(pitch)-MgZ*cos(roll)*sin(pitch);
  //double YH = MgY*cos(roll)+MgZ*sin(roll);

  //yaw = atan2(YH,XH);
  // yaw = atan2((double)MgY,(double)MgX)*180/PI;

  //while (yaw < -180) yaw += 180;
  //while (yaw > 360) yaw -= 180;

  /*yaw = atan2(MgY,MgX);
  if(yaw < 0)
    yaw+=2*PI;
  if(yaw > 2*PI)
    yaw -= 2*PI;
  yaw = yaw*180/PI;*/

  //Serial.print(" yaw: ");
  //Serial.println(yaw);

  //AxisPrint();
}

void AxisPrint() {
  Serial.print(" pitch: "); Serial.print(pitch);
  Serial.print(" roll: "); Serial.print(roll);
  Serial.print(" yaw: "); Serial.println(yaw);
}
