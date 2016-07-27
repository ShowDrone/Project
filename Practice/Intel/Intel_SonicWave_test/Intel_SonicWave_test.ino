int Trig = 12;                                      
int Echo = 13;
int distance = 0;

// setup()은 시작할 때 한번만 실행

void setup() {
  // pinMode함수는 디지털핀을 어떤 용도로 쓸건지 정하는 함수
  pinMode(Trig,OUTPUT); //초음파를 보ㅈ내야하니 OUTPUT
  pinMode(Echo,INPUT); //초음파를 받아야 하니 INPUT

  // 하드웨어 - Pc간의 직렬 통신
  Serial.begin(115200);
}
// loop()는 계속 반복

void loop() {
  // Trig 초음파의 노이즈 제거
  digitalWrite(Trig,HIGH); // 디지털핀에 HIGH(5V), LOW(0V)를 줄지 결정
  delayMicroseconds(10);
  digitalWrite(Trig,LOW);
  delayMicroseconds(10);

  distance = pulseIn(Echo,HIGH)/58.8; // 거리 재기
  Serial.print("distance: "); //개행없는 출력
  Serial.print(distance);    //개행없는 출력
  Serial.println("cm");     //개행있는 출력
}
