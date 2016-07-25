
#define BLDC_SPEED_MAX 255 // 예시 값
#define BLDC_SPEED_MIN 0
#define DC_SPEED_MAX 100 // 예시 값
#define DC_SPEED_MIN 0
#define PITCH_MIN -30 // pitch 값 범위 (for mapping)
#define PITCH_MAX 30 
#define ROLL_MIN -30
#define ROLL_MAX 30
#define YAW_MIN -20
#define YAW_MAX 20
#define PID_MAX 80 // 이 값으로 할지 -30~+30으로 할진 미정
#define PID_MIN -80 // PID값 범위
#define Motor1_A 2 // Direction_A            모터 변수 이름 의미
#define Motor1_B 3 // Direction_B                   [전]
#define Motor2_A 4 // Direction_A                 1번 모터
#define Motor2_B 5 // Direction_B        [좌] 4번 모터    2번 모터 [우]
#define Motor3_A 6 // Direction_A                 3번 모터
#define Motor3_B 7 // Direction_B                   [후]
#define Motor4_A 8 // Direction_A
#define Motor4_B 9 // Direction_B
#define Motor5_A 10 // LANDING_A
#define Motor5_B 11 // LANDING_B
#define Motor6_A 12 // LANDING_A
#define Motor6_B 13 // LANDING_B
#define BLDC_A 54 // Speed A0
#define BLDC_B 55 // Speed A1

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

// 정방향, 역방향을 구분하기 위한 변수
boolean Motor1_Status = 0, Motor2_Status = 0;
boolean Motor3_Status = 0, Motor4_Status = 0;

// Motor의 A, B스피드 PID연산을 위한
int Motor1_A_Speed, Motor1_B_Speed;
int Motor2_A_Speed, Motor2_B_Speed;
int Motor3_A_Speed, Motor3_B_Speed;
int Motor4_A_Speed, Motor4_B_Speed;
int Motor5_A_Speed, Motor5_B_Speed;
int Motor6_A_Speed, Motor6_B_Speed;

// Motor의 최종스피드
int Motor1_Speed, Motor2_Speed;
int Motor3_Speed, Motor4_Speed;
int Motor5_Speed, Motor6_Speed;

int BLDC_Speed; // BLDC 모터 스피드

// Emergency용 변수
boolean Emergency = false;
int16_t EmergencyTime = 0;
int16_t EmergencySpeed = 0;


int16_t UartTime = 0; // 조종 데이터를 5ms마다 읽어들이게끔 확인하는 변수

void PID_init() {
  pinMode(Motor1_B, OUTPUT);
  pinMode(Motor1_A, OUTPUT);
  pinMode(Motor2_B, OUTPUT);
  pinMode(Motor2_A, OUTPUT);
  pinMode(Motor3_B, OUTPUT);
  pinMode(Motor3_A, OUTPUT);
  pinMode(Motor4_B, OUTPUT);
  pinMode(Motor4_A, OUTPUT);
  pinMode(Motor5_B, OUTPUT);
  pinMode(Motor5_A, OUTPUT);
  pinMode(Motor6_B, OUTPUT);
  pinMode(Motor6_A, OUTPUT);
  pinMode(BLDC_A, OUTPUT);
  pinMode(BLDC_B, OUTPUT);
  //모터 안정화
  MOT_Stability();
}

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

  // 응급 상황이 아닌 경우 BLDC스피드는 buf[3]값 그대로
  if (Emergency == false)
    BLDC_Speed = buf[3];

  // 응급 상황일 경우 속도를 줄여나감
  if (Emergency == true) {
    if (BLDC_Speed >= 0) {
      if (BLDC_Speed >= 30)
        EmergencySpeed = BLDC_Speed / 10;
      else
        EmergencySpeed = BLDC_Speed;
      if (EmergencyTime + 1000 > millis()) {
        BLDC_Speed -= EmergencySpeed;
        EmergencyTime = millis();
      }
    }
  }

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

  // 응급 상황일 경우 기체를 수평으로.
  if (Emergency == true) {
    pitch = 0;
    roll = 0;
    yaw = 0;
  }

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

  Limit_BLDC(&BLDC_Speed);

  if (BLDC_Speed <= 10) // BLDC가 돌아가는 최소 신호값으로 지정, 10은 임의값
    MOT_Stability(); // 로터부 수평

  if (YAW_PI < 0) {
    Motor1_A_Speed = 0;
    Motor2_A_Speed = 0;
    Motor3_A_Speed = 0;
    Motor4_A_Speed = 0;
    Motor1_B_Speed = YAW_PI;
    Motor2_B_Speed = YAW_PI;
    Motor3_B_Speed = YAW_PI;
    Motor4_B_Speed = YAW_PI;
  }
  else {
    Motor1_A_Speed = YAW_PI;
    Motor2_A_Speed = YAW_PI;
    Motor3_A_Speed = YAW_PI;
    Motor4_A_Speed = YAW_PI;
    Motor1_B_Speed = 0;
    Motor2_B_Speed = 0;
    Motor3_B_Speed = 0;
    Motor4_B_Speed = 0;
  }
  if (PITCH_PID < 0) {
    Motor2_B_Speed += PITCH_PID;
    Motor4_B_Speed += PITCH_PID;
  }
  else {
    Motor2_A_Speed += PITCH_PID;
    Motor4_A_Speed += PITCH_PID;
  }
  if (ROLL_PID < 0) {
    Motor1_B_Speed += ROLL_PID;
    Motor3_B_Speed += ROLL_PID;
  }
  else {
    Motor1_A_Speed += ROLL_PID;
    Motor3_A_Speed += ROLL_PID;
  }

  Motor1_Speed = Motor1_A_Speed + Motor1_B_Speed;
  Motor2_Speed = Motor2_A_Speed + Motor2_B_Speed;
  Motor3_Speed = Motor3_A_Speed + Motor3_B_Speed;
  Motor4_Speed = Motor4_A_Speed + Motor4_B_Speed;
  Limit_DC(&Motor1_Speed);
  Limit_DC(&Motor2_Speed);
  Limit_DC(&Motor3_Speed);
  Limit_DC(&Motor4_Speed);

  MOT_Mapping(); // 모터 매핑

  MOT_Update(); // 모터 구동
}

