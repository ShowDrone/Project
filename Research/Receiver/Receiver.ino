#include<SoftwareSerial.h>
SoftwareSerial mySerial(8, 9);

void setup() {
  Serial.begin(115200);

  mySerial.begin(300);
  /*mySerial.begin(1200);
    mySerial.begin(2400);
    mySerial.begin(4800);
    mySerial.begin(9600);
    mySerial.begin(19200);
    mySerial.begin(38400);
    mySerial.begin(74880);
    mySerial.begin(16200);*/
}

int8_t read[10] = {0,};

int16_t time = 0;
int16_t pre_time = 0;

boolean input_check = true;
boolean OnePrint = true;
boolean word_check = false;
boolean rate_check = false;
boolean first_loop = false;
int32_t check = 0;
int8_t word_count = 0;
int32_t delay_time = 0;
int32_t baud_rate = 300;

void loop() {
  while (input_check) {
    if (OnePrint) {
      Serial.println(" - - - - - - - - - - - - - - - - - - -");
      Serial.println(" | Transmiter Data Count:  [1]       |");
      Serial.println(" | baud rate:              [2]       |");
      Serial.println(" | All OK:                 [A]       |");
      Serial.println(" |                                   |");
      Serial.println(" | [Now]                             |");

      if (word_count > 9) {
        Serial.print(" | count:                  ["); Serial.print(word_count); Serial.println("]      |");
      }
      else {
        Serial.print(" | count:                  ["); Serial.print(word_count); Serial.println("]       |");
      }

      if (rate_check < 999 ) {
        Serial.print(" | rate:                   ["); Serial.print(baud_rate); Serial.print("]"); Serial.println("    |");
      }
      else if (rate_check > 999 && rate_check < 9999) {
        Serial.print(" | rate:                   ["); Serial.print(baud_rate); Serial.print("]"); Serial.println("  |");
      }
      else if (rate_check > 9999 && rate_check < 99999) {
        Serial.print(" | rate:                   ["); Serial.print(baud_rate); Serial.print("]"); Serial.println("|");
      }
      else if (rate_check > 99999 && rate_check < 999999) {
        Serial.print(" | rate:                   ["); Serial.print(baud_rate); Serial.print("]"); Serial.println("|");
      }

      Serial.print(" - - - - - - - - - - - - - - - - - - -");
      OnePrint = false;
      for (int i = 0; i < 4; i++)
        Serial.println();
    }

    if (Serial.available()) {
      check = Serial.read();
      if (check == '1') {
        for (int i = 0; i < 6; i++)
          Serial.println();
here:
        Serial.println(" Enter the number of send data from 1 to 10: ");

        for (int i = 0; i < 8; i++)
          Serial.println();
        while (!Serial.available()) {}
        if (Serial.available()) {
          check = Serial.parseInt();
          if ( 1 <= check && check <= 10) { // ASKII Code
            word_count = check;
            Serial.print(" You choose ["); Serial.print(word_count); Serial.println("] data transmission ");
            for (int i = 0; i < 9; i++)
              Serial.println();
            delay(2000);
            OnePrint = true;
            word_check = true;
          }
          else {
            for (int i = 0; i < 8; i++)
              Serial.println();
            Serial.println(" Please enter again ");
            for (int i = 0; i < 9; i++)
              Serial.println();
            delay(2000);
            goto here;
          }
        }
      }

      else if (check == '2') {
baud_here:
        for (int i = 0; i < 8; i++)
          Serial.println();

        Serial.println(" Please choose the number from under the table ");
        Serial.println(" - - - - - - - - - - - - - - -");
        Serial.println(" | baud rate 300 :      [1]  |");
        Serial.println(" | baud rate 1200 :     [2]  |");
        Serial.println(" | baud rate 2400 :     [3]  |");
        Serial.println(" | baud rate 4800 :     [4]  |");
        Serial.println(" | baud rate 9600 :     [5]  |");
        Serial.println(" | baud rate 19200 :    [6]  |");
        Serial.println(" | baud rate 38400 :    [7]  |");
        Serial.println(" | baud rate 57600 :    [8]  |");
        Serial.println(" | baud rate 162000 :  [9]  |");
        Serial.println(" - - - - - - - - - - - - - - -");
        while (!Serial.available()) {}
        if (Serial.available()) {
          check = Serial.parseInt();
          if ( check < 0 || check > 9) {
            Serial.println(" You out of the number range ");
            Serial.println(" Please repeat again ");
            delay(2500);
            goto baud_here;
          }
          else {
            for (int i = 0; i < 8; i++)
              Serial.println();
            baud_rate = Translation(check);
            Serial.print("You choice the ["); Serial.print(baud_rate);  Serial.println("] ");
          }
          for (int i = 0; i < 9; i++)
            Serial.println();
          OnePrint = true;
          rate_check = true;
          delay(2000);
        }
      }

      else if (check == 'A') {
        for (int i = 0; i < 8; i++)
          Serial.println();
        if (word_check == true && rate_check == true) {
          Serial.println(" You are Succesful the[data Count] and [baud rate]");
          input_check = false;
          first_loop = true;
        }
        else {
          Serial.println(" You are not choice another things ");
          OnePrint = true;
        }
        for (int i = 0; i < 9; i++)
          Serial.println();
        delay(2000);
      }
    }
  }

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


int32_t Translation(int32_t rate) {
  switch (rate) {
    case 1:
      mySerial.end();
      mySerial.begin(300);
      return 300;
      break;
    case 2:
      mySerial.end();
      mySerial.begin(1200);
      return 1200;
      break;
    case 3:
      mySerial.end();
      mySerial.begin(2400);
      return 2400;
      break;
    case 4:
      mySerial.end();
      mySerial.begin(4800);
      return 4800;
      break;
    case 5:
      mySerial.end();
      mySerial.begin(9600);
      return 9600;
      break;
    case 6:
      mySerial.end();
      mySerial.begin(19200);
      return 19200;
      break;
    case 7:
      mySerial.end();
      mySerial.begin(38400);
      return 38400;
      break;
    case 8:
      mySerial.end();
      mySerial.begin(57600);
      return 57600;
      break;
    case 9:
      mySerial.end();
      mySerial.begin(115200);
      return 16200;
      break;
  }
}

