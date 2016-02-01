#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

byte TX = 22;
byte RX = 23;
byte piezo = 25;

LiquidCrystal lcd(16,17,18,19,20,21); //lcd
SoftwareSerial mySerial(TX,RX); // bluetooth

int x[] = {10,11,12,13,14}; // x[5]
int y[] = {2,3,4,5,6,7,8,9}; // y[8]
int enemy_y;
int no = 0;
int yes = 1;
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
int time, timecount=1;
void loop() {  
  
  time = millis()/1000;
  /* Enemy */
   delay(10);
   enemy(time);
   ch_output();
  /* Character */
  if(Serial.available()) { // if(input)
  ch_output();
  ch_control();
  }  
  if(ch_move == eny_move) {
    if(enemy_y==0) {
      tone(piezo,850,2000);
      lcd_output(yes);
    } // second if
  } // first if
} // Function

void enemy(int time) {
  enemy_x();
  y_clear();
  digitalWrite(y[enemy_y],HIGH);
  delay(15);
  if(time == timecount) {
  enemy_y--; 
  timecount++;
  } // if
  
  if(enemy_y == -1) {
  eny_ySetup();
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

void ch_control() {
  int ch_LR = (char)Serial.read();
  delay(10);
  //Left
  if(ch_LR == 49) {
  Serial.println("Left");
  if(ch_move>0) {
  ch_move--;
  count++;
  lcd_output(no);
  } // second if
  } // first if
  
  //Right
  if(ch_LR == 50) {
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
  lcd.setCursor(3,0);
  lcd.print("Your live!"); 
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
