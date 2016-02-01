int segment[10][7] = {
 {0,0,0,0,0,0,1}, // 0
 {1,0,0,1,1,1,1}, // 1
 {0,0,1,0,0,1,0}, // 2
 {0,0,0,0,1,1,0}, // 3
 {1,0,0,1,1,0,0}, // 4
 {0,1,0,0,1,0,0}, // 5
 {0,1,0,0,0,0,0}, // 6
 {0,0,0,1,1,0,1}, // 7
 {0,0,0,0,0,0,0}, // 8
 {0,0,0,0,1,0,0}, // 9
}; //segment exit
//ASKII code 48 = 0, 49 = 1 ... A = 65 , a = 97
int myInt[2] = {0,0};
int seg[7] = {4,5,6,7,8,9,10};
int seg_1 = 13; // anode type , VCC = OFF, GND = ON
int seg_2 = 12;
int seg_3 = 11;
int seg_4 = 10;
#include<SoftwareSerial.h>
int blueTx = 2;
int blueRX = 3;
SoftwareSerial mySerial(2,3); // Tx, Rx
void setup() {
for(int i=3;i<14;i++)
{
  pinMode(i,OUTPUT); //4A,5B,6C,7D,8E,9F,10G
}
mySerial.begin(9600);
Serial.begin(9600);
while(!Serial) {
}
delay(100);
Serial.println("Hello!, Seung Hyun Lee");
}
int num1=0;
int num2=0;
void loop() {
   if(mySerial.available())
   {
   num1 = mySerial.read()-48;  
   delay(10);
   num2 = mySerial.read()-48;
   Serial.println((String)num1+" "+(String)num2);
   }
 digitalWrite(seg_1,HIGH);
 digitalWrite(seg_2,LOW);
 for(int j=0;j<8;j++)
 {
   digitalWrite(seg[j],segment[num1][j]);
 }
 delay(5);
 digitalWrite(seg_1,LOW);
 digitalWrite(seg_2,HIGH);
 for(int j=0;j<8;j++)
 {
   digitalWrite(seg[j],segment[num2][j]);
 }
 delay(5);
}// loop exit



