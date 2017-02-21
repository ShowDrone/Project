
// Network
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>  
#include "wiringPi.h"
#include "BLDC.h"
#include "DC.h"
#include "AccelGyro.h"
#include "softServo.h"
#include "Landing.h"
#include "Stabilize.h"
#include "Network.h"

// roll, pitch, throttle, rudder

int main()
{
	int threadNetworkCheck;
	int threadPidCheck;
	pthread_t p_thread;
	
	// 하드웨어 핀 셋
	wiringPiSetup();
	setMpu9150();
	setLandingPin();
	setBLDCPin();
	setDCPin();
	
     threadPidCheck   = pthread_create (&p_thread, NULL, &updatePID, NULL) ;
	
	if(threadPidCheck != 0) {
		puts("Thread Create Error Repeat Again Please");
		delay(500);
		main();
	}
	
	while (true) {
		getControlData();
	}
			
	return 0;
}
