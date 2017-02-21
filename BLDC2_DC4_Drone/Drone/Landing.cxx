
#include "Landing.h"


void setLandingPin() {
	pinMode(LANDING_SWITCH, OUTPUT);
	pinMode(LANDING1_A, OUTPUT);
	pinMode(LANDING1_B, OUTPUT);
	pinMode(LANDING2_A, OUTPUT);
	pinMode(LANDING2_B, OUTPUT);
}

// LANDING 데이터 받기
bool getCurrentState() {
	if(landingStart) {
		if(landingOnce) {
			 landingLooptime = micros() + LANDING_TIME;
			landingOnce = false;
			landingState = !landingState;
		}
		if(landingLooptime < micros())
			currentState = true;
		else {
			currentState = false;
			landingStart = false;
		}
	}
	return currentState;
}
