void setup() {
  Serial.begin(115200);
}

void loop() {
  //A0에 온도센서 신호선 연결되어 있음
  int Temp = analogRead(A0);
  //아날로그 Read값은 0~1023이니 5를 곱해주고 1024로 나누면 전압값 0~5가 됨
  float TempRead = Temp*5.0/1024.0; 

  //0.5(V)를 빼줘야 우리가 원하는 값이 됨
  float TempData = (TempRead-0.5)*100.0;
  //하드웨어 스펙에 따라 10mV가 1도이고 10mV는 0.001V이므로 100을 곱해야 1라는 온도 값이 나옴
 
  //데이터출력
  Serial.print(TempData);
  Serial.println("'C");
  delay(300);
}
