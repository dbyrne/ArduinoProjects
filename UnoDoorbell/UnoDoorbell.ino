const int piezoPin = 9;
const int buttonPin = 2;

const int noteDuration = 175;
const int pauseDuration = 100;

/*
 * Note frequencies and periods taken from http://soundoctor.com/freq.htm
 * Starts at middle C and goes up (including sharps/flats)
 */
const double freqs[] = {261.63, 277.18, 293.67, 311.13, 329.63, 349.23, 369.99, 392.00, 415.30, 440.00, 466.16, 493.88, 523.25}; 
int tones[13];

const int songLength = 23;

typedef struct {
  char notes[songLength];
  char beats[songLength];
  char tie[songLength];
} Song;

const Song spiderman = {
  {2, 5, 9, 9, -1, 8, 5, 2, 2, -1, 2, 5, 9, 9, 10, 9, 8, 5, 2, 2, -1, 6, 10},
  {2, 1, 1, 2,  2, 2, 1, 1, 2,  2, 2, 1, 1, 1,  1, 1, 1, 1, 1, 2,  2, 2,  1},
  {0, 0, 1, 0,  0, 0, 0, 1, 0,  0, 0, 0, 1, 0,  0, 0, 0, 0, 1, 0,  0, 0,  0}
};

/*
const Song blackSheep = {
  "ccggaaaagffeeddc",
  {2, 2, 2, 2, 1, 1, 1, 1, 4, 2, 2, 2, 2, 2, 2, 4}
};

const Song scale = {
  "cdefgabCCbagfedc",
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
*/

const Song songs[] = {spiderman};

const int numberOfSongs = sizeof(songs) / sizeof(Song);

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
  attachInterrupt(0, playRandom, FALLING);
}

//Main loop isn't needed
void loop() {
}

//Plays a random song when the button is pushed
void playRandom() {
  const Song song = songs[random(numberOfSongs)];

  for (int i = 0; i < songLength; i++) {
    const int note = song.notes[i];
    const int duration = song.beats[i] * noteDuration;
   
    if (note != -1) {
      playTone(tones[note], duration);   
    } else {
       delay(duration * 10L);
    }
  
    const int pause = pauseDuration * 10L;
    
    if (song.tie[i] == 1) {
      delay(pause / 2);
    } else {
      delay(pause);
    }  
  }    
}


