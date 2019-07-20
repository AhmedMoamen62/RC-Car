#define motor_F1 5
#define motor_B1 4
#define motor_F2 10
#define motor_B2 11
#define s1 3
#define s2 9
#define trig   13
#define echo   12
#define RS 7
#define LS 8
#define MS 2
int flag = 0;
char car_direction ;
int flag_l=0;
int flag_u=0;
float duration ,cm ,dis_line;
void forward_line()
{
  analogWrite(s1,80);
  analogWrite(s2,80);
  digitalWrite(motor_F1,0);
  digitalWrite(motor_B1,1);
  digitalWrite(motor_F2,1);
  digitalWrite(motor_B2,0);
  }
void right_line()
{
  analogWrite(s1,0);
  analogWrite(s2,100);
  digitalWrite(motor_F1,0);
  digitalWrite(motor_B1,0);
  digitalWrite(motor_F2,1);
  digitalWrite(motor_B2,0);
}
void left_line()
{
  analogWrite(s1,100);
  analogWrite(s2,0);
  digitalWrite(motor_F1,0);
  digitalWrite(motor_B1,1);
  digitalWrite(motor_F2,0);
  digitalWrite(motor_B2,0);
}
void handle_forward ()
{
  digitalWrite(motor_F1,0);
  digitalWrite(motor_B1,1);
  digitalWrite(motor_F2,1);
  digitalWrite(motor_B2,0);
}
void handle_backward ()
{
  digitalWrite(motor_F1,1);
  digitalWrite(motor_B1,0);
  digitalWrite(motor_F2,0);
  digitalWrite(motor_B2,1);
}
void handle_left ()
{
  digitalWrite(motor_F1,0);
  digitalWrite(motor_B1,1);
  digitalWrite(motor_F2,0);
  digitalWrite(motor_B2,0);
}
void handle_right ()
{
  digitalWrite(motor_F1,0);
  digitalWrite(motor_B1,0);
  digitalWrite(motor_F2,1);
  digitalWrite(motor_B2,0);
}
void handle_stop ()
{
  analogWrite(s1,0);
  analogWrite(s2,0);
  digitalWrite(motor_F1,0);
  digitalWrite(motor_B1,0);
  digitalWrite(motor_F2,0);
  digitalWrite(motor_B2,0);
}
float calcDistance()
{
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  duration = pulseIn(echo,HIGH,17000);
  cm = (duration/2)*0.0343 ;
  if(duration == 0)
  {
    cm =300;
   }
    return cm ;
}
void ultrasonic ()
{
while(flag_u)
{
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  duration = pulseIn(echo,HIGH);
  cm = (duration/2)*0.0343 ;
  if(Serial.available())
  {
    car_direction = Serial.read();
  if (car_direction !='W' && car_direction !='S')
  {
    flag_u=0;
    break ; 
  }
  }
  if (cm<35)
  {
//    handle_stop();
//    delay(100); 
  if(Serial.available())
  {
    car_direction = Serial.read();
  if (car_direction !='W' && car_direction !='S')
  {
    flag_u=0;
    break ; 
  }
  }
//    analogWrite(s1,200);
//    analogWrite(s2,200);
//    handle_backward();
//    delay(500); 
  analogWrite(s1,150);
  analogWrite(s2,150);
  digitalWrite(motor_F1,0);
  digitalWrite(motor_B1,1);
  digitalWrite(motor_F2,0);
  digitalWrite(motor_B2,1);
  delay(750);
if(Serial.available())
  {
    car_direction = Serial.read();
  if (car_direction !='W' && car_direction !='S')
  {
    flag_u=0;
    break ; 
  }
  } 
  }
  else 
  {
  analogWrite(s1,200);
  analogWrite(s2,200);
  handle_forward();
  if(Serial.available())
  {
    car_direction = Serial.read();
  if (car_direction !='W' && car_direction !='S')
  {
    flag_u=0;
    break ; 
  }
  } 
  }      
}
}
void line_followerR ()
{
while(flag_l)
{
float D = calcDistance();
if(D < 15)
{
  handle_stop();
  delay(250);
  analogWrite(s1,120);
  analogWrite(s2,120);
  digitalWrite(motor_F1,1);
  digitalWrite(motor_B1,0);
  digitalWrite(motor_F2,1);
  digitalWrite(motor_B2,0);
  delay(200);
  forward_line();
  delay(200);
D = calcDistance();
while(D > 30)
{
if(digitalRead(LS) == 1 && digitalRead(RS) == 1 && digitalRead(MS) == 1)
{
analogWrite(s1,90);
analogWrite(s2,90);
handle_forward();
}
else if(digitalRead(RS) == 0)
{
  analogWrite(s1,150);
  analogWrite(s2,150);
  digitalWrite(motor_F1,1);
  digitalWrite(motor_B1,0);
  digitalWrite(motor_F2,1);
  digitalWrite(motor_B2,0);
  delay(450);
  flag = 1;
  break;
}
D = calcDistance();
}
}
  else 
  {  
if( digitalRead(LS) == 1 && digitalRead(RS) == 1 && digitalRead(MS) == 0 )
  {
    flag = 3;
   forward_line();
   if(Serial.available())
  {
    car_direction = Serial.read();
  if (car_direction !='U' && car_direction !='S')
  {
    flag_u=0;
    break ; 
  }
  } 
  }
   else if( digitalRead(LS) == 1 && digitalRead(RS) == 1 && digitalRead(MS) == 1 )
  {
    if( flag == 1)
    {
  analogWrite(s1,100);
  analogWrite(s2,100);
  digitalWrite(motor_F1,1);
  digitalWrite(motor_B1,0);
  digitalWrite(motor_F2,1);
  digitalWrite(motor_B2,0);
  if(Serial.available())
  {
    car_direction = Serial.read();
  if (car_direction !='U' && car_direction !='S')
  {
    flag_u=0;
    break ; 
  }
  } 
    }
    else if(flag == 2)
    {
  analogWrite(s1,100);
  analogWrite(s2,100);
  digitalWrite(motor_F1,0);
  digitalWrite(motor_B1,1);
  digitalWrite(motor_F2,0);
  digitalWrite(motor_B2,1);
  if(Serial.available())
  {
    car_direction = Serial.read();
  if (car_direction !='U' && car_direction !='S')
  {
    flag_u=0;
    break ; 
  }
  } 
    }
    else if (flag == 3)
    {
      forward_line();
      if(Serial.available())
  {
    car_direction = Serial.read();
  if (car_direction !='U' && car_direction !='S')
  {
    flag_u=0;
    break ; 
  }
  } 
    }
  }
  else if( digitalRead(RS) == 0 && digitalRead(MS) == 0 )
  {
  analogWrite(s1,80);
  analogWrite(s2,80);
  digitalWrite(motor_F1,0);
  digitalWrite(motor_B1,1);
  digitalWrite(motor_F2,1);
  digitalWrite(motor_B2,0);
  if(Serial.available())
  {
    car_direction = Serial.read();
  if (car_direction !='U' && car_direction !='S')
  {
    flag_u=0;
    break ; 
  }
  } 
  }
  else if( digitalRead(LS) == 0 && digitalRead(MS) == 0 )
  {
  analogWrite(s1,80);
  analogWrite(s2,80);
  digitalWrite(motor_F1,0);
  digitalWrite(motor_B1,1);
  digitalWrite(motor_F2,1);
  digitalWrite(motor_B2,0);
  if(Serial.available())
  {
    car_direction = Serial.read();
  if (car_direction !='U' && car_direction !='S')
  {
    flag_u=0;
    break ; 
  }
  } 
  }
  else if( digitalRead(LS) == 0 && digitalRead(RS) == 0 && digitalRead(MS) == 0 )
  {
    forward_line();
    delay(50);
    if(Serial.available())
  {
    car_direction = Serial.read();
  if (car_direction !='U' && car_direction !='S')
  {
    flag_u=0;
    break ; 
  }
  } 
  }
 else if( digitalRead(RS) == 0 && digitalRead(LS) == 1 )
  {
    flag = 1;
    right_line();
    if(Serial.available())
  {
    car_direction = Serial.read();
  if (car_direction !='U' && car_direction !='S')
  {
    flag_u=0;
    break ; 
  }
  } 
  }
    
 else if( digitalRead(LS) == 0 && digitalRead(RS) == 1 )
  {
    flag = 2;
    left_line();
    if(Serial.available())
  {
    car_direction = Serial.read();
  if (car_direction !='U' && car_direction !='S')
  {
    flag_u=0;
    break ; 
  }
  } 
  }
  }
}
}


