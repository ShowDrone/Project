
#define PITCH_MIN -30 // pitch 값 범위 (for mapping)
#define PITCH_MAX 30
#define ROLL_MIN -30
#define ROLL_MAX 30
#define YAW_MIN -20 // 테스트하면서 30으로 할지 20으로 할지 결정
#define YAW_MAX 20

double const PITCH_P = 0.85, PITCH_I = 0.1, PITCH_D = 0.15; // Pitch PID 게인값
double const ROLL_P = 1, ROLL_I = 0.05, ROLL_D = 1; // Roll PID 게인값
double const YAW_P = 1, YAW_I = 0.05, YAW_D = 1; // Yaw PID 게인값

// 순서대로 오차값, 이전오차값(previous), P제어의 결과값 변수, I제어의 결과값 변수, D제어의 결과값 변수, PID값
double PITCH_ERR, PITCH_PERR, PITCH_ERR_P, PITCH_ERR_I = 0, PITCH_ERR_D, PITCH_PID;
double ROLL_ERR, ROLL_PERR, ROLL_ERR_P, ROLL_ERR_I = 0, ROLL_ERR_D, ROLL_PID;
double YAW_ERR, YAW_ERR_P, YAW_ERR_I = 0, YAW_PI;

// PITCH, ROLL PID의 이전 값을 담아두는 변수
double PITCH_PRE, ROLL_PRE;

// Ctl = Control, 조작 값을 담아두는 변수
int16_t PITCH_Ctl, roll_Ctl, yaw_Ctl;
int16_t PITCH_Ctl_Last, roll_Ctl_Last, yaw_Ctl_Last;

// 조종 데이터를 5ms마다 읽어들이게끔 확인하는 변수
int16_t UartTime = 0;

void PID_Update() {
  
  // 카메라보드에서 5ms마다 데이터를 송신해주므로 5ms마다 조종 데이터를 수신
  if (UartTime + 5 < millis()) {
    Control_UART_Update();
    UartTime = millis();
  }

  // 매핑
  PITCH_Ctl = map(buf[2], 88, 168, PITCH_MIN, PITCH_MAX);
  roll_Ctl = map(buf[1], 88, 168, ROLL_MIN, ROLL_MAX);
  yaw_Ctl = map(buf[4], 70, 176, YAW_MIN, YAW_MAX);
  // buf[3]은 mapping할 필요X, 읽어들이는 값 자체가 8비트

  // pitch, roll, yaw값들이 범위값을 벗어날 경우 이전 값을 대입
  if (PITCH_Ctl < PITCH_MIN || PITCH_Ctl > PITCH_MAX) {
    PITCH_Ctl = PITCH_Ctl_Last;
  }
  if (roll_Ctl < ROLL_MIN || roll_Ctl > ROLL_MAX) {
    roll_Ctl = roll_Ctl_Last;
  }
  if (yaw_Ctl < YAW_MIN || yaw_Ctl > ROLL_MAX) {
    yaw_Ctl = yaw_Ctl_Last;
  }

  PITCH_Ctl_Last = PITCH_Ctl;
  roll_Ctl_Last = roll_Ctl;
  yaw_Ctl_Last = yaw_Ctl;

  // Pitch, Roll, Yaw값을 최신의 것으로 업데이트
  AccelGyro_Update();

  //PITCH
  PITCH_ERR = PITCH_Ctl - pitch; //목표값 - 현재값
  PITCH_PERR = (pitch - PITCH_PRE); //DT; //  기울기 차이/샘플링 주기
  PITCH_ERR_P = PITCH_ERR * PITCH_P; // 오차*P게인
  PITCH_ERR_I = PITCH_ERR_I + (PITCH_ERR * PITCH_I) * DT;
  Limit_I(&PITCH_ERR_I);
  PITCH_ERR_D = PITCH_PERR * PITCH_D; // 기울기 차이*D게인
  PITCH_PID = PITCH_ERR_P + PITCH_ERR_I + PITCH_ERR_D;
  PITCH_PRE = pitch;

  //ROLL
  // 현재 테스트시에는 ROLL의 목표 값을 0으로 두지만 차후엔 모드를 구분해서 조종 데이터를 목표 값으로도 둘 예정
  roll_Ctl = 0;
  ROLL_ERR = roll_Ctl - roll;
  ROLL_PERR = (roll - ROLL_PRE) / DT;
  ROLL_ERR_P = ROLL_ERR * ROLL_P;
  ROLL_ERR_I = ROLL_ERR_I + (ROLL_ERR * ROLL_I) * DT;
  Limit_I(&ROLL_ERR_I);
  ROLL_ERR_D = ROLL_PERR * ROLL_D;
  ROLL_PID = ROLL_ERR_P + ROLL_ERR_I + ROLL_ERR_D;
  ROLL_PRE = roll;

  //YAW
  YAW_ERR = yaw_Ctl - yaw;
  YAW_ERR_P = YAW_ERR * YAW_P;
  YAW_ERR_I = YAW_ERR_I + (YAW_ERR * YAW_I) * DT;
  Limit_I(&YAW_ERR_I);
  YAW_PI = YAW_ERR_P + YAW_ERR_I;
}

// I게인 값이 계속 누적되서 커지지 않도록 한계값 설정
void Limit_I(double *value) {
  if (*value >= 100)
    *value = 100;
  else if (*value <= -100)
    *value = -100;
}

