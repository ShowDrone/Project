int P1_sw_left = 20; // Left
int P1_sw_right = 21; // Right
int P1_sw_up = 18;
int P1_sw_down = 19;
int x[] = {10,11,13,14,15}; // ON : LOW 
int y[] = {2,3,4,5,6,7,8,9}; // ON : HIGH
//
int P1_ch_move = 2;
int P1_ch_ud = 0;
int P1_ch_coordinate[5] = {0,0,1,0,0}; //character1 L,R coordinate
int P1_ch_updown[8] = {1,0,0,0,0,0,0,0}; // character1 U,D coordinate
//
void setup() {
  Serial.begin(9600); // Serial
  pinMode(P1_sw_left,INPUT_PULLUP); // P1_Left
  pinMode(P1_sw_right,INPUT_PULLUP);// P1_Right
  pinMode(P1_sw_down,INPUT_PULLUP); // P1_down
  pinMode(P1_sw_up,INPUT_PULLUP);// P1_ up
  for(int i=0;i<8;i++)
  {
    pinMode(y[i],OUTPUT);
  }
  for(int i=0;i<6;i++)
  {
    pinMode(x[i],OUTPUT);
  }  
}
void loop() {
 byte P1_sw1 = digitalRead(P1_sw_left);
 byte P1_sw2 = digitalRead(P1_sw_right);
 byte P1_sw3 = digitalRead(P1_sw_up);
 byte P1_sw4 = digitalRead(P1_sw_down);
 delay(95);
 if(P1_sw1 == 0 || P1_sw2 == 0)
 {
 ch1(P1_sw1,P1_sw2);
 }
 else if(P1_sw3 == 0 || P1_sw4 == 0)
 {
 ch2(P1_sw3,P1_sw4);
 }
 CoorPrint(); // Coordinate Print
}
int value = 0;

void ch2(byte sw3, byte sw4)
{
  digitalWrite(x[P1_ch_move],LOW);
  if(sw3 == 0)
 {
   if(P1_ch_ud <= 7)
   {
     P1_ch_ud+=1;
   }
 }
else if(sw4 == 0)
   {
     if(P1_ch_ud >= 0 )
     {
       P1_ch_ud-=1;
     }
   }
 switch(P1_ch_ud)
 {
   case 0:
   digitalWrite(y[P1_ch_ud],HIGH);
   for(int i=1;i<8;i++)
   {
     digitalWrite(y[P1_ch_ud],LOW);
   }
   break;
   case 1:
   digitalWrite(y[P1_ch_ud],HIGH);
   digitalWrite(y[P1_ch_ud-1],LOW);
   for(int i=2;i<8;i++)
   {
     digitalWrite(y[P1_ch_ud],LOW);
   }
   break;
   case 2:
   digitalWrite(y[P1_ch_ud-1],LOW);
   digitalWrite(y[P1_ch_ud-2],LOW);
   digitalWrite(y[P1_ch_ud],HIGH);
    for(int i=2;i<8;i++)
   {
     digitalWrite(y[P1_ch_ud],LOW);
   } 
   break;
   case 3:
   digitalWrite(y[P1_ch_ud],HIGH);
   digitalWrite(y[P1_ch_ud-1],LOW);
   digitalWrite(y[P1_ch_ud-2],LOW);
   digitalWrite(y[P1_ch_ud-3],LOW);
     for(int i=3;i<8;i++)
   {
     digitalWrite(y[P1_ch_ud],LOW);
   } 
   break;
   case 4:
   digitalWrite(y[P1_ch_ud],HIGH);
    for(int i=4;i>0;i--)
   {
     digitalWrite(y[P1_ch_ud-i],LOW);
   } 
   for(int i=4;i<8;i++)
   {
     digitalWrite(y[P1_ch_ud],LOW);
   } 
   break;
   case 5:
   digitalWrite(y[P1_ch_ud],HIGH);
    for(int i=5;i>0;i--)
   {
     digitalWrite(y[P1_ch_ud-i],LOW);
   } 
   for(int i=5;i<8;i++)
   {
     digitalWrite(y[P1_ch_ud],LOW);
   } 
   break;
   case 6:
   digitalWrite(y[P1_ch_ud],HIGH);
    for(int i=6;i>0;i--)
   {
     digitalWrite(y[P1_ch_ud-i],LOW);
   } 
   for(int i=6;i<8;i++)
   {
     digitalWrite(y[P1_ch_ud],LOW);
   } 
   break;
   case 7:
   digitalWrite(y[P1_ch_ud],HIGH);
   for(int i=7;i>0;i--)
   {
     digitalWrite(y[P1_ch_ud-i],LOW);
   } 
   break;
 }
 } 

void ch1(byte sw1, byte sw2) {
 digitalWrite(y[P1_ch_ud],HIGH); // Y ON
 if(sw1==0)
   {
   if(P1_ch_move>0)
   {
   P1_ch_move-=1;
   }
 }
 else if(sw2==0)
 {
   if(P1_ch_move<5)
   {
     P1_ch_move+=1;
   }
 }
 switch(P1_ch_move) {
   case 0: // [0,0]
   digitalWrite(x[P1_ch_move],LOW);
   P1_ch_coordinate[P1_ch_move] = {1};
   for(int i=1;i<5;i++)
   {
     digitalWrite(x[P1_ch_move+i],HIGH);
     P1_ch_coordinate[P1_ch_move+i] = {0};
   }
   break;
   case 1: // [1,0]
   digitalWrite(x[P1_ch_move],LOW);
   P1_ch_coordinate[P1_ch_move] = {1};
   digitalWrite(x[P1_ch_move-1], HIGH);
   P1_ch_coordinate[P1_ch_move-1] = {0};
   for(int i=1;i<4;i++)
   {
     digitalWrite(x[P1_ch_move+i],HIGH);
     P1_ch_coordinate[P1_ch_move+i] = {0};
   }
   break;
   case 2: // [2,0]
   digitalWrite(x[P1_ch_move],LOW);
   P1_ch_coordinate[P1_ch_move] = {1};
   for(int i=1;i<3;i++)
   {
     digitalWrite(x[P1_ch_move-i],HIGH);
     digitalWrite(x[P1_ch_move+i],HIGH);
     P1_ch_coordinate[P1_ch_move-i] = {0};
     P1_ch_coordinate[P1_ch_move+i] = {0};
   }
   break;
   case 3: //[3,0]
   digitalWrite(x[P1_ch_move],LOW);
   P1_ch_coordinate[P1_ch_move] = {1};
   digitalWrite(x[P1_ch_move+1],HIGH);
   P1_ch_coordinate[P1_ch_move+1] = {0};
   for(int i=1;i<4;i++)
   {
     digitalWrite(x[P1_ch_move-i],HIGH);
     P1_ch_coordinate[P1_ch_move-i] = {0};
   }
   break;
   case 4:
   digitalWrite(x[P1_ch_move],LOW);
   P1_ch_coordinate[P1_ch_move] = {1};
   for(int i=1;i<5;i++)
   {
     digitalWrite(x[P1_ch_move-i],HIGH);
     P1_ch_coordinate[P1_ch_move-i] = {0};
   }
   break;
 }
}


void CoorPrint() {
for(int i=0;i<5;i++)
 {
   Serial.print(P1_ch_coordinate[i]);
   delay(1);
   if(i==4)
   {
     Serial.println("");
   }
 }
}
