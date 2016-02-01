const int TRIG = 13;
const int ECHO = 12;
const int LED_Green = 11;
const int LED_Yellow= 10;
const int LED_Red = 9;
const int Switch = 8;
void setup() {
pinMode(TRIG,OUTPUT);
pinMode(ECHO,INPUT);
pinMode(LED_Yellow, OUTPUT);
pinMode(LED_Green, OUTPUT);
pinMode(LED_Red, OUTPUT);
pinMode(Switch,INPUT_PULLUP);
Serial.begin(9600);
}
void loop() {
digitalWrite(TRIG, LOW);
delayMicroseconds(2);
digitalWrite(TRIG,HIGH);
delayMicroseconds(5);
digitalWrite(TRIG,LOW);
unsigned int distance = (pulseIn(ECHO, HIGH) / 58.2) ;
  Serial.println("distance:" +(String)distance);
if (distance <= 10)
{
  if(LED_Yellow == 1)
  {
  digitalWrite(LED_Yellow,LOW);
  }
  if (LED_Green == 1)
  {
  digitalWrite(LED_Green,LOW);
  }
  digitalWrite(LED_Red,HIGH);
}
else if (distance <= 20)
{
  if(LED_Red == 1)
  {
    digitalWrite(LED_Red,LOW);
  }
  if (LED_Green == 1)
  {
  digitalWrite(LED_Green,LOW);
  } 
  digitalWrite(LED_Yellow,HIGH);
}
else if (distance <= 30)
{
  if(LED_Yellow == 1)
  {
    digitalWrite(LED_Yellow,LOW);
  }
  if (LED_Red == 1)
  {
  digitalWrite(LED_Red,LOW);
  }
  digitalWrite(LED_Green,HIGH);
}
else
{
  Serial.println("DATA OUT");
}

}
