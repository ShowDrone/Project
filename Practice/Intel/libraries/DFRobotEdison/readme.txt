一、DFRobotEdison库操作
1、把DFRobotEdison库放到arduino-1.5.3-Intel.1.0.4\hardware\arduino\edison\libraries目录
2、在arduino IDE 中File->Examples->Library->DFRobotEdison可以找到两个例子analogRead和Motor
3、如果是一个新建一个文件可以通过Sketch->Import Library->DFRobotEdison添加头文件就可以用我们的函数

二、DFRobotEdison库函数介绍
1、readAnalog()：读取A0-A5端口的模拟值
				 输入参数为:A0、A1 A2、A3、A4、A5
2、controlMotor(uint32_t ulPin, uint32_t ulValue):控制板子上的M1和M2电机端口
												  输入参数：ulPin： M1、M2
												  ulValue:电机速度值