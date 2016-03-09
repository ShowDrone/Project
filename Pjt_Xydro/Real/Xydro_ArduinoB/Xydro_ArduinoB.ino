/*
/////////////////////////////


          Inside Part


/////////////////////////////
*/



/*
Wire Number

DC1_A 2
DC1_B 3
DC2_A 4
DC2_B 5
BLDC_A 10
BLDC_B 11


//////////// Arduino B /////////////
  Test Board : Arduino Uno
*/

void setup() {
  Serial.begin(19200);
  
  AccelGyro_init();
  Control_UART_init();
  Transmiter_init();
  PID_init();
}

int time_pre = 0;

void loop() {
  
  int time = millis() - time_pre;
  time_pre = millis();
  //Serial.print("time: "); Serial.print(time);
  
  Transmiter_Update();
  PID_Update();
}
