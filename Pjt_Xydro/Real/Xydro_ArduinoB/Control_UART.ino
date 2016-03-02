#include<SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);

int buf[8] = {0,};
int Lastbuf[8] = {0,};
boolean Loop = true;
boolean Emergency = false;

void Control_UART_init() {
  Serial.begin(19200);
  mySerial.begin(19200);
}

void Control_UART_Update() {
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
    Emergency = true;
  }

  //Serialprint();

  if (!Loop) {
    for (int i = 0; i < 8; i++) {
      Lastbuf[i] = buf[i];
    }
  }
  Serialreset();
}

void Serialreset() {
  mySerial.end();
  mySerial.begin(19200);
}

void Serialprint() {
  for (int i = 1; i < 5; i++) {
    Serial.print(" "); Serial.print(buf[i]); Serial.print(" ");
  }
  Serial.println();
}

