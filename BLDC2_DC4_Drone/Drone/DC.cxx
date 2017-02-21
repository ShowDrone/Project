
#include "DC.h"

void Limit_DC(double *value);
long map(long x, long in_min, long in_max, long out_min, long out_max);

struct DCMotor {
	bool Status;
	double ASpeed;
	double BSpeed;
	double currentSpeed;
};

static struct DCMotor DC1;
static struct DCMotor DC2;
static struct DCMotor DC3;
static struct DCMotor DC4;

void setDCPin() { 
  pinMode(DC1_A, OUTPUT);
  pinMode(DC1_B, OUTPUT);
  pinMode(DC2_A, OUTPUT);
  pinMode(DC2_B, OUTPUT);
  pinMode(DC3_A, OUTPUT);
  pinMode(DC3_B, OUTPUT);
  pinMode(DC4_A, OUTPUT);
  pinMode(DC4_B, OUTPUT);
}

// dc 모터 작동 알고리즘
void getDCSpeed(double ROLL_PID, double PITCH_PID, double YAW_PI) {
	
	if (YAW_PI > 0) {
		DC1.ASpeed = YAW_PI;
		DC2.ASpeed = YAW_PI;
		DC3.ASpeed = YAW_PI;
		DC4.ASpeed = YAW_PI;
		DC1.BSpeed = 0;
		DC2.BSpeed = 0;
		DC3.BSpeed = 0;
		DC4.BSpeed = 0;
	}
	else {
		DC1.ASpeed = 0;
		DC2.ASpeed = 0;
		DC3.ASpeed = 0;
		DC4.ASpeed = 0;
		DC1.BSpeed = YAW_PI;
		DC2.BSpeed = YAW_PI;
		DC3.BSpeed = YAW_PI;
		DC4.BSpeed = YAW_PI;
	}
	
	if (PITCH_PID > 0) {
		DC2.ASpeed += PITCH_PID;
		DC4.ASpeed += PITCH_PID;
	}
	else {
		DC2.BSpeed += PITCH_PID;
		DC4.BSpeed += PITCH_PID;	
	}
	
	if (ROLL_PID < 0) {
		DC1.ASpeed += ROLL_PID;
		DC3.ASpeed += ROLL_PID;
	}
	else {
		DC1.BSpeed += ROLL_PID;
		DC3.BSpeed += ROLL_PID;	
	}
	DC1.currentSpeed = DC1.ASpeed + DC1.BSpeed;
	DC2.currentSpeed = DC2.ASpeed + DC2.BSpeed;
	DC3.currentSpeed = DC3.ASpeed + DC3.BSpeed;
	DC4.currentSpeed = DC4.ASpeed + DC4.BSpeed;
}

double setDC1Speed() {
	Limit_DC(&DC1.currentSpeed);
	DC1.currentSpeed = map(DC1.currentSpeed, PID_MIN, PID_MAX, DC_SPEED_MIN, DC_SPEED_MAX);
	 if (DC1.currentSpeed > 0)
		DC1.Status = true;
     else
		DC1.Status = false;
	return DC1.currentSpeed;
}

double setDC2Speed() {
	Limit_DC(&DC2.currentSpeed);
	DC2.currentSpeed = map(DC2.currentSpeed, PID_MIN, PID_MAX, DC_SPEED_MIN, DC_SPEED_MAX);
	if (DC2.currentSpeed > 0)
		DC2.Status = true;
     else
		DC2.Status = false;
	return DC2.currentSpeed;
}

double setDC3Speed() {
	Limit_DC(&DC3.currentSpeed);
	DC3.currentSpeed = map(DC3.currentSpeed, PID_MIN, PID_MAX, DC_SPEED_MIN, DC_SPEED_MAX);
	if (DC3.currentSpeed > 0)
		DC3.Status = true;
     else
		DC3.Status = false;
	return DC3.currentSpeed;
}

double setDC4Speed() {
	Limit_DC(&DC4.currentSpeed);
	DC4.currentSpeed = map(DC4.currentSpeed, PID_MIN, PID_MAX, DC_SPEED_MIN, DC_SPEED_MAX);
	if (DC4.currentSpeed > 0)
		DC4.Status = true;
     else
		DC4.Status = false;
	return DC4.currentSpeed;
}

// DC 모터 한계 값 지정
void Limit_DC( double *value) {
	if (*value >= PID_MAX)
		*value = PID_MAX;
	else if (*value <= PID_MIN)
		*value = PID_MIN;
}                

long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
