#include<AltSoftSerial.h>
AltSoftSerial altSerial;

void Transmiter_init() {
  altSerial.begin(19200);
}
void Transmiter_Update() {
  altSerial.write(roll);
  delayMicroseconds(5);
  altSerial.write(pitch);
  delayMicroseconds(5);
  altSerial.write(yaw);
  delayMicroseconds(2);
}
