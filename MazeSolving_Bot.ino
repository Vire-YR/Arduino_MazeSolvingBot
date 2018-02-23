const int IR1=4,IR2=3,IR3=5;
const int LM1=11,LM2=10,RM1=6,RM2=9;
String s1="",s2="";
String previous="",present="",next="",event="";
int turn=0,r=0,l=0;
int change=0,i=0,y=0;
int t=0,event_time=0;
int previous_time=0,present_time=0,next_time=0;
long randomNum;

void right()
{
  s1="right";
    analogWrite(LM1,170);
    analogWrite(LM2,0);
    analogWrite(RM1,0);
    analogWrite(RM2,170);
}

void left()
{
  s1="left";
    analogWrite(LM1,0);
    analogWrite(LM2,170);
    analogWrite(RM1,170);
    analogWrite(RM2,0);
}

void straight()
{
  s1="straight";
   analogWrite(LM1,230);
   analogWrite(LM2,0);
   analogWrite(RM1,230);
   analogWrite(RM2,0);
}

void events_record(String s1,String s2)
{
  event=s1;

   if(s2==s1)
    event_time=millis()-t; 
    
  if(s2!=s1)
  {
     Serial.println();
     Serial.println("moving ");
     Serial.println(s1);
     if(event_time>400)
     {
       t=millis();
         next=event;
         next_time=event_time;
         Serial.println();
         Serial.print("Next Event found : ");
         Serial.println(next);
         Serial.print("Next time found : ");
         Serial.print(next_time);
         Serial.println(" which is greater than 400");
       }       
      }
      
   if(present!="")
   {
    if(previous==present)
       {
        previous_time+=present_time;
        y--;
        Serial.println();
        Serial.print("Time of previous event changed to: ");
        Serial.println(previous_time);
       }
    if(next==present)
       {
        present_time+=next_time;
        y--;
        Serial.println();
        Serial.print("Time of present event changed to: ");
        Serial.println(present_time);
       }
   }   
    
  }


  if(next==previous && next!="straight" && next!=present && present_time>700)
  {
      if(present=="right")
            r++;
      if(present=="left")
            l++;      
      turn++;
      Serial.println();
      Serial.print(present);
      Serial.println(" turn detected as present time>700");
      Serial.print("turn=");
      Serial.println(turn);
      Serial.print("r=");
      Serial.println(r);
      Serial.print("l=");
      Serial.println(l);
  }

  if(turn==5)
    {
      if(r==turn||l==turn)
        change++;
      turn=0;
      r=0;
      l=0;
      Serial.println("Changing the default move as turn=6 ");
      Serial.print("change=");
      Serial.println(change);
      Serial.println("turn=0,r=0,l=0");
    }
  
  if(event_time%1000==0)
     {
      Serial.print("still moving ");
      Serial.println(s1);
     }   

  previous=present;
  present=next;
  next="";
  previous_time=present_time;
  present_time=next_time;
  next_time=0;
  Serial.print("Previous Event changed to: ");
  Serial.println(previous);
  Serial.print("Previous Time changed to: ");
  Serial.println(previous_time);
  Serial.print("Present Event changed to: ");
  Serial.println(present);
  Serial.print("Present time changed to: ");
  Serial.println(present_time);  
     
}
 
void setup() 
{
  pinMode(IR1,INPUT);
  pinMode(IR2,INPUT);
  pinMode(IR3,INPUT);
  pinMode(LM1,OUTPUT);
  pinMode(LM2,OUTPUT);
  pinMode(RM1,OUTPUT);
  pinMode(RM2,OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(A0));
}

void loop() {
  s2=s1;
  int IR1_read=digitalRead(IR1);
  int IR2_read =digitalRead(IR2);
  int IR3_read =digitalRead(IR3);
  if(IR1_read==LOW && IR2_read==LOW && IR3_read==HIGH)
         straight();  

  else if(IR1_read==HIGH && IR2_read==LOW){
    left();    
  }
  
  else if((IR1_read==LOW && IR2_read==HIGH)||(IR1_read==LOW&&IR3_read==LOW&&IR2_read==LOW))
  {
    right();
  }
  
  else if(IR1_read==HIGH&&IR3_read==HIGH&&IR2_read==HIGH)
  {
    Serial.println("NODE ENCOUNTERED");
    Serial.print("change = ");
    Serial.println(change);
    if(change==0)
           right();

    if(change==1)
            left();
   
    if(change==2)
     {
      if(i%2==0)
            right();
      else
             left();  
     }
     
    if(change==3)
     {
      if(i==0||i==1)
         right();
      else
         left();
     }
     
    if(change==4)
    {
      randomNum=random(0,2);
      if(randomNum==0)
         right();
      if(randomNum==1)
         left();
    }

    i++;
    if(i>4)
       i=0;
  }     
  
  events_record(s1,s2);
  
 }

