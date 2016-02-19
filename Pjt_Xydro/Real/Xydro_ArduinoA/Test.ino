
#include<NewSoftSerial.h>
NewSoftSerial newSerial;

double pitch_B, roll_B, yaw_B;
uint8_t rxpin = 7;

void Status_UART_init() {
  newSerial.begin(19200);
  //newSerial.setRX(rxpin);
}
void Status_UART_Update() {
  int i = 0;
  while (newSerial.available()) {
    if (i == 0)
      roll_B = newSerial.read();
    else if (i == 1)
      pitch_B = newSerial.read();
    else if (i == 2)
      yaw_B = newSerial.read();
    i++;
    if ( i == 3) {
      StatusPrint();
      break;
    }
  }
}

// output delay time = 2ms + ( 27 * 0.5 ) = 15.5ms / error range 1ms
// output delay time = 2ms + ( 33 * 0.5 ) = 18.5ms / error range 1ms
void StatusPrint() {
  Serial.print(" roll_B:"); Serial.print(roll_B);
  Serial.print(" pitch_B:"); Serial.print(pitch_B);
  Serial.print(" yaw_B:"); Serial.println(yaw_B);
  Serial.print("time: "); Serial.print(time);
}
