
void setup() {

  Serial.begin(19200);
  AccelGyro_init();
  Control_UART_init();
  PID_init();

}

int time_pre = 0;

void loop() {

  int time = millis() - time_pre; // 한 루프를 도는데 걸리는 시간 측정
  time_pre = millis();
  //Serial.print("time: "); Serial.print(time);
  PID_Update();

}
