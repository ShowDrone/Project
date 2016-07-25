
// UART통신으로 조종 데이터를 읽어들이는 탭

#include<SoftwareSerial.h>
SoftwareSerial mySerial(50, 51);

int buf[8] = {0,}; // 카메라보드로부터 읽어들일 8개의 변수
int Lastbuf[8] = {0,}; // 카메라보드로부터 읽어들 8개의 변수의 이전 값

boolean Loop = true; // Control_UART_Update가 실행될 때 if문으로 딱 한 번만 처리해주기위한 변수

void Control_UART_init() {
  Serial.begin(19200);
  mySerial.begin(19200);
}

// 조종 데이터를 읽어들이는 함수일
void Control_UART_Update() {
  boolean gotoCheck = 0; // goto Check용 변수

  // 카메라보드로부터 수신되는 데이터가 없을 시 조종 데이터에 default값을 대입
  if ( mySerial.available() < 1) {
    buf[1] = 129;
    buf[2] = 129;
    buf[3] = 0;
    buf[4] = 129;
    Serial.println(" No Control Data ");
  }

here: // [Goto]

  // 카메라보드로부터 수신될 때 실행되는 while문
  while (mySerial.available()) {
    for (int j = 0; j < 8; j++) {
      buf[j] = mySerial.read();
    }
    if (buf[5] != 0) // checksum의 값이 0과 다를 때 Goto
      goto here;

    if (Loop) { // 48번줄을 위한 용도
      for (int i = 0; i < 8; i++) {
        Lastbuf[i] = buf[i];
      }
      Loop = false;
    }

    // buf값이 송신측에서 규정한 값의 범위를 벗어날경우 이전의 buf값을 현재 buf값에 대입
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

