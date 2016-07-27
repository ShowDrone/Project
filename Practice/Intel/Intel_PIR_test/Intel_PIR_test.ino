
int PIR_Sensor = 2;
int LED_Sensor = 3;
int PIR_Data = LOW;
void setup() {
pinMode(PIR_Sensor,INPUT); //PIR센서를 INPUT으로 설정
pinMode(LED_Sensor,OUTPUT); //LED센서를 OUTPUT으로 설정
}

void loop() {
  PIR_Data = digitalRead(PIR_Sensor); //PIR_Data에 PIR센서값 읽어들여 저장
  if(PIR_Data==HIGH) //
  {
    digitalWrite(LED_Sensor,HIGH); //사람이 감지되면
  }
  if(PIR_Data==LOW)
  {
    digitalWrite(LED_Sensor,LOW); //사람이 감지되지 않으면
  }
}
