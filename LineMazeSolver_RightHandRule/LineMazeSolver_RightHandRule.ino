char directions[30];
#include<LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
int rm1=10;
int rm2=11;
int lm1=8;
int lm2=9;
int l,c1,c2,c3,r;
int i;
int tdelay=565;
int fdelay=60;
int udelay=1400;

void Stop()
{
  digitalWrite(lm1,0);
  digitalWrite(lm2,0);
  digitalWrite(rm1,0);
  digitalWrite(rm2,0);
}

void forward()
{
  digitalWrite(lm1,1);
  digitalWrite(lm2,0);
  digitalWrite(rm1,1);
  digitalWrite(rm2,0);
} 

void smallright()
{
  digitalWrite(lm1,1);
  digitalWrite(lm2,0);
  digitalWrite(rm1,0);
  digitalWrite(rm2,0);
  }

  void smallleft()
  {
  digitalWrite(lm1,0);
  digitalWrite(lm2,0);
  digitalWrite(rm1,1);
  digitalWrite(rm2,0);
  }

  void right()
{
  digitalWrite(lm1,1);
  digitalWrite(lm2,0);
  digitalWrite(rm1,0);
  digitalWrite(rm2,1);
}

void left()
{
  digitalWrite(lm1,0);
  digitalWrite(lm2,1);
  digitalWrite(rm1,1);
  digitalWrite(rm2,0);
}

int eosens()
{
  readsens();
  if(((c1+c2+c3)==1) || ((c1+c2+c3)==2))
  return 1;
  else
  return 0;
}

void readsens()
{
  l=digitalRead(2);
  c1=digitalRead(3);
  c2=digitalRead(4);
  c3=digitalRead(5);
  r=digitalRead(6);
}

void inch()
{
  lcd.print("Inch Function");
  Stop();
  delay(100);
  forward();
  delay(300);
  Stop();
  delay(100);
  readsens();
  lcd.clear();
}

void align()
{
  Stop();
  delay(100);
  forward();
  delay(70);
  Stop();
  delay(100);
  lcd.clear();
  readsens();
}

void printing(char prtdirection[])
{
  lcd.clear();
  for(i=0;prtdirection[i]!='E';i++)
  {
    lcd.print(prtdirection[i]);
  }
  delay(3000);
}

void setup()
{
  lcd.begin(16,2);
  lcd.print("MSR with LHR");
  delay(500);
  lcd.clear();
  pinMode(lm1,OUTPUT);
  pinMode(lm2,OUTPUT);
  pinMode(rm1,OUTPUT);
  pinMode(rm2,OUTPUT);
  pinMode(2,INPUT);
  pinMode(3,INPUT);  
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,INPUT);
}

void loop()
{
  lcd.clear();
  readsens();
  lcd.clear();

  if((l==1)&&(c1==1)&&(c2==0)&&(c3==1)&&(r==1))                                                                 // FORWARD
  {
    lcd.print("Forward");
    forward();
  }
  else if(((l==1)&&(c1==0)&&(c2==1)&&(c3==1)&&(r==1))||((l==1)&&(c1==0)&&(c2==0)&&(c3==1)&&(r==1))||((l==0)&&(c1==0)&&(c2==1)&&(c3==1)&&(r==1))||((l==0)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==1)))
  {
    lcd.print("Left");
    smallleft();                    //small left
  }

  //Right
    else if(((l==1)&&(c1==1)&&(c2==1)&&(c3==0)&&(r==1))||((l==1)&&(c1==1)&&(c2==0)&&(c3==0)&&(r=1))||((l==1)&&(c1==1)&&(c2==1)&&(c3==0)&&(r==0))||((l==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==0)))
  {
    lcd.print("Right");
    smallright();                   //small right
  }

  else if((l==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==1))                                                           // U-TURN
  {
    
    lcd.print(" U turn");
    right();
    delay(udelay);
    directions[i]='U';
    i++;
  }

  else if(((l==0)&&(c1==0)) || ((c3==0)&&(r==0)))
  {
    align();
    

                                            // Right Only   and   Straight & Right
    
    
    if(((l==1)&&(c1==1)&&(c2==0)&&(c3==0)&&(r==0)) || ((l==1)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==0)))        // RIGHT-ONLY
    {
      lcd.print("RT/Strt n rt?");
      inch();
      if((l==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==1))                                                       // ALL 5 WHITE
      {
        lcd.print("right");
        right();
        delay(tdelay);
      }
      else if((l==1)&&(r==1)&&(eosens()))                                                                 // STRAIGHT LINE
      {
        lcd.print("Right");
        directions[i]='R';
        i++;
        right();
        delay(tdelay);
      }
    }


                                              //Left   And   Straight & Left
                                      

    else if(((l==0)&&(c1==0)&&(c2==0)&&(c3==1)&&(r==1)) || ((l==0)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==1)))    // LEFT-ONLY
    {
      lcd.print("lft/srt n lft?");
      inch();
      if((l==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==1))                                                        // ALL 5 WHITE
      {
        lcd.print("Left");
        left();
        delay(tdelay);
      }
    

      else if((l==1)&&(r==1)&&(eosens()))                                                                  // STRAIGHT LINE
      {
        lcd.print("straight");
        directions[i]='S';
        i++;
        forward();
        delay(fdelay);
      }
    }


                                  //  4 WAY INTERSECTION   /   T INTERSECTION   /   END OF MAZE
                                  

    else if((l==0)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==0))                                                   // 4 WAY INTERSECTION                                                    
    {
      lcd.print("T/END/4");                                                                              
      inch(); 
      if((l==1)&&(r==1)&&(eosens()))                                                                     //STRAIGHT LINE
      {
        lcd.print("4 Way");
        directions[i]='R';
        i++;
        right();
        delay(tdelay);
      }
    
      else if((l==1)&&(c1==1)&&(c2==1)&&(c3==1)&&(r==1))                                                // ALL 5 WHITE
      {
        lcd.print("T-inter");                                                                           // T INTERSECTION
        directions[i]='R';
        i++;
        right();
        delay(tdelay);
      }
      
      else if((l==0)&&(c1==0)&&(c2==0)&&(c3==0)&&(r==0))                                              // ALL 5 BLACK
        {
          lcd.print("End of maze");                                                                     // END OF MAZE
          directions[i]='E';
          printing(directions);
          while(1)
          {
            Stop();
          }
          }
        }
      }
    }
   
