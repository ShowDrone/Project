
#include <iostream>
#include <math.h>
#include "wiringPi.h"

#define BLDC_SPPED_MAX 255
#define BLDC_SPPED_MIN 0
#define DC_SPEED_MAX 100
#define DC_SPEED_MIN 0
#define PID_MAX 80
#define PID_MIN -80
#define DC1_A 2
#define DC1_B 3
#define DC2_A 4
#define DC2_B 5
#define DC3_A 6
#define DC3_B 7
#define DC4_A 8
#define DC4_B 9

void setDCPin();
void getDCSpeed(double ROLL_PID, double PITCH_PID, double YAW_PI);
double setDC1Speed();
double setDC2Speed();
double setDC3Speed();
double setDC4Speed();
void Limit_DC( double *value);
long map(long x, long in_min, long in_max, long out_min, long out_max);
