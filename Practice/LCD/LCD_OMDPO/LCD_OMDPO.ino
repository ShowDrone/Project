#include<LiquidCrystal.h>
LiquidCrystal lcd(13,12,11,10,9,8);
void setup() {
lcd.begin(16,2);
Serial.begin(9600);
pinMode(2,OUTPUT);
pinMode(3,OUTPUT);
pinMode(4,2);
pinMode(5,2);
}
float g = 25.0;
void loop() {
  // put your main code here, to run repeatedly:
int ondo = analogRead(A5);
float a = (500.0*ondo)/1024.0;
Serial.print(a);
Serial.println("'C");
int sw1 = digitalRead(4); // ++
int sw2 = digitalRead(5); // --
if ( sw1 == 0)
{
  g++;
}
if ( sw2 == 0)
{
  g--;
}
Serial.println(g);
lcd.print(a);
lcd.setCursor(0,0);
lcd.print(g);
lcd.setCursor(0,1);
if(a<g)
{
  digitalWrite(2,0);
  digitalWrite(3,1);
  delay(1500);
}
else if(a>g);
{
  digitalWrite(2,1);
  digitalWrite(3,0);
  delay(1500);
}

}
