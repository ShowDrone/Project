
#define SPEED_MAX 2000 //예시
#define SPEED_MIN 1000
#define XY_MIN -30 // 상보필터 값에 맞게 셋팅
#define XY_MAX 30 // 
#define ROLL_MIN -30
#define ROLL_MAX 30
#define YAW_MIN -180
#define YAW_MAX 180

/*
브러시모터 2~9 브러시리스모터 10-11, PWM핀이여야함(테스트보드는 Arduino Mega)
테스트시 모터방향에 따라 선택
이 소스에서는 A2=LOW에 A1로 속도제어 (B도 동일)
*/

#define DC3_A 5 //A1, A2 Set
#define DC3_B 6
#define DC4_A 9
#define DC4_B 10


double const XY_P = 0.85, XY_I = 0.1, XY_D = 0.15; // PID 게인값으로 테스트를 통해 값 바꿔나가야 함
double const ROLL_P = 1, ROLL_I = 0.05, ROLL_D = 1;
double const YAW_P = 1, YAW_I = 0.05, YAW_D = 1;
double XY_ERR, XY_PERR, XY_ERR_P, XY_ERR_I = 0, XY_ERR_D, XY_PID;
double ROLL_ERR, ROLL_PERR, ROLL_ERR_P, ROLL_ERR_I = 0, ROLL_ERR_D, ROLL_PID;
double YAW_ERR, YAW_ERR_P, YAW_ERR_I = 0, YAW_PI;
double xy_PRE, roll_PRE;
int xy_Ctl, roll_Ctl, yaw_Ctl;
int xy_Ctl_Last, roll_Ctl_Last, yaw_Ctl_Last;
int DC3S_A, DC3S_B, DC4S_A, DC4S_B;
int motSpeed;

int dcSpeed = 200; // 파라미터

/*
Buf1  Roll값      Buf2 Pitch값       Buf3 Speed값       Buf4 Yaw값
-중심값 0x80, 129  -중심값 0x80, 129   -최소값 0x00, 0     -중심값 0x80, 129
-왼쪽값 0x58, 88   -전진값 0xA8, 168   -최대값 0xff, 255   -왼쪽값 0x50, 80
-오른쪽 0xA8, 168  -후진값 0x58,  88                     -오른쪽 0xB0, 176
*/

int time = millis();

void PID_init() {
  pinMode(DC3_A, OUTPUT);
  pinMode(DC3_B, OUTPUT);
  pinMode(DC4_A, OUTPUT);
  pinMode(DC4_B, OUTPUT);
  //모터 안정화
  MOT_Stop();
}

int uartTime = 0;

