int TRIG = 12;
int ECHO = 13;
void setup() {
  pinMode(TRIG,OUTPUT);
  pinMode(ECHO,INPUT);
  pinMode(11,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(TRIG,LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG,HIGH);
  delayMicroseconds(5);
  digitalWrite(TRIG,LOW);
  int value = (pulseIn(ECHO,HIGH)/58.2);
  Serial.print("value:"+(String)value);
  Serial.println("cm");
  delay(100);
  if(value >= 10)
  {
    digitalWrite(11,LOW);
  }
  else if(value < 10)
  {
  digitalWrite(11,HIGH);
  tone(10,300,(1000/4));
  }
}
