 
// 속도 제어 BLDC 2개 / 방향 제어 DC 4개 / 랜딩 기어 2개

#define SPEED_MAX 255 //예시
#define SPEED_MIN 0
#define XY_MIN -30 // 상보필터 값에 맞게 셋팅
#define XY_MAX 30 // 
#define ROLL_MIN -30
#define ROLL_MAX 30
#define YAW_MIN -20
#define YAW_MAX 20
#define DC1_A 3 // direction
#define DC1_B 5 // direction
#define DC2_A 6 // direction
#define DC2_B 9 // direction
#define DC3_A 0 // LANDING
#define DC3_B 1 // LANDING
#define BLDC_A 10 // Velocity
#define BLDC_B 11 // Velocity
double const XY_P = 0.85, XY_I = 0.1, XY_D = 0.15;
double const ROLL_P = 1, ROLL_I = 0.05, ROLL_D = 1;
double const YAW_P = 1, YAW_I = 0.05, YAW_D = 1;
double XY_ERR, XY_PERR, XY_ERR_P, XY_ERR_I = 0, XY_ERR_D, XY_PID;
double ROLL_ERR, ROLL_PERR, ROLL_ERR_P, ROLL_ERR_I = 0, ROLL_ERR_D, ROLL_PID;
double YAW_ERR, YAW_ERR_P, YAW_ERR_I = 0, YAW_PI;
double xy_PRE, roll_PRE;
int xy_Ctl, roll_Ctl, yaw_Ctl;
int xy_Ctl_Last, roll_Ctl_Last, yaw_Ctl_Last;
int DC1S_A, DC1S_B, DC2S_A, DC2S_B;
int BLDC1_S, BLDC2_S, motSpeed;
boolean level = false;
int16_t dcSpeed = 200; // 파라미터

#include<SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU9150.h"
MPU9150 accelGyroMag;

int16_t AcX, AcY, AcZ;
int16_t GyX, GyY, GyZ;
double rollGyro, pitchGyro, yawGyro;
double rollAcc, pitchAcc, yawAcc;
double pitch, roll, yaw;
float DT = 0.01;

int8_t buf[8] = {0,};
int8_t Lastbuf[8] = {0,};
boolean Loop = true;
boolean Emergency = false;

void setup() {
  Serial.begin(19200);
  AccelGyro_init();
  Control_UART_init();
  PID_init();
}

int time_pre = 0;

void loop() {
  int time = millis() - time_pre;
  time_pre = millis();
  //Serial.print("time: "); Serial.print(time);
  PID_Update();
}

void PID_init() {
  pinMode(DC1_B, OUTPUT);
  pinMode(DC1_A, OUTPUT);
  pinMode(DC2_B, OUTPUT);
  pinMode(DC2_A, OUTPUT);
  pinMode(DC3_B, OUTPUT);
  pinMode(DC3_A, OUTPUT);
  pinMode(BLDC_B, OUTPUT);
  pinMode(BLDC_A, OUTPUT);
  //모터 안정화
  MOT_Stop();
}

int16_t uartTime = 0;
int16_t emergencyTime = 0;
int16_t emergencySpeed = 0;

