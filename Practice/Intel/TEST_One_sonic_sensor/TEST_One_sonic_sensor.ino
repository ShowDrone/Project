#define TRIG 12
#define ECHO 13

#include <DFRobot.h>
#include <IIC1.h>
#include <Intel_Edison_BT_SPP.h>
Intel_Edison_BT_SPP spp = Intel_Edison_BT_SPP();

int Wave_Data = 0;
int search_distance = 18;
boolean Control_Manual = false;
boolean Control_Auto = false;
boolean while_check = false;
String BT_Value = "";
String BT_Value_cp = "";
DFrobotEdison motor;

void setup() {
  // Serial SET
  Serial.begin(115200);
  // TRIG SET
  pinMode(TRIG,OUTPUT);
  // ECHO SET
  pinMode(ECHO,INPUT);
  // SPP SET
  spp.open();
}

void loop() {
  
  // 값 체크
  ssize_t size = spp.read();
  
  /*// 초음파 셋팅
  Wave_Begin();
  Wave_Data = pulseIn(ECHO,HIGH)/58.8;
  Serial.println(Wave_Data);*/
  
  //블루투스 시작
  if(size != -1)
  {
    BT_Value = spp.getBuf(); // spp.getBuf() == const char*   
    
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

  // 자동주행
  if(Control_Auto == true)
  {
      if(BT_Value_cp.equals("CM"))
      {
        Control_Auto = false;
        Control_Manual = true;
      }
      
      Wave_Begin(); //노이즈 방지
      Wave_Data = pulseIn(ECHO,HIGH)/58.8; //340*Wave_Data)/10000)/2;
      Serial.println(Wave_Data);
      
      if(Wave_Data > search_distance)
      { 
          Serial.println("Forward");
          Forward();
      }      
      else if(Wave_Data <= search_distance)
      {
          Auto_Reverse();
          delay(1100);
          Auto_TurnRight();
          delay(800);
          Stop();
          delay(500);
      }
      
 } // if(Control_Auto == true)
    
      // 수동 주행
    if(Control_Manual == true)
    {
      Serial.println("Manual");
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
        Serial.println("Manual_Right");
        Manual_TurnRight();
      }
      else if(BT_Value.equals("b")) //뒤로
      {
        Serial.println("Reverse");
        Manual_Reverse();
      }
      else if(BT_Value.equals("n")) //스탑
      {
        Serial.println("stop");
        Stop();
      }
    } // 수동 주행 if문
  } // (size != -1) 
} // loop

void Wave_Begin() {
  digitalWrite(TRIG,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG,LOW);
  delayMicroseconds(10);
}


void Manual_Reverse(){
  Serial.println("Reverse");
  motor.wheelEnSlv(AntiClockwiseM1);
  controlMotor(M1, 255);
  motor.wheelEnSlv(ClockwiseM2);
  controlMotor(M2, 255);    
}

void Auto_Reverse(){
  Serial.println("Reverse");
  motor.wheelEnSlv(AntiClockwiseM1);
  controlMotor(M1, 130);
  motor.wheelEnSlv(ClockwiseM2);
  controlMotor(M2, 130);    
}

void Forward(){
  Serial.println("Forward");
  motor.wheelEnSlv(ClockwiseM1);
  controlMotor(M1, 255);
  motor.wheelEnSlv(AntiClockwiseM2);
  controlMotor(M2, 255);   
}

void Manual_TurnRight(){
  Serial.println("Right");
  motor.wheelEnSlv(AntiClockwiseM1);
  controlMotor(M1, 255);
  motor.wheelEnSlv(AntiClockwiseM2);
  controlMotor(M2, 255);   
}

void Auto_TurnRight() {
  Serial.println("Auto_Right");
  motor.wheelEnSlv(AntiClockwiseM1);
  controlMotor(M1, 120);
  motor.wheelEnSlv(AntiClockwiseM2);
  controlMotor(M2, 130);
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
