//  DC 3.7~5 V, 350mA 이하, UART(baudrate=19200), 640 x 480 VGA

#include<SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX, RX핀에다 와이파이보드 노란색 선 연결

int buf[8] = {0,};
int Lastbuf[8] = {0,};
boolean Loop = true;
int32_t time1 = 0;

void setup() {
  Serial.begin(19200);
  mySerial.begin(19200);
}

void loop() {

/* 
데이터시트에 따르면 5ms간격마다 데이터를 쏘아보내기 때문에
10ms 간격마다 Update함수를 실행하게 함.
10ms인 이유는 안정적으로 데이터를 받기 위해
실제 본 소스에서는 다른 함수 지연 시간 때문에
이 부분에서 5ms이하로 설정을 해도 상관없을꺼라 봄
*/
  if (time1 + 10 < millis()) {
    Update();
    time1 = millis();
  }
}

void Update() {

 /* if ( mySerial.available() < 1) {
    Serial.println("No control data");
  }*/

  
here: // [Goto A]
  while (mySerial.available()) {
    //here: // [Goto A]
    for (int j = 0; j < 8; j++) {
      buf[j] = mySerial.read();
    }
    if (buf[5] != 0) // [Goto A]
      goto here;

    if (Loop) {
      for (int i = 0; i < 8; i++) {
        Lastbuf[i] = buf[i];
      }
      Loop = false;
    }

    if ((buf[1] > 168) || (buf[1] < 88))
      buf[1] = Lastbuf[1];
    if ((buf[2] > 168) || (buf[2] < 88))
      buf[2] = Lastbuf[2];
    if ((buf[3] > 255) || (buf[3] < 0))
      buf[3] = Lastbuf[3];
    if ((buf[4] > 176) || (buf[4] < 80))
      buf[4] = Lastbuf[4];
  }

  if (!Loop) {
    for (int i = 0; i < 8; i++)
      Lastbuf[i] = buf[i];
  }

  //here: // [Goto B]

  mySerialreset;
  Serialprint();
}

void mySerialreset() {
  mySerial.end();
  mySerial.begin(19200);
}

void Serialprint() {
  for (int i = 1; i < 5; i++) {
    Serial.print(" "); Serial.print(buf[i]); Serial.print(" ");
  }
  Serial.println();
}
