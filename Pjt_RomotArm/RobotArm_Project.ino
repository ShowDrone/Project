/*
///////////////////////////////////////////

Test Board    : Arduino Mega
Source Ver    : 1.0
Arduino Ver   : 1.6.2
Starting Date : 2016.1.6

*Main
Arduino Mega  x1
Servo motor   x2
Step motor    x3
Step driver   x3  , ULN2003
HC-06         x1  , Slave

*DIY Controller
HC-05         x1  , Master
LED           x3  , Red/Green/Blue
Joystick      x1
MPU6050       x1
DIY Frame     x1  , 3d modeling

///////////////////////////////////////////
*/

#define A_in1 2
#define A_in2 3
#define A_in3 4
#define A_in4 5
#define B_in1 6
#define B_in2 7
#define B_in3 8
#define B_in4 9
#define C_in1 10
#define C_in2 11
#define C_in3 12
#define C_in4 13

#include<Servo.h>
#include<Stepper.h>

const int one_round = 64; // one step = 5.625

// 2048 한바퀴
// 360도를 도는데 100이 필요
Stepper myStepperA (one_round,A_in4,A_in2,A_in3,A_in1);
Stepper myStepperB (one_round,B_in4,B_in2,B_in3,B_in1);
Stepper myStepperC (one_round,C_in4,C_in2,C_in3,C_in1);


void setup() {
  Serial.begin(38400);
  myStepperA.setSpeed(360);
  myStepperB.setSpeed(10);
  myStepperC.setSpeed(10);
}

// 한번돌때22.5번 4번돌때90
int time_pre = 0;

void loop() {
  //for(int i=0;i<32;i++)
  myStepperA.step(64);
  //myStepperB.step(one_round);
  //myStepperC.step(one_round);
  //delay(500);
  //myStepperA.step(-300);
  //delay(500);
}
