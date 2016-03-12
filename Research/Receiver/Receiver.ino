#include<SoftwareSerial.h>
SoftwareSerial mySerial(8, 9);

void setup() {
  Serial.begin(9600);

  mySerial.begin(300);
  /*mySerial.begin(1200);
    mySerial.begin(2400);
    mySerial.begin(4800);
    mySerial.begin(9600);
    mySerial.begin(19200);
    mySerial.begin(38400);
    mySerial.begin(74880);
    mySerial.begin(115200);*/
}

int time = 0;
int pre_time = 0;

int8_t read[10] = {0,};

void loop() {
  One_Byte();
  /*Two_Byte();
  Three_Byte();
  Four_Byte();
  Five_Byte();
  Six_Byte();
  Seven_Byte();
  Eight_Byte();
  Nine_Byte();
  Ten_Byte();*/
}

void One_Byte() {
  if (mySerial.available()) {
    read[0] = mySerial.read();
  }
}

void Two_Byte() {
  if (mySerial.available()) {
    read[0] = mySerial.read();
    Serialprint(0);
  }
}

void Three_Byte() {
}

void Four_Byte() {
}

void Five_Byte() {
}

void Six_Byte() {
}

void Seven_Byte() {
}

void Eight_Byte() {
}

void Nine_Byte() {
}

void Ten_Byte() {
}

void Serialprint(int Number) {

  switch (Number) {
    case 0:
      Serial.print(read[0]);
      break;

    case 1:
      Serial.print(read[0]);
      Serial.print(" ");
      Serial.print(read[1]);
      break;

    case 2:
      for (int i = 0; i <= Number; i++) {
        if ( i != 0)
          Serial.print(" ");
        Serial.print(read[i]);
        if ( i != Number)
          Serial.print(" ");
      }
      break;

    case 3:
      for (int i = 0; i <= Number; i++) {
        if ( i != 0)
          Serial.print(" ");
        Serial.print(read[i]);
        if ( i != Number)
          Serial.print(" ");
      }
      break;

    case 4:
      for (int i = 0; i <= Number; i++) {
        if ( i != 0)
          Serial.print(" ");
        Serial.print(read[i]);
        if ( i != Number)
          Serial.print(" ");
      }
      break;

    case 5:
      for (int i = 0; i <= Number; i++) {
        if ( i != 0)
          Serial.print(" ");
        Serial.print(read[i]);
        if ( i != Number)
          Serial.print(" ");
      }
      break;

    case 6:
      for (int i = 0; i <= Number; i++) {
        if ( i != 0)
          Serial.print(" ");
        Serial.print(read[i]);
        if ( i != Number)
          Serial.print(" ");
      }
      break;

    case 7:
      for (int i = 0; i <= Number; i++) {
        if ( i != 0)
          Serial.print(" ");
        Serial.print(read[i]);
        if ( i != Number)
          Serial.print(" ");
      }
      break;

    case 8:
      for (int i = 0; i <= Number; i++) {
        if ( i != 0)
          Serial.print(" ");
        Serial.print(read[i]);
        if ( i != Number)
          Serial.print(" ");
      }
      break;

    case 9:
      for (int i = 0; i <= Number; i++) {
        if ( i != 0)
          Serial.print(" ");
        Serial.print(read[i]);
        if ( i != Number)
          Serial.print(" ");
      }
      break;
  }


  Serial.println();
}

