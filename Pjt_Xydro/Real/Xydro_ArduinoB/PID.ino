
#define SPEED_MAX 255 //예시
#define SPEED_MIN 0
#define XY_MIN -30 // 상보필터 값에 맞게 셋팅
#define XY_MAX 30 // 
#define ROLL_MIN -30
#define ROLL_MAX 30
#define YAW_MIN -20
#define YAW_MAX 20

#define DC1_A 3 //
#define DC1_B 5 // 
#define DC2_A 6 //
#define DC2_B 9 // 
#define BLDC_A 10
#define BLDC_B 11

double const XY_P = 0.85, XY_I = 0.1, XY_D = 0.15; // PID 게인값으로 테스트를 통해 값 바꿔나가야 함
double const ROLL_P = 1, ROLL_I = 0.05, ROLL_D = 1;
double const YAW_P = 1, YAW_I = 0.05, YAW_D = 1;
double XY_ERR, XY_PERR, XY_ERR_P, XY_ERR_I = 0, XY_ERR_D, XY_PID;
double ROLL_ERR, ROLL_PERR, ROLL_ERR_P, ROLL_ERR_I = 0, ROLL_ERR_D, ROLL_PID;
double YAW_ERR, YAW_ERR_P, YAW_ERR_I = 0, YAW_PI;
double xy_PRE, roll_PRE;
int xy_Ctl, roll_Ctl, yaw_Ctl;
int xy_Ctl_Last, roll_Ctl_Last, yaw_Ctl_Last;
int DC1S_A, DC1S_B, DC2S_A, DC2S_B;
int BLDC1_S, BLDC2_S, motSpeed;
boolean level = false;

int dcSpeed = 200; // 파라미터

/*
Buf1  Roll값      Buf2 Pitch값       Buf3 Speed값       Buf4 Yaw값
-중심값 0x80, 129  -중심값 0x80, 129   -최소값 0x00, 0     -중심값 0x80, 129
-왼쪽값 0x58, 88   -전진값 0xA8, 168   -최대값 0xff, 255   -왼쪽값 0x50, 80
-오른쪽 0xA8, 168  -후진값 0x58,  88                     -오른쪽 0xB0, 176
*/

int time = millis();

void PID_init() {
  pinMode(DC1_B, OUTPUT);
  pinMode(DC1_A, OUTPUT);
  pinMode(DC2_B, OUTPUT);
  pinMode(DC2_A, OUTPUT);
  pinMode(BLDC_B, OUTPUT);
  pinMode(BLDC_A, OUTPUT);
  //모터 안정화
  MOT_Stop();
}

int uartTime = 0;
int emergencyTime = 0;
int emergencySpeed = 0;

void PID_Update() {

  if (uartTime + 5 < millis()) {
    Control_UART_Update();
    uartTime = millis();
  }

  xy_Ctl = map(buf[2], 88, 168, XY_MIN, XY_MAX);
  roll_Ctl = map(buf[1], 88, 168, ROLL_MIN, ROLL_MAX);
  yaw_Ctl = map(buf[4], 70, 176, YAW_MIN, YAW_MAX);

  if (Emergency == false)
    motSpeed = buf[3];

  if (Emergency == true) {
    if (motSpeed >= 0) {
      if (motSpeed >= 30)
        emergencySpeed = motSpeed / 10;
      else
        emergencySpeed = motSpeed;
      if (emergencyTime + 1000 > millis()) {
        motSpeed -= emergencySpeed;
        emergencyTime = millis();
      }
    }
  }

  if (xy_Ctl < XY_MIN || xy_Ctl > XY_MAX) {
    xy_Ctl = xy_Ctl_Last;
  }
  if (roll_Ctl < ROLL_MIN || roll_Ctl > ROLL_MAX) {
    roll_Ctl = roll_Ctl_Last;
  }
  if (yaw_Ctl < YAW_MIN || yaw_Ctl > ROLL_MAX) {
    yaw_Ctl = yaw_Ctl_Last;
  }

  xy_Ctl_Last = xy_Ctl;

  roll_Ctl_Last = roll_Ctl;
  yaw_Ctl_Last = yaw_Ctl;


  AccelGyro_Update();


  if (Emergency == true) {
    pitch = 0;
    roll = 0;
    yaw = 0;
  }

  //PITCH
  //XY_ERR = xy_Ctl - pitch; //목표값 - 현재값
  XY_ERR = 0 - pitch; //목표값 - 현재값
  XY_PERR = (pitch - xy_PRE); //DT; //  기울기 차이/샘플링 주기
  XY_ERR_P = XY_ERR * XY_P; // 오차*P게인
  XY_ERR_I = XY_ERR_I + (XY_ERR * XY_I) * DT;
  Limit_I(&XY_ERR_I);
  XY_ERR_D = XY_PERR * XY_D; // 기울기 차이*D게인
  XY_PID = XY_ERR_P + XY_ERR_I + XY_ERR_D;
  xy_PRE = pitch;

  //ROLL
  ROLL_ERR = roll_Ctl - roll;
  ROLL_PERR = (roll - roll_PRE) / DT;
  ROLL_ERR_P = ROLL_ERR * ROLL_P;
  ROLL_ERR_I = ROLL_ERR_I + (ROLL_ERR * ROLL_I) * DT;
  Limit_I(&ROLL_ERR_I);
  ROLL_ERR_D = ROLL_PERR * ROLL_D;
  ROLL_PID = ROLL_ERR_P + ROLL_ERR_I + ROLL_ERR_D;
  roll_PRE = roll;

  //YAW
  YAW_ERR = yaw_Ctl - yaw;
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

  //얼마나 기울지 파악, PID제어

  Limit_Speed(&motSpeed);

  if (motSpeed < 1050) {
    level = true;
    MOT_Stop(); // 로터부 수평
  }

  if (XY_PID > 0) {
    DC2S_A = dcSpeed + abs(XY_PID);
    DC2S_B = 0;
    //DC2S_A = 0;
    //DC2S_B = dcSpeed+abs(XY_PID);
  }

  else if (XY_PID < 0) {
    DC2S_A = 0;
    DC2S_B = dcSpeed + abs(XY_PID);
    //DC2S_A = dcSpeed+abs(XY_PID);
    //DC2S_B = 0;
  }

  if (YAW_PI > 0) {
    DC1S_A = dcSpeed + abs(YAW_PI);
    DC1S_B = 0;
    //DC2S_A = 0;
    //DC2S_B = dcSpeed+abs(XY_PID);
  }

  else if (YAW_PI < 0) {
    DC1S_A = 0;
    DC1S_B = dcSpeed + abs(YAW_PI);
    //DC2S_A = dcSpeed+abs(XY_PID);
    //DC2S_B = 0;
  }

  //Serial.print(" PID :"); Serial.println(YAW_PI);
  //Serial.print(" DC2_A: "); Serial.print(DC2S_A);
  //Serial.print(" DC2_B: "); Serial.println(DC2S_B);

  MOT_Update();
}

inline void MOT_Update() {
  //analogWrite(DC1_A, DC1S_A);
  //analogWrite(DC1_B,DC1S_B);
  analogWrite(DC2_A, DC2S_A);
  analogWrite(DC2_B, DC2S_B);
  //analogWrite(BLDC_A,motSpeed);
  //analogWrite(BLDC_B,motSpeed);
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