void MOT_Update() {
  // BLDC Part ESC - BLDC를 역으로 연결해 정방향, 역방향 사용
  analogWrite(BLDC_A, BLDC_Speed);
  analogWrite(BLDC_B, BLDC_Speed);

  // DC Part 라즈베리파이에서 어떤 함수로 구동할지 선택
  if (Motor1_Status == true) {
    analogWrite(Motor1_A, Motor1_Speed);
    analogWrite(Motor1_B, 0);
  }
  else {
    analogWrite(Motor1_B, Motor1_Speed);
    analogWrite(Motor1_A, 0);
  }
  
  if (Motor2_Status == true) {
    analogWrite(Motor2_A, Motor2_Speed);
    analogWrite(Motor2_B, 0);
  }
  else {
    analogWrite(Motor2_B, Motor2_Speed);
    analogWrite(Motor2_A, 0);
  }
  
  if (Motor3_Status == true) {
    analogWrite(Motor3_A, Motor3_Speed);
    analogWrite(Motor3_B, 0);
  }
  else {
    analogWrite(Motor3_B, Motor3_Speed);
    analogWrite(Motor3_A, 0);
  }
  
  if (Motor4_Status == true) {
    analogWrite(Motor4_A, Motor4_Speed);
    analogWrite(Motor4_B, 0);
  }
  else {
    analogWrite(Motor4_B, Motor4_Speed);
    analogWrite(Motor4_A, 0);
  }
}

void MOT_Mapping() {
  Motor1_Speed = map(Motor1_Speed, PID_MIN, PID_MAX, DC_SPEED_MIN, DC_SPEED_MAX);
  Motor2_Speed = map(Motor2_Speed, PID_MIN, PID_MAX, DC_SPEED_MIN, DC_SPEED_MAX);
  Motor3_Speed = map(Motor3_Speed, PID_MIN, PID_MAX, DC_SPEED_MIN, DC_SPEED_MAX);
  Motor4_Speed = map(Motor4_Speed, PID_MIN, PID_MAX, DC_SPEED_MIN, DC_SPEED_MAX);

  // 아래 코드는 DC모터의 정방향, 역방향 구분 용도

  if (Motor1_Speed > 0)
    Motor1_Status = true;
  else if (Motor1_Speed < 0)
    Motor1_Status = false;

  if (Motor2_Speed > 0)
    Motor2_Status = true;
  else if (Motor2_Speed < 0)
    Motor2_Status = false;

  if (Motor3_Speed > 0)
    Motor3_Status = true;
  else if (Motor3_Speed < 0)
    Motor3_Status = false;

  if (Motor4_Speed > 0)
    Motor4_Status = true;
  else if (Motor4_Speed < 0)
    Motor4_Status = false;
}

void MOT_Stability() {

  // DC모터를 수평으로 돌리게끔 라즈베리파이에서 코딩
  
}

// 계산된 DC모터스피드값이 정해진 DC모터스피드 값의 범위를 벗어나지 않도록 한계 지정
void Limit_DC(int *value) {  // -80~+80으로 할지 -20~+20으로 할지 미정(테스트결과에따라)
  if (*value >= DC_SPEED_MAX)
    *value = DC_SPEED_MAX;
  else if (*value <= DC_SPEED_MIN)
    *value = DC_SPEED_MIN;
}

// I게인 값이 계속 누적되서 커지지 않도록 한계값 설정
void Limit_I(double *value) {
  if (*value >= 100)
    *value = 100;
  else if (*value <= -100)
    *value = -100;
}

// BLDC의 값이 BLDC_Speed값을 벗어나지 않도록 한계 지정
void Limit_BLDC(int *value) {
  if (*value >= BLDC_SPEED_MAX)
    *value = BLDC_SPEED_MAX;
  else if (*value <= BLDC_SPEED_MIN)
    *value = BLDC_SPEED_MIN;
}
