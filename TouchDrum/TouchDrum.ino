

#define FLOOR_TOM 41 // 1
#define RIDE_CYMBAL 51 // 2
#define LOW_TOM 45 // 3
#define HIGH_TOM 50 // 4
#define BASS_DRUM 35 // 5
#define CRASH_SYMBAL 49 // 6 
#define ACOUSTIC_SNARE 40 // 7
#define HIGH_HAT 44 // 8

#include <Wire.h>
#include "Adafruit_MPR121.h"

Adafruit_MPR121 cap = Adafruit_MPR121();

uint16_t Last_Touched = 0;
uint16_t Current_Touched = 0;

byte Drum[8] = {0, };


void setup() {
  while (!Serial);
  Serial.begin(9600);
  Serial.println("Adafruit MPR121 Capacitive Touch sensor test");

  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");
}

void loop() {
  Touch_Check();
  Output_Sound(Drum);
}

void Output_Sound(byte Drum[]) {
  for (uint8_t i = 0; i < 8; i++) {
    if (Drum[i] == 1) {
      Serial.write(0x90);
      switch (i) {
        case 0:
          Serial.write(FLOOR_TOM);
          //Serial.print("0"); Serial.println(" Boom");
          break;
        case 1:
          Serial.write(RIDE_CYMBAL);
          //Serial.print("1"); Serial.println(" Boom");
          break;
        case 2:
          Serial.write(LOW_TOM);
          //Serial.print("2"); Serial.println(" Boom");
          break;
        case 3:
          Serial.write(HIGH_TOM);
          //Serial.print("3"); Serial.println(" Boom");
          break;
        case 4:
          Serial.write(BASS_DRUM);
          //Serial.print("4"); Serial.println(" Boom");
          break;
        case 5:
          Serial.write(CRASH_SYMBAL);
          //Serial.print("5"); Serial.println(" Boom");
          break;
        case 6:
          Serial.write(ACOUSTIC_SNARE);
          //Serial.print("6"); Serial.println(" Boom");
          break;
        case 7:
          Serial.write(HIGH_HAT);
          //Serial.print("7"); Serial.println(" Boom");
          break;
      }
      Serial.write(127);
    }
  }
}


void Touch_Check() {
  Current_Touched = cap.touched();

  for (uint8_t i = 0; i < 12; i++) {
    if ((Current_Touched & _BV(i)) && !(Last_Touched & _BV(i)) ) {
      Drum[i] = 1;
      //Serial.print(i); Serial.println(" touched");
    }
    if (!(Current_Touched & _BV(i)) && (Last_Touched & _BV(i)) ) {
      Drum[i] = 0;
      //Serial.print(i); Serial.println(" released");
    }
  }
  Last_Touched = Current_Touched;
  return;
}

