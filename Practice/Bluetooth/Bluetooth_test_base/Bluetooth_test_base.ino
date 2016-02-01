int segment[16][7] = {
 {0,0,0,0,0,0,1}, // 0
 {1,0,0,1,1,1,1}, // 1
 {0,0,1,0,0,1,0}, // 2
 {0,0,0,0,1,1,0}, // 3
 {1,0,0,1,1,0,0}, // 4
 {0,1,0,0,1,0,0}, // 5
 {0,1,0,0,0,0,0}, // 6
 {0,0,0,1,1,0,1}, // 7
 {0,0,0,0,0,0,0}, // 8
 {0,0,0,0,1,1,0}, // 9
 {0,0,0,0,1,0,0}, // A
 {1,1,0,0,0,0,0}, // B
 {0,1,1,0,0,0,1}, // C
 {1,0,0,0,0,1,0}, // D
 {0,1,1,0,0,0,0}, // E
 {0,1,1,1,0,0,0}, // F
}; //segment exit
//ASKII code 48 = 0, 49 = 1 ... A = 65 , a = 97
String myString = "";
String yourString = "";
int seg_1 = 13; // anode type , VCC = OFF, GND = ON
int seg_2 = 12;
int seg_3 = 11;
int seg_4 = 10;
#include<SoftwareSerial.h>
int blueTx = 2;
int blueRX = 3;
SoftwareSerial mySerial(2,3); // Tx, Rx
void setup() {
for(int i=3;i<10;i++)
{
  pinMode(i,OUTPUT); //3A,4B,5C,6D,7E,8F,9G
}
mySerial.begin(9600);
Serial.begin(9600);
while(!Serial) {
}
delay(100);
Serial.println("Hello!, Seung Hyun Lee");
}

void loop() {

  while(mySerial.available())
  {
    char myChar = mySerial.read();
    myString+=myChar;
  }
  if(myString != "")
  {
     Serial.print(myString);
     delay(50);
     myString = "";
     Serial.println(" ");
  }
  while(Serial.available())
  {
    char yourChar = Serial.read();
    yourString+=yourChar;
  }
  if(yourString != "");
  {
    mySerial.println(yourString);
    delay(50);
    yourString = "";
  }
}// loop exit

