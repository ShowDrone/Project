

#include <stdio.h>
#include "wiringPi.h"
#include "BLDC.h"
#include "DC.h"
#include "AccelGyro.h"
#include "Landing.h"
#include "softServo.h"

#define PITCH_MIN -30 // pitch 값 범위 (for mapping)
#define PITCH_MAX 30
#define ROLL_MIN -30
#define ROLL_MAX 30
#define YAW_MIN -20 // 테스트하면서 30으로 할지 20으로 할지 결정
#define YAW_MAX 20

// temporary
#define SPEED_MIN 0
#define SPEED_MAX 1

// temporary
#define AILERON_MIN 0
#define AILERON_MAX 1

#define ELEVATOR_MIN 0
#define ELEVATOR_MAX 1

#define THROTTLE_MIN 0
#define THROTTLE_MAX 1

#define RUDDER_MIN 0
#define RUDDER_MAX 1

struct _PID {
	double P, I, D;
	double ERR, PERR, ERR_P, ERR_I, ERR_D;
	double _PI;
	double PID;
	double PRE;
	int Control, lastControl;
	double Data;
};

struct _PID pitch;
struct _PID roll;
struct _PID yaw;

void updateBLDC();
void updateDC();
void updateLANDING();
void *updatePID();
void Limit_I(double *value);

double aileron, elevator, rudder;
double throttle, lastThrottle; 

double DC1, DC2, DC3, DC4;
double BLDC1, BLDC2;
 
