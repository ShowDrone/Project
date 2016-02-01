void setup() {
pinMode(11,OUTPUT); //LED
pinMode(13,INPUT); // ECHO
pinMode(12,OUTPUT); //TRIG
Serial.begin(9600);
}
void loop() {
  digitalWrite(12,LOW);
  delayMicroseconds(2);
  digitalWrite(12,HIGH);
  delayMicroseconds(5);
  digitalWrite(12, LOW);
int distance = (pulseIn(13,HIGH) / 58.2);

if (distance < 10)
{
  digitalWrite(11,HIGH);
  delay(100);
  digitalWrite(11,LOW);
  delay(100);
}
else if(distance < 20)
{
  digitalWrite(11,HIGH);
  delay(500);
  digitalWrite(11,LOW);
  delay(500);
}
else if(distance < 30)
{
  digitalWrite(11,HIGH);
  delay(1000);
  digitalWrite(11,LOW);
  delay(1000);
}
}
