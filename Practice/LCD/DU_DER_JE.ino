#include<LiquidCrystal.h>
LiquidCrystal lcd (8,9,10,11,12,13);
int time=0;

void setup() {
for (int sw = 2; sw < 5; sw++) // Switch ON
{
  pinMode(sw,INPUT_PULLUP);
}
for (int led = 5; led < 8; led++) //LED ON
{
  pinMode(led,OUTPUT);
}
lcd.begin(16,2); //lcd begin
Serial.begin(9600);
}
int sw1,sw2,sw3;
int led1,led2,led3;
int led_rand;
int led_value;
int score1 = 0;
int led_1,led_2,led_3;
void loop(){
 sw1 = digitalRead(2);
 delay(50);
 sw2 = digitalRead(3);
 delay(50);
 sw3 = digitalRead(4);
 delay(50);
 se();
 led1 = digitalRead(5);
 led2 = digitalRead(6);
 led3 = digitalRead(7);
 led_rand = random(0,3);
 rand1();
 score();
 if (score < 0)
 {
   over();
 }
 led_();
 lcd.setCursor(0,0);
 lcd.print("Score:");
 //time1();
}
/*void time1() {
 time = millis()/1000;
 lcd.setCursor(0,1);
 lcd.print("Time:");
 lcd.setCursor(5,1); 
 lcd.print(time);
 if(time == 11)
 {
over();
 }
}*/
void over() {
     lcd.clear();
   lcd.setCursor(3,0);
   lcd.print("GAMe OVER");
   lcd.setCursor(3,1);
   lcd.print("GAME OVER");
   delay(1000000);
}
void se() {
Serial.print("sw1:");
Serial.print(sw1);
Serial.print("  Led1:");
Serial.println(led1);
Serial.print("sw2:");
Serial.print(sw2);
Serial.print("  Led2:");
Serial.println(led2);
Serial.print("sw3:");
Serial.print(sw3);
Serial.print("  Led3:");
Serial.println(led3);
}

void rand1() {
if(led_rand == 0)
{
 digitalWrite(5,1); 
 digitalWrite(6,0);
 digitalWrite(7,0);
 delay(500);
}
else if(led_rand == 1)
{
  digitalWrite(6,1); 
 digitalWrite(5,0);
 digitalWrite(7,0);
  delay(500);
}
else if(led_rand == 2)
{
  digitalWrite(7,1); 
  digitalWrite(6,0);
  digitalWrite(5,0);
  delay(500);
}
}
void led_(){
if (sw1 == 0)
{
  led_1 = 1;
  led_2 = 0;
  led_3 = 0;
}
if (sw2 == 0)
{
  led_1 = 0;
  led_2 = 1;
  led_3 = 0;
}
if (sw3 == 0)
{
  led_1 = 0;
  led_2 = 0;
  led_3 = 1;
}
}
void score() {
if(led1==1&&sw1==0)
{
    lcd.print(score1);
    lcd.setCursor(0,0);
    lcd.print("Score:");
    lcd.setCursor(6,0);
    score1++;
}
else if(led2==1 && sw2==0)
  {
    lcd.print(score1);
    lcd.setCursor(0,0);
    lcd.print("Score:");
    lcd.setCursor(6,0);
    score1++;  
  }
else if(led3==1&&sw3==0)
  {
    lcd.print(score1);
    lcd.setCursor(0,0);
    lcd.print("Score:");
    lcd.setCursor(6,0);
    score1++;
  }
 if (led1 == 0 && sw1 ==0)
 {
   lcd.print(score1);
    lcd.setCursor(0,0);
    lcd.print("Score:");
    lcd.setCursor(6,0);
    score1--;
 }
 if(led2 == 0 && sw2 ==0)
 {
   lcd.print(score1);
    lcd.setCursor(0,0);
    lcd.print("Score:");
    lcd.setCursor(6,0);
    score1--;
 }
 if(led3 ==0 && sw3 == 0)
 {
   lcd.print(score1);
    lcd.setCursor(0,0);
    lcd.print("Score:");
    lcd.setCursor(6,0);
    score1++;
 }
  }

