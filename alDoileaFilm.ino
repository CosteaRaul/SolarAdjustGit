#include <Servo.h>
Servo incliner ;
#define servoPin 9 
#define R 5000
int motor_angle = 0;
#define VIN 5
int x=0;
int error ; 

int difference (int a , int b )
{
  int diff; 
  if (a > b)
    diff =  a - b ;
  else 
    diff = b - a ; 
  return diff ; 
}
int Conversion(int valueToConv)
{
  float Voltage = float(valueToConv) * (VIN / float(1023));
  float Resistance = (R * (VIN - Voltage))/Voltage; 
  int Lumen = 500/(Resistance/1000); 
  return Lumen;
}
void setup() {
  incliner.attach(servoPin);
  int i;
  Serial.begin(9600);
  int rezVal_r = 0;
  int rezVal_l = 0;
  for (i=1;i>=100;i++)
  {
    rezVal_r = analogRead(A5);
    rezVal_l = analogRead(A4);
    error = rezVal_r + rezVal_l ;  
  }
  error = error/200;
}


void loop() {
  int ok=0, caz , e , w , motor_value;
  int left , right , diffy ; 
  int rezVal_r = 0 ;
  int rezVal_l = 0 ;
  int k=0;
  int mappedVal_r;
  int mappedVal_l;

  delay(250);
  
  rezVal_r = analogRead(A5);
  rezVal_l = analogRead(A4);
  
  mappedVal_r=map(rezVal_r, 4 , 951 , 0 , 180 );
  mappedVal_l=map(rezVal_l, 0 , 954 , 0 , 180 );
  
  //Serial.println("val rezist right : ");
  //Serial.println(mappedVal_r);
  //Serial.println("val rezist left : ");
  //Serial.println(mappedVal_l);
  left = mappedVal_l;
  right =  mappedVal_r;
  int grater ;
  if (left > right)
    grater = left ; 
  else if (right  > left )
    grater = right ; 
  diffy =  difference(right , left);
  if(right < 17 && left < 25 && ok!=1 )
      {Serial.println("NB BOSS ");ok=1;caz = 1;}
  if( (left-error) > right && ok!=1 )
      {Serial.println("merge in stanga");ok=1;caz = 2;}
  if((right-error) > left && ok!=1)
      {Serial.println("merge in dreapta");ok=1;caz= 3;} 
  
  switch (caz)
  {
    case 1:          //intuneric
        w = analogRead(A4);
        e = analogRead(A5);
        while( w < 60  && e < 60 )
        {
          incliner.write(80);
          w = analogRead(A4);
          e = analogRead(A5);
        }
                
    break;
    case 2:       //stanga 
        w = left;
        e = right;
        while(w > e  && motor_value <= 170)
        {
          e = analogRead(A5);
          w = analogRead(A4);
          
          motor_value = motor_value + 1 ; 
          delay(20);
          incliner.write(motor_value);
        }
        incliner.write(motor_value-1);
    break;
    case 3:             //dreapta
        w = left ;
        e = right ;
        while(e > w && motor_value >= 1 )
        {
          e = analogRead(A5);
          w = analogRead(A4);
          motor_value = motor_value - 1;
          delay(20);
          incliner.write(motor_value);
        }
        incliner.write(motor_value+1);
    break;
  }
        
     
  
  
  
  
}
