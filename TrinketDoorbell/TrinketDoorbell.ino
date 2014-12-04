const int piezoPin = 3;
const int buttonPin = 2;

const int noteDuration = 175;
const int pauseDuration = 100;

/*
 * Note frequencies and periods taken from http://soundoctor.com/freq.htm
 * Starts at middle C and goes up (including sharps/flats)
 */
const double freqs[] = {261.63, 277.18, 293.67, 311.13, 329.63, 349.23, 369.99, 392.00, 415.30, 440.00, 466.16, 493.88, 523.25}; 
int tones[13];

// timeHigh = 1 / (2 * toneFrequency)
void calculateTones() { 
  for (int i = 0; i < 13; i++) {
    double tone = 1000000 * (1 / (freqs[i] * 2));
    tones[i] = (int) tone;
  }  
}

//TODO: Switch to analogWrite?
void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(piezoPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(piezoPin, LOW);
    delayMicroseconds(tone);
  }
}

//Set up a hardware interrupt to execute a callback when the button is pressed
void setup() {
  calculateTones();
  pinMode(piezoPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(0, playScale, FALLING);
}

//Main loop isn't needed
void loop() {
}

//Plays a random song when the button is pushed
void playScale() {
  for (int i = 0; i < 13; i++) {   
    playTone(tones[i], noteDuration);   

    const int pause = pauseDuration * 10L;
    delay(pause);

  }
}