void line_followerL ()
{
while(flag_l)
{
float D = calcDistance();
if(D < 15)
{
  handle_stop();
  delay(250);
  analogWrite(s1,120);
  analogWrite(s2,120);
  digitalWrite(motor_F1,0);
  digitalWrite(motor_B1,1);
  digitalWrite(motor_F2,0);
  digitalWrite(motor_B2,1);
  delay(200);
  forward_line();
  delay(200);
D = calcDistance();
while(D > 30)
{
if(digitalRead(LS) == 1 && digitalRead(RS) == 1 && digitalRead(MS) == 1)
{
analogWrite(s1,90);
analogWrite(s2,90);
handle_forward();
}
else if(digitalRead(RS) == 0)
{
  analogWrite(s1,150);
  analogWrite(s2,150);
  digitalWrite(motor_F1,0);
  digitalWrite(motor_B1,1);
  digitalWrite(motor_F2,0);
  digitalWrite(motor_B2,1);
  delay(450);
  flag = 2;
  break;
}
D = calcDistance();
}
}
  else 
  {  
if( digitalRead(LS) == 1 && digitalRead(RS) == 1 && digitalRead(MS) == 0 )
  {
    flag = 3;
   forward_line();
   if(Serial.available())
  {
    car_direction = Serial.read();
  if (car_direction !='U' && car_direction !='S')
  {
    flag_u=0;
    break ; 
  }
  } 
  }
   else if( digitalRead(LS) == 1 && digitalRead(RS) == 1 && digitalRead(MS) == 1 )
  {
    if( flag == 1)
    {
  analogWrite(s1,100);
  analogWrite(s2,100);
  digitalWrite(motor_F1,1);
  digitalWrite(motor_B1,0);
  digitalWrite(motor_F2,1);
  digitalWrite(motor_B2,0);
  if(Serial.available())
  {
    car_direction = Serial.read();
  if (car_direction !='U' && car_direction !='S')
  {
    flag_u=0;
    break ; 
  }
  } 
    }
    else if(flag == 2)
    {
  analogWrite(s1,100);
  analogWrite(s2,100);
  digitalWrite(motor_F1,0);
  digitalWrite(motor_B1,1);
  digitalWrite(motor_F2,0);
  digitalWrite(motor_B2,1);
  if(Serial.available())
  {
    car_direction = Serial.read();
  if (car_direction !='U' && car_direction !='S')
  {
    flag_u=0;
    break ; 
  }
  } 
    }
    else if (flag == 3)
    {
      forward_line();
      if(Serial.available())
  {
    car_direction = Serial.read();
  if (car_direction !='U' && car_direction !='S')
  {
    flag_u=0;
    break ; 
  }
  } 
    }
  }
  else if( digitalRead(RS) == 0 && digitalRead(MS) == 0 )
  {
  analogWrite(s1,80);
  analogWrite(s2,80);
  digitalWrite(motor_F1,0);
  digitalWrite(motor_B1,1);
  digitalWrite(motor_F2,1);
  digitalWrite(motor_B2,0);
  if(Serial.available())
  {
    car_direction = Serial.read();
  if (car_direction !='U' && car_direction !='S')
  {
    flag_u=0;
    break ; 
  }
  } 
  }
  else if( digitalRead(LS) == 0 && digitalRead(MS) == 0 )
  {
  analogWrite(s1,80);
  analogWrite(s2,80);
  digitalWrite(motor_F1,0);
  digitalWrite(motor_B1,1);
  digitalWrite(motor_F2,1);
  digitalWrite(motor_B2,0);
  if(Serial.available())
  {
    car_direction = Serial.read();
  if (car_direction !='U' && car_direction !='S')
  {
    flag_u=0;
    break ; 
  }
  } 
  }
  else if( digitalRead(LS) == 0 && digitalRead(RS) == 0 && digitalRead(MS) == 0 )
  {
    forward_line();
    delay(50);
    if(Serial.available())
  {
    car_direction = Serial.read();
  if (car_direction !='U' && car_direction !='S')
  {
    flag_u=0;
    break ; 
  }
  } 
  }
 else if( digitalRead(RS) == 0 && digitalRead(LS) == 1 )
  {
    flag = 1;
    right_line();
    if(Serial.available())
  {
    car_direction = Serial.read();
  if (car_direction !='U' && car_direction !='S')
  {
    flag_u=0;
    break ; 
  }
  } 
  }
    
 else if( digitalRead(LS) == 0 && digitalRead(RS) == 1 )
  {
    flag = 2;
    left_line();
    if(Serial.available())
  {
    car_direction = Serial.read();
  if (car_direction !='U' && car_direction !='S')
  {
    flag_u=0;
    break ; 
  }
  } 
  }
  }
}
}

  
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(motor_F1,OUTPUT);
pinMode(motor_B1,OUTPUT);
pinMode(motor_F2,OUTPUT);
pinMode(motor_B2,OUTPUT);
pinMode(s1,OUTPUT);
pinMode(s2,OUTPUT);
pinMode(trig,OUTPUT);
pinMode(echo,INPUT);
pinMode(LS,INPUT);
pinMode(RS,INPUT); 
pinMode(MS,INPUT); 
pinMode(A0,INPUT);
pinMode(A1,INPUT);
pinMode(A2,INPUT);
pinMode(A3,INPUT);
}

