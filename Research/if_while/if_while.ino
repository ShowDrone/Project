#include<SoftwareSerial.h>
SoftwareSerial mySerial(8, 9);

void setup() {
  Serial.begin(19200);
  mySerial.begin(19200);
}

int time = 0;
int pre_time = 0;
int check = 0;
int value = 0;
int32_t value_sum = 0;
boolean value_check = 0;

void loop() {
  time = micros() - pre_time;
  pre_time = micros();
  while (mySerial.available()) { // 이부분만 while로 바꿈
    check = mySerial.read();
  }

  if (value < 1000) {
    value_sum += time;
    value++;
  }

  if (value == 1000) {
    Serial.println(value_sum / value);
    value_sum = 0;
    value = 0;
    delay(3000);
  }
  Serial.print(value); Serial.print(" "); Serial.println(time);
}
