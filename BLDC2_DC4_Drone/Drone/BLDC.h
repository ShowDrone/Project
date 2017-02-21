

#include "wiringPi.h"
#include "Network.h"

#define BLDC_SPEED_MAX 255 // 예시 값
#define BLDC_SPEED_MIN 0
#define BLDC_A 54 // Speed A0
#define BLDC_B 55 // Speed A1


long map(long x, long in_min, long in_max, long out_min, long out_max);
void Limit_BLDC(int *value);
void setBLDCPin();
double getBLDCSpeed();

 // 나중에 Control.cpp / .h 만들어서 대체하기 컴파일 에러 안나게 하는 용도.
