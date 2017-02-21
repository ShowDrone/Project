

#include "Stabilize.h"

void *updatePID();
void updateBLDC();
void updateDC();
void updateLANDING() ;
void Limit_I(double *value);

void *updatePID() {
	
	// 조종 데이터 받는 함수 추가 필요 //  
	
	// aileron, elevator, rudder, throttle 이 조종 데이터
	
	// 데이터 범위값 매핑
	roll.Control = map(aileron, AILERON_MIN, AILERON_MAX, ROLL_MIN, ROLL_MAX);
	pitch.Control = map(elevator, ELEVATOR_MIN, ELEVATOR_MAX, PITCH_MIN, PITCH_MAX);
	yaw.Control = map(rudder, RUDDER_MIN, RUDDER_MAX, YAW_MIN, YAW_MAX);
	throttle = map(throttle, THROTTLE_MIN, THROTTLE_MAX, SPEED_MIN, SPEED_MAX);
	
	// 한계값 지정
	if ( pitch.Control < PITCH_MIN || pitch.Control > PITCH_MAX)
		pitch.Control = pitch.lastControl;
	if ( roll.Control < ROLL_MIN || roll.Control > ROLL_MAX)
		roll.Control = roll.lastControl;
	if ( yaw.Control < YAW_MIN || yaw.Control > YAW_MAX)
		yaw.Control = yaw.lastControl;
	if ( throttle < SPEED_MIN || throttle > SPEED_MAX)
		throttle = lastThrottle;
	
	// 이전 상태값
	pitch.lastControl = pitch.Control;
	roll.lastControl = roll.Control;
	yaw.lastControl = yaw.Control;
	lastThrottle = throttle;

	roll.Data = setRollData();
	pitch.Data = setPitchData();
	yaw.Data = setYawData();

	// PID 

  // ROLL   
   roll.ERR = roll.Control - roll.Data;
   roll.PERR = (aileron - roll.ERR); // /DT;
   roll.ERR_P = roll.ERR * roll.P;
   roll.ERR_I = roll.ERR_I * (roll.ERR * roll.I); // *DT;
   Limit_I (&roll.ERR_I);
   roll.ERR_D = roll.PERR * pitch.D;
   roll.PID = pitch.ERR_P + pitch.ERR_I + pitch.ERR_D;
   roll.PRE = aileron;
   
   // PITCH
	pitch.ERR = pitch.Control - pitch.Data;
	pitch.PERR = (elevator - pitch.ERR); // /DT;
	pitch.ERR_P = pitch.ERR * pitch.P;
	pitch.ERR_I = pitch.ERR_I * (pitch.ERR * pitch.I); // *DT;
	Limit_I (&pitch.ERR_I);
	pitch.ERR_D = pitch.PERR * pitch.D;
	pitch.PID = pitch.ERR_P + pitch.ERR_I + pitch.ERR_D;
	pitch.PRE = elevator;
	
	// YAW
	yaw.ERR = yaw.Control - yaw.Data;
	yaw.ERR_P = yaw.ERR * yaw.P;
	yaw.ERR_I = yaw.ERR_I * (yaw.ERR * yaw.I); // *DT;
	Limit_I (&yaw.ERR_I);
	yaw._PI = yaw.ERR_P + yaw.ERR_I;
	
	//작동부
	updateDC();
	updateBLDC();
	updateLANDING();
}

void updateDC() {
	getDCSpeed(roll.PID, pitch.PID, yaw._PI);
	DC1 = setDC1Speed();
	DC2 = setDC2Speed();
	DC3 = setDC3Speed();
	DC4 = setDC4Speed();
	// 작동
}

void updateBLDC() {
	setBLDCSpeed();
	BLDC1 = getBLDCSpeed();
	BLDC2 = getBLDCSpeed();
	// 작동																																												
}

// 랜딩
void updateLANDING() {
	
	if (switchState == true) {
		LANDING = getCurrentState();
		if (LANDING == false) {
			digitalWrite(LANDING1_A, 0);
			digitalWrite(LANDING1_B, landingSpeed);
			digitalWrite(LANDING2_A, 0);
			digitalWrite(LANDING2_B, landingSpeed);
		}
		else {
			digitalWrite(LANDING1_A, landingSpeed);
			digitalWrite(LANDING1_B, 0);
			digitalWrite(LANDING2_A, landingSpeed);
			digitalWrite(LANDING2_B, 0); 
		}
		switchState = false;
	}
}

// I게인 값이 계속 누적되서 커지지 않도록 한계값 설정
void Limit_I(double *value) {
  if (*value >= 100)
    *value = 100;
  else if (*value <= -100)
    *value = -100;
}

