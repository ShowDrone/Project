#include<AltSoftSerial.h>

AltSoftSerial yourSerial;

double pitch_B, roll_B, yaw_B;

void Status_UART_init() {
  yourSerial.begin(19200);
  while (1) {
    while (yourSerial.available()) {
      int check = yourSerial.read();
      if (check == 'B') {
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
boolean Between = false;
boolean Finish = false;

int correct = 0;

void Status_UART_Update() {
  if (Starting == true)
    StartingCheck();

  if (Between == true)
    BetweenCheck();

  if (Finish == true)
    FinishCheck();

}

void StartingCheck() {
  int count = 0;

  while (yourSerial.available() > 0) {
    int Check = yourSerial.read();
    count++;

    if (Check == 'S') {
      correct++;
      Between = true;
      Starting = false;
    }

    if (count == 1)
      break;
  }
}

void BetweenCheck() {
  int count = 0;
  int sum = 0;
  while (yourSerial.available() > 0) {
    int Check = yourSerial.read();
    count++;
    sum += Check;

    if (count == 2) {
      int Confirm = CheckSum(sum);

      if (Confirm == 0) {
        Finish = true;
        Between = false;
        correct += 3;
      }
      break;
    }
  }
}


void FinishCheck() {
  int count = 0;

  while (yourSerial.available() > 0) {
    int Check = yourSerial.read();
    count++;
    correct++;

    if (Check == 'F' && correct == 4) {
      Starting = true;
      Finish = false;
    }

    if (count == 1)
      break;
  }
}

int CheckSum(int sum) {
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
  Serial.print(" yaw_B:"); Serial.println(yaw_B);
  Serial.print("time: "); Serial.println(time);
}
