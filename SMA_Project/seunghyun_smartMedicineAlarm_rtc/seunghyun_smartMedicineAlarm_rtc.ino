/*
Title    : Smart Medicine Alarm
Maker    : Lee Seung Hyun, Lee Eui Chan
Platform : Arduino Mini Pro (AtMega328, 5V, 16MHz)
Data     : 2015/08/20
ver      : basic_ver 1.4
*/


#include <LiquidCrystal.h>
LiquidCrystal lcd(10,9,8,7,6,5);

int
sw1 = 3,
sw2 = 1,
LED = 2,
vibrater = 4,
cds = A0,
cds_data,
num = 0,
cds_score = 0,
sw1_data = 0,
sw2_data = 0,
time1,
reset_time = -1,
repeat_time = -1,
repeat_value = 0,
clock_timer = -1,
basic_clock = -1,
clock_value = 0,
check = 0;

void setup() {
  
  lcd.begin(16,2);
  lcd.setCursor(2, 0);
  lcd.print("Smart Alarm");
  Serial.begin(115200);
  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  digitalWrite(LED,HIGH);
  delay(3000);
  lcd.clear();
}
 
void loop() {
  ds1302_struct rtc;
  char buffer[80];
  DS1302_clock_burst_read( (uint8_t *) &rtc);
  
  lcdprint();
 
  time1 = millis()/1000;  
  //Serial.print("time :");
  
  
  //reading switch data
  sw1_data = digitalRead(sw1);
  sw2_data = digitalRead(sw2);
  delay(70);
  
  //reading cds data & change cds data scope
  cds_data = map(cds,0,1024,0,100); // 0~1024 == analog Data scope
  //alarm set
  if(sw1_data == 0)
  {
    //debouncing
    if(clock_timer >= time1+3)
    {
      clock_timer += 3;
      Serial.println("Two clock");
      Serial.println(clock_timer);
      delay(100);
    }
    else if(clock_timer < time1)
    {
      clock_timer = time1+3;
      Serial.println("One clock");
      Serial.println(clock_timer);
      delay(100);
    }
  }
  
  //alarm start
  if(clock_timer == time1)
  {
    check = time1+10;
    alarm(check);
    clock_timer = -1;
  }
  
  //reset
  if(sw2_data == 0)
  {
    clock_timer = -1;
  }
   
    // repeat Prevention
  if(cds_data <= 50)
  {
    repeat_value = time1+3;
  }
  if(cds_data > 55) // take a medicine
  {
    if(repeat_value >= time1);
    {
      alarm(10);
    }
  }
  
    sprintf( buffer, "%02d:%02d:%02d", \
    bcd2bin( rtc.h12.Hour10, rtc.h12.Hour), \
    bcd2bin( rtc.Minutes10, rtc.Minutes), \
    bcd2bin(rtc.Seconds10, rtc.Seconds));
    Serial.println( buffer);
  
}

  void lcdprint() {
    
}

/*void lcd_zero() {
    hour0 = 0;
    hour1 = 0;
    minutes0 = 0;
    minutes1 = 0;
    seconds0 = 0;
    seconds1 = 0;
    lcd.setCursor(1,0);
    lcd.print("Time ");
    lcd.setCursor(6,0);
    lcd.print(hour0);
    lcd.setCursor(7,0);
    lcd.print(hour1);
    lcd.setCursor(8,0);
    lcd.print(":");
    lcd.setCursor(9,0);
    lcd.print(minutes0);
    lcd.setCursor(10,0);
    lcd.print(minutes1);
    lcd.setCursor(11,0);
    lcd.print(":");
    lcd.setCursor(12,0);
    lcd.print(seconds0);
    lcd.setCursor(13,0);
    lcd.print(seconds1);
}*/

void alarm(int check_time) {
       while(time1<check_time)
       {
         if(time1 + 1 < millis()/1000) {
           digitalWrite(LED,LOW);
           tone(4,10000,1000);
         }
         if(time1 + 2 < millis()/1000) {
           time1 = millis()/1000;
           digitalWrite(LED,HIGH);
         }
       }
       
         time1 = millis()/1000;
       /*tone(vibrater,10000,1000);     
       for(int i=0;i<max1;i++)
       {
       Serial.println("function Test");
       digitalWrite(LED, LOW); // Low is LED ON // commonAnode
       delay(500);
       digitalWrite(LED, HIGH);
       delay(500);
       digitalWrite(LED, LOW);
       delay(500);
       digitalWrite(LED, HIGH);
       delay(500);
       digitalWrite(LED, LOW);
       delay(500);
       digitalWrite(LED, HIGH);
       delay(3000);
       }  */
}

void DS1302_clock_burst_read( uint8_t *p)
{
  int i;

  _DS1302_start();

  _DS1302_togglewrite( DS1302_CLOCK_BURST_READ, true);  

  for( i=0; i<8; i++)
  {
    *p++ = _DS1302_toggleread();
  }
  _DS1302_stop();
}

void DS1302_clock_burst_write( uint8_t *p)
{
  int i;

  _DS1302_start();

  _DS1302_togglewrite( DS1302_CLOCK_BURST_WRITE, false);  

  for( i=0; i<8; i++)
  {
    
    _DS1302_togglewrite( *p++, false);  
  }
  _DS1302_stop();
}

uint8_t DS1302_read(int address)
{
  uint8_t data;
  bitSet( address, DS1302_READBIT);  

  _DS1302_start();
  
  _DS1302_togglewrite( address, true);  
  data = _DS1302_toggleread();
  _DS1302_stop();

  return (data);
}

void DS1302_write( int address, uint8_t data)
{
  bitClear( address, DS1302_READBIT);   

  _DS1302_start();
  _DS1302_togglewrite( address, false); 
  _DS1302_togglewrite( data, false); 
  _DS1302_stop();  
}

void _DS1302_start( void)
{
  digitalWrite( DS1302_CE_PIN, LOW);
  pinMode( DS1302_CE_PIN, OUTPUT);  

  digitalWrite( DS1302_SCLK_PIN, LOW);
  pinMode( DS1302_SCLK_PIN, OUTPUT);

  pinMode( DS1302_IO_PIN, OUTPUT);

  digitalWrite( DS1302_CE_PIN, HIGH); 
  delayMicroseconds(4);          
}

void _DS1302_stop(void)
{
  
  digitalWrite( DS1302_CE_PIN, LOW);

  delayMicroseconds( 4); 
}

uint8_t _DS1302_toggleread( void)
{
  uint8_t i, data;

  data = 0;
  for( i = 0; i <= 7; i++)
  {
    digitalWrite( DS1302_SCLK_PIN, HIGH);
    delayMicroseconds( 1);

    digitalWrite( DS1302_SCLK_PIN, LOW);
    delayMicroseconds( 1);
    bitWrite( data, i, digitalRead( DS1302_IO_PIN)); 
  }
  return( data);
}

void _DS1302_togglewrite( uint8_t data, uint8_t release)
{
  int i;

  for( i = 0; i <= 7; i++)
  { 
    digitalWrite( DS1302_IO_PIN, bitRead(data, i));  
    delayMicroseconds( 1);

    digitalWrite( DS1302_SCLK_PIN, HIGH);     
    delayMicroseconds( 1); 

    if( release && i == 7)
    {
      pinMode( DS1302_IO_PIN, INPUT);

    }
    else
    {
      digitalWrite( DS1302_SCLK_PIN, LOW);
      delayMicroseconds( 1);  
    }
  }
}

