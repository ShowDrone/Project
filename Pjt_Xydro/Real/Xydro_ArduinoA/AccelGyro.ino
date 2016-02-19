
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU9150.h"

MPU9150 accelGyroMag;

int16_t AcX, AcY, AcZ;
int16_t GyX, GyY, GyZ;

double rollGyro = 0;
double pitchGyro = 0;
double yawGyro = 0;
double rollAcc = 0;
double pitchAcc = 0;
double yawAcc = 0;
double pitch = 0;
double roll = 0;
double yaw = 0;
float DT = 0.01;

void AccelGyro_init() {
  Wire.begin();
  accelGyroMag.initialize();
}

void AccelGyro_Update() {
    accelGyroMag.getMotion6(&AcX,&AcY,&AcZ,&GyX,&GyY,&GyZ);

  //가속도 계산 Rad to Deg
  pitchAcc = atan2(AcY, AcZ) * 180 / PI; // arctan(X,Z)
  rollAcc = -atan2(AcX, AcZ) * 180 / PI; // arctan(Y,Z);
  yawAcc = atan2(AcX, AcY) * 180 / PI; // arctan(X,Y);

  //자이로 계산
  pitchGyro = GyX / 131.07; // 16비트 값 to 250'/sec
  rollGyro = GyY / 131.07;
  yawGyro = GyZ / 131.07;


  //상보필터
  pitch = (0.98 * (pitch + (pitchGyro * DT))) + (0.02 * pitchAcc);
  roll = (0.98 * (roll + (rollGyro * DT))) + (0.02 * rollAcc);
  yaw = (0.98 * (yaw = (yawGyro * DT))) + (0.02 * yawAcc);

  //yaw 계산
  //yawXY = atan2(MgY, MgX) * 180 / PI + 180;

  //double XH = MgX*cos(pitch)+MgY*sin(roll)*sin(pitch)-MgZ*cos(roll)*sin(pitch);
  //double YH = MgY*cos(roll)+MgZ*sin(roll);

  AxisPrint();
}

void AxisPrint() {
  Serial.print(" pitch: "); Serial.print(pitch);
  Serial.print(" roll: "); Serial.print(roll);
  Serial.print(" yaw: "); Serial.println(yaw);
}
