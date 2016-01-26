
/*
Wire Number

DC3_A 6
DC3_B 7
DC4_A 8
DC4_B 9

///////////// Arduino A /////////////

  Test Board : Arduino Uno
  불의로 통신 끊겼을 시 호버링 유지하는 기능
*/
void setup() {
  UART_Setup();
  Serial.begin(19200);
  AccelGyro_Setup();
  SPI_Setup();
  PID_Setup();
  Serial.println("Start");
  delay(500);
}


int time_pre = 0;

void loop() {
  int time = millis() - time_pre;
  time_pre = millis();
  Serial.print("time: " + (String)time);
  
  SPI_Update();
  PID_Update();
}

