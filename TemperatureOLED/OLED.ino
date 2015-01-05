#include "IIC_without_ACK.h"
#include "oledfont.c"
#include <stdio.h>

#define OLED_SDA 8
#define OLED_SCL 9

IIC_without_ACK lucky(OLED_SDA, OLED_SCL);

void setup() {
  lucky.Initial();
  delay(10);
}

void tempToString(char* str, float temp, char unit) {
  int d1 = temp;
  float f2 = temp - d1;
  int d2 = int(f2 * 10000);
  sprintf(str, "%d.%01d %c", d1, d2, unit);
}

void loop() {
  int reading = analogRead(0);
  
  float voltage = reading * 5.0;
  voltage /= 1024.0;
  
  float celsius = (voltage - 0.5) * 100;
  float fahrenheit = (celsius * 9.0 / 5.0) + 32.0;
  
  char fstr[16];
  char cstr[16];
  
  tempToString(fstr, fahrenheit, 'F');
  tempToString(cstr, celsius, 'C');
  
  lucky.Fill_Screen(0x00);
  lucky.Char_F8x16(0,0, fstr);
  lucky.Char_F8x16(0,2, cstr);

  delay(5000);
}
