
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
  Serial.begin(19200);
  
  AccelGyro_init();
  Control_UART_init();
  Status_UART_init();
  PID_init();
  
  Serial.println("Start");
  delay(500);
}

int time_pre = 0;

void loop() {
  int time = millis() - time_pre;
  time_pre = millis();
  Serial.print("time: "); Serial.print(time);
  
  Status_UART_Update();
  PID_Update();
}