void PID_Update() {
  if (uartTime + 5 < millis()) {
    Control_UART_Update();
    uartTime = millis();
  }

  xy_Ctl = map(buf[2], 88, 168, XY_MIN, XY_MAX);
  roll_Ctl = map(buf[1], 88, 168, ROLL_MIN, ROLL_MAX);
  yaw_Ctl = map(buf[4], 70, 176, YAW_MIN, YAW_MAX);

  if (Emergency == false)
    motSpeed = buf[3];

  if (Emergency == true) {
    if (motSpeed >= 0) {
      if (motSpeed >= 30)
        emergencySpeed = motSpeed / 10;
      else
        emergencySpeed = motSpeed;
      if (emergencyTime + 1000 > millis()) {
        motSpeed -= emergencySpeed;
        emergencyTime = millis();
      }
    }
  }

  if (xy_Ctl < XY_MIN || xy_Ctl > XY_MAX) {
    xy_Ctl = xy_Ctl_Last;
  }
  if (roll_Ctl < ROLL_MIN || roll_Ctl > ROLL_MAX) {
    roll_Ctl = roll_Ctl_Last;
  }
  if (yaw_Ctl < YAW_MIN || yaw_Ctl > ROLL_MAX) {
    yaw_Ctl = yaw_Ctl_Last;
  }

  xy_Ctl_Last = xy_Ctl;

  roll_Ctl_Last = roll_Ctl;
  yaw_Ctl_Last = yaw_Ctl;

  AccelGyro_Update();

  if (Emergency == true) {
    pitch = 0;
    roll = 0;
    yaw = 0;
  }

  //PITCH
  //XY_ERR = xy_Ctl - pitch; //목표값 - 현재값
  XY_ERR = 0 - pitch; //목표값 - 현재값
  XY_PERR = (pitch - xy_PRE); //DT; //  기울기 차이/샘플링 주기
  XY_ERR_P = XY_ERR * XY_P; // 오차*P게인
  XY_ERR_I = XY_ERR_I + (XY_ERR * XY_I) * DT;
  Limit_I(&XY_ERR_I);
  XY_ERR_D = XY_PERR * XY_D; // 기울기 차이*D게인
  XY_PID = XY_ERR_P + XY_ERR_I + XY_ERR_D;
  xy_PRE = pitch;

  //ROLL
  ROLL_ERR = roll_Ctl - roll;
  ROLL_PERR = (roll - roll_PRE) / DT;
  ROLL_ERR_P = ROLL_ERR * ROLL_P;
  ROLL_ERR_I = ROLL_ERR_I + (ROLL_ERR * ROLL_I) * DT;
  Limit_I(&ROLL_ERR_I);
  ROLL_ERR_D = ROLL_PERR * ROLL_D;
  ROLL_PID = ROLL_ERR_P + ROLL_ERR_I + ROLL_ERR_D;
  roll_PRE = roll;

  //YAW
  YAW_ERR = yaw_Ctl - yaw;
  YAW_ERR_P = YAW_ERR * YAW_P;
  YAW_ERR_I = YAW_ERR_I + (YAW_ERR * YAW_I) * DT;
  Limit_I(&YAW_ERR_I);
  YAW_PI = YAW_ERR_P + YAW_ERR_I;

  Limit_Speed(&motSpeed);

  if (motSpeed < 1050) {
    level = true;
    MOT_Stop(); // 로터부 수평
  }

  if (XY_PID > 0) {
    DC2S_A = dcSpeed + abs(XY_PID);
    DC2S_B = 0;
    //DC2S_A = 0;
    //DC2S_B = dcSpeed+abs(XY_PID);
  }

  else if (XY_PID < 0) {
    DC2S_A = 0;
    DC2S_B = dcSpeed + abs(XY_PID);
    //DC2S_A = dcSpeed+abs(XY_PID);
    //DC2S_B = 0;
  }

  if (YAW_PI > 0) {
    DC1S_A = dcSpeed + abs(YAW_PI);
    DC1S_B = 0;
    //DC2S_A = 0;
    //DC2S_B = dcSpeed+abs(XY_PID);
  }

  else if (YAW_PI < 0) {
    DC1S_A = 0;
    DC1S_B = dcSpeed + abs(YAW_PI);
    //DC2S_A = dcSpeed+abs(XY_PID);
    //DC2S_B = 0;
  }

  //Serial.print(" PID :"); Serial.println(YAW_PI);
  //Serial.print(" DC2_A: "); Serial.print(DC2S_A);
  //Serial.print(" DC2_B: "); Serial.println(DC2S_B);

  MOT_Update();
}

inline void MOT_Update() {
  //analogWrite(DC1_A, DC1S_A);
  //analogWrite(DC1_B,DC1S_B);
  analogWrite(DC2_A, DC2S_A);
  analogWrite(DC2_B, DC2S_B);
  //analogWrite(BLDC_A,motSpeed);
  //analogWrite(BLDC_B,motSpeed);
}

void MOT_Stop() {
}

void Limit_I(double *value) {
  if (*value >= 100)
    *value = 100;
  else if (*value <= -100)
    *value = -100;
}

void Limit_Speed(int *value) {
  if (*value >= SPEED_MAX)
    *value = SPEED_MAX;
  else if (*value <= SPEED_MIN)
    *value = SPEED_MIN;
}

void Control_UART_init() {
  mySerial.begin(19200);
}

void Control_UART_Update() {
  if (mySerial.available() < 1) {
    buf[1] = 129; buf[2] = 129;
    buf[3] = 0; buf[4] = 129;
    Serial.println(" No control Data ");
    Emergency = true;
  }
here:
  while (mySerial.available()) {
    for (int j = 0; j < 8; j++) {
      buf[j] = mySerial.read();
    }
    if (buf[5] != 0) {
      goto here;
    }
    if (Loop) {
      for (int i = 0; i < 8; i++) {
        Lastbuf[i] = buf[i];
      }
      Loop = false;
    }
    if ((buf[1] > 168) || (buf[1] < 88)) {
      buf[1] = Lastbuf[1];
    }
    if ((buf[2] > 168) || (buf[2] < 88)) {
      buf[2] = Lastbuf[2];
    }
    if ((buf[3] > 255) || (buf[3] < 0)) {
      buf[3] = Lastbuf[3];
    }
    if ((buf[4] > 176) || (buf[4] < 80)) {
      buf[4] = Lastbuf[4];
    }
  }

  if (!Loop) {
    for (int i = 0; i < 8; i++) {
      Lastbuf[i] = buf[i];
    }
  }
  Serialreset();
  Serialprint();
}

void Serialreset() {
  mySerial.end();
  mySerial.begin(19200);
}

void Serialprint() {
  for (int i = 1; i < 5; i++) {
    Serial.print(" "); Serial.print(buf[i]); Serial.print(" ");
  }
  Serial.println();
}

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
  accelGyroMag.setDLPFMode(3);
}

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
