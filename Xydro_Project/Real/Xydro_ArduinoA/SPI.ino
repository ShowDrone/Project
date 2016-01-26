/*
SPI 규칙
데이터 총 9byte
통신 순서
8 - 0 - 1 - 2 - 3 - 4 - 5 - 6 - 7

0, 1, 2 = roll(x)
3, 4, 5 = pitch(y)
6, 7, 8 = yaw(z)

(0,3,6) First = 구조체명.add
(1,4,7) Second = 구조체명.rest
(2,5,8) Third = 구조체명.multiple
*/

#include <SPI.h>

void SPI_Setup (void) {
  SPI.begin ();
  digitalWrite(SS, HIGH);
  SPI.setClockDivider(SPI_CLOCK_DIV16);
}

boolean A_Check = true;
boolean B_Check = false;
boolean C_Check = false;
boolean D_Check = false;


void SPI_Update (void) {
  
  digitalWrite(SS, LOW);
  if (A_Check) {
    SPI.transfer(buf[1]);
    Serial.print(" ");
    Serial.print(buf[1]);
    Serial.print(" ");
    delayMicroseconds(3100);
    A_Check = false;
    B_Check = true;
  }
  if (B_Check) {
    SPI.transfer(buf[2]);
    Serial.print(buf[2]);
    Serial.print(" ");
    delayMicroseconds(3100);
    B_Check = false;
    C_Check = true;
  }
  if (C_Check) {
    SPI.transfer(buf[3]);
    Serial.print(buf[3]);
    Serial.print(" ");
    delayMicroseconds(3100);
    C_Check = false;
    D_Check = true;
  }
  if (D_Check) {
    SPI.transfer(buf[4]);
    Serial.println(buf[4]);
    D_Check = false;
    A_Check = true;
    //delayMicroseconds(1250);
  }
  digitalWrite(SS, HIGH);
}

