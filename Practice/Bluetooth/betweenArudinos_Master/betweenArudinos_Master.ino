#include<TextFinder.h>

String Remote ="201312050483";
void setup() {
Serial.begin(9600);
Serial.print("Test");
delay(100);
Serial.println("c"+ Remote + "\r");
delay(100);
Serial.println("SM,1");
delay(100);
Serial.println("+++," + Remote + "\r");
delay(100);
}

void loop() {

}
