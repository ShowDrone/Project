#include<Servo.h>
Servo myServo;
#include<LiquidCrystal.h>
LiquidCrystal lcd(8,7,6,5,4,3);
int sw_left = 12;
int sw_right = 11;
int TRIG = 10; // OUTPUT
int ECHO = 9; //INPUT
void setup() {
  myServo.attach(13); // Servo begin
  pinMode(sw_right,2); //sw_right INPUT_PULLUP
  pinMode(sw_left,2);  //sw_left INPUT_PULLUP
  pinMode(TRIG,OUTPUT);
  pinMode(ECHO,INPUT); 
  Serial.begin(9600); // Serial begin
  lcd.begin(16,2); // lcd begin
}
int LED_BLUE = A5;
int left = 0;
int right = 0;
void loop() {
 left = digitalRead(sw_left);
 right = digitalRead(sw_right);
 lcd.setCursor(2,0);
 lcd.print("Auto : Left");
 lcd.setCursor(1,1);
 lcd.print("Manual : Right");
 if(left == 0)
 {
   lcd.clear();
   lcd.setCursor(6,0);
   lcd.print("Auto");
   lcd.setCursor(3,1);
   lcd.print("GAME START");
   Auto();
 }
 if(right == 0)
 {
   lcd.clear();
   lcd.setCursor(5,0);
   lcd.print("Manual");
   lcd.setCursor(3,1);
   lcd.print("GAME START");
   Manual();
 }
} //loop exit
 
void Auto() {
 while(1) {
 ledprint();
 int dis = distance();
 if(dis <= 10)
 myServo.write(180);
 if(dis > 10)
 {
   delay(500);
   myServo.write(0);
 }
 }
}
void Manual() {
 while(1) {
 ledprint();
 right = digitalRead(sw_right);
 left = digitalRead(sw_left);
 Serial.print("right"+(String)right);
 Serial.println("   Left"+(String)left);
 if(right == 0)
 myServo.write(180);
 if(left == 0)
 myServo.write(0);
 }
}
void ledprint() {
 int dis = distance();
 if(dis <= 10)
 analogWrite(LED_BLUE,130);
 else
 analogWrite(LED_BLUE,0);
}


int distance() {
 digitalWrite(TRIG,LOW);
 delayMicroseconds(2);
 digitalWrite(TRIG,HIGH);
 delayMicroseconds(2);
 digitalWrite(TRIG,LOW);
 delayMicroseconds(5);
 int dis = pulseIn(ECHO,HIGH)/ 58.2;
 delay(10);
 return dis;
}

