#include <SPI.h>

void SPI_Setup (void) {
  pinMode(MISO, OUTPUT);
  pinMode(MOSI, INPUT);
  pinMode(SCK, INPUT);
  pinMode(SS, INPUT);
  SPCR |= _BV(SPE);
  SPCR &= ~_BV(MSTR);
  SPCR |= _BV(SPIE);

  SPI.setClockDivider(SPI_CLOCK_DIV16);

  Serial.begin(19200);
}

boolean plus = false;
boolean minus = false;

boolean Check[4] = {0,};
byte Confirm = 0;

ISR (SPI_STC_vect)
{ 
  if (Confirm == 0) {
    Check[0] = true;
    Check[1] = false;
    Check[2] = false;
    Check[3] = false;
  }
  else if (Confirm == 1) {
    Check[0] = false;
    Check[1] = true;
    Check[2] = false;
    Check[3] = false;
  }
  else if (Confirm == 2) {
    Check[0] = false;
    Check[1] = false;
    Check[2] = true;
    Check[3] = false;
  }
  else if (Confirm == 3) {
    Check[0] = false;
    Check[1] = false;
    Check[2] = false;
    Check[3] = true;
  }

}

int time_pre = 0;
void SPI_Update (void) {

  int time = millis() - time_pre;
  time_pre = millis();
  Serial.print("time: "+(String)time);

  if (Check[0] == true) {
    buf[0] = SPDR;
    Confirm++;
    Check[0] = false;
    Serial.print(" 0 ");
  }
  if (Check[1] == true) {
    buf[1] = SPDR;
    Confirm++;
    Check[1] = false;
    Serial.print(" 1 ");
  }
  if (Check[2] == true) {
    buf[2] = SPDR;
    Confirm++;
    Check[2] = false;
    Serial.print(" 2 ");
  }

  if (Check[3] == true) {
    buf[3] = SPDR;
    Confirm = 0;
    Check[3] = false;
    Serial.print(" 3  ");
  }

  /*Serial.print(buf[0]); Serial.print(" ");
  Serial.print(buf[1]); Serial.print(" ");
  Serial.print(buf[2]); Serial.print(" ");
  Serial.println(buf[3]);*/

}
