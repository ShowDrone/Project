#include <DFRobot.h>
#include <IIC1.h>

DFrobotEdison motor;

int speedLeft = 200;
int speedRight = 200;

void setup() {
}

void loop() {
  
  Forward();    // 앞으로
  delay(3000);  // 3초 딜레이
  Reverse();    // 뒤로
  delay(3000);
  TurnLeft();   // 왼쪽으로
  delay(3000);
  TurnRight();  // 오른쪽으로
  delay(3000);
  Stop();       // 멈추고
  delay(3000);
}

void Forward(){
  motor.wheelEnSlv(ClockwiseM1); // M1모터를 시계 방향으로 회전
  controlMotor(M1, speedLeft);
  motor.wheelEnSlv(AntiClockwiseM2); // M2모터를 반시계 방향으로 회전
  controlMotor(M2, speedRight);   
}

void Reverse(){
  motor.wheelEnSlv(AntiClockwiseM1); // M1모터를 반시계 방향으로 회전
  controlMotor(M1, speedLeft);
  motor.wheelEnSlv(ClockwiseM2); // M2모터를 시계 방향으로 회전
  controlMotor(M2, speedRight);    
}

void TurnLeft(){
  motor.wheelEnSlv(AntiClockwiseM1); // M1모터를 반시계 방향으로 회전
  controlMotor(M1, speedLeft);
  motor.wheelEnSlv(AntiClockwiseM2); // M2모터를 반시계 방향으로 회전
  controlMotor(M2, speedRight);   
}

void TurnRight(){
  motor.wheelEnSlv(ClockwiseM1); // M1모터를 시계 방향으로 회전
  controlMotor(M1, speedLeft);
  motor.wheelEnSlv(ClockwiseM2); // M2모터를 시계 방향으로 회전
  controlMotor(M2, speedRight);   
}

void Stop(){
  motor.wheelEnSlv(ClockwiseM1); //  M1모터를 시계 방향으로 회전
  controlMotor(M1, 0);
  motor.wheelEnSlv(AntiClockwiseM2); // M2모터를 반시계 방향으로 회전
  controlMotor(M2, 0);   
}