void loop() {
  char l = analogRead(A0);
  char b = analogRead(A1);
  char r = analogRead(A2);
  char f = analogRead(A4);
  if(f==1 && b==0 && r==0 && l==0)
  {
      handle_forward();
  }
  else if(f==0 && b==1 && r==0 && l==0)
  {
      handle_backward();
  }
  else if(f==0 && b==0 && r==1 && l==0)
  {
      handle_right();
 }
  else if(f==0 && b==0 && r==0 && l==1)
 {
      handle_left();
  }
  else if(f==1 && b==1 && r==0 && l==0)
  {
      flag_u=1;
      ultrasonic();
  }
  else if(f==0 && b==0 && r==1 && l==1)
  {
      flag_l=1;
      line_followerR ();
  }
  else 
  {
      handle_stop();
  }
  if(Serial.available())
  {
    car_direction = Serial.read();  
    switch (car_direction)
    {
    case 'F' :  analogWrite(s1,255);
                analogWrite(s2,255);
                handle_forward();
         break ; 
    case 'B' :   analogWrite(s1,255);
                 analogWrite(s2,255);
                 handle_backward();
         break ; 
    case 'R' :  analogWrite(s1,0);
                analogWrite(s2,255);
                handle_right();
         break ; 
    case 'L' :   analogWrite(s1,255);
                 analogWrite(s2,0);
                 handle_left();
         break ;
    case 'U' : flag_l=1;
               line_followerR();
          break;
   case 'V' : flag_l=1;
               line_followerL();
          break;
  
    case 'W' : flag_u=1;
               ultrasonic ();     
         break;         
    default  : handle_stop();
        break;
     }
   }
}
