
/*
Wire Number

DC1_A 2
DC1_B 3
DC2_A 4
DC2_B 5
BLDC_A 10
BLDC_B 11


///////////// Arduino B /////////////
  Test Board : Arduino Uno
*/

void setup() {
  AccelGyro_Setup();
  SPI_Setup();
  PID_Setup();
}

void loop() {
  SPI_Update();
  PID_Update();
}
