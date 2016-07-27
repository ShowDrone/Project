
// TRIG1 & ECHO1 == Left WAVE
// TRIG2 & ECHO2 == Front WAVE
// TRIG3 & ECHO3 == Right WAVE
#define TRIG1 12
#define TRIG2 2
#define TRIG3 10
#define ECHO1 13
#define ECHO2 3
#define ECHO3 11
#define LED 9

#include <DFRobot.h>
#include <IIC1.h>
#include <Intel_Edison_BT_SPP.h>
Intel_Edison_BT_SPP spp = Intel_Edison_BT_SPP();

int Wave_Front_Data = 0;
int Wave_Right_Data = 0;
int Wave_Left_Data = 0;
int search_distance = 15;
boolean Control_Manual = false;
boolean Control_Auto = false;
String BT_Value = "";

DFrobotEdison motor;

void setup() {
  
  //Power ON
  pinMode(LED,OUTPUT);
  digitalWrite(LED,HIGH);
  
  // Serial SET
  Serial.begin(115200);
  
  // TRIG SET
  pinMode(TRIG1,OUTPUT);
  pinMode(TRIG2,OUTPUT);
  pinMode(TRIG3,OUTPUT);
  
  // ECHO SET
  pinMode(ECHO1,INPUT);
  pinMode(ECHO2,INPUT);
  pinMode(ECHO3,INPUT);
  
  // SPP SET
  spp.open();
  
  delay(2000);
  digitalWrite(LED,LOW);
}

void loop() {
  
  // 값 체크
  ssize_t size = spp.read();
  
  // 초음파 셋팅
  Wave_Left_Begin();
  Wave_Left_Data = (pulseIn(ECHO1,HIGH)/58.2);
  Wave_Front_Begin();
  Wave_Front_Data = (pulseIn(ECHO2,HIGH)/58.2);
  Wave_Right_Begin();
  Wave_Right_Data = (pulseIn(ECHO3,HIGH)/58.2);
  Serial.print(Wave_Front_Data);
  Serial.print("   ");
  Serial.print(Wave_Left_Data);
  Serial.print("   ");
  Serial.println(Wave_Right_Data);
  
  //블루투스 시작
  if(size != -1)
  {
    BT_Value = spp.getBuf();
    
    if(BT_Value.equals("CA"))
    {
      Serial.println("Auto ON");
      Stop();
      Control_Auto = true;
      Control_Manual = false;
    }
    else if(BT_Value.equals("CM"))
    {
      Serial.println("Manual ON");
      Stop();
      Control_Auto = false;
      Control_Manual = true;
    }
    
    // 수동 주행
    if(Control_Manual == true)
    {
      if(BT_Value.equals("w")) //앞으로
      {
        Serial.println("Forward");
        Forward();
      }
      else if(BT_Value.equals("a")) //왼쪽으로
      {
        Serial.println("Left");
        TurnLeft();
      }
      else if(BT_Value.equals("d")) //오른쪽으로
      {
        Serial.println("Right");
        TurnRight();
      }
      else if(BT_Value.equals("b")) //뒤로
      {
        Serial.println("Reverse");
        Reverse();
      }
      else if(BT_Value.equals("n")) //스탑
      {
        Serial.println("stop");
        Stop();
      }
    }
    // 자동주행
    else if(Control_Auto == true)
    {
      if(Wave_Front_Data > search_distance)
      { 
        Forward();
      }
      else if(Wave_Front_Data <= search_distance)
      {
        if(Wave_Left_Data<search_distance && Wave_Right_Data>search_distance)
        {
          TurnRight();
          //delay(2300);
        }
        else if(Wave_Left_Data>search_distance && Wave_Right_Data<search_distance)
        {
         TurnLeft();
         //delay(2300);
         }
        else if(Wave_Left_Data>search_distance && Wave_Right_Data>search_distance)
        {
          TurnRight();
          //delay(3300);
          Serial.println("****Right****");
        }
        else if(Wave_Left_Data<search_distance && Wave_Right_Data<search_distance) 
        {
          Serial.println("Stop");
          Stop();
          delay(1500);
          Reverse();
          delay(3000);
          TurnRight();
          delay(2300);
        }
    }
    else if(Wave_Left_Data==0&&Wave_Right_Data==0&&Wave_Front_Data==0)
    {
       Stop();
    }
    } // if(Control_Auto == true) 닫는 괄호
      
  } // (size != -1) 닫는 괄호
} // loop 닫는 괄호

void Wave_Left_Begin() {
  digitalWrite(TRIG1,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG1,LOW);
}

void Wave_Front_Begin() {
  digitalWrite(TRIG2,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG2,LOW);
}


void Wave_Right_Begin() {
  digitalWrite(TRIG3,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG3,LOW);
}



void Reverse(){
  Serial.println("Reverse");
  motor.wheelEnSlv(AntiClockwiseM1);
  controlMotor(M1, 255);
  motor.wheelEnSlv(ClockwiseM2);
  controlMotor(M2, 255);    
}

void Forward(){
  Serial.println("Forward");
  motor.wheelEnSlv(ClockwiseM1);
  controlMotor(M1, 255);
  motor.wheelEnSlv(AntiClockwiseM2);
  controlMotor(M2, 255);   
}

void TurnRight(){
  Serial.println("Right");
  motor.wheelEnSlv(AntiClockwiseM1);
  controlMotor(M1, 255);
  motor.wheelEnSlv(AntiClockwiseM2);
  controlMotor(M2, 255);   
}

void TurnLeft(){
  Serial.println("Left");
  motor.wheelEnSlv(ClockwiseM1);
  controlMotor(M1, 255);
  motor.wheelEnSlv(ClockwiseM2);
  controlMotor(M2, 255);   
}

void Stop(){
  motor.wheelEnSlv(ClockwiseM1);
  controlMotor(M1, 0);
  motor.wheelEnSlv(AntiClockwiseM2);
  controlMotor(M2, 0);   
}