void PID_Update() {

  
  if (uartTime + 5 < millis()) {
    Control_UART_Update();
    uartTime = millis();
  }
  
  /*for(int i =1;i<5;i++) {
    Serial.print(" ");
    Serial.print(buf[i]);
  }
  Serial.println();*/

  xy_Ctl = map(buf[2], 88, 168, XY_MIN, XY_MAX);
  roll_Ctl = map(buf[1], 88, 168, ROLL_MIN, ROLL_MAX);
  yaw_Ctl = map(buf[4], 70, 176, YAW_MIN, YAW_MAX);
  motSpeed = map(buf[3], 0, 255, SPEED_MIN, SPEED_MAX);

  if (xy_Ctl < XY_MIN || xy_Ctl > XY_MAX)
    xy_Ctl = xy_Ctl_Last;
  if (roll_Ctl < ROLL_MIN || roll_Ctl > ROLL_MAX)
    roll_Ctl = roll_Ctl_Last;
  if (yaw_Ctl < YAW_MIN || yaw_Ctl > ROLL_MAX)
    yaw_Ctl = yaw_Ctl_Last;

  xy_Ctl_Last = xy_Ctl;
  roll_Ctl_Last = roll_Ctl;
  yaw_Ctl_Last = yaw_Ctl;


  AccelGyro_Update();
  int targetPoint = 0;
  //PITCH
  XY_ERR = targetPoint - pitch; //목표값 - 현재값
  XY_PERR = (pitch - xy_PRE); //DT; //  기울기 차이/샘플링 주기
  XY_ERR_P = XY_ERR * XY_P; // 오차*P게인
  XY_ERR_I = XY_ERR_I + (XY_ERR * XY_I) * DT;
  Limit_I(&XY_ERR_I);
  XY_ERR_D = XY_PERR * XY_D; // 기울기 차이*D게인
  XY_PID = XY_ERR_P + XY_ERR_I + XY_ERR_D;
  xy_PRE = pitch;

  //ROLL
  /*ROLL_ERR = targetPoint - roll;
  ROLL_PERR = (roll - roll_PRE) / DT;
  ROLL_ERR_P = ROLL_ERR * ROLL_P;
  ROLL_ERR_I = ROLL_ERR_I + (ROLL_ERR * ROLL_I) * DT;
  Limit_I(&ROLL_ERR_I);
  ROLL_ERR_D = ROLL_PERR * ROLL_D;
  ROLL_PID = ROLL_ERR_P + ROLL_ERR_I + ROLL_ERR_D;
  roll_PRE = roll;*/

  //YAW
  YAW_ERR = targetPoint - yaw;
  YAW_ERR_P = YAW_ERR * YAW_P;
  YAW_ERR_I = YAW_ERR_I + (YAW_ERR * YAW_I) * DT;
  Limit_I(&YAW_ERR_I);
  YAW_PI = YAW_ERR_P + YAW_ERR_I;


  /*
  Serial.print("Gyro: "); Serial.print(MgZ/182.02);
  Serial.print(" yaw: "); Serial.print(yaw);
  Serial.print(" YAW_P: "); Serial.print(YAW_ERR_P);
  Serial.print(" YAW_I: "); Serial.print(YAW_ERR_I);
  Serial.print(" YAW_PI: "); Serial.println(YAW_PI);
  */

  /*
  아래 파라미터 값은 전부 예시
  테스트를 통해 값을 찾아내야 함!
  */


  /*
  조작 값에 따라 PID값의 변화를 체크
  조작값 buf1[roll], buf2[pitch], buf3[throttle], buf4[yaw]
  아래는 Example
  buf1 왼쪽 감소, 오른쪽 증가
  buf2 위쪽 증가, 아래쪽 감소
  buf4 왼쪽 감소, 오른쪽 증가

  buf1 값이 증가하면 드론이 오른쪽으로 감, 감소하면 왼쪽으로 감
  buf2 값이 증가하면 드론이 앞으로 감, 감소하면 뒤로 기움
  buf4 값이 증가하면 동체부 아직 미정
  buf1, buf2에 의해 얼마나 기울지는 로터부의 yaw값을 이용

  */


  if (motSpeed < 1050);
  {
    MOT_Stop(); // 로터부 수평
  }


  // 정방향 A=HIGH, B=LOW
  // 정방향이 pitch를 앞쪽으로

  // 역방향 A=LOW, B=HIGH;
  // 역방향이 pitch를 뒤쪽으로


  if (XY_PID > 0) {
    DC3S_A = dcSpeed + abs(XY_PID);
    DC3S_B = 0;
    //DC2S_A = 0;
    //DC2S_B = dcSpeed+abs(XY_PID);
  }

  else if (XY_PID < 0) {
    DC3S_A = 0;
    DC3S_B = dcSpeed + abs(XY_PID);
    //DC2S_A = dcSpeed+abs(XY_PID);
    //DC2S_B = 0;
  }

  /*Serial.print(" XY_PID :"+(String)+XY_PID);
  Serial.print(" / "+(String)DC3S_A);
  Serial.println(" / "+(String)DC3S_B);*/

  MOT_Update();
}

inline void MOT_Update() {

  analogWrite(DC3_A, DC3S_A);
  analogWrite(DC3_B, DC3S_B);

  //analogWrite(DC4_A,DC4S_B);
  //analogWrite(DC4_B,DC4S_A);
}

void MOT_Stop() {
}

void Limit_I(double *value) {
  if (*value >= 100)
    *value = 100;
  else if (*value <= -100)
    *value = -100;
}

void Limit_Speed(int *value) {
  if (*value >= SPEED_MAX)
    *value = SPEED_MAX;
  else if (*value <= SPEED_MIN)
    *value = SPEED_MIN;
}
