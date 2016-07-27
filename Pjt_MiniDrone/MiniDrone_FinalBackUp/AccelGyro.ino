#include "Wire.h"
#include "I2Cdev.h"
#include "MPU9150.h"

MPU9150 accelGyroMag;

int16_t AcX, AcY, AcZ; // I2C통신으로 받아오는 Accel X, Y, Z값 변수
int16_t GyX, GyY, GyZ; // I2C통신으로 받아오는 Gyro X, Y, Z값 변수

double rollGyro = 0, pitchGyro = 0, yawGyro = 0; // 각속도용 변수 
double rollAcc = 0, pitchAcc = 0, yawAcc = 0; // 가속도용 변수
double roll = 0, pitch = 0, yaw = 0; // 각속도, 가속도로 뽑아낸 최종 값의 변수
float DT = 0.01; // 적분하는 시간 


// AccelGyro 
void AccelGyro_init() {
  Wire.begin();
  accelGyroMag.initialize();
  while (1) {
    int16_t Connection = accelGyroMag.testConnection();
    if (Connection == true); {
      Serial.println("Connection Success");
      delay(500);
      break;
    }
  } 
  //             Accel                    Gyro
  // DLPF_CFG  Bandwidth  Delay  Bandwidth  Delay Samplerate
  //     3      44Hz,  4.0ms    |   42Hz,   4.8ms,  1kHz
  accelGyroMag.setDLPFMode(3);
}


// AccelGyro값을 받아오고 자이로는 각속도, 엑셀은 가속도로 변환 뒤 상보 필터를 사용하여 roll, pitch, yaw를 뽑아냄.
void AccelGyro_Update() {
  
  accelGyroMag.getMotion6(&AcX, &AcY, &AcZ, &GyX, &GyY, &GyZ);

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

  //AxisPrint();
}

void AxisPrint() {
  Serial.print(" pitch: "); Serial.print(pitch);
  Serial.print(" roll: "); Serial.print(roll);
  Serial.print(" yaw: "); Serial.println(yaw);
}
