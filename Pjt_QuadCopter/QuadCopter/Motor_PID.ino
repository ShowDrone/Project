
#include "rc_rx.h";

//서보모터 setup
#include<Servo.h>
Servo motF_L;
Servo motF_R;
Servo motB_L;
Servo motB_R;

int Motor_roll = 0;
int motSpeed;
int throttle = 0;
double ch1, ch2, ch3, ch4;
int motAC=0, motBD=0;

#include <math.h>

//PID setup
#include <PID_v1.h>

double const PITCH_P=4, PITCH_I=1.0, PITCH_D=1; // PID 게인값으로 테스트를 통해 값 바꿔나가야 함
double const ROLL_P=4, ROLL_I=1.0, ROLL_D=1;
double const YAW_P=1.800, YAW_I=0.05, YAW_D=1;
double input_X=0, input_Y=0, input_Z=0;
double roll_PRE=0, pitch_PRE=0, yaw_PRE=0;
double Outpoint_X=0, Outpoint_Y=0, Outpoint_Z=0;
double ROLL_ERR=0, PITCH_ERR=0, YAW_ERR=0;
double ROLL_AERR=0, PITCH_AERR=0, YAW_AERR=0;
double ROLL_PERR=0, PITCH_PERR=0;
double ROLL_ERR_P=0, ROLL_ERR_I=0, ROLL_ERR_D=0;
double PITCH_ERR_P=0, PITCH_ERR_I=0, PITCH_ERR_D=0;
double YAW_ERR_P=0, YAW_ERR_I=0;
double ROLL_ERR_PRE=0, PITCH_ERR_PRE=0;
double ROLL_PID=0,PITCH_PID=0,YAW_PI=0;

#define MAX_SPEED 2000 // 최고속도
#define MIN_SPEED 1000 // 최저속도
#define PITCH_MIN -30
#define PITCH_MAX 30
#define ROLL_MIN -30
#define ROLL_MAX 30
#define YAW_MIN -30
#define YAW_MAX 30
#define PITCH_INFLUENCE 100
#define ROLL_INFLUENCE 100
#define YAW_INFLUENCE 100

/*
모터 회전 첫번째 탭 참조
1=motA, 2=motB, 3=motC, 4=motD
*/
int motA=0, motB=0, motC=0, motD=0;

//PID(input,output,Setpoint,Pgain,Igain,Dgain,Controldirection)
/*
PID pid_X(&input_X,&Outpoint_X,&ch2,ROLL_P,ROLL_I,ROLL_D,REVERSE); // roll
PID pid_Y(&input_Y,&Outpoint_Y,&ch1,PITCH_P,PITCH_I,PITCH_D,REVERSE); // pitch
PID pid_Z(&input_Z,&Outpoint_Z,&ch4,YAW_P,YAW_I,YAW_D,REVERSE); // Yaw
*/
void Motor_PID_setup() {
  
   init_rc_rx(); // RF 통신 setup
  
  motF_L.attach(8);  // 앞 - 왼쪽 모터
  motF_R.attach(7); // 앞 - 오른쪽 모터
  motB_L.attach(10); // 뒤 - 왼쪽 모터
  motB_R.attach(11); // 뒤 - 오른쪽 모터
  
  // 안정성을 위해 시동 시 모터 전체 OFF
  motF_L.writeMicroseconds(MIN_SPEED);
  motB_R.writeMicroseconds(MIN_SPEED);
  motF_R.writeMicroseconds(MIN_SPEED);
  motB_L.writeMicroseconds(MIN_SPEED);
  delay(2500);
  
  // PID Auto Setting
  /*
  pid_X.SetMode(AUTOMATIC);
  pid_X.SetOutputLimits(-ROLL_INFLUENCE,ROLL_INFLUENCE);
  pid_Y.SetMode(AUTOMATIC);
  pid_Y.SetOutputLimits(-PITCH_INFLUENCE,PITCH_INFLUENCE);
  pid_Z.SetMode(AUTOMATIC);
  pid_Z.SetOutputLimits(-YAW_INFLUENCE,YAW_INFLUENCE);
  */
}

