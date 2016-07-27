#include <DFRobot.h>
#include <IIC1.h>

int speedLeft = 200;
int speedRight = 200;

DFrobotEdison motor;

void setup() {
  Serial.begin(115200);
  Forward();
  delay(200);
  Stop();
}

void loop() {
  Forward();
  delay(3000);
  Reverse();
  delay(3000);
  TurnLeft();
  delay(3000);
  TurnRight();
  delay(3000);
  Stop();
  delay(3000);
}

void Forward(){
  motor.wheelEnSlv(ClockwiseM1);
  controlMotor(M1, speedLeft);
  motor.wheelEnSlv(AntiClockwiseM2);
  controlMotor(M2, speedRight);   
}

void Reverse(){
  motor.wheelEnSlv(AntiClockwiseM1);
  controlMotor(M1, speedLeft);
  motor.wheelEnSlv(ClockwiseM2);
  controlMotor(M2, speedRight);    
}

void TurnLeft(){
  motor.wheelEnSlv(AntiClockwiseM1);
  controlMotor(M1, speedLeft);
  motor.wheelEnSlv(AntiClockwiseM2);
  controlMotor(M2, speedRight);   
}

void TurnRight(){
  motor.wheelEnSlv(ClockwiseM1);
  controlMotor(M1, speedLeft);
  motor.wheelEnSlv(ClockwiseM2);
  controlMotor(M2, speedRight);   
}

void Stop(){
  motor.wheelEnSlv(ClockwiseM1);
  controlMotor(M1, 0);
  motor.wheelEnSlv(AntiClockwiseM2);
  controlMotor(M2, 0);   
}
