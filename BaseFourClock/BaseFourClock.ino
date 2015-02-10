#include "Wire.h"
const int DS3231_I2C_ADDRESS = 0x68;

const int data = 3;
const int clock = 6;
const int latch = 5;
const int hoursButton = 9;
const int minutesButton = 7;
const int secondsButton = 2;
const int AM = 8;
const int PM = 4;

byte second, minute, hour;

byte decToBcd(byte val) {
  return (val/10*16) + (val%10);
}

byte bcdToDec(byte val) {
  return (val/16*10) + (val%16);
}

void updateLEDs(long value) {
  digitalWrite(latch, LOW);
  shiftOut(data, clock, MSBFIRST, value >> 16);
  shiftOut(data, clock, MSBFIRST, value >> 8);
  shiftOut(data, clock, MSBFIRST, value); 
  digitalWrite(latch, HIGH);
}

void setDS3231time(byte second, byte minute, byte hour) {
  // sets time and date data to DS3231
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(second)); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  Wire.write(decToBcd(hour)); // set hours

  Wire.endTransmission();
}

void readDS3231time(byte *second, byte *minute, byte *hour) {
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set DS3231 register pointer to 00h
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 3);
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
}

long getShiftValue(int second, int minute, int hour) {
  unsigned long result = 0;
  int remainder = second % 4;
  if (remainder > 0) {
    result |= 1 << (remainder - 1);
  }
  
  remainder = (second / 4) % 4;
  if (remainder > 0) {
    result |= 1 << (remainder + 2);
  }
  
  remainder = (second / 16) % 4;
  if (remainder > 0) {
    result |= 1 << (remainder + 5);
  }
  
  remainder = minute % 4;
    if (remainder > 0) {
    result |= 1 << (remainder + 8);
  }
  
  remainder = (minute / 4) % 4;
    if (remainder > 0) {
    result |= 1 << (remainder + 11);
  }
  
  remainder = (minute / 16) % 4;
    if (remainder > 0) {
    result |= 1L << (remainder + 14);
  }
  
  int ampm;
  
  if (hour == 0) {
    ampm = 12;
  } else if (hour > 12) {
    ampm = hour - 12;
  } else {
    ampm = hour;
  }
  
  if (hour > 11) {
    digitalWrite(PM, HIGH);
    digitalWrite(AM, LOW);
  } else {
    digitalWrite(PM, LOW);
    digitalWrite(AM, HIGH);
  }
  
  remainder = ampm % 4;
  if (remainder > 0) {
    result |= 1L << (remainder + 17);
  }
  
  remainder = (ampm / 4) % 4;
    if (remainder > 0) {
    result |= 1L << (remainder + 20);
  }
  
  return result;
}

void displayTime() {
  readDS3231time(&second, &minute, &hour);
  unsigned long shiftValue = getShiftValue(second, minute, hour);
  Serial.println(hour);
  updateLEDs(shiftValue);
}

void setup() {
 Wire.begin();  
 pinMode(data, OUTPUT);
 pinMode(clock, OUTPUT);
 pinMode(latch, OUTPUT); 
 pinMode(hoursButton, INPUT_PULLUP);
 pinMode(minutesButton, INPUT_PULLUP);
 pinMode(secondsButton, INPUT_PULLUP);
 pinMode(AM, OUTPUT);
 pinMode(PM, OUTPUT);
 Serial.begin(9600);
}
void loop() {
 boolean setDelay = false;
 if (digitalRead(hoursButton) == LOW) {
   hour = (hour + 1) % 24;
   setDelay = true;
 }
 
 if (digitalRead(minutesButton) == LOW) {
   minute = (minute + 1) % 60;
   setDelay = true;
 }
 
 if (digitalRead(secondsButton) == LOW) {
   second = 0;
   setDelay = true;
 }
 
 if (setDelay) {
   setDS3231time(second, minute, hour);
 }
 
 displayTime();
 
 if (setDelay) {
   delay(500);
 }
}
