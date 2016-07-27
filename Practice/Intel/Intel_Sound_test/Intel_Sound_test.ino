
int LED = 13;
int sensorValue = A0;
void setup()
{
  Serial.begin(115200); // 시리얼 통신 ON
}
void loop()
{
  sensorValue = analogRead(sensorValue);
  Serial.println(sensorValue,DEC);
}

