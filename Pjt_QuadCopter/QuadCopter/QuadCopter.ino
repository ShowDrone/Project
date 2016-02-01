/*
Date    :   2015-00-00
Maker   :   SeungHyun Lee (Blog address : blog.naver.com/dkwltmdgus)
MCU     :   Arduino Mega2560
Purpose :   Hand Control QuadCopter (first basic QuadCopter)

Please do not change this section
이부분은 변경하지 말아주세요.

[motor direction] 
    1     2
  
    4     3
(1,3 정방향 2,4 역방향)

*/


void setup() {
  Serial.begin(115200);
  MPU6050_setup(); // MPU6050 Tap setting
  Motor_PID_setup(); //Motor Tap setting
}

void loop() {
  MPU6050_loop();
  Motor_PID(); // with Update Motor
}

