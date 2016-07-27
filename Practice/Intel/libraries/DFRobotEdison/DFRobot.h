/*
 *Copyright (c) 2015��DFRobot
 *All rights reserved
 *
 *�ļ����ƣ�DFRobot.h
 *�ļ���ʶ��
 *ժ    Ҫ�� dfrobot ���ļ�
 *
 *��ǰ�汾��V1.0
 *��    �ߣ�Gavin
 *���ʱ�䣺2015.4.30
 *
 *ȡ���汾��V1.0
 *ԭ����  : ������(15196617738@163.com)
 *���ʱ�䣺2014.12.18
 */
 
#ifndef DFROBOT_H
#define DFROBOT_H

#include "IIC1.h"
#include "Arduino.h"
#include "pins_arduino.h"
#include "trace.h"

#define MUX_ANALOG_INPUTS 19
#define MIN_ANALOG_INPUTS  14
#define M1 10 //�������M1
#define M2 9  //�������M2
#define MY_TRACE_PREFIX "wiring_analog"
#define analogRead  (dFrobotEdison.readAnalog)
#define controlMotor (dFrobotEdison.motorControl)

#define ClockwiseM1 0x1A
#define ClockwiseM2 0x2A
#define AntiClockwiseM1   0x1B
#define AntiClockwiseM2  0x2B

 
class DFrobotEdison {
	public: 
		DFrobotEdison();
		uint32_t readAnalog(uint32_t ulPin); 
		void motorControl(uint32_t ulPin, uint32_t ulValue);
	public: //private formly
        void wheelEnSlv(uint32_t cmd);   //new add
		void writeToSlv(uint32_t cmd, uint32_t value );    //void writeToSlv(uint32_t cmd, uint32_t value );
		void readFromSlv(uint32_t *outBuf);
};

extern DFrobotEdison dFrobotEdison ;

#endif