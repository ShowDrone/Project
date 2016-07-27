/*
 *Copyright (c) 2015，DFRobot
 *All rights reserved
 *
 *文件名称：WiringAnalog.c
 *文件标识：
 *摘    要： 读取IO口的模拟量+电机控制
 *
 *当前版本：V1.1
 *作    者：Gavin
 *完成时间：2015.4.30
 *
 *取代版本：V1.0
 *原作者  : 邓卫兵(15196617738@163.com)
 *完成时间：2014.12.18
 */
 
#include "DFRobot.h" 

DFrobotEdison dFrobotEdison = DFrobotEdison();

/*
 *brief: 构造函数
 *param: @No 
 *retval: @No
 */
DFrobotEdison::DFrobotEdison()
{
	
}

/*
 *brief: 读取A0-A5端口的模拟量
 *param: @(input) ulPin:A0, A1, A2, A3, A4, A5   
 *retval: @读取出来的模拟值
 */
uint32_t DFrobotEdison::readAnalog(uint32_t ulPin)
{
	uint32_t ulValue = 0; 
	if ((ulPin > MUX_ANALOG_INPUTS)  || (ulPin < MIN_ANALOG_INPUTS))
	{
		trace_error("Invalid analog input channel specified\n");
		return 0;
	}
	
	switch (ulPin)
	{
		case A0:
		{
			writeToSlv(0xA0, 0xA0);
			readFromSlv(&ulValue);
			break;
		}
		case A1:
		{
			writeToSlv(0xA1, 0xA1);
			readFromSlv(&ulValue);

			break;
		}
		case A2:
		{
			writeToSlv(0xA2, 0xA2);
			readFromSlv(&ulValue);

			break;
		}
		case A3:
		{
			writeToSlv(0xA3, 0xA3);
			readFromSlv(&ulValue);

			break;
		}
		case A4:
		{
			writeToSlv(0xA4, 0xA4);
			readFromSlv(&ulValue);

			break;
		}
		case A5:
		{
			writeToSlv(0xA5, 0xA5);
			readFromSlv(&ulValue);

			break;
		}
		default:
		{
			trace_error("error \n");
			break;
		}
	}

	return ulValue;
}

/*
 *brief: 电机控制
 *param: @(input) ulPin:M1，M2
         @(input) ulValue:电机速度值
 *retval: NO
 */
void DFrobotEdison::motorControl(uint32_t ulPin, uint32_t ulValue)
{
	if ((ulPin < 9) || (ulPin > 10))
	{ 
		trace_error("Invalid analog input channel specified\n");
		return ;
	}
	
	switch (ulPin)
	{
		case M1:
		{ 
			writeToSlv(0xDA, ulValue);
			break;
		}

		case M2:
		{
			writeToSlv(0xDB, ulValue);
			break;
		}

		default:
		{
			trace_error("error \n");
			break;
		}
	}
}

/*
 *brief: 写数据去从机
 *param: @(input) cmd:写命令数据
         @(input) value: 写数据
 *retval: NO
 */
 void DFrobotEdison::writeToSlv(uint32_t cmd, uint32_t value )
{
    Wire.begin();        
    Wire.beginTransmission(4);
	Wire.write(0x55);
	Wire.write(0xaa);
    Wire.write(cmd);        
    Wire.write(value);
	Wire.write((unsigned char)(0x55+0xaa+cmd+value));	
    Wire.endTransmission();    
}

void DFrobotEdison::wheelEnSlv(uint32_t cmd)
{
    Wire.begin();
    Wire.beginTransmission(4);
    Wire.write(0x55);
    Wire.write(0xaa);
    Wire.write(cmd);
    Wire.write(0);
    Wire.write((unsigned char)(0x55+0xaa+cmd+0));
    Wire.endTransmission();
}
/*
 *brief: 读数据去从机
 *param: @(output) outBuf:读出的模拟值
 *retval: NO
 */
 void DFrobotEdison::readFromSlv(uint32_t *outBuf)
{
	unsigned int value = 0;
	unsigned int count = 0;
	unsigned char num=0;
	unsigned char buf[5]={0};
	Wire.begin();
	int ret = Wire.requestFrom(4, 5);
	while(num<5){
		count = 0;
		while (Wire.available() == 0)
		{
			if(++count == 1000){
				value = -1;
				break;
			}
			delay(1);
		}
		if(count < 1000){
			buf[num++] = Wire.read();
		}else{
			break;
		}
	}
 
	
	if((count >= 1000)
		||(buf[0]!=0x55)
		||(buf[1]!=0xaa)
		||(buf[4]!=(unsigned char)(buf[0]+buf[1]+buf[2]+buf[3]))){
		*outBuf = -1;
	}else{
		*outBuf = buf[2]+(buf[3]<<8); 
	}
}
