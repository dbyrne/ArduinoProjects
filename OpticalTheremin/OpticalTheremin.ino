#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>

//TODO: Add a second light sensor for volume control

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

//Used to set LCD backlight for different screens
#define RED 0x1
#define VIOLET 0x5
#define WHITE 0x7

//Can't use analog 4 or 5 because of the LCD shield
#define LIGHT_SENSOR 1

//Tones will range from 0 hertz up to note C6
#define C6 1046

//Used to calibrate the theremin for different light levels
int high;
int low;
int range;
double scale;

//Prompt the user to calibrate the light level
int getReading(String prompt, uint8_t backlight) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.setBacklight(backlight);
  lcd.print(prompt);
  while (true) {
    const uint8_t buttons = lcd.readButtons();
    if (buttons & BUTTON_SELECT) {
      lcd.setCursor(0, 1);
      const int reading = analogRead(LIGHT_SENSOR);
      lcd.print(reading);
      delay(2000);
      return reading;
    }
  }
}

void setup() {
  lcd.begin(16, 2);
  
  //Before we start playing calibrate high and low light levels
  high = getReading("Set High", VIOLET);
  low = getReading("Set Low", RED);
  range = high - low;
  scale = C6 / range;
   
  lcd.setBacklight(WHITE);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Playing...");
}

void loop() {
  
  lcd.setCursor(0, 1);
  
  const int reading = analogRead(LIGHT_SENSOR);
  const int value = max(0, scale * (reading - low));
  
  lcd.print(value);
  lcd.print("   ");
  
  tone(9, value);
  delay(10);
}
