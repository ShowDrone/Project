void setup() {  
  int i;
  Serial.begin(9600);
  pinMode(13,INPUT_PULLUP); //Switch
  for (i=8;i<=12; i++) //LED
  {
    pinMode(i,OUTPUT);
  }

}

void loop() { 
 //CAR , LED NUMBER IS 8,9,10 (8=Green, 9 = Yellow, 10 = Red)
 //Human, LED NUMBER IS 11,12 (11 = Green, 12 = Red)
int i;
int swt = Serial.println(digitalRead(13));
digitalWrite(8,1);
if (digitalRead(8) ==1) //CAR LED <GREEN ON> Human LED <RED ON>
  digitalWrite(12,1);
else if(swt ==
0)
 {
  digitalWrite(8,0);
  digitalWrite(9,1);
  delay(1000);
  digitalWrite(9,0);
  digitalWrite(10,1);
  // Under led   
  digitalWrite(12,0);
  digitalWrite(11,1);
  delay(3000);
    for(int h=0 ; h<5; h++)
    {
    digitalWrite(11,0);
    delay(300);
    digitalWrite(11,1);
    delay(300);  
    }
    digitalWrite(11,0);

  digitalWrite(10,0);
  digitalWrite(9,1);
  delay(1000);
  digitalWrite(9,0);
  digitalWrite(8,1);
   //CAR , LED NUMBER IS 8,9,10 (8=Green, 9 = Yellow, 10 = Red)
 //Human, LED NUMBER IS 11,12 (11 = Green, 12 = Red)
 }
}
