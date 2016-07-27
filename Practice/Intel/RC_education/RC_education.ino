
/*
Title    : RC Car_Ultrasonic ver
Maker    : Lee Seung Hyun
Date     : 2015/08/20
Platform : Intel Edison Romeo Board
*/


#include <DFRobot.h>
#include <IIC1.h>
#include <Wire.h>
#include <Intel_Edison_BT_SPP.h>

DFrobotEdison motor;
Intel_Edison_BT_SPP spp = Intel_Edison_BT_SPP();

//Ultrasonic settings
#define WAVE_TRIG1 2
#define WAVE_ECHO1 3
#define WAVE_TRIG2 13
#define WAVE_ECHO2 12
#define WAVE_TRIG3 5
#define WAVE_ECHO3 4
#define SW1 8
#define SW2 9

void setup() {
        
	Serial.begin(115200);
	Serial.println("Intel Edison BT SPP test!");
	spp.open();

        // TRIG SET
        pinMode(WAVE_TRIG1,OUTPUT);
        pinMode(WAVE_TRIG2,OUTPUT);
        pinMode(WAVE_TRIG3,OUTPUT);
        
        // ECHO SET
        pinMode(WAVE_ECHO1,INPUT);
        pinMode(WAVE_ECHO2,INPUT);
        pinMode(WAVE_ECHO3,INPUT);
        
        // SW SET
        pinMode(SW1,INPUT_PULLUP);
        pinMode(SW2,INPUT_PULLUP);
        
}

int WAVE_Front = 0;
int WAVE_Left = 0;
int WAVE_Right = 0;
int BT_Value = 0;
int SW1_Value = 0;
int SW2_Value = 0;

boolean Control_Auto = false;
boolean Control_Manual = false;
void loop() {
        
        //Ultra wave begin & inserting Date
        WAVE_Front_begin();
        WAVE_Front = pulseIn(WAVE_ECHO1,HIGH)/58.2;
     
        WAVE_Left_begin();
        WAVE_Left = pulseIn(WAVE_ECHO2,HIGH)/58.2;
        
        WAVE_Right_begin();
        WAVE_Right = pulseIn(WAVE_ECHO3,HIGH)/58.2;
        
        //Bluetooth Data reading
	ssize_t size = spp.read();
       
        
       
        //SW1 setting
        SW1_Value = digitalRead(SW1);
        SW2_Value = digitalRead(SW2);
        
        if(SW1_Value == 0) //Manual
        {
          Control_Auto = false;
          Control_Manual = true;
        }
        else if(SW2_Value == 0) //Auto
        {
          Control_Manual = false;
          Control_Auto = true;
        }
       
        if(Control_Manual == true)
        {
	if (size != -1) {
          if(BT_Value == 1) { // Front;
          }
          else if(BT_Value == 2) { // LEFT
	  }
          else if(BT_Value == 3) { //Right
          }
          else if(BT_Value == 4) { // Back
          }
          else if(BT_Value == 5) { // Stop
          }

        else
                delay(300);
        } // if(size != -1) exit
        }
        else if(Control_Auto == true) 
        {
          if(WAVE_Front < 15)
          {
            if(WAVE_Left > 15 && WAVE_Right > 15)
            {
              TurnRight();
            }
            else if(WAVE_Left < 15 && WAVE_Right > 15)
            {
              TurnRight();
            }
            else if(WAVE_Left > 15 && WAVE_Right < 15)
            {
              TurnLeft();
            }
            else if(WAVE_Left < 15 && WAVE_Right < 15)
            { 
              Reverse();
              delay(2000);
              TurnRight();
              delay(1000);
            }
          }
        }
        
}


void WAVE_Front_begin() {
        digitalWrite(WAVE_TRIG1,LOW);
        delayMicroseconds(2);  
        digitalWrite(WAVE_TRIG1,HIGH);
        delayMicroseconds(10);
        digitalWrite(WAVE_TRIG1,LOW);

}

void WAVE_Left_begin() {
        digitalWrite(WAVE_TRIG2,LOW);
        delayMicroseconds(2);  
        digitalWrite(WAVE_TRIG2,HIGH);
        delayMicroseconds(10);
        digitalWrite(WAVE_TRIG2,LOW);
}

void WAVE_Right_begin() {
        digitalWrite(WAVE_TRIG3,LOW);
        delayMicroseconds(2);  
        digitalWrite(WAVE_TRIG3,HIGH);
        delayMicroseconds(10);
        digitalWrite(WAVE_TRIG3,LOW);
}

void Forward(){
  motor.wheelEnSlv(ClockwiseM1);
  controlMotor(M1, 210);
  motor.wheelEnSlv(AntiClockwiseM2);
  controlMotor(M2, 210);   
}

void Reverse(){
  motor.wheelEnSlv(AntiClockwiseM1);
  controlMotor(M1, 160);
  motor.wheelEnSlv(ClockwiseM2);
  controlMotor(M2, 160);    
}

void TurnLeft(){
  motor.wheelEnSlv(AntiClockwiseM1);
  controlMotor(M1, 30);
  motor.wheelEnSlv(AntiClockwiseM2);
  controlMotor(M2, 30);   
}

void TurnRight(){
  motor.wheelEnSlv(ClockwiseM1);
  controlMotor(M1, 30);
  motor.wheelEnSlv(ClockwiseM2);
  controlMotor(M2, 30);   
}

void Stop(){
  motor.wheelEnSlv(ClockwiseM1);
  controlMotor(M1, 0);
  motor.wheelEnSlv(AntiClockwiseM2);
  controlMotor(M2, 0);   
}
