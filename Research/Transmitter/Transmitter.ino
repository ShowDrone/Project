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
    mySerial.begin(115200);*/
}

boolean input_check = true;
boolean OnePrint = true;
boolean word_check = false;
boolean delay_check = false;
boolean data_check = false;
boolean rate_check = false;
boolean start_end_check = false;
boolean first_loop = false;
boolean start_end = 0;
unsigned int time = 0;
unsigned int pre_time = 0;
unsigned int what_data = 0;
int32_t check = 0;
int8_t word_count = 0;
unsigned int delay_time = 0;
unsigned int baud_rate = 300;

void loop() {
  while (input_check) {
    if (OnePrint) {
      for (int i = 0; i < 15; i++)
        Serial.println();
      Serial.println(" - - - - - - - - - - - - - - - - - - -");
      Serial.println(" | Transmiter Data Count:  [1]       |");
      Serial.println(" | delay time:             [2]       |");
      Serial.println(" | Transmiter proper Data: [3]       |");
      Serial.println(" | baud rate:              [4]       |");
      Serial.println(" | Start/end Signal:       [5]       |");
      Serial.println(" | All OK:                 [A]       |");
      Serial.println(" |                                   |");
      Serial.println(" | [Now]                             |");

      if (word_count > 9) {
        Serial.print(" | count:                  ["); Serial.print(word_count); Serial.println("]      |");
      }
      else {
        Serial.print(" | count:                  ["); Serial.print(word_count); Serial.println("]       |");
      }

      if (delay_time < 9) {
        Serial.print(" | delay:                  ["); Serial.print(delay_time); Serial.println("]       |");
      }
      else if (delay_time > 9 && delay_time < 99) {
        Serial.print(" | delay:                  ["); Serial.print(delay_time); Serial.println("]      |");
      }
      else if (delay_time > 99 && delay_time < 999) {
        Serial.print(" | delay:                  ["); Serial.print(delay_time); Serial.println("]     |");
      }
      else if (delay_time > 999 && delay_time < 9999) {
        Serial.print(" | delay:                  ["); Serial.print(delay_time); Serial.println("]    |");
      }
      else if (delay_time > 9999 && delay_time < 99999) {
        Serial.print(" | delay:                  ["); Serial.print(delay_time); Serial.println("]   |");
      }

      if (what_data < 9) {
        Serial.print(" | data:                   ["); Serial.print(what_data); Serial.println("]       |");
      }
      else if (what_data > 9) {
        Serial.print(" | data:                   ["); Serial.print(what_data); Serial.println("]     |");
      }
      else if (what_data > 99 && what_data < 999) {
        Serial.print(" | data:                   ["); Serial.print(what_data); Serial.println("]    |");
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

      if (start_end == 1)
        Serial.println(" | start/end:              [On]      |");
      else if (start_end == 0)
        Serial.println(" | start/end:              [Off]     |");

      Serial.println(" - - - - - - - - - - - - - - - - - - -");
      OnePrint = false;
    }

    if (Serial.available()) {
      check = Serial.read();
      if (check == '1') {
        for (int i = 0; i < 10; i++)
          Serial.println();
here:
        Serial.println(" Input the 1~10 Number ");

        for (int i = 0; i < 10; i++)
          Serial.println();
        while (!Serial.available()) {}
        if (Serial.available()) {
          check = Serial.parseInt();
          if ( 1 <= check && check <= 10) { // ASKII Code
            word_count = check;
            Serial.print(" You choose ["); Serial.print(word_count); Serial.println("] data transmission ");
            for (int i = 0; i < 12; i++)
              Serial.println();
            delay(2000);
            OnePrint = true;
            word_check = true;
          }
          else {
            for (int i = 0; i < 8; i++)
              Serial.println();
            Serial.println(" Please enter again ");
            for (int i = 0; i < 13; i++)
              Serial.println();
            delay(2000);
            goto here;
          }
        }
      }

      else if (check == '2') {
        for (int i = 0; i < 10; i++)
          Serial.println();
        Serial.print(" input the delay time in us: ");

        for (int i = 0; i < 10; i++)
          Serial.println();
        while (!Serial.available()) {}

        if (Serial.available()) {
          check = Serial.parseInt();
          delay_time = check;
          for (int i = 0; i < 10; i++)
            Serial.println();
          Serial.print("["); Serial.print(delay_time); Serial.print("]");
          Serial.println("us will be delayed by the interval");
          for (int i = 0; i < 12; i++)
            Serial.println();
          delay_check = true;
          delay(2000);
          OnePrint = true;
        }
      }

      else if (check == '3') {
        for (int i = 0; i < 10; i++)
          Serial.println();

        Serial.println(" input the proper data from -127 to 128: ");

        for (int i = 0; i < 10; i++)
          Serial.println();
        while (!Serial.available()) {}
        if (Serial.available()) {
          check = Serial.parseInt();
          if (check <= 128 && check >= -127) {
            what_data = check;
            Serial.print("You input the ["); Serial.print(what_data);  Serial.println("] ");
            data_check = true;
          }
          if ( check < -127 || check > 128) {
            Serial.println(" You out of the data range ");
          }
          for (int i = 0; i < 10; i++)
            Serial.println();
          OnePrint = true;
          delay(2000);
        }
      }


      else if (check == '4') {

baud_here:
        for (int i = 0; i < 8; i++)
          Serial.println();

        Serial.println(" Choose the number from under the table ");
        Serial.println(" - - - - - - - - - - - -");
        Serial.println(" | rate 300 :      [1]  |");
        Serial.println(" | rate 1200 :     [2]  |");
        Serial.println(" | rate 2400 :     [3]  |");
        Serial.println(" | rate 4800 :     [4]  |");
        Serial.println(" | rate 9600 :     [5]  |");
        Serial.println(" | rate 19200 :    [6]  |");
        Serial.println(" | rate 38400 :    [7]  |");
        Serial.println(" | rate 57600 :    [8]  |");
        Serial.println(" | rate 115200 :   [9]  |");
        Serial.println(" - - - - - - - - - - - -");
        while (!Serial.available()) {}
        if (Serial.available()) {
          check = Serial.parseInt();
          if ( check < 0 || check > 9) {
            Serial.println(" You out of the number range ");
            delay(2500);
            goto baud_here;
          }
          else {
            for (int i = 0; i < 7; i++)
              Serial.println();
            baud_rate = Translation(check);
            Serial.print("You choice the ["); Serial.print(baud_rate);  Serial.println("] ");
          }
          for (int i = 0; i < 12; i++)
            Serial.println();
          OnePrint = true;
          rate_check = true;
          delay(2000);
        }
      }

      else if (check == '5') {

        for (int i = 0; i < 5; i++)
          Serial.println();

        Serial.println(" Start/End Signal || On: 1 || Off: 0 ");

        for (int i = 0; i < 9; i++)
          Serial.println();
        while (!Serial.available()) {}
        if (Serial.available()) {
          check = Serial.parseInt();
          if (check == 1 || check == 0)
            start_end = check;
          if (start_end == 1)
            Serial.println("You choose Start/End [On] ");
          if (start_end == 0)
            Serial.println("You choose Start/End [Off] ");

          start_end_check = true;
        }
        else {
          Serial.println(" You out of the number range ");
        }
        for (int i = 0; i < 10; i++)
          Serial.println();
        OnePrint = true;
        delay(2000);
      }

      else if (check == 'A') {
        for (int i = 0; i < 10; i++)
          Serial.println();
        if (data_check == true && word_check == true && delay_check == true  && rate_check == true && start_end_check == true) {
          Serial.println(" You are Succesful");
          input_check = false;
          first_loop = true;
        }
        else {
          Serial.println(" You are not choice another things ");
          OnePrint = true;
        }
        for (int i = 0; i < 7; i++)
          Serial.println();
        delay(2000);
      }
    }
  }

  if (first_loop == true) {

    Serial.println(" - - - - - - - - - - - - - - - - - - -");
    Serial.println(" |                                   |");
    Serial.println(" | if you want to come back,         |");
    Serial.println(" | press the [A]                     |");
    Serial.println(" - - - - - - - - - - - - - - - - - - -");

    for (int i = 0; i < 4; i++)
      Serial.println();
    delay(2800);
    first_loop = false;
  }
  if (Serial.available()) {
    check = mySerial.read();
    if (check = 'A') {
      input_check = true;
      data_check = false;
      word_check = false;
      delay_check = false;
      rate_check = false;
      start_end_check == false;
    }
  }
  if (start_end == 0) {
    for (int i = 1; i <= word_count; i++) {
      mySerial.write(what_data);
      delayMicroseconds(delay_time);
      Serial.println("Hi:"+(String)i);
    }
  }
  else if (start_end == 1) {
    for (int i = 1; i <= word_count; i++) {
      if (i == 1) {
        mySerial.write('S');
        delayMicroseconds(delay_time);
      }
      mySerial.write(what_data);
      delayMicroseconds(delay_time);

      if (i == word_count) {
        mySerial.write('E');
        delayMicroseconds(delay_time);
      }
    }
  }
}

unsigned int Translation(unsigned int rate) {
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
      return 115200;
      break;
  }
}
