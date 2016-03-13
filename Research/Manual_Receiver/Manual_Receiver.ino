#include<SoftwareSerial.h>

SoftwareSerial mySerial(8, 9);


int check = 0;
int read[10] = {0, };
int sum = 0;
unsigned int time = 0;
unsigned int pre_time = 0;

void setup() {
  Serial.begin(115200);
  mySerial.begin(300);
}

void loop() {
  time = micros() - pre_time;
  if (Serial.available()) {
    check = Serial.parseInt();
  }
  if (mySerial.available()) {
    for (int i = 0; i < check; i++) {
      read[i] = mySerial.read();
      sum += read[i];
    }
    check = CheckSum(sum);
    sum = 0;
    if (check == 0)
      Serialprint(check);
  }

  pre_time = micros();
}

void Serialprint(int Number) {

  switch (Number - 1) {
    case 0:
      Serial.print(read[0]);
      Serial.print("  "); Serial.print(time);
      break;

    case 1:
      Serial.print(read[0]);
      Serial.print(" ");
      Serial.print(read[1]);
      Serial.print(" ");
      Serial.print(time);
      break;

    case 2:
      for (int i = 0; i <= Number; i++) {
        if ( i != 0)
          Serial.print(" ");
        Serial.print(read[i]);
        if ( i != Number)
          Serial.print(" ");
        if (i == Number) {
          Serial.print("  "); Serial.print(time);
        }
      }
      break;

    case 3:
      for (int i = 0; i <= Number; i++) {
        if ( i != 0)
          Serial.print(" ");
        Serial.print(read[i]);
        if ( i != Number)
          Serial.print(" ");
        if (i == Number) {
          Serial.print("  "); Serial.print(time);
        }
      }
      break;

    case 4:
      for (int i = 0; i <= Number; i++) {
        if ( i != 0)
          Serial.print(" ");
        Serial.print(read[i]);
        if ( i != Number)
          Serial.print(" ");
        if (i == Number) {
          Serial.print("  "); Serial.print(time);
        }
      }
      break;

    case 5:
      for (int i = 0; i <= Number; i++) {
        if ( i != 0)
          Serial.print(" ");
        Serial.print(read[i]);
        if ( i != Number)
          Serial.print(" ");
        if (i == Number) {
          Serial.print("  "); Serial.print(time);
        }
      }
      break;

    case 6:
      for (int i = 0; i <= Number; i++) {
        if ( i != 0)
          Serial.print(" ");
        Serial.print(read[i]);
        if ( i != Number)
          Serial.print(" ");
        if (i == Number) {
          Serial.print("  "); Serial.print(time);
        }
      }
      break;

    case 7:
      for (int i = 0; i <= Number; i++) {
        if ( i != 0)
          Serial.print(" ");
        Serial.print(read[i]);
        if ( i != Number)
          Serial.print(" ");
        if (i == Number) {
          Serial.print("  "); Serial.print(time);
        }
      }
      break;

    case 8:
      for (int i = 0; i <= Number; i++) {
        if ( i != 0)
          Serial.print(" ");
        Serial.print(read[i]);
        if ( i != Number)
          Serial.print(" ");
        if (i == Number) {
          Serial.print("  "); Serial.print(time);
        }
      }
      break;

    case 9:
      for (int i = 0; i <= Number; i++) {
        if ( i != 0)
          Serial.print(" ");
        Serial.print(read[i]);
        if ( i != Number)
          Serial.print(" ");
        if (i == Number) {
          Serial.print("  "); Serial.print(time);
        }
      }
      break;
  }


  Serial.println();
}

char CheckSum(int sum) {
  int total = sum;
  sum &= 0xFF;
  sum = ~sum + 1;
  total = total + sum;
  total &= 0xFF;
  return total;
}
