#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

byte blueTX = 2;
byte blueRX = 3;
byte piezo = 25;
byte sw1 = 26;
byte sw2 = 27;

LiquidCrystal lcd(16,17,18,19,20,21); //lcd
SoftwareSerial mySerial(28,29); // bluetooth

int x[] = {10,11,12,13,14}; // x[5]
int y[] = {2,3,4,5,6,7,8,9}; // y[8]
int enemy_y;
int no = 0;
int yes = 1;
int mode = 0;
void setup() {
  
  //Dot setup
for(int i=0;i<5;i++) {
  pinMode(x[i],OUTPUT);
}
for(int i=0;i<8;i++) {
  pinMode(y[i],OUTPUT);
}

  //piezo setup
  pinMode(piezo,OUTPUT);

  //switch setup
  pinMode(sw1,INPUT_PULLUP);
  pinMode(sw2,INPUT_PULLUP);
  
lcd.begin(16,2);
mySerial.begin(9600);
Serial.begin(9600); 
      while(!Serial) {
      delay(50);
      }
      
delay(50);
Serial.write("Hello LeeSH");
  
  // Only One
  ch_output();
  lcd_output(no);
  eny_ySetup();

} // setup

int ch_move = 2;
int eny_move = random(4);
int count = 0;
boolean terms = true;
int time,timecount=0;
int enemycount=0;
void loop() {  
  
  int sw_left = digitalRead(sw1);
  int sw_right = digitalRead(sw2);

  time = millis()/100; // speed

  Serial.println(time);
  /* Enemy */
   delay(50);
   enemy(time);
   ch_output();
   
  /* Character */
  if(Serial.available() || sw_left == 0 || sw_right == 0) { // if(input)
  ch_output();
  ch_control(sw_left,sw_right);
  }  
  if(ch_move == eny_move) {
    if(enemy_y==0) {
      tone(piezo,800,2000);
      lcd_output(yes);
    } // second if
  } // first if
} // Function

void enemy(int time) {
  enemy_x();
  y_clear();
  digitalWrite(y[enemy_y],HIGH);
  delay(10);
  if(time == timecount) {
  enemy_y--; 
  timecount++;
  } // if
  
  if(enemy_y == -1) {
  eny_ySetup();
  enemycount++;
  }
} // function

void eny_ySetup() {
  enemy_y = 7;
  eny_move = random(4);
}

void enemy_x() {
  for(int i=eny_move;i<5;i++)
  {
    for(int j=0;j<5;j++)
    {
      if(i==j)
      digitalWrite(x[eny_move],LOW);
      else
      digitalWrite(x[j],HIGH);
    } // first for
  } // second for
} // function


void ch_control(int sw_left,int sw_right) {
  int ch_LR = Serial.read();
  Serial.println(ch_LR);
  //Left
  if(ch_LR == 49 || sw_left == 0) {
  Serial.println("Left");
  if(ch_move>0) {
  ch_move--;
  count++;
  lcd_output(no);
  } // second if
  } // first if
  
  //Right
  if(ch_LR == 50 || sw_right == 0) {
  Serial.println("Right");
  if(ch_move<4) {
  ch_move++;
  count++;
  lcd_output(no);
  } // second if
  } // first if
} // function

void ch_output() {
  y_clear();
  digitalWrite(y[0],HIGH);
  for(int i=ch_move;i<5;i++)
  {
    for(int j=0;j<5;j++)
    {
      if(i==j)
      digitalWrite(x[ch_move],LOW);
      else if(i!=j)
      digitalWrite(x[j],HIGH);
    } // Second for
  } // first for
} // function

void lcd_output(int i) {
  if(i==0) {
  lcd.setCursor(1,0);
  lcd.print("avoid count:"); 
  lcd.setCursor(14,0);
  lcd.print(enemycount); 
  } //it
  
  if(i==1) {
  lcd.clear();
  
  lcd.setCursor(3,0);
  lcd.print("GAME OVER!");
  lcd.setCursor(3,1);
  lcd.print("Oh My God!");
  
  x_clear();
  y_clear();
  
  while(1) {
  }
  
  } // if
  
  lcd.setCursor(4,1);
  lcd.print("move:");
  lcd.setCursor(9,1);
  lcd.print(count);
}


void x_clear() {
for(int i=0;i<5;i++) {
  digitalWrite(x[i],HIGH);
}
} // Function

void y_clear() {
for(int i=0;i<8;i++) {
  digitalWrite(y[i],LOW);
}
} // Function
