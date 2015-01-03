#include <Wire.h>

//Pin connected to ST_CP of 74HC595
const int latchPin = 8;
//Pin connected to SH_CP of 74HC595
const int clockPin = 12;
////Pin connected to DS of 74HC595
const int dataPin = 11;

#define COMPASS_I2C_ADDR 0x1E

void setup() {
  
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(13, OUTPUT);
  
  Serial.begin(9600);
  Wire.begin();
  
  Wire.beginTransmission(COMPASS_I2C_ADDR);
  Wire.write(0x02); //select mode register
  Wire.write(0x00); //continuous measurement mode
  Wire.endTransmission();
}

int getHeading(int cx, int cy, int cz) {
  int var_compass=atan2((double)cy,(double)cx) * (180 / PI) -90; // angle in degrees
  if (var_compass>0){
    var_compass=var_compass-360;
  }
  var_compass=360+var_compass;
 
  return (var_compass);
}

void loop(){  

  int x,y,z; //triple axis data

  Wire.beginTransmission(COMPASS_I2C_ADDR);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();
  
 //Read data from each axis, 2 registers per axis
  Wire.requestFrom(COMPASS_I2C_ADDR, 6);
  if(6<=Wire.available()){
    x = Wire.read()<<8; //X msb
    x |= Wire.read(); //X lsb
    z = Wire.read()<<8; //Z msb
    z |= Wire.read(); //Z lsb
    y = Wire.read()<<8; //Y msb
    y |= Wire.read(); //Y lsb
  }
  
  int heading = getHeading(x, y, z);
  int shiftValue;

  if (heading <= 45) {
    shiftValue = 1;
  } else if (heading <= 90) {
    shiftValue = 2;
  } else if (heading <= 135) {
    shiftValue = 4;
  } else if (heading <= 180) {
    shiftValue = 8;
  } else if (heading <= 225) {
    shiftValue = 16;
  } else if (heading <= 270) {
    shiftValue = 32;
  } else if (heading <= 315) {
    shiftValue = 64;
  } else if (heading <= 360) {
    shiftValue = 128;
  }
  
  digitalWrite(latchPin, LOW);
  // shift out the bits:
  shiftOut(dataPin, clockPin, MSBFIRST, shiftValue);  

  //take the latch pin high so the LEDs will light up:
  digitalWrite(latchPin, HIGH);
  
  delay(50);
  
}
