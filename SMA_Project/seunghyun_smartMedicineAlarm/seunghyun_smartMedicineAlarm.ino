/*
Title    : Smart Medicine Alarm
Maker    : Lee Seung Hyun, Lee Eui Chan
Platform : Arduino Pro mini (AtMega328, 5V, 16MHz)
Data     : 2015/08/20
ver      : basic_ver 1.4
*/
#define DS1302_SCLK_PIN   13    // The Serial Clock
#define DS1302_IO_PIN     12    // The Data I/O
#define DS1302_CE_PIN     11    // The Chip Enable
#define bcd2bin(h,l)    (((h)*10) + (l))
#define bin2bcd_h(x)   ((x)/10)
#define bin2bcd_l(x)    ((x)%10)
#define DS1302_SECONDS           0x80
#define DS1302_MINUTES           0x82
#define DS1302_HOURS             0x84
#define DS1302_DATE              0x86
#define DS1302_MONTH             0x88
#define DS1302_DAY               0x8A
#define DS1302_YEAR              0x8C
#define DS1302_ENABLE            0x8E
#define DS1302_TRICKLE           0x90
#define DS1302_CLOCK_BURST       0xBE
#define DS1302_CLOCK_BURST_WRITE 0xBE
#define DS1302_CLOCK_BURST_READ  0xBF
#define DS1302_RAMSTART          0xC0
#define DS1302_RAMEND            0xFC
#define DS1302_RAM_BURST         0xFE
#define DS1302_RAM_BURST_WRITE   0xFE
#define DS1302_RAM_BURST_READ    0xFF
#define DS1302_D0 0
#define DS1302_D1 1
#define DS1302_D2 2
#define DS1302_D3 3
#define DS1302_D4 4
#define DS1302_D5 5
#define DS1302_D6 6
#define DS1302_D7 7
#define DS1302_READBIT DS1302_D0 // READBIT=1: read instruction
#define DS1302_RC DS1302_D6
#define DS1302_CH DS1302_D7   // 1 = Clock Halt, 0 = start
#define DS1302_AM_PM DS1302_D5 // 0 = AM, 1 = PM
#define DS1302_12_24 DS1302_D7 // 0 = 24 hour, 1 = 12 hour
#define DS1302_WP DS1302_D7   // 1 = Write Protect, 0 = enabled
#define DS1302_ROUT0 DS1302_D0
#define DS1302_ROUT1 DS1302_D1
#define DS1302_DS0   DS1302_D2
#define DS1302_DS1   DS1302_D2
#define DS1302_TCS0  DS1302_D4
#define DS1302_TCS1  DS1302_D5
#define DS1302_TCS2  DS1302_D6
#define DS1302_TCS3  DS1302_D7
typedef struct ds1302_struct
{
  uint8_t Seconds:4;      // low decimal digit 0-9
  uint8_t Seconds10:3;    // high decimal digit 0-5
  uint8_t CH:1;           // CH = Clock Halt
  uint8_t Minutes:4;
  uint8_t Minutes10:3;
  uint8_t reserved1:1;
  union
  {
    struct
    {
      uint8_t Hour:12;
      uint8_t Hour10:2;
      uint8_t reserved2:1;
      uint8_t hour_12_24:1; // 0 for 24 hour format
    } h24;
    struct
    {
      uint8_t Hour:12;
      uint8_t Hour10:1;
      uint8_t AM_PM:1;      // 0 for AM, 1 for PM
      uint8_t reserved2:1;
      uint8_t hour_12_24:1; // 1 for 12 hour format
    } h12;
  };
  uint8_t Date:4;           // Day of month, 1 = first day
  uint8_t Date10:2;
  uint8_t reserved3:2;
  uint8_t Month:4;          // Month, 1 = January
  uint8_t Month10:1;
  uint8_t reserved4:3;
  uint8_t Day:3;            // Day of week, 1 = first day (any day)
  uint8_t reserved5:5;
  uint8_t Year:4;           // Year, 0 = year 2000
  uint8_t Year10:4;
  uint8_t reserved6:7;
  uint8_t WP:1;             // WP = Write Protect
};


#include <LiquidCrystal.h>
LiquidCrystal lcd(5,6,7,8,9,10);

