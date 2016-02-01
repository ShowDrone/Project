
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
