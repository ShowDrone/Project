#include <SPI.h>

void setup (void)
{
  pinMode(MISO, OUTPUT);
  pinMode(MOSI, INPUT);
  pinMode(SCK, INPUT);
  pinMode(SS, INPUT);
  SPCR |= _BV(SPE);
  //SPCR |= _BV(DORD);
  SPCR &= ~_BV(MSTR);
  SPCR |= _BV(SPIE);

  SPI.setClockDivider(SPI_CLOCK_DIV16);

  Serial.begin(9600);
}

struct Axis {
  double rest;
  int16_t add;
} messenger;

boolean plus = false;
boolean minus = false;

boolean Check[6] = {0,};

ISR (SPI_STC_vect)
{
  int Confirm = SPDR;
  Serial.println(sizeof(SPDR));
  delay(1500);
  if (Confirm == 0) {
    Check[0] = true;
    Check[1] = false;
    Check[2] = false;
    Check[3] = false;
    Check[4] = false;
    Check[5] = false;
  }
  else if (Confirm == 1) {
    Check[0] = false;
    Check[1] = true;
    Check[2] = false;
    Check[3] = false;
    Check[4] = false;
    Check[5] = false;
  }
  else if (Confirm == 2) {
    Check[0] = false;
    Check[1] = false;
    Check[2] = true;
    Check[3] = false;
    Check[4] = false;
    Check[5] = false;
  }
  else if (Confirm == 3) {
    Check[0] = false;
    Check[1] = false;
    Check[2] = false;
    Check[3] = true;
    Check[4] = false;
    Check[5] = false;
  }
  else if (Confirm == 4) {
    Check[0] = false;
    Check[1] = false;
    Check[2] = false;
    Check[3] = false;
    Check[4] = true;
    Check[5] = false;
  }
  else if (Confirm == 1000) {
    Check[0] = false;
    Check[1] = false;
    Check[2] = false;
    Check[3] = false;
    Check[4] = false;
    Check[5] = true;
    //Serial.println("_");
  }
  
}

  double pitch = 32.555;
  double roll = 3155.5;
  double yaw = 3055.5;


  void loop (void)
  {
    struct Axis X_Axis;
    X_Axis = Sep(roll);

    struct Axis Y_Axis;
    Y_Axis = Sep(pitch);

    struct Axis Z_Axis;
    Z_Axis = Sep(yaw);

    /*Serial.print(X_Axis.add); Serial.print(" + ");
    Serial.print(X_Axis.rest); Serial.print(" / ");
    Serial.print(Y_Axis.add); Serial.print(" + ");
    Serial.print(Y_Axis.rest); Serial.print(" / ");
    Serial.print(Z_Axis.add); Serial.print(" + ");
    Serial.println(Z_Axis.rest);*/

    /*

    SPI 규칙
    데이터 총 9byte
    통신 순서
    8 - 0 - 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8
    */

    // Roll (X)
    
    if (Check[0] == true) {
      SPDR = X_Axis.add;
      Serial.print(X_Axis.add);
      Serial.print(" ");
      //Serial.print("x1");
      Check[0] = false;
    }
    else if (Check[1] == true) {
      X_Axis.rest = X_Axis.rest * 100;
      int TempX= X_Axis.rest;
      SPDR = X_Axis.rest;
      Serial.print(X_Axis.rest);
      Serial.print(" ");
      //Serial.print("x2");
      Check[1] = false;
    }
    // Pitch (Y)
    else if (Check[2] == true) {
      SPDR = Y_Axis.add;
      Serial.print(Y_Axis.add);
      Serial.print(" ");
      //Serial.print("y1");
      Check[2] = false;
    }
    else if (Check[3] == true) {
      Y_Axis.rest = Y_Axis.rest * 100;
      int TempY= Y_Axis.rest;
      SPDR = Y_Axis.rest;
      Serial.print(Y_Axis.rest);
      Serial.print(" ");
      //Serial.print("y2");
      Check[3] = false;
    }

    // Yaw (Z)
    else if (Check[4] == true) {
      SPDR = Z_Axis.add;
      Serial.print(Z_Axis.add);
      Serial.print(" ");
      //Serial.print("z1");
      Check[4] = false;
    }
    else if (Check[5] == true) {
      Z_Axis.rest = Z_Axis.rest * 100;
      int TempZ= Z_Axis.rest;
      SPDR = Z_Axis.rest;
      Serial.println(Z_Axis.rest);
      //Serial.println("z2");
      Check[5] = false;
    }

  }

  // Data분리 함수 Sep = Separation
  struct Axis Sep(double value) {
    if (value == 0) {
      messenger.rest = 0;
      messenger.add = 0;
      return messenger;
    }
    if (value > 0) {
      plus = true;
      minus = false;
    }

    else if (value < 0) {
      plus = false;
      minus = true;
    }

    value = abs(value);

    if (plus)
      messenger.rest = value - floor(value);
    else if (minus)
      messenger.rest = -(value - floor(value));
    
    messenger.add = floor(value);
    
    return messenger;
  }