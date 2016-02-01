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
static int x_arr[] = {0,0,0,0,0};
static int y_arr[] = {1,1,1,1,1,1,1,1};
int valueNUM = 0;
static int i = 0;
static int j = 0;
void loop() {
for(i=0;i<8;i++)
  Serial.println("y_Value Test");
  if(i==0)
  {
  y_arr[0] = 1;
  Serial.println("y_del Test");
  for(i+1;i<8;i++)
  {
    y_arr[i+1] = 0;
  }
  if(i>0)
  {
    for(i-1;i>=0;i--)
    {
      if(!(y_arr[i] == 1))
      y_arr[i-1] = 0;
    }
  }
  }
  else if(i==1)
  {
  y_arr[1] = 1;
  Serial.println("y_del Test");
  for(i+1;i<8;i++)
  {
    y_arr[i+1] = 0;
  }
  if(i>0)
  {
    for(i-1;i>=0;i--)
    {
      if(!(y_arr[i] == 1))
      y_arr[i-1] = 0;
    }
  }
  }
  else if(i==2)
  {
  y_arr[2] = 1;
  Serial.println("y_del Test");
  for(i+1;i<8;i++)
  {
    y_arr[i+1] = 0;
  }
  if(i>0)
  {
    for(i-1;i>=0;i--)
    {
      if(!(y_arr[i] == 1))
      y_arr[i-1] = 0;
    }
  }
  }
  else if(i==3)
  {
  y_arr[3] = 1;
  Serial.println("y_del Test");
  for(i+1;i<8;i++)
  {
    y_arr[i+1] = 0;
  }
  if(i>0)
  {
    for(i-1;i>=0;i--)
    {
      if(!(y_arr[i] == 1))
      y_arr[i-1] = 0;
    }
  }
  }
  else if(i==4)
  {
  y_arr[4] = 1;
  Serial.println("y_del Test");
  for(i+1;i<8;i++)
  {
    y_arr[i+1] = 0;
  }
  if(i>0)
  {
    for(i-1;i>=0;i--)
    {
      if(!(y_arr[i] == 1))
      y_arr[i-1] = 0;
    }
  }
  }
  else if(i==5)
  {
  y_arr[5] = 1;
  Serial.println("y_del Test");
  for(i+1;i<8;i++)
  {
    y_arr[i+1] = 0;
  }
  if(i>0)
  {
    for(i-1;i>=0;i--)
    {
      if(!(y_arr[i] == 1))
      y_arr[i-1] = 0;
    }
  }
  }
  else if(i==6)
  {
  y_arr[6] = 1;
  Serial.println("y_del Test");
  for(i+1;i<8;i++)
  {
    y_arr[i+1] = 0;
  }
  if(i>0)
  {
    for(i-1;i>=0;i--)
    {
      if(!(y_arr[i] == 1))
      y_arr[i-1] = 0;
    }
  }
  }
  else if(i==7)
  {
  y_arr[7] = 1;
  Serial.println("y_del Test");
  for(i+1;i<8;i++)
  {
    y_arr[i+1] = 0;
  }
  if(i>0)
  {
    for(i-1;i>=0;i--)
    {
      if(!(y_arr[i] == 1))
      y_arr[i-1] = 0;
    }
  }
  }
  Serial.println("y value  OO ");
  digitalWrite(y[i],y_arr[i]);
  for(j=0;j<5;j++)
  {
  Serial.println("x_Value Test");
  if(j==0)
  {
  x_arr[0] = 0;
  {
  Serial.println("x_del Test");
  for(j+1;j<5;j++)
  {
    x_arr[j+1] = 1;
  }
  if(j>0)
  {
    for(j-1;j>=0;j--)
    {
      if(!(x_arr[j] == 0))
      x_arr[j-1] = 1;
    }
  }
  }
  }
  else if(j==1)
  {
  x_arr[1] = 0;
  {
  Serial.println("x_del Test");
  for(j+1;j<5;j++)
  {
    x_arr[j+1] = 1;
  }
  if(j>0)
  {
    for(j-1;j>=0;j--)
    {
      if(!(x_arr[j] == 0))
      x_arr[j-1] = 1;
    }
  }
  }
  }
  else if(j==2)
  {
  x_arr[2] = 0;
  for(j+1;j<5;j++)
  {
    x_arr[j+1] = 1;
  }
  if(j>0)
  {
    for(j-1;j>=0;j--)
    {
      if(!(x_arr[j] == 0))
      x_arr[j-1] = 1;
    }
  }
  }
  else if(j==3)
  {
  x_arr[3] = 0;
  for(j+1;j<5;j++)
  {
    x_arr[j+1] = 1;
  }
  if(j>0)
  {
    for(j-1;j>=0;j--)
    {
      if(!(x_arr[j] == 0))
      x_arr[j-1] = 1;
    }
  }
}
  else if(j==4)
  {
  x_arr[4] = 0;
  for(j+1;j<5;j++)
  {
    x_arr[j+1] = 1;
  }
  if(j>0)
  {
    for(j-1;j>=0;j--)
    {
      if(!(x_arr[j] == 0))
      x_arr[j-1] = 1;
    }
  }
}
    Serial.println("x value  OO ");
    digitalWrite(x[j],x_arr[j]);
    delay(100);
  }
}
