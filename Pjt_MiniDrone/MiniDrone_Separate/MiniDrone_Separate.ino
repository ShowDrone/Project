
// 속도 제어 BLDC 2개 / 방향 제어 DC 4개 / 랜딩 기어 2개

void setup() {

  Serial.begin(19200);
  AccelGyro_init();
  Control_UART_init();
  PID_init();

}

int time_pre = 0;

void loop() {

  int time = millis() - time_pre;
  time_pre = millis();
  //Serial.print("time: "); Serial.print(time);
  PID_Update();

}
