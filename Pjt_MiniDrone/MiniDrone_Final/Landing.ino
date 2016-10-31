
#define LANDING_TIME 5000 // ms단위이며, 랜딩 기어가 접히고 펴지는데 걸리는 시간(임의 값 테스트 필요)
#define LandingMotor1_A 10 // LANDING_A
#define LandingMotor1_B 11 // LANDING_B
#define LandingMotor2_A 12 // LANDING_A
#define LandingMotor2_B 13 // LANDING_B

boolean Landing_Status = true; // 드론은 비행할 때 빼고 랜딩기어가 항상 On(펴짐 상태)
boolean Landing_Start = false; // 랜딩 기어의 접고 펴짐을 알리는 신호
boolean Landing_Once = false; // 한 번만 실행하게끔 하는 용도
int Landing_LoopTime = 0; // Landing_Start를 5초 동안만 동작하게하는 함수
int Landing_Speed = DC_SPEED_MAX;

/*
  비행 테스트시에는 토글랜딩으로 랜딩 기어를 On/Off하며
  코딩하신 앱으로 Control_UART를 갈아엎어야 하니
  Control_UART을 갈아엎으시면서 스마트폰에서
  랜딩기어 On/Off 데이터를 송신하는 기능과
  수신하는 코드 추가 부탁을 드립니다
*/

void Landing_Setup() {
  pinMode(LandingMotor1_A, OUTPUT);
  pinMode(LandingMotor1_B, OUTPUT);
  pinMode(LandingMotor2_A, OUTPUT);
  pinMode(LandingMotor2_B, OUTPUT);
}

/*
 * Landing_Check는 스마트폰 앱의 토글 스위치가 On 되었을 때 실행됩니다.(테스트시에만 토글 스위치 사용
 * 5초동안 동안 실행됩니다. (38~42번줄)
 */
void Landing_Check() {
  
  // 토글 스위치로 인해 Landing_Start와 Landing_Once에 true가 입력된 상황
  if (Landing_Start) {
    if (Landing_Once) {
      Landing_LoopTime = millis() + LANDING_TIME;
      Landing_Once = false;
      Landing_Status = !Landing_Status;
    }
    if (Landing_LoopTime > millis())
      Landing_Update();
    else
      Landing_Start = false;
  }
}

/*
 * Status가 false일 땐 정방향, true일 땐 역방향으로 돌게 만들었습니다.
 * 랜딩 기어 모터: 정방향 이륙(접힘), 역방향 착륙(펴짐)
 */
void Landing_Update() {
  if (Landing_Status == false) {
    digitalWrite(LandingMotor1_A, 0);
    digitalWrite(LandingMotor1_B, Landing_Speed);
    digitalWrite(LandingMotor2_A, 0);
    digitalWrite(LandingMotor2_B, Landing_Speed);
  }
  else {
    digitalWrite(LandingMotor1_A, Landing_Speed);
    digitalWrite(LandingMotor1_B, 0);
    digitalWrite(LandingMotor2_A, Landing_Speed);
    digitalWrite(LandingMotor2_B, 0);    
  }
}
