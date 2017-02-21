

#include "BLDC.h"

 
long map(long x, long in_min, long in_max, long out_min, long out_max);
void setBLDCPin();
void Limit_BLDC(double *value);

void setBLDCPin() {
  pinMode(BLDC_A, OUTPUT);
  pinMode(BLDC_B, OUTPUT);
}

double getBLDCSpeed() {
	currentSpeed = controlSpeed();
	Limit_BLDC(&currentSpeed);
	currentSpeed = map(currentSpeed, throttleMin, throttleMax, BLDC_SPEED_MIN, BLDC_SPEED_MAX);
	return currentSpeed;
}

// BLDC 모터 한계값 지정
void Limit_BLDC(double *value) {
  if (*value >= BLDC_SPEED_MAX)
    *value = BLDC_SPEED_MAX;
  else if (*value <= BLDC_SPEED_MIN)
    *value = BLDC_SPEED_MIN;
}


long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
