const int buttonPin = 2;
const int piezoPin = 13;

void setup() {                
  pinMode(buttonPin, INPUT);
  pinMode(piezoPin, OUTPUT);
  digitalWrite(buttonPin, HIGH);
  
  attachInterrupt(0, play, FALLING);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(piezoPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(200);               // wait for a second
  digitalWrite(piezoPin, LOW);    // turn the LED off by making the voltage LOW
  delay(200);
  Serial.print("Hello");
  Serial.print(digitalRead(piezoPin));  
}

void play() {
  digitalWrite(piezoPin, HIGH);    // Toggle LED on pin 13/
}
