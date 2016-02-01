void setup() {
  for(int i=7; i<=13; i++)
  {
  pinMode(i, OUTPUT);
  }
  pinMode(2, OUTPUT);
  pinMode(3,INPUT_PULLUP);
  Serial.begin(9600);
}
int sw=0;
int app=0;
void loop() {
   digitalWrite(2,1);
   int sw = digitalRead(3);
   delay(100); 
   Serial.println("sw =" +(String)sw);
   zero();
   if(sw==0 && app == 0)
   {
   one(); 
   app++; 
   delay(1000);
   }
   if(sw==1 && app == 0)
   {
     delay(500);
   }
   if (sw==0 && app == 1)
   {
   two();
   app++;
   delay(1000);
   }
   /*
   three();
   delay(500);
   four();
   delay(500);
   five();
   delay(500);
   six();
   delay(500);
   seven();
   delay(500);
   eight();
   delay(500);
   nine();
   delay(500);*/
}

void zero() {
  for(int j=13;j>=8;j--)
  {
digitalWrite(j,LOW);
  }
  digitalWrite(7,HIGH);
}
void one() {
  digitalWrite(12,LOW);
  digitalWrite(11,LOW);
  digitalWrite(13,HIGH);
  for (int a = 10; a>=7 ;a--)
  {
    digitalWrite(a,HIGH);
  }
}

void two() { //A,B,G,D,E
digitalWrite(13,LOW);
digitalWrite(7,LOW);
digitalWrite(12,LOW);
digitalWrite(10,LOW);
digitalWrite(9,LOW);
digitalWrite(11,HIGH);
digitalWrite(8,HIGH);
}

void three() {//a,b,c,d,g
digitalWrite(13,LOW);
digitalWrite(7,LOW);
digitalWrite(12,LOW);
digitalWrite(10,LOW);
digitalWrite(11,LOW);
digitalWrite(9,HIGH);
digitalWrite(8,HIGH);
}

void four() {//F,G,B,C
digitalWrite(13,HIGH);
digitalWrite(12,LOW);
digitalWrite(11,LOW);
digitalWrite(10,HIGH);
digitalWrite(9,HIGH);
digitalWrite(8,LOW);
digitalWrite(7,LOW);
}

void five() {
digitalWrite(13,LOW);
digitalWrite(12,HIGH);
digitalWrite(11,LOW);
digitalWrite(10,LOW);
digitalWrite(9,HIGH);
digitalWrite(8,LOW);
digitalWrite(7,LOW);
}

void six() {
digitalWrite(13,LOW);
digitalWrite(12,HIGH);
digitalWrite(11,LOW);
digitalWrite(10,LOW);
digitalWrite(9,LOW);
digitalWrite(8,LOW);
digitalWrite(7,LOW);
}
void seven() {
digitalWrite(13,LOW);
digitalWrite(12,LOW);
digitalWrite(11,LOW);
digitalWrite(10,HIGH);
digitalWrite(9,HIGH);
digitalWrite(8,LOW);
digitalWrite(7,HIGH);
}

void eight() {
digitalWrite(13,LOW);
digitalWrite(12,LOW);
digitalWrite(11,LOW);
digitalWrite(10,LOW);
digitalWrite(9,LOW);
digitalWrite(8,LOW);
digitalWrite(7,LOW);
}

void nine() {
digitalWrite(13,LOW);
digitalWrite(12,LOW);
digitalWrite(11,LOW);
digitalWrite(10,LOW);
digitalWrite(9,HIGH);
digitalWrite(8,LOW);
digitalWrite(7,LOW);
}
