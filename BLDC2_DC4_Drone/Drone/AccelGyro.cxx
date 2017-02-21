
#include "AccelGyro.h"

int AcX, AcY, AcZ;
int GyX, GyY, GyZ ;

float rollGyro, pitchGyro, yawGyro;
float rollAcc, pitchAcc, yawAcc;
float roll, pitch, yaw;
float DT = 0.01; // 적분하는 시간 

int Address = 0x68;

void setMpu9150() {
    Address =wiringPiI2CSetup(0x68);
	wiringPiI2CReadReg8(Address, 0x6B);
	wiringPiI2CWriteReg8(Address, 0x1A, 3);
}

float getAccelGyroData() {
	AcX = wiringPiI2CReadReg8(Address,0x3B);
	AcX= AcX << 8 | wiringPiI2CReadReg8(Address,0x3C);
	AcY= wiringPiI2CReadReg8(Address,0x3D);
	AcY= AcY << 8 | wiringPiI2CReadReg8(Address,0x3E);
	AcZ = wiringPiI2CReadReg8(Address,0x3F);
	AcZ= AcZ << 8 | wiringPiI2CReadReg8(Address,0x40);
	
	GyX = wiringPiI2CReadReg8(Address,0x43);
	GyX= GyX << 8 | wiringPiI2CReadReg8(Address,0x44);
	GyY = wiringPiI2CReadReg8(Address,0x45);
	GyY= GyX << 8 | wiringPiI2CReadReg8(Address,0x46);
	GyZ = wiringPiI2CReadReg8(Address,0x47);
	GyZ= GyX << 8 | wiringPiI2CReadReg8(Address,0x48);
}

// 상보필터로 데이터 추출
float setRollData() {
	getAccelGyroData();
	rollAcc = -atan2(AcX, AcZ)*(180/PI);
	rollGyro = GyX / 131.7;
	roll = (0.98 * (roll + rollGyro*DT)) + (0.02*rollAcc);
	return roll;
}

float setPitchData() { 
	getAccelGyroData();
	pitchAcc = atan2(AcY, AcZ)*(180/PI);
	pitchGyro = GyY / 131.7;
	pitch = (0.98*(pitch + pitchGyro*DT)) + (0.02*pitchAcc);
	return pitch;
}

float setYawData() {
	getAccelGyroData();
	yawAcc = atan2(AcX, AcY)*(180/PI);
	yawGyro = GyZ / 131.7;
	yaw = (0.98*(yaw + yawGyro*DT)) + (0.02*yawAcc);
	return yaw;
}
