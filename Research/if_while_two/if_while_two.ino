#include<SoftwareSerial.h>
SoftwareSerial mySerial(8, 9);

void setup() {
  Serial.begin(19200);
  mySerial.begin(19200);
}

int sum = 0;
int data[2] = {0,};
int check = 0;

int time = 0;
int pre_time = 0;
int32_t looptime = 0;
int count = 0;
///////// while ////////

void loop() {
  time = micros() - pre_time;
  pre_time = micros();

  if (looptime + 5000 > micros()) {
    count++;
    reading();
    looptime = micros();
  }

}

void reading() {
  if (mySerial.available()) {
    for (int i = 0; i < 2; i++) {
      data[i] = mySerial.read();
    }
    if (mySerial.available() == 61) {
      Serial.print(micros()-(count*5000));
      delay(10000);
    }
  }
  for (int i = 0; i < 2; i++) {
    Serial.print(" ");
    Serial.print(data[i]);
  }
  Serial.println();
}
