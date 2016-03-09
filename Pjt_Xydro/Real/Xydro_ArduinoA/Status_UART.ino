#include<AltSoftSerial.h>

AltSoftSerial yourSerial;

double pitch_B, roll_B, yaw_B;

struct Axis {
  int realN;
  double integer;
};

struct Axis X;
struct Axis Y;
struct Axis Z;

void Status_UART_init() {
  yourSerial.begin(19200);
  while (1) {
    if (yourSerial.available()) {
      char Check = yourSerial.read();
      if (Check == 'B') {
        yourSerial.write('O');
        delayMicroseconds(500);
        Serial.println("Status_UART OK");
        delay(50);
        break;
      }
    }
  }
}

boolean Starting = true;
boolean ROLL = false;
boolean PITCH = false;
boolean YAW = false;
boolean Finish = false;

void Status_UART_Update() {

  if (Starting == true)
    StartingCheck();

  if (ROLL == true)
    RollCheck();

  if (PITCH == true)
    PitchCheck();

  if (YAW == true)
    YawCheck();


  if (Finish == true)
    FinishCheck();


  // StatusPrint();

  yourSerialreset();

}

void StartingCheck() {

  if (yourSerial.available() > 0) {
    char Check = yourSerial.read();

    if (Check == 'S') {
      ROLL = true;
      Starting = false;
    }
    else
      FaildPrint(0x00);
  }
}

void RollCheck() {
  int count = 0;
  int sum = 0;
  while (yourSerial.available() > 0) {

    if (count == 0) {
      char Check = yourSerial.read();
      if ( Check == 'X') {
        Serial.println(" 2 ");
        count++;
      }

      else if ( Check = ! 'X') {
        ROLL = false;
        Starting = true;
        FaildPrint(0x01);
        break;
      }
    }

    if (count == 1) {
      X.realN = yourSerial.read();
      sum += X.realN;
      count++;
    }
    if (count == 2) {
      X.integer = yourSerial.read();
      X.integer /= 100;
      sum += X.integer * 100;
      count++;
    }

    else if (count == 3) {;
      int Confirm = CheckSum(sum);
      if (Confirm == 0) {
        PITCH = true;
        ROLL = false;
        roll_B = X.realN + X.integer;
        break;
      }

      else if (Confirm != 0) {
        Starting = true;
        ROLL = false;
        FaildPrint(0x01);
        break;
      }
    }
  }
}

void PitchCheck() {
  int count = 0;
  int sum = 0;
  while (yourSerial.available() > 0) {

    if (count == 0) {
      char Check = yourSerial.read();

      if ( Check == 'Y')
        count++;

      else if ( Check = ! 'Y') {
        PITCH = false;
        Starting = true;
        FaildPrint(0x01);
        break;
      }
    }

    if (count == 1) {
      Y.realN = yourSerial.read();
      sum += Y.realN;
      count++;
    }
    if (count == 2) {
      Y.integer = yourSerial.read();
      Y.integer /= 100;
      sum += Y.integer * 100;

      count++;
    }

    else if (count == 3) {
      int Confirm = CheckSum(sum);

      if (Confirm == 0) {
        YAW = true;
        ROLL = false;
        pitch_B = Y.realN + Y.integer;
        break;
      }

      else if (Confirm != 0) {
        Starting = true;
        PITCH = false;
        FaildPrint(0x02);
        break;
      }
    }
  }
}

void YawCheck() {
  int count = 0;
  int sum = 0;
  while (yourSerial.available() > 0) {

    if (count == 0) {
      char Check = yourSerial.read();

      if ( Check == 'Z')
        count++;

      else if ( Check = ! 'Z') {
        YAW = false;
        Starting = true;
        FaildPrint(0x02);
        break;
      }
    }

    if (count == 1) {
      Z.realN =  yourSerial.read();
      sum += Z.realN;
      count++;
    }
    if (count == 2) {
      Z.integer = yourSerial.read();
      Z.integer /= 100;
      sum += Z.integer * 100;
      count++;
    }

    else if (count == 3) {
      int Confirm = CheckSum(sum);

      if (Confirm == 0) {
        Finish = true;
        YAW = false;
        yaw_B = Z.realN + Z.integer;
        break;
      }

      else if (Confirm != 0) {
        Starting = true;
        YAW = false;
        FaildPrint(0x03);
        break;
      }
    }
  }
}


void FinishCheck() {

  if (yourSerial.available() > 0) {
    char Check = yourSerial.read();

    if (Check == 'F') {
      //StatusPrint();
      Finish = false;
      Starting = true;
    }

    else {
      Starting = true;
      Finish = false;
      FaildPrint(0x04);
    }
  }
}

char CheckSum(int sum) {
  int total = sum;
  sum &= 0xFF;
  sum = ~sum + 1;
  total = total + sum;
  total &= 0xFF;
  return total;
}

void yourSerialreset() {
  yourSerial.end();
  yourSerial.begin(19200);
}

// No time, output delay time = 2ms + ( 27 * 0.5 ) = 15.5ms / error range 1ms
// Yes time, output delay time = 2ms + ( 33 * 0.5 ) = 18.5ms / error range 1ms
// Control, output delay time = 2ms + ( 48 * 0.5 ) = 26.5ms / error range 1ms
void StatusPrint() {
  Serial.print(" roll_B:"); Serial.print(roll_B);
  Serial.print(" pitch_B:"); Serial.print(pitch_B);
  Serial.print(" yaw_B:"); Serial.print(yaw_B);
  Serial.print("time: "); Serial.println(time);
}

void FaildPrint(char Check) {
  /*
  if (Check == 0x00)
    Serial.print(" STARTING EROOR!!! ");

  else if (Check == 0x01)
    Serial.print(" ROLL ERROR!!! ");

  else if (Check == 0x02)
    Serial.print(" PITCH ERROR!!! ");

  else if (Check == 0x03)
    Serial.print(" YAW ERROR!!! ");

  else if (Check == 0x04)
    Serial.print(" Finish ERROR!!! ");

  Serial.println();
  */
}
