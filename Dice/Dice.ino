//LED & Button Pins
#define MIDDLE 0
#define MR_ML  1
#define TR_BL  4
#define BR_TL  3
#define BUTTON 2

#define numberDuration 2000
#define rollAnimationLength 3
#define rollAnimationPause 150

void rollAnimation() {
  const int ledPins[] = {MR_ML, TR_BL, BR_TL, MIDDLE};
  for (int x = 0; x < rollAnimationLength; x++) {
    for (int y = 0; y < 4; y++) {
      digitalWrite(ledPins[y], HIGH);
      delay(rollAnimationPause);
      digitalWrite(ledPins[y], LOW);  
    }
  }  
}

void togglePins(int middle, int mr_ml, int tr_bl, int br_tl) {
  digitalWrite(MIDDLE, middle);
  digitalWrite(MR_ML,  mr_ml);
  digitalWrite(TR_BL,  tr_bl);
  digitalWrite(BR_TL,  br_tl);
  delay(numberDuration);
  digitalWrite(MIDDLE, 0);
  digitalWrite(MR_ML,  0);
  digitalWrite(TR_BL,  0);
  digitalWrite(BR_TL,  0);
}

void showNumber() {
  const int number = random(1, 7);
  switch (number) {
    case 1:
      togglePins(HIGH, LOW, LOW, LOW);
      break;
    case 2:
      togglePins(LOW, LOW, HIGH, LOW);
      break;
    case 3:
      togglePins(HIGH, LOW, HIGH, LOW);
      break;
    case 4:
      togglePins(LOW, LOW, HIGH, HIGH);
      break;
    case 5:
      togglePins(HIGH, LOW, HIGH, HIGH);
      break;
    case 6:
      togglePins(LOW, HIGH, HIGH, HIGH);
  }
}

void rollDice() {
  rollAnimation();
  showNumber();
}

void setup() {
  randomSeed(analogRead(0));
  
  pinMode(MIDDLE, OUTPUT);
  pinMode(MR_ML, OUTPUT);
  pinMode(TR_BL, OUTPUT);
  pinMode(BR_TL, OUTPUT);
  
  pinMode (BUTTON, INPUT_PULLUP); 
}

void loop() {
  if (digitalRead(BUTTON) == LOW) {
    rollDice(); 
  } 
}


