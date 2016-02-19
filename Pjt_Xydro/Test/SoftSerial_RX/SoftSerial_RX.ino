#include <SoftwareSerial.h>

SoftwareSerial Serial_one(8, 9);
SoftwareSerial Serial_two(10, 11);

void setup()
{
  Serial_one.begin(19200);
  Serial_two.begin(19200);
  Serial.begin(19200);
}

int one_A, one_B, one_C;
int two_A, two_B, two_C;

boolean one = false, two = false;

void loop()
{
  int i = 0;

  Serial_one.listen();
  while (Serial_one.available()) {
    if (i == 0)
      one_A = Serial_one.read();
    else if (i == 1)
      one_B = Serial_one.read();
    else if (i == 2)
      one_C = Serial_one.read();
    i++;
    if ( i == 3) {
      one = true;
      two = false;
      break;
    }
  }

  Serial_two.listen();
  while (Serial_two.available()) {
    if (i == 0)
      two_A = Serial_one.read();
    else if (i == 1)
      two_B = Serial_one.read();
    else if (i == 2)
      two_C = Serial_one.read();
    i++;
    if ( i == 3) {
      one = false;
      two = true;
      break;
    }
  }
  if (one)
    Statusprint(true,one_A, one_B, one_C);
  else if (two)
    Statusprint(false,two_A, two_B, two_C);
}

void Statusprint(int check, int A, int B, int C) {
  Serial.print("This is "); Serial.print(check);
  Serial.print(" A: "); Serial.print(A);
  Serial.print(" B: "); Serial.print(B);
  Serial.print(" C: "); Serial.println(C);
}
