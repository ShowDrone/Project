
int time = 0; // 루프 시간 측정 변수
int time_pre = 0; // 루프 시간 측정 변수의 이전 값

void setup() {
  Serial.begin(19200);
  AccelGyro_init();
  Control_UART_init();
  Fly_init();
  Landing_Setup();
}

void loop() {

  time = millis() - time_pre; // 한 루프를 도는데 걸리는 시간 측정
  time_pre = millis();
  //Serial.print("time: "); Serial.print(time);
  PID_Update();
  Fly_Update();
  Landing_Check();
}
