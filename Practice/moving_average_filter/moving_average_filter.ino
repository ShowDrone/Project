#include<AltSoftSerial.h>
AltSoftSerial altSerial;

double X_Axis[4] = {0.0,};
double Y_Axis[4] = {0.0,};
double Z_Axis[4] = {0.0,};

int init_check = 1;
boolean initSucces = false;

void setup() {
  Serial.begin(19200);
  altSerial.begin(19200);
  while (initSucces == false)
    initialize();
  Serial.println(" ||| init Succesful ||| ");
  delay(500);
}

void loop() {
  while (altSerial.available()) {
bye:
    X_Axis[0] = altSerial.read();
    Y_Axis[0] = altSerial.read();
    Z_Axis[0] = altSerial.read();
    double sum = X_Axis[0] + Y_Axis[0] + Z_Axis[0];
    int checksum = CheckSum(sum);
    if (checksum != 0)
      goto bye;

    MAF(X_Axis[0], Y_Axis[0], Z_Axis[0]);
    //altprint(checksum, 3);
    altAllprint();
  }
}

void MAF(double X, double Y, double Z) {
  X_Axis[2] = X_Axis[1];
  X_Axis[1] = X_Axis[0];
  X_Axis[0] = X;
  for (int i = 0; i < 3; i++)
    X_Axis[3] += X_Axis[i];
  X_Axis[3] /= 3;

  Y_Axis[2] = Y_Axis[1];
  Y_Axis[1] = Y_Axis[0];
  Y_Axis[0] = Y;
  for (int i = 0; i < 3; i++)
    Y_Axis[3] += Y_Axis[i];
  Y_Axis[3] /= 3;

  Z_Axis[2] = Z_Axis[1];
  Z_Axis[1] = Z_Axis[0];
  Z_Axis[0] = Z;
  for (int i = 0; i < 3; i++)
    Z_Axis[3] += Z_Axis[i];
  Z_Axis[3] /= 3;
}



void altAllprint() {
  Serial.print("X: "); Serial.print(X_Axis[0]); Serial.print(" ");
  Serial.print(X_Axis[1]); Serial.print(" "); Serial.print(X_Axis[2]);
  Serial.print(" | Y: "); Serial.print(Y_Axis[0]); Serial.print(" ");
  Serial.print(Y_Axis[1]); Serial.print(" "); Serial.print(Y_Axis[2]);
  Serial.print(" | Z: "); Serial.print(Z_Axis[0]); Serial.print(" ");
  Serial.print(Z_Axis[1]); Serial.print(" "); Serial.println(Z_Axis[2]);
}

int CheckSum(int sum) {
  int temp = sum & 0xFF;
  temp = ~temp + 1;
  sum = temp + sum;
  sum = sum & 0xFF;
  return sum;
}

void initialize() {
  if (init_check < 3) {
    X_Axis[init_check] = altSerial.read();
    Y_Axis[init_check] = altSerial.read();
    Z_Axis[init_check] = altSerial.read();
    init_check++;
    altprint(0, init_check);
  }
  if (init_check == 2)
    initSucces = true;

}

void altprint(int checksum, int i) {
  Serial.print("X: "); Serial.print(X_Axis[i]);
  Serial.print(" Y: "); Serial.print(Y_Axis[i]);
  Serial.print(" Z: "); Serial.print(Z_Axis[i]);
  Serial.print(" ||| "); Serial.println(checksum);
}
