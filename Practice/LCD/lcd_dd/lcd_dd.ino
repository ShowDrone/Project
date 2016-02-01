/*
#define do1  65
#define re1  73
#define me1  82
#define fa1  87
#define sol1 98
*/

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int arr[] =  {100,200,300,400,500};

int ECHO = 10;
int TRIG = 9;
int Pi=8;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(TRIG,OUTPUT);
  pinMode(ECHO,INPUT);
  pinMode(Pi,OUTPUT);
}

void loop(){
   digitalWrite(TRIG,LOW);
 delayMicroseconds(2);
 digitalWrite(TRIG,HIGH);
 delayMicroseconds(5);
 digitalWrite(TRIG,LOW);
 int ji = (pulseIn(ECHO,HIGH)/58.2);
 if(ji < 10)
 {
   for(int num = 1; num < 6; num++)
   {
     tone(Pi,arr[num]);
   }
 }
 Serial.println("cm = " +(String)ji);

 lcd.setCursor(0,0);
 lcd.print(ji);
 delay(100);
  lcd.clear();
  }
