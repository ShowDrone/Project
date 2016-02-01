#include<LiquidCrystal.h>
LiquidCrystal lcd(11,10,9,8,7,6);

int sw1 = 13; // left
int sw2 = 12; // right
int sw3 = 5; // up & down

void setup() {
pinMode(sw1,INPUT_PULLUP); // Switch num1
pinMode(sw2,INPUT_PULLUP); // Switch num2
pinMode(sw3,INPUT_PULLUP); // Switch num3
Serial.begin(9600);
lcd.begin(16,2); // lcd begin
}

int sw_1; // input swit
int sw_2; // input swit
int sw_3; // input swit
int move0; // move
int value = 0; // value line
int value_line = 0;
void loop() {
  sw_1 = digitalRead(13);
  sw_2 = digitalRead(12);
  sw_3 = digitalRead(5);
  if(sw_1 == 0) {
  if(value > 0)
  {
  value--;
  }
  delay(200);  
  }
  if(sw_2 == 0) {
   if(value < 15)
   {
    value++;
   }
 delay(200);  
  }
  if(sw_3 == 0) {
   if(value_line == 0)
   {
     value_line++;
   }
   else if(value_line == 1)
   {
     value_line--;
   }
  delay(200);
  }
  lcd.clear();
  lcd.setCursor(value,value_line);
  lcd.println("0");
}
