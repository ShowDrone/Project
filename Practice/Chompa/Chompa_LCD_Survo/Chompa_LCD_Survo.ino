// Servo motor = 13
// Liquid crystal = 12,11,10,9,8,7
// TRIG = 6
// ECHO = 5
#include<Servo.h>
#include<LiquidCrystal.h>
Servo servo;
LiquidCrystal lcd (12,11,10,9,8,7);
int TRIG = 6;
int ECHO = 5;
void setup() {
lcd.begin(16,2);
servo.attach(13);
Serial.begin(9600);
pinMode(TRIG,OUTPUT);
pinMode(ECHO,INPUT);
}

int chompa;
void loop() {
  digitalWrite(TRIG,LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG,HIGH);
  delayMicroseconds(5);
  digitalWrite(TRIG,LOW);
  chompa = (pulseIn(ECHO,HIGH)/58.2);
  if(chompa<=30)
  {
    Serial.println(chompa);
    lcd.setCursor(12,0);
    lcd.print(chompa);
  }
  if(chompa<=10)
  {
    servo.write(180);
  }  
  else
  {
  servo.write(0);
  }
  delay(300);
}

