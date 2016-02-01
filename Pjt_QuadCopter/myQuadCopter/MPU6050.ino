#include<Wire.h>
const int MPU=0x68;  // MPU6050 I2C통신줏소
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
double rollGyro,pitchGyro,yawGyro;
double rollAcc,pitchAcc,yawAcc;
double pitch, roll, yaw;
unsigned long msec=0;
float dt;
float DT = 0.01;

void MPU6050_setup(){
 
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  
}

void MPU6050_loop(){  
  
  //시간의 변화량
  dt = (millis()-msec)/1000.0;
  msec = millis();
  
  // 가속도, 자이로 계산
  MPU6050_cal();
  
  // 가속도, 자이로 평균 내기
  
  //가속도
  rollAcc = -atan2(AcX,AcZ)*180/PI; // 라디안 값 to 각도값
  pitchAcc = atan2(AcY,AcZ)*180/PI; // 라디안 값 to 각도값
  yawAcc = atan2(AcX,AcY)*180/PI; // 라디안 값 to 각도값
  
  //자이로값 셋팅
  rollGyro = GyY/131.07; // 16비트 값 to 250'/sec
  pitchGyro = GyX/131.07; // 16비트 값 to 250'/sec
  yawGyro = GyZ/131.07; // 18비트 값 to 250'/sec
  
  ////////////////상보필터////////////////
  /*
  pitch = (0.98 * (pitch + (pitchGyro*dt))) + (0.02*pitchAcc);
  roll = (0.98 * (roll + (rollGyro*dt))) + (0.02*rollAcc);
  yaw = (0.98 * (yaw + (yawGyro*dt))) + (0.02*yawAcc);
  */
  pitch = (0.95 * (pitch + (pitchGyro*DT))) + (0.05*pitchAcc);
  roll = (0.95 * (roll + (rollGyro*DT))) + (0.05*rollAcc);
  yaw = (0.95 * (yaw + (yawGyro*DT))) + (0.05*yawAcc);

  Serial.print("dt:"); Serial.print(DT);
  Serial.print(" pitch: "); Serial.print(pitch);
  Serial.print(" roll: "); Serial.print(roll);
  Serial.print("  yaw: "); Serial.println(yaw);
  
  /*Serial.print("AcX = "); Serial.print(AcX);
  Serial.print(" | AcY = "); Serial.print(AcY);
  Serial.print(" | AcZ = "); Serial.print(AcZ);
  Serial.print(" | GyX = "); Serial.print(GyX);
  Serial.print(" | GyY = "); Serial.print(GyY);
  Serial.print(" | GyZ = "); Serial.println(GyZ);*/
}

void MPU6050_cal(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
}
