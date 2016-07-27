#define TRIG 12 // TRIG 핀
#define ECHO 13 // EHCO 핀

// 라이브러리
#include <DFRobot.h>
#include <IIC1.h>
#include <Intel_Edison_BT_SPP.h>
Intel_Edison_BT_SPP spp = Intel_Edison_BT_SPP();

// 변수선언
int Wave_Data = 0;
int search_distance = 10;
int time1_check = 0;
int time1 = 0;
boolean while_check = false;
boolean Control_Manual = false;
boolean Control_Auto = false;
String BT_Value = "";
String BT_Value_cp = ".";
DFrobotEdison motor;
void setup() {
  Serial.begin(115200); // 하드웨어 - PC간의 직렬 통신
  Serial.println("Hello Edison");

  pinMode(TRIG,OUTPUT); // 초음파를 보내는 핀이니 OUTPUT
  pinMode(ECHO,INPUT); // 보낸 초음파를 받는 핀이니 INPUT

  spp.open(); // 가상 시리얼 환경 오픈
}

void loop() {

  // 에디슨이 동작될 때부터 시간 계산
  time1 = millis()/1000;
  // 값 체크
  ssize_t size = spp.read();
  
  //블루투스 시작
  if(size != -1)
  {
    BT_Value = spp.getBuf(); // spp.getBuf() == const char*
    
    if(BT_Value.equals("time")) // 객체를 비교하는 equals()
    {
       if(time1_check >= time1) // 시간 증가를 여러번 눌렀을 시
       {
         time1_check += 5;
         Serial.println(time1_check);
       }
       else if(time1_check < time1) // 시간 증가를 한번 눌렀을 시
      {
         time1_check = time1+5;
         Serial.println(time1_check);
      }
    }
    if(BT_Value.equals("CA")) // Auto 클릭 
    {
      Serial.println("Auto ON");
      Stop();
      Control_Auto = true;
      Control_Manual = false;
      if(time1_check>=time1)
      {
         while_check = true;
      }
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
        while(while_check)
        { 
          time1 = millis()/1000; // while문에서의 millis
          Wave_Begin(); //노이즈 방지
          Wave_Data = pulseIn(ECHO,HIGH)/58.8; // 340*Wave_Data)/10000)/2;
          if(Wave_Data > search_distance) // 일정 거리안에 물체가 없으면
          { 
            Forward();
            Serial.println("Forward");
          }      
          else if(Wave_Data <= search_distance)  // 일정 거리안에 물체가 있으면
          {
            Stop();
            delay(500);
            Auto_Reverse();
            delay(500);
            Auto_TurnRight();
            delay(500);
          }
          if(time1_check<=time1) // 시간됐으면 while_check = false
          {
              Stop();
              delay(100);
              Serial.println("Stop");
              while_check = false;
              Control_Auto = false;
          }
        }
 } // if(Control_Auto == true) 닫는 괄호
    
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
}

void Auto_Reverse(){
  Serial.println("Reverse");
  motor.wheelEnSlv(AntiClockwiseM1);
  controlMotor(M1, 150);
  motor.wheelEnSlv(ClockwiseM2);
  controlMotor(M2, 150);    
}

void Forward(){
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
  controlMotor(M2, 120);
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
