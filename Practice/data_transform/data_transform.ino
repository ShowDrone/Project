/*

Date    :  2015-01-15
Maker   :  Lee SeungHyun (Blog Address : http://dkwltmdgus.blog.me)
MCU     :  Arduino Mega
Purpose :  9Byte / Real number SPI Commnuication Test
Please do not change this section

아래 소스는 실수 데이터를 3바이트로 변환하는 소스입니다.
SPI 통신 시 1바이트(0~255) 밖에 전달을 못하는 단점을 보완하기 위해
제작한 소스이므로 300.5라는 소스가 있다고 가정하고 예를 들자면
변수명 rest에 0.5, add에 45, multiple에 1이라는 값이 대입됩니다.
이걸 다시 원래 데이터로 변환하자면 add+rest+multiple*255 하시면
원래 데이터인 300.5가 나옵니다.

이 소스를 SPI용으로 변경하셔서 사용하시면 됩니다.

*/


void setup() {
  Serial.begin(9600);
}

struct Axis {
  double rest;
  int multiple;
  int add;
} messenger;

double pitch = 32.55;
double roll =  3155.5;
double yaw = 3055.5;

double A, B, C;

void loop() {
  struct Axis X_Axis;
  X_Axis = Sep(roll);
  A = Trans(X_Axis);

  struct Axis Y_Axis;
  Y_Axis = Sep(pitch);
  B = Trans(X_Axis);

  struct Axis Z_Axis;
  Z_Axis = Sep(yaw);
  C = Trans(X_Axis);

  Serial.print(X_Axis.add); Serial.print(" + ");
  Serial.print(X_Axis.rest); Serial.print(" + ");
  Serial.print(X_Axis.multiple); Serial.print(" / ");
  Serial.print(Y_Axis.add); Serial.print(" + ");
  Serial.print(Y_Axis.rest); Serial.print(" + ");
  Serial.print(Y_Axis.multiple); Serial.print(" / ");
  Serial.print(Z_Axis.add); Serial.print(" + ");
  Serial.print(Z_Axis.rest); Serial.print(" + ");
  Serial.println(Z_Axis.multiple);
  //Serial.print(C); Serial.println("!!");
}


boolean plus = false;
boolean minus = false;

// Data분리 함수 Sep = Separation
struct Axis Sep(double value) {
  if (value == 0) {
    messenger.rest = 0;
    messenger.multiple = 0;
    messenger.add = 0;
    return messenger;
  }
  boolean add_Check = true;

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

  value = floor(value);

  if (value >= 255) {
    if (plus)
      messenger.multiple = value / 255;
    else if (minus)
      messenger.multiple = -(value / 255);
  }

  else if (0 < value && value < 255) {
    messenger.multiple = 0;
    if (minus)
      value = -value;
  }

  for (int i = 0; i < abs(messenger.multiple); i++) {
    if (plus)
      messenger.add = value - (255 * messenger.multiple);
    else if (minus)
      messenger.add = -(value + (255 * messenger.multiple));
    add_Check = false;
  }
  if (add_Check)
    messenger.add = value;
  return messenger;
}

// Data 변환함수 Trans == Transformation
double Trans(struct Axis value) {
  return value.add + value.rest + (value.multiple * 255);
}
