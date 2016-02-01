
void setup() {
for(int LED=2;LED<29;LED++) // PIN_LED
{
  pinMode(LED,OUTPUT); // LOW = ON, HIGH = OFF
}
} // setup exit

void loop() {
} // loop exit

void Led_clear(int Area) {
  switch(Area) {
    case 0: // All
    Led_clear(1);
    Led_clear(2);
    Led_clear(3);
    break;
    case 1: // Bottom
    
    break;
    case 2: // Middle
    
    break;
    case 3: // Top 
    
    break;
    } // Switch exit
} // Function exit
