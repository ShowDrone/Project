int LED = 3;
void setup() {
  pinMode(LED,OUTPUT); //LED센서는 출력이니 OUTPUT으로 설정
}

void loop() {
  //2초 간격으로 LED가 깜빡거리는 소스
  digitalWrite(LED,HIGH); //LED ON
  delay(2000); // 2초
  digitalWrite(LED,LOW); //LED OFF
  delay(2000); // 2초

  
}

