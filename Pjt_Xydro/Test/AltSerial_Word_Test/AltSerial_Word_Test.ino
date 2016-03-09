
// Transmite Code

/*#include<AltSoftSerial.h>

AltSoftSerial altSerial;

void setup() {

  altSerial.begin(19200);

}

void loop() {

  altSerial.write('A');

  delay(1);

}*/



// Receive Code

#include<AltSoftSerial.h>

AltSoftSerial altSerial;

void setup() {

  altSerial.begin(19200);
  Serial.begin(19200);
}

void loop() {

  if (altSerial.available()) {
    char readSerial = altSerial.read();
    if (readSerial == 'A')
      Serial.println(readSerial);

  }

}
