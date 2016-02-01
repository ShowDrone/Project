#include<LiquidCrystal.h>
LiquidCrystal lcd (16,17,18,19,20,21);
//
int x[] = {10,11,13,14,15}; // ON : LOW 
int y[] = {2,3,4,5,6,7,8,9}; // ON : HIGH
//
int direct = 0; // left, Right
int time = 0; // time 
int score = 0; // game score
int left_switch = 22;
int right_switch = 23;
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
  int left = digitalRead(left_switch); 
  int right = digitalRead(right_switch);

int Hello1[8][5] = {
  {1,1,1,1,1},
  {1,0,1,0,1},
  {1,0,1,0,1},
  {1,0,0,0,1},
  {1,0,1,0,1},
  {1,0,1,0,1},
  {1,1,1,1,1},
  {1,1,1,1,1},
};
int Hello2[8][5] = {
  {1,1,1,1,1},
  {1,0,0,0,1},
  {1,0,1,1,1},
  {1,0,0,0,1},
  {1,0,1,1,1},
  {1,0,0,0,1},
  {1,1,1,1,1},
  {1,1,1,1,1},
};

int Hello3[8][5] = {
  {1,1,1,1,1},
  {1,1,1,1,1},
  {1,1,1,1,1},
  {1,1,1,1,1},
  {1,0,0,0,0},
  {1,0,1,1,1},
  {1,0,1,1,1},
  {1,0,1,1,1},
};

int Hello4[8][5] = {
  {1,0,0,0,0},
  {1,0,1,1,1},
  {1,0,1,1,1},
  {1,0,1,1,1},
  {1,1,1,1,1},
  {1,1,1,1,1},
  {1,1,1,1,1},
  {1,1,1,1,1},
};

int Hello5[8][5] = {
  {1,1,1,1,1},
  {1,1,0,1,1},
  {1,0,1,0,1},
  {1,0,1,0,1},
  {1,0,1,0,1},
  {1,1,0,1,1},
  {1,1,1,1,1},
  {1,1,1,1,1},
};

int intel1[8][5] = {
    {1,1,1,1,1},
    {1,0,0,0,1},
    {1,1,0,1,1},
    {1,1,0,1,1},
    {1,1,0,1,1},
    {1,0,0,0,1},
    {1,1,1,1,1},
    {1,1,1,1,1},
};
int intel2[8][5] = {
    {1,1,1,1,1},
    {0,1,1,1,0},
    {0,1,1,0,0},
    {0,1,0,1,0},
    {0,0,1,1,0},
    {0,1,1,1,0},
    {1,1,1,1,1},
    {1,1,1,1,1},
};

int intel3[8][5] = {
    {1,1,1,1,1},
    {1,1,0,1,1},
    {1,1,0,1,1},
    {1,1,0,1,1},
    {1,1,0,1,1},
    {0,0,0,0,0},
    {1,1,1,1,1},
    {1,1,1,1,1},
};

int intel4[8][5] = {
    {1,1,1,1,1},
    {1,0,0,0,1},
    {1,0,1,1,1},
    {1,0,0,0,1},
    {1,0,1,1,1},
    {1,0,0,0,1},
    {1,1,1,1,1},
    {1,1,1,1,1},
};

int intel5[8][5] = {
    {1,1,1,1,1},
    {0,0,0,0,0},
    {0,1,1,1,1},
    {0,1,1,1,1},
    {0,1,1,1,1},
    {0,1,1,1,1},
    {1,1,1,1,1},
    {1,1,1,1,1},
};

int allON[8][5] = {
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,0,0,0,0},
  {0,0,0,0,0},
};

int time_value = 3;
void _while(int arr[8][5]) {
while(1)
  {
  arr_value(arr);
  time = millis()/1000;
  Serial.println(time);
  if(time >= time_value)
  {
    time_value+=1;
    break;
  }
  }
}
int one_loop = 0;
void loop() {
  if(one_loop = 1)
  {
  sub_main(); // road);
  x_clear();
  y_clear();
  _while(allON);
  _while(allON);
  _while(Hello1);
  _while(Hello2);
  _while(Hello3);
  _while(Hello4);
  _while(Hello5);
  _while(intel1);
  _while(intel2);
  _while(intel3);
  _while(intel4);
  _while(intel5);
  one_loop = 0;
  }
  game_start();
  delay(3000);
  moving();
//  _game  
}//loop exit

void ingame() {
  moving();  
}
int ch = 2;
int ch_coor = 2;
void moving() {
  game_score();
  digitalWrite(y[0],HIGH);
  if(left == 0)
  {
    ch--;
    if(ch!=0)
    digitalWrite(x[ch],LOW);
  }
  else if(right == 0)
  {
    if(ch!=4)
    {
      digitalWrite(x[ch],HIGH);
    }
  }
}

void game_start() {
  lcd.setCursor(3,0);
  lcd.print("Game Start");
  lcd.setCursor(3,1);
  lcd.print("Game Start");
}

void game_score() {
  lcd.setCursor(0,0);
  lcd.print("Score:");
  lcd.setCursor(6,0);
  lcd.print(score);
}

void arr_value(int arr[8][5]) {
   for(int i=0;i<8;i++)
   {
   delay(1);
   digitalWrite(y[i],HIGH); // Y OFF
   for(int j=0;j<5;j++)
   {
     if(arr[i][j] == 0)
     digitalWrite(x[j],LOW);
     else
     digitalWrite(x[j],HIGH);
   }
   delay(1);
   digitalWrite(y[i],LOW); // Y ON
   } 
}// arr_value exit
void y_basic_setup(int i) {
 for(int a=0;a<8;a++)
 {
  if(a==i)
  digitalWrite(y[a],HIGH);
  else
  digitalWrite(y[a],LOW);
  delay(10);
 }
}

void sub_main()
{
  y_clear();  // y clear
  for(int a=0;a<8;a++)
  { 
    x_clear(); // x_clear
    y_basic_setup(a);
    if(direct == 0)
    {
     left_print();
     direct = 1;
    }
   else if(direct == 1) 
   {
     right_print();
     direct = 0;
   }
  } //for exit
} // main loop exit

void x_clear() {
for(int i=0;i<5;i++)
{
  digitalWrite(x[i],HIGH);
}
}

void y_clear(){
for(int i=0;i<8;i++)
{
  digitalWrite(y[i],LOW);
}
}

void left_print() {
for(int i=0;i<5;i++)
{
  for(int j=0;j<5;j++)
  {
    if(i==j)
    digitalWrite(x[j],LOW);
    else
    digitalWrite(x[j],HIGH); 
   }
  delay(50);
}
}

void right_print() {
for(int i=4;i>=0;i--)
{
  for(int j=4;j>=0;j--)
  {
    if(i==j)
    digitalWrite(x[j],LOW);
    else
    digitalWrite(x[j],HIGH); 
   }
    delay(50);
}
}

