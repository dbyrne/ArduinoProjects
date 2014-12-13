#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
 
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
} 
 
 
void loop() 
{ 
  int delayTime = random(3,40);
  for(pos = 20; pos < 165; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(delayTime);                       // waits 15ms for the servo to reach the position 
  } 
  delayTime = random(4000);
  delay(delayTime);
  delayTime = random(3,40);
  for(pos = 165; pos>=20; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(delayTime);                       // waits 15ms for the servo to reach the position 
  }
  delayTime = random(4000);
  delay(delayTime); 
}