#include<SoftwareSerial.h>
SoftwareSerial BTSerial(14, 15); // TX, RX

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
  ds1302_struct rtc;
  DS1302_write (DS1302_ENABLE, 0);
  DS1302_write (DS1302_TRICKLE, 0x00);
  #define SET_DATE_TIME_JUST_ONCE     //DATA standing
  #ifdef SET_DATE_TIME_JUST_ONCE  
  int seconds,
  minutes,
  hours,
  dayofweek,
  dayofmonth,
  month,
  year;
  
  seconds    = 30;
  minutes    = 50;
  hours      = 10;
  dayofmonth = 24; 
  month      = 8;  
  year       = 2015;
  memset ((char *) &rtc, 0, sizeof(rtc));
  rtc.Seconds    = bin2bcd_l( seconds);
  rtc.Seconds10  = bin2bcd_h( seconds);
  rtc.CH         = 0;      // 1 for Clock Halt, 0 to run;
  rtc.Minutes    = bin2bcd_l( minutes);
  rtc.Minutes10  = bin2bcd_h( minutes);
   rtc.h24.Hour   = bin2bcd_l( hours);
  rtc.h24.Hour10 = bin2bcd_h( hours);
  rtc.h24.hour_12_24 = 0; // 0 for 24 hour format
 // rtc.h12.Hour = bin2bcd_l(hours);
 // rtc.h12.Hour10 = bin2bcd_h(hours);
 // rtc.h12.AM_PM = 0;
 // rtc.h12.hour_12_24 = 1;
  
  rtc.Date       = bin2bcd_l( dayofmonth);
  rtc.Date10     = bin2bcd_h( dayofmonth);
  rtc.Month      = bin2bcd_l( month);
  rtc.Month10    = bin2bcd_h( month);
  rtc.Day        = dayofweek;
  rtc.Year       = bin2bcd_l( year - 2000);
  rtc.Year10     = bin2bcd_h( year - 2000);
  rtc.WP = 0;  
  DS1302_clock_burst_write( (uint8_t *) &rtc);
  #endif
  
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
  
   ds1302_struct rtc;
  char buffer[80];     // the code uses 70 characters.

  // Read all clock data at once (burst mode).
  DS1302_clock_burst_read( (uint8_t *) &rtc);
 
 
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
    
    alarm_Hour10 = rtc.h24.Hour10;
    alarm_Hour = rtc.h24.Hour;
    alarm_Minutes10 = rtc.Minutes10;
    alarm_Minutes = rtc.Minutes;
    alarm_Seconds10 = rtc.Seconds10;
    alarm_Seconds = rtc.Seconds;
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
  Serial.print(buffer);
  Serial.print("  ");
  Serial.print(clock_timer);
  Serial.print("  ");
  Serial.println(cds_data);
  
  sprintf( buffer, "Time = %02d:%02d:%02d, ", \
    bcd2bin( rtc.h24.Hour10, rtc.h24.Hour), \
    bcd2bin( rtc.Minutes10, rtc.Minutes), \
    bcd2bin( rtc.Seconds10, rtc.Seconds));
    
    //real time
    lcd.setCursor(0,1);
    lcd.print("Real :");
    lcd.setCursor(7,1);
    lcd.print(rtc.h24.Hour10);
    lcd.setCursor(8,1);
    lcd.print(rtc.h24.Hour);
    lcd.setCursor(9,1);
    lcd.print(":");
    lcd.setCursor(10,1);
    lcd.print(rtc.Minutes10);
    lcd.setCursor(11,1);
    lcd.print(rtc.Minutes);
    lcd.setCursor(12,1);
    lcd.print(":");
    lcd.setCursor(13,1);
    lcd.print(rtc.Seconds10);
    lcd.setCursor(14,1);
    lcd.print(rtc.Seconds);

  
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
  delayMicroseconds( 4);         
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
    delayMicroseconds( 1);     // tDC = 200ns
    digitalWrite( DS1302_SCLK_PIN, HIGH);     
    delayMicroseconds( 1);     // tCH = 1000ns, tCDH = 800ns

    if( release && i == 7)
    {
      pinMode( DS1302_IO_PIN, INPUT);
    }
    else
    {
      digitalWrite( DS1302_SCLK_PIN, LOW);
      delayMicroseconds( 1);       // tCL=1000ns, tCDD=800ns
    }
  }
}
