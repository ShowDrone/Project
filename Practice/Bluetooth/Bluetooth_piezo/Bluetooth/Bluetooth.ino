


#define do1  262
#define re1  294
#define me1  330
#define pa1  349
#define sol1 392
#define ra1  440
#define ci1  494
#define do2  523

int music[] = { me1,re1,do1,re1,me1,me1,me1,0,re1,re1,re1,
me1,sol1,sol1,0,me1,re1,do1,re1,me1,me1,me1,0,re1,re1,me1,re1,do1,me1,sol1,do2};
int distance = 31;
int umop[] = {
2.5,8,4,4,4,4,8,
2,
4,4,2,4,4,8,
2,
2.5,8,4,4,4,4,8,
2,
4,4,2,8,4,4,4,4};
void setup()
{
  Serial.begin(9600);
  pinMode(11,OUTPUT);
}
 
void loop()
{
  char test = Serial.read();
  if(test == 48)
  {
  for(int i=0; i<distance; i++)
  {
    tone(10,music[i],1000/umop[i]);
    delay((1000/umop[i])*1.3);
    Serial.println(music[i]);
  }
  delay(5000);
  }
}


