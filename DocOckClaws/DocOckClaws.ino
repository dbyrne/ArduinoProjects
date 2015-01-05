#include <Servo.h> 
 
Servo servo1;
Servo servo2;
 
int pos = 0;
 
void setup() 
{ 
  servo1.attach(9);
  servo2.attach(10);
} 
 
 
void loop() 
{ 
  int delayTime = random(3,40);
  for(pos = 20; pos < 165; pos += 1)  
  {                                   
    servo1.write(pos);   
    servo2.write(pos);       
    delay(delayTime);             
  } 
  delayTime = random(4000);
  delay(delayTime);
  delayTime = random(3,40);
  for(pos = 165; pos>=20; pos-=1)  
  {                                
    servo1.write(pos);
    servo2.write(pos);       
    delay(delayTime);            
  }
  delayTime = random(4000);
  delay(delayTime); 
}
