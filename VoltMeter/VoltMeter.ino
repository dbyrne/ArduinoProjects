double r1 = 1230;
double r2 = 807;
double maxVoltage = 20.33898305;

//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 9;
////Pin connected to DS of 74HC595
int dataPin = 7;

int leftAnode = 12;
int midAnode = 11;
int rightAnode = 10;

int topMiddle = 1;
int topRight = 2;
int topLeft = 4;
int middleMiddle = 8;
int bottomRight = 16;
int decimalPlace = 32;
int bottomMiddle = 64;
int bottomLeft = 128;

int off   = 255;
int zero  = 255 - topLeft - topMiddle - topRight - bottomLeft - bottomMiddle - bottomRight;
int one   = 255 - topRight - bottomRight;
int two   = 255 - topMiddle - topRight - middleMiddle - bottomLeft - bottomMiddle;
int three = 255 - topMiddle - topRight - middleMiddle - bottomRight - bottomMiddle;
int four  = 255 - topLeft - topRight - middleMiddle - bottomRight;
int five  = 255 - topMiddle - topLeft - middleMiddle - bottomRight - bottomMiddle;
int six   = 255 - topMiddle - topLeft - middleMiddle - bottomRight - bottomMiddle - bottomLeft;
int seven = 255 - topMiddle - topRight - bottomRight;
int eight = 255 - topMiddle - middleMiddle - bottomMiddle - topLeft - bottomLeft - topRight - bottomRight;
int nine  = 255 - topMiddle - middleMiddle - bottomMiddle - topLeft - topRight - bottomRight;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(A1, INPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(leftAnode, OUTPUT);
  pinMode(midAnode, OUTPUT);
  pinMode(rightAnode, OUTPUT);
}

void setDigit(int number) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, number);  
  digitalWrite(latchPin, HIGH); 
}

int getEncoded(int digit) {
  switch(digit) {
    case 0: return zero;
    case 1: return one;
    case 2: return two;
    case 3: return three;
    case 4: return four;
    case 5: return five;
    case 6: return six;
    case 7: return seven;
    case 8: return eight;
    case 9: return nine;
  };
}

// the loop function runs over and over again forever
void loop() {
  double raw = (double) analogRead(A1);
  double voltage = (raw / 1023) * maxVoltage;
  
  int tensDigit   = (int) voltage       / 10;
  int onesDigit   = (int) voltage       % 10;
  int tenthsDigit = (int)(voltage * 10) % 10;
  
  int tensEncoded = getEncoded(tensDigit);
  int onesEncoded = getEncoded(onesDigit);
  int tenthsEncoded = getEncoded(tenthsDigit);
  
  digitalWrite(leftAnode, HIGH);
  if (tensEncoded == zero) {
    tensEncoded = off;
  }
  setDigit(tensEncoded);
  digitalWrite(leftAnode, LOW);
  setDigit(255);
  digitalWrite(midAnode, HIGH);
  setDigit(onesEncoded - decimalPlace);
  digitalWrite(midAnode, LOW);  
  setDigit(255);
  digitalWrite(rightAnode, HIGH);
  setDigit(tenthsEncoded);
  digitalWrite(rightAnode, LOW);
  setDigit(255);
}
