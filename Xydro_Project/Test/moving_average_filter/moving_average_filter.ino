
///////////////////Create By///////////////////
/////* http://blog.naver.com/dkwltmdgus */////
////////////////Date 2015-01-27//////////////
////////Optimization-UART_Sum_RX.ino////////

#include<AltSoftSerial.h>
AltSoftSerial altSerial;

struct buf {
  // arr part 1=first_value, 2=second_value, 3=third_Value, 4=average_value
  double buf[4] = {0,};
} messenger;

struct buf X_Axis;
struct buf Y_Axis;
struct buf Z_Axis;

void setup() {
  Serial.begin(19200);
  altSerial.begin(19200);
  int count = 0;
  while (1) {
    if (altSerial.available()) {
      X_Axis.buf[count] = altSerial.read();
      Y_Axis.buf[count] = altSerial.read();
      Z_Axis.buf[count] = altSerial.read();
      count++;
    }
    if (count == 2)
      break;
  }
  for (int i = 0; i < 3; i++) {
    X_Axis.buf[3] += X_Axis.buf[i];
    Y_Axis.buf[3] += Y_Axis.buf[i];
    Z_Axis.buf[3] += Z_Axis.buf[i];
    if (i == 2) {
      X_Axis.buf[3] /= 3;
      Y_Axis.buf[3] /= 3;
      Z_Axis.buf[3] /= 3;
    }
  }
}


void loop() {
  if (altSerial.available()) {
    double X = altSerial.read();
    double Y = altSerial.read();
    double Z = altSerial.read();
    X_Axis = calculation(X, 'X');
    Y_Axis = calculation(Y, 'Y');
    Z_Axis = calculation(Z, 'Z');
  }
 
  altSerialprint();
}

void altSerialprint() {
  Serial.print(X_Axis.buf[3]); Serial.print(" ");
  Serial.print(Y_Axis.buf[3]); Serial.print(" ");
  Serial.println(Z_Axis.buf[3]);
}


struct buf calculation(double value, char check) {
  if (check == 'X')
    messenger = cal_for(X_Axis, value);
  else if (check == 'Y')
    messenger = cal_for(Y_Axis, value);
  else if (check == 'Z')
    messenger = cal_for(Z_Axis, value);
    
  return messenger;
}

// cal_for == calculation for
struct buf cal_for(struct buf A, double value) {
  A.buf[2] = A.buf[1];
  A.buf[1] = A.buf[0];
  A.buf[0] = value;
  A.buf[3] = 0;
  for(int i = 0;i< 3;i++) {
    A.buf[3] += A.buf[i];
  }
  A.buf[3] /= 3;
  return A;
}
