#include<LiquidCrystal.h>
LiquidCrystal lcd (16,17,18,19,20,21);
//
int x[] = {10,11,13,14,15}; // ON : LOW 
int y[] = {2,3,4,5,6,7,8,9}; // ON : HIGH
//
int score = 0; // game score
int left_switch = 23;
int right_switch = 22;
void setup() {
  Serial.begin(9600); // Serial
  lcd.begin(16,2); // lcd 
  for(int i=0;i<8;i++)
  {
    pinMode(y[i],OUTPUT);
  }
  for(int i=0;i<5;i++)
  {
    pinMode(x[i],OUTPUT);
  }
  pinMode(left_switch,INPUT_PULLUP);
  pinMode(right_switch,INPUT_PULLUP);
}
int ch[5] = {1,1,0,1,1};
void loop() {
  y_clear();
  x_clear();
  ch_Function();
  //y_set();
  Serial.print(ch[0]);
  Serial.print(ch[1]);
  Serial.print(ch[2]);
  Serial.print(ch[3]);
  Serial.println(ch[4]);
} //loop exit
int time;
int time_value = 1;
int enemy_y[8] = {1,0,0,0,0,0,0,0};
void y_set() {
for(int i=7;i>=0;i--)
{
  while(1)
  {
  time = millis()/1000;
  if(i==enemy_y[i])
  digitalWrite(y[i],HIGH);
  else
  digitalWrite(y[i],LOW); /////////////////////////Here
  x_set();
  if(time >= time_value)
  {
    time_value+=1;
    break;
  }
  } //while exit
} // for exit
}// Function exit
int enemy[5] = {1,1,0,1,1};
void x_set() {
  for(int i=0;i<5;i++)
  {
    digitalWrite(x[i],enemy[i]);
  }
}

void ch_Function() {
int left = digitalRead(left_switch);
int right = digitalRead(right_switch);
digitalWrite(y[0],HIGH);

for(int i=0;i<5;i++)
{
  for(int j=0;j<5;j++)
  {
    if(ch[j]==0)
    digitalWrite(x[j],LOW);
    else
    digitalWrite(x[j],HIGH);
  }
}
if(left == 0)
{
  if(ch[0] != 0)
  {
    for(int i=0;i<5;i++)
    {
      if(ch[i] == 0)
      {
        ch[i] = 1;
        ch[i-1] = 0;
        delay(300);
      } //if exit
    } //for eixt
  } //if exit
} // left if exit

else if(right == 0)
{
  if(ch[4] != 0)
  {
    for(int i=4;i>=0;i--)
    {
      if(ch[i] == 0)
      {
        ch[i] = 1;
        ch[i+1] = 0;
        delay(300);
      } //if exit
    } //for eixt
  } //if exit
} // left if exit
}



void y_clear() {
for(int i=0;i<8;i++)
{
  digitalWrite(y[i],LOW);
}
}
void x_clear() {
for(int i=0;i<5;i++)
{
  digitalWrite(x[i],HIGH);
}
}