void Motor_PID()
{
  /*
  ******read RF data******
  CH1 Pitch 오른쪽 위, 아래
  CH2 Roll 오른쪽 좌, 우
  CH3 Velocity(throttle)
  CH4 Yaw 왼쪽 좌, 우
  왼쪽100 오른쪽 0
  */
  read_rc_rx();
  ch1=floor(CH1); // 소숫점 이하 제거
  ch1=floor(CH1);
  ch2=floor(CH2); 
  ch3=floor(CH3);
  ch4=floor(CH4);
  

  ch1=map(ch1,0,100,PITCH_MIN,PITCH_MAX);
  ch2=map(ch2,0,100,ROLL_MIN,ROLL_MAX);
  ch4=map(ch4,0,100,YAW_MIN,YAW_MAX);
  /*Serial.print(ch1); Serial.print(" ");
  Serial.print(ch2); Serial.print(" ");
  Serial.print(ch3); Serial.print(" ");
  Serial.println(ch4);*/
  
  throttle = ch3;

  motSpeed = map(throttle,0,100,MIN_SPEED,MAX_SPEED); //throttle 범위 매핑
  if(motSpeed <= 1130)
  {
    motSpeed = 1000;
  }
  //Serial.println(motSpeed);
  
  /*
  input_X = abs(roll);
  input_Y = abs(pitch);
  input_Z = abs(yaw);
  */
  
  /*Serial.print("Input_X: "); Serial.print(input_X);
  Serial.print(" Input_Y: "); Serial.print(input_Y);
  Serial.print(" Input_Z: "); Serial.println(input_Z);*/
  
  input_X = roll;
  input_Y = pitch;
  input_Z = yaw;
  
  
  // PID gain Set
  /*
  pid_X.SetTunings(ROLL_P,ROLL_I,ROLL_D);
  pid_Y.SetTunings(PITCH_P,PITCH_I,PITCH_D);
  pid_Z.SetTunings(YAW_P,YAW_I,YAW_D);
  
  // PID ON
  pid_X.Compute();
  pid_Y.Compute();
  pid_Z.Compute();
  */

  // PITCH 컨트롤 
  PITCH_ERR = ch1-input_Y; // 오차
  PITCH_PERR = (pitch-pitch_PRE)/DT; // (현재 기울기-이전 기울기)/샘플링 주기
  
  PITCH_ERR_P = PITCH_ERR*PITCH_P;
  PITCH_ERR_I = PITCH_ERR_I + (PITCH_ERR*PITCH_I)*DT;
  Limit(&PITCH_ERR_I);
  PITCH_ERR_D = PITCH_PERR*PITCH_D;
  pitch_PRE = pitch;
  
  PITCH_PID = PITCH_ERR_P+PITCH_ERR_I+PITCH_ERR_D;
  ////////////////////////////////////////////
  
  // ROLL 컨트롤
  ROLL_ERR = ch2-input_X;
  ROLL_PERR = (roll-roll_PRE)/DT;
  //ROLL_PERR = input_X-input_X_PRE;
  
  ROLL_ERR_P = ROLL_ERR*ROLL_P;
  ROLL_ERR_I = ROLL_ERR_I + (ROLL_I*ROLL_ERR)*DT;
  Limit(&ROLL_ERR_I);
  ROLL_ERR_D = ROLL_PERR*ROLL_D;
  roll_PRE = roll;
  
  ROLL_PID = ROLL_ERR_P+ROLL_ERR_I+ROLL_ERR_D;
  ////////////////////////////////////////////
  
  // YAW 컨트롤
  YAW_ERR = ch4-input_Z;
  YAW_AERR += YAW_ERR;
  
  YAW_ERR_P = YAW_ERR*YAW_P;
  YAW_ERR_I += YAW_AERR*YAW_I*DT;
  Limit(&YAW_ERR_I);
  
  YAW_PI = YAW_ERR_P+YAW_ERR_I;
  ////////////////////////////////////////////

  /*Serial.print(" pitch:"); Serial.print(roll);
  Serial.print("  roll:"); Serial.print(roll_PRE);
  Serial.print("  yaw:"); Serial.println(ROLL_PERR);*/
  /*Serial.print("dt:"); Serial.print(dt); 
  Serial.print(" pitch:"); Serial.print(pitch);
  Serial.print("  roll:"); Serial.print(roll);
  Serial.print("  yaw:"); Serial.println(yaw);*/
  
  /*Serial.print("pitch:"); Serial.print(PITCH_PID);
  Serial.print(" roll:"); Serial.print(ROLL_PID);
  Serial.print(" yaw:"); Serial.println(YAW_PI);*/
  
  /*
  pitch: 앞 증가, 아래 감소 (오른쪽 위, 아래)
   roll: 왼쪽 증가, 오른쪽 감소 (오른쪽 좌, 우)
    yaw: 왼쪽 증가, 오른쪽 감소라고 가정
  */
 
  // 모터방향에 맞게 생각 PITCH, ROLL, YAW 각각 따로
  /*motA = -PITCH_PID - ROLL_PID - YAW_PI + motSpeed;
  motB = -PITCH_PID + ROLL_PID + YAW_PI + motSpeed;
  motC = PITCH_PID - ROLL_PID - YAW_PI + motSpeed;
  motD = PITCH_PID + ROLL_PID + YAW_PI + motSpeed;*/
  
  motA = (PITCH_PID+ROLL_PID)*0.5 + motSpeed;
  motB = (PITCH_PID-ROLL_PID)*0.5 + motSpeed;
  motC = (-PITCH_PID-ROLL_PID)*0.5 + motSpeed;
  motD = (-PITCH_PID+ROLL_PID)*0.5 + motSpeed;
  
  Limit_speed(&motA);
  Limit_speed(&motB);
  Limit_speed(&motC);
  Limit_speed(&motD);
  
  if(motA<1030||motB<1030||motC<1030||motD<1030)
  {
    motA = 1000;
    motB = 1000;
    motC = 1000;
    motD = 1000;
  }
  
  
  /*Serial.print(motA); Serial.print("  ");
  Serial.print(motB); Serial.print("  ");
  Serial.print(motC); Serial.print("  ");
  Serial.print(motD); Serial.println();*/
  
  
 Motor_update(); 
  
  
  
}


// inline = 연산속도 up, but 짧은 함수에만 OK
inline void Motor_update() {
  //motF_L.writeMicroseconds(motA);
  //motF_R.writeMicroseconds(motB);
  //motB_R.writeMicroseconds(motC);
  //motB_L.writeMicroseconds(motD);
}

void Limit(double *value) {
  if(*value < -100)
  {
    *value = -100;
  }
  else if(*value > 100)
  {
    *value = 100;
  }
}

void Limit_speed(int *value) {
  if(*value < MIN_SPEED)
  {
    *value = MIN_SPEED;
  }
  else if(*value > 1800)
  {
    //*value = MAX_SPEED;
    *value = 1800;
  }
}


