
SoftwareSerial yourSerial(4, 5);

double pitch_B, roll_B, yaw_B;

void Status_UART_init() {
  yourSerial.begin(19200);
}


void Status_UART_Update() {
  yourSerial.listen();
  int i = 0;
  while (yourSerial.available()) {
    if (i == 0)
      roll_B = yourSerial.read();
    else if (i == 1)
      pitch_B = yourSerial.read();
    else if (i == 2)
      yaw_B = yourSerial.read();
    i++;
    if ( i == 3) {
      yourSerialreset;
      StatusPrint();
      break;
    }
  }
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
