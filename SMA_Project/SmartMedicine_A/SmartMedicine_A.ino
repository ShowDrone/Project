/*
Title    : Smart Medicine Alarm
Maker    : Lee Seung Hyun, Lee Eui Chan
Platform : Arduino Pro mini (AtMega328, 5V, 16MHz)
Data     : 2015/08/20
ver      : basic_ver 1.4*/

#include <LiquidCrystal.h>
LiquidCrystal lcd(5,6,7,8,9,10);

#include<SoftwareSerial.h>
SoftwareSerial BTSerial(11, 12); // TX, RX

int
sw1 = 2,
sw2 = 1,
LED = 3,
vibrater = 4,
cds = A0,
cds_read = 0,
cds_data,
num = 0,
cds_score = 0,
sw1_data = 0,
sw2_data = 0,
reset_time = -1,
repeat_time = -1,
repeat_value = 0,
clock_timer = -1,
basic_clock = -1,
clock_value = 0,
check = 0,
check_time = 0,
value_test = 0,
data_value=0,
alarm_Hour10,
alarm_Hour,
alarm_Minutes,
alarm_Minutes10,
alarm_Seconds10,
alarm_Seconds,
value1=0,
value2=0,
value3=0,
value4=0,
alarm_test;
long time1 = millis()/1000;


void setup() {
  
  lcd.begin(16,2);
  lcd.setCursor(2, 0);
  lcd.print("Smart Alarm");
  Serial.begin(115200);
  BTSerial.begin(115200);
  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  digitalWrite(LED,HIGH);
  delay(3000);
  lcd.clear();
}

int sw_value = 0;
void loop() {

  time1 = millis()/1000;
  //Serial.println(buffer);
  //reading switch data
  sw1_data = digitalRead(sw1);
  sw2_data = digitalRead(sw2);
  delay(50);
  //reading cds data & change cds data scope
  cds_read = analogRead(A0);
  cds_data = map(cds_read,0,1024,0,100); // 0~1024 == analog Data scope
  //alarm set
  if(sw1_data == 0)
  {
    //debouncing
    if(clock_timer >= time1+1)
    {
      clock_timer += 5;
      value_test +=5;
    }
    else if(clock_timer < time1)
    {
      clock_timer = time1+5;
      value_test = 5;
    }
    /*
    alarm_Hour10 = rtc.h24.Hour10;
    alarm_Hour = rtc.h24.Hour;
    alarm_Minutes10 = rtc.Minutes10;
    alarm_Minutes = rtc.Minutes;
    alarm_Seconds10 = rtc.Seconds10;
    alarm_Seconds = rtc.Seconds;*/
    value1 = value_test/10;
    value2= value_test%10;
 
    alarm_Seconds10 += value1;
    alarm_Seconds += value2;
    if(alarm_Seconds>=9)
    {
      alarm_Seconds = 0;
      alarm_Seconds10 +=1;
    }
    if(alarm_Seconds10>=6)
    {
      alarm_Seconds10 = 0;
      alarm_Minutes += 1;
    }
    if(alarm_Minutes>=9)
    {
      alarm_Minutes = 0;
      alarm_Minutes10 += 1;
    }
    if(alarm_Minutes10>=5)
    {
      alarm_Minutes10 = 0;
      alarm_Hour += 1;
    }
    if(alarm_Hour>=9)
    {
      alarm_Hour = 0;
      alarm_Hour10 +=1;
    }
    lcd.clear();
    alarm_test = 1;
    if(alarm_test==1)
    {
    lcd.setCursor(0,0);
    lcd.print("Alarm:");
    lcd.setCursor(7,0);
    lcd.print(alarm_Hour10);
    lcd.setCursor(8,0);
    lcd.print(alarm_Hour);
    lcd.setCursor(9,0);
    lcd.print(":");
    lcd.setCursor(10,0);
    lcd.print(alarm_Minutes10);
    lcd.setCursor(11,0);
    lcd.print(alarm_Minutes);
    lcd.setCursor(12,0);
    lcd.print(":");
    lcd.setCursor(13,0);
    lcd.print(alarm_Seconds10);
    lcd.setCursor(14,0);
    lcd.print(alarm_Seconds);
    }  
    delay(70);
    while(sw1_data == 1)
    {
      ;
    }
    delay(70);
  }
    if(alarm_test==0)
    {
    lcd.setCursor(0,0);
    lcd.print("Alarm:");
    lcd.setCursor(7,0);
    lcd.print(0);
    lcd.setCursor(8,0);
    lcd.print(0);
    lcd.setCursor(9,0);
    lcd.print(":");
    lcd.setCursor(10,0);
    lcd.print(0);
    lcd.setCursor(11,0);
    lcd.print(0);
    lcd.setCursor(12,0);
    lcd.print(":");
    lcd.setCursor(13,0);
    lcd.print(0);
    lcd.setCursor(14,0);
    lcd.print(0);
    }
    
  
  Serial.print(time1);
  Serial.print("  ");
  Serial.print(clock_timer);
  Serial.print("  ");
  Serial.println(cds_data);
    
    //real time
   /* lcd.setCursor(0,1);
    lcd.print("Real :");
    lcd.setCursor(7,1);
    lcd.print(h24.Hour10);
    lcd.setCursor(8,1);
    lcd.print(h24.Hour);
    lcd.setCursor(9,1);
    lcd.print(":");
    lcd.setCursor(10,1);
    lcd.print(Minutes10);
    lcd.setCursor(11,1);
    lcd.print(Minutes);
    lcd.setCursor(12,1);
    lcd.print(":");
    lcd.setCursor(13,1);
    lcd.print(Seconds10);
    lcd.setCursor(14,1);
    lcd.print(Seconds);*/

  
  //alarm start
  if(clock_timer == time1)
  {
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("Alarm ON");
    lcd.setCursor(0,1);
    lcd.print("Take a medicine");
    alarm(14);
    clock_timer = -1;
    value_test = 0;
    lcd.clear();
    alarm_test = 0;
  }
  
  //reset
  if(sw2_data == 0)
  {
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("Alarm Reset");
    lcd.setCursor(3,0);
    lcd.print("Alarm Reset");
    clock_timer = -1;
    value_test = 0;
    alarm_test = 0;
    delay(5000);
    lcd.clear();
  }
    // repeat Prevention
  if(cds_data >= 20)
  {
    repeat_value = time1+5;
    
  }
  if(cds_data < 28) // take a medicine
  {
    if(repeat_value >= time1);
    {
      alarm(5);
    }
  }
  
}


  
void alarm(int check_time) {
  check_time += time1;
  while(check_time>time1) {
  if(time1+1<millis()/1000) {
   digitalWrite(LED,LOW);
   tone(vibrater,10000);
   BTSerial.write("Alarm");
 }
 if(time1+2<millis()/1000) {
   time1 = millis()/1000;
   digitalWrite(2,HIGH);
   BTSerial.write("Alarm");
 }
}
}
