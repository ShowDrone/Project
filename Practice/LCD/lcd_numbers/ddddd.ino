#include <LiquidCrystal.h>
LiquidCrystal lcd (7,6,5,4,3,13);

void setup(){
lcd.begin(16,2);
}

int number =0;
void loop() {
  for (int j=0;j<2;j++)
  {
    for (int i=0;i<16;i++)
    {
     lcd.setCursor(i,j); 
     if(number >9)
     {
       i++;
     }
      if(number >= 100)
     {
       number = 0;
       break;
     }
     lcd.print(number++);
     delay(100);  
  }
  }
  lcd.clear();
}
