const int DATA = 2;
const int CLOCK = 3;
const int LATCH = 4;

const int S0 = 10;
const int S1 = 11;
const int S2 = 12;
const int S3 = 13;
const int SIG = 5;

int ledState = 0;

int readChannel(int channel) {
  digitalWrite(S0, bitRead(channel, 0));
  digitalWrite(S1, bitRead(channel, 1));
  digitalWrite(S2, bitRead(channel, 2));
  digitalWrite(S3, bitRead(channel, 3));
  
  return analogRead(SIG);
}

int readLEDValues() {
  
  int sigValue = 0;
  
  for (int channel = 0; channel < 8; channel++) {
    if (readChannel(channel) > 25) {
      bitSet(sigValue, channel);
    } else {
      bitClear(sigValue, channel);
    }  
  }
  return sigValue;
}

void updateLEDs(int value) {
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, MSBFIRST, value);
  digitalWrite(LATCH, HIGH);
}

void setup() {
  pinMode(DATA,  OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(LATCH, OUTPUT);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);  
}

void loop() {
  const int shiftRegisterValue = readLEDValues();
  updateLEDs(shiftRegisterValue);
}
