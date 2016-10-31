
#define BLDC_SPEED_MAX 255 // 예시 값
#define BLDC_SPEED_MIN 0
#define DC_SPEED_MAX 100 // 예시 값
#define DC_SPEED_MIN 0
#define PID_MAX 80 //   PITCH의 PID + ROLL의 PID + YAW의 PID를 한 값들의 최대 범위
#define PID_MIN -80 //  // 최소 범위
#define Motor1_A 2 // Direction_A            모터 변수 이름 의미
#define Motor1_B 3 // Direction_B                   [전]
#define Motor2_A 4 // Direction_A                 1번 모터
#define Motor2_B 5 // Direction_B        [좌] 4번 모터    2번 모터 [우]
#define Motor3_A 6 // Direction_A                 3번 모터
#define Motor3_B 7 // Direction_B                   [후]
#define Motor4_A 8 // Direction_A
#define Motor4_B 9 // Direction_B
#define BLDC_A 54 // Speed A0
#define BLDC_B 55 // Speed A1

// 정방향, 역방향을 구분하기 위한 변수
boolean Motor1_Status = 0, Motor2_Status = 0;
boolean Motor3_Status = 0, Motor4_Status = 0;

// Motor1~5까지의 A, B스피드 PID연산을 위한
int Motor1_A_Speed, Motor1_B_Speed;
int Motor2_A_Speed, Motor2_B_Speed;
int Motor3_A_Speed, Motor3_B_Speed;
int Motor4_A_Speed, Motor4_B_Speed;

// Motor의 최종스피드
int Motor1_Speed, Motor2_Speed;
int Motor3_Speed, Motor4_Speed;

int BLDC_Speed; // BLDC 모터 스피드

void Fly_init() { // Flying Initialize
  pinMode(Motor1_A, OUTPUT);
  pinMode(Motor1_B, OUTPUT);
  pinMode(Motor2_A, OUTPUT);
  pinMode(Motor2_B, OUTPUT);
  pinMode(Motor3_A, OUTPUT);
  pinMode(Motor3_B, OUTPUT);
  pinMode(Motor4_A, OUTPUT);
  pinMode(Motor4_B, OUTPUT);
  pinMode(BLDC_A, OUTPUT);
  pinMode(BLDC_B, OUTPUT);
}

/*
 *  PID 결과 값을 가지고 방향 제어 계산과 모터 매핑 그리고 작동 함수를 실행하는 함수
 */

void Fly_Update() {
  
  Limit_BLDC(&BLDC_Speed);
  
  if (YAW_PI > 0) {
    Motor1_A_Speed = YAW_PI;
    Motor2_A_Speed = YAW_PI;
    Motor3_A_Speed = YAW_PI;
    Motor4_A_Speed = YAW_PI;
    Motor1_B_Speed = 0;
    Motor2_B_Speed = 0;
    Motor3_B_Speed = 0;
    Motor4_B_Speed = 0;
  }
  else {
    Motor1_A_Speed = 0;
    Motor2_A_Speed = 0;
    Motor3_A_Speed = 0;
    Motor4_A_Speed = 0;
    Motor1_B_Speed = YAW_PI;
    Motor2_B_Speed = YAW_PI;
    Motor3_B_Speed = YAW_PI;
    Motor4_B_Speed = YAW_PI;
  }
  if (PITCH_PID > 0) {
    Motor2_A_Speed += PITCH_PID;
    Motor4_A_Speed += PITCH_PID;
  }
  else {
    Motor2_B_Speed += PITCH_PID;
    Motor4_B_Speed += PITCH_PID;
  }
  if (ROLL_PID > 0) {
    Motor1_A_Speed += ROLL_PID;
    Motor3_A_Speed += ROLL_PID;
  }
  else {
    Motor1_B_Speed += ROLL_PID;
    Motor3_B_Speed += ROLL_PID;
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
  // 라즈베리파이에선 Servo모터 라이브러리를 사용하는게 안정성이 높아보임
  analogWrite(BLDC_A, BLDC_Speed);
  analogWrite(BLDC_B, BLDC_Speed);

  // DC Part 라즈베리파이에서 어떤 함수로 구동할지 선택
  if (Motor1_Status == true) {
    digitalWrite(Motor1_A, Motor1_Speed);
    digitalWrite(Motor1_B, 0);
  }
  else {
    digitalWrite(Motor1_B, Motor1_Speed);
    digitalWrite(Motor1_A, 0);
  }

  if (Motor2_Status == true) {
    digitalWrite(Motor2_A, Motor2_Speed);
    digitalWrite(Motor2_B, 0);
  }
  else {
    digitalWrite(Motor2_B, Motor2_Speed);
    digitalWrite(Motor2_A, 0);
  }

  if (Motor3_Status == true) {
    digitalWrite(Motor3_A, Motor3_Speed);
    digitalWrite(Motor3_B, 0);
  }
  else {
    digitalWrite(Motor3_B, Motor3_Speed);
    digitalWrite(Motor3_A, 0);
  }

  if (Motor4_Status == true) {
    digitalWrite(Motor4_A, Motor4_Speed);
    digitalWrite(Motor4_B, 0);
  }
  else {
    digitalWrite(Motor4_B, Motor4_Speed);
    digitalWrite(Motor4_A, 0);
  }
}

//  PID 
void MOT_Mapping() {
  Motor1_Speed = map(Motor1_Speed, PID_MIN, PID_MAX, DC_SPEED_MIN, DC_SPEED_MAX);
  Motor2_Speed = map(Motor2_Speed, PID_MIN, PID_MAX, DC_SPEED_MIN, DC_SPEED_MAX);
  Motor3_Speed = map(Motor3_Speed, PID_MIN, PID_MAX, DC_SPEED_MIN, DC_SPEED_MAX);
  Motor4_Speed = map(Motor4_Speed, PID_MIN, PID_MAX, DC_SPEED_MIN, DC_SPEED_MAX);

  // 아래 코드는 DC모터의 정방향, 역방향 구분 용도
  if (Motor1_Speed > 0)
    Motor1_Status = true;
  else
    Motor1_Status = false;

  if (Motor2_Speed > 0)
    Motor2_Status = true;
  else
    Motor2_Status = false;

  if (Motor3_Speed > 0)
    Motor3_Status = true;
  else
    Motor3_Status = false;

  if (Motor4_Speed > 0)
    Motor4_Status = true;
  else                               
    Motor4_Status = false;
}

// 계산된 DC모터스피드값이 정해진 DC모터스피드 값의 범위를 벗어나지 않도록 한계 지정
void Limit_DC(int *value) {  // -80~+80으로 할지 -20~+20으로 할지 미정(테스트결과에따라)
  if (*value >= PID_MAX)
    *value = PID_MAX;
  else if (*value <= PID_MIN)
    *value = PID_MIN;
}

// BLDC의 값이 BLDC_Speed값을 벗어나지 않도록 한계 지정
void Limit_BLDC(int *value) {
  if (*value >= BLDC_SPEED_MAX)
    *value = BLDC_SPEED_MAX;
  else if (*value <= BLDC_SPEED_MIN)
    *value = BLDC_SPEED_MIN;
}
