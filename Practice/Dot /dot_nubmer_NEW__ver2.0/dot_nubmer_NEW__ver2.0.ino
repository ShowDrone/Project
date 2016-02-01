int x[] = {10,11,13,14,15}; // ON : LOW 
int y[] = {2,3,4,5,6,7,8,9}; // ON : HIGH
//
void setup() {
  Serial.begin(9600); // Serial
  for(int i=0;i<8;i++)
  {
    pinMode(y[i],OUTPUT);
  }
  for(int i=0;i<5;i++)
  {
    pinMode(x[i],OUTPUT);
  }  
}
static int x_arr[5];
static int y_arr[8];
static int a = 128;
void loop() {
for(int i=0;i<8;i++)
{
  digitalWrite(y[i],a);
}
digitalWrite(x[0],LOW);
} 
  
