

#ifndef __LANDING_H__
#define __LANDING_H__

#include "wiringPi.h"
#include "DC.h"
#include <time.h>
#define LANDING_TIME 5000 // ms단위이며, 랜딩 기어가 접히고 펴지는데 걸리는 시간(임의 값 테스트 필요)
#define LANDING1_A 10 // LANDING_A
#define LANDING1_B 11 // LANDING_B
#define LANDING2_A 12 // LANDING_A
#define LANDING2_B 13 // LANDING_B
#define LANDING_SWITCH 14

void setLandingPin();
bool getCurrentState();

bool landingState = true; // 드론은 비행할 때 빼고 랜딩기어가 항상 On(펴짐 상태)
bool landingStart = false; // 랜딩 기어의 접고 펴짐을 알리는 신호
bool landingOnce = false; // 한 번만 실행하게끔 하는 용도
bool currentState = false;
bool switchState = false;
bool LANDING = true;

int landingLooptime = 0; // landingStart를 5초 동안만 동작하게하는 함수
int landingSpeed = DC_SPEED_MAX;

#endif
