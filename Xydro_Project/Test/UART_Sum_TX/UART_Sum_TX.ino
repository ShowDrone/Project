#include<SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX
SoftwareSerial mySerial_(4, 5); // RX, TX

int buf[8] = {0,};
int Lastbuf[8] = {0,};
int UART[5] = {0, 1, 2, 3, 4};
boolean Loop = true;

void setup() {
  Serial.begin(19200);
  mySerial.begin(19200);
  mySerial_.begin(19200);
}

int time = 0;
boolean A_Start = true;
boolean B_Start = false;

void loop() {
  if (A_Start)
    A_UART_Update();
  if (B_Start)
    B_UART_Update();
}

void B_UART_Update() {
  for (int i = 0; i < 5; i++) {
    mySerial_.write(UART[i]);
  }
  A_Start = true;
  B_Start = false;
  
  mySerial_.end();
  mySerial_.begin(19200);
}

void A_UART_Update() {
  if (mySerial.available()) {
    here:
    for (int j = 0; j < 8; j++) {
      buf[j] = mySerial.read();
    }
    if (buf[5] != 0) {
      goto here;
    }

    if (Loop) {
      for (int i = 0; i < 8; i++) {
        Lastbuf[i] = buf[i];
      }
      Loop = false;
    }

    if ((buf[1] > 168) || (buf[1] < 88)) {
      buf[1] = Lastbuf[1];
    }
    if ((buf[2] > 168) || (buf[2] < 88)) {
      buf[2] = Lastbuf[2];
    }
    if ((buf[3] > 255) || (buf[3] < 0)) {
      buf[3] = Lastbuf[3];
    }
    if ((buf[4] > 176) || (buf[4] < 80)) {
      buf[4] = Lastbuf[4];
    }
  }
  else
  {
    buf[1] = 129;
    buf[2] = 129;
    buf[3] = 0;
    buf[4] = 129;
  }

  //Serialprint();

  if (!Loop) {
    for (int i = 0; i < 8; i++) {
      Lastbuf[i] = buf[i];
    }
  }
  Serialreset();
  
  A_Start = false;
  B_Start = true;
}

void Serialreset() {
  mySerial.end();
  mySerial.begin(19200);
  Serial.end();
  Serial.begin(19200);
}

void Serialprint() {
  for (int i = 1; i < 5; i++) {
    Serial.print(" "); Serial.print(buf[i]); Serial.print(" ");
  }
  Serial.println();
}
