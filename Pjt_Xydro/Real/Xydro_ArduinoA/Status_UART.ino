#include<AltSoftSerial.h>
AltSoftSerial altSerial;

double pitch_B, roll_B, yaw_B;

void Status_UART_init() {
  altSerial.begin(19200);
}

void Status_UART_Update() {
  int i = 0;
  while (altSerial.available()) {
    if (i == 0)
      roll_B = altSerial.read();
    else if (i == 1)
      pitch_B = altSerial.read();
    else if (i == 2)
      yaw_B = altSerial.read();
    i++;
    if ( i == 3) {
      //StatusPrint();
      break;
    }
  }
}

void StatusPrint() {
  Serial.print(" roll_B:"); Serial.print(roll_B);
  Serial.print(" pitch_B:"); Serial.print(pitch_B);
  Serial.print(" yaw_B:"); Serial.println(yaw_B);
}
