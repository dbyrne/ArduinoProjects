
const int BOTTOM = 13;
const int MIDDLE = 12;
const int TOP    = 11;

const int FAR_RIGHT     = 10;
const int FAR_MIDDLE    = 2;
const int FAR_LEFT      = 3;
const int MIDDLE_RIGHT  = 4;
const int MIDDLE_MIDDLE = 5;
const int MIDDLE_LEFT   = 6;
const int NEAR_RIGHT    = 9;
const int NEAR_MIDDLE   = 8;
const int NEAR_LEFT     = 7;

void setup() {
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  
  pinMode(TOP,   OUTPUT);
  pinMode(MIDDLE,OUTPUT);
  pinMode(BOTTOM,OUTPUT);
}

void flash(int pin) {
  digitalWrite(pin, HIGH);
  delay(200);
  digitalWrite(pin, LOW);  
}

void quick_flash(int pin) {
  digitalWrite(pin, HIGH);
  delay(200);
  digitalWrite(pin, LOW); 
}

void flash3(int pin1, int pin2, int pin3) {
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, HIGH);
  digitalWrite(pin3, HIGH);
  delay(200);
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW); 
  digitalWrite(pin3, LOW); 
}

void zigzag() {
  quick_flash(FAR_RIGHT);
  quick_flash(FAR_MIDDLE);
  quick_flash(FAR_LEFT);
  quick_flash(MIDDLE_LEFT);
  quick_flash(MIDDLE_MIDDLE);
  quick_flash(MIDDLE_RIGHT);
  quick_flash(NEAR_RIGHT);
  quick_flash(NEAR_MIDDLE);
  quick_flash(NEAR_LEFT);
}

void rev_zigzag() {  
  quick_flash(NEAR_LEFT);
  quick_flash(NEAR_MIDDLE);
  quick_flash(NEAR_RIGHT);
  quick_flash(MIDDLE_RIGHT);
  quick_flash(MIDDLE_MIDDLE);
  quick_flash(MIDDLE_LEFT);
  quick_flash(FAR_LEFT);
  quick_flash(FAR_MIDDLE);
  quick_flash(FAR_RIGHT);
}

void swerve() {
  flash(NEAR_LEFT);
  flash(NEAR_MIDDLE);
  flash(NEAR_RIGHT);
  flash(MIDDLE_RIGHT);
  flash(FAR_RIGHT);
  flash(FAR_MIDDLE);
  flash(FAR_LEFT);
  flash(MIDDLE_LEFT);
  flash(MIDDLE_MIDDLE);
  flash(MIDDLE_RIGHT);
  flash(NEAR_RIGHT);
  flash(NEAR_MIDDLE);
  flash(NEAR_LEFT);
  flash(MIDDLE_LEFT);
  flash(FAR_LEFT);
  flash(FAR_MIDDLE);
  flash(FAR_RIGHT);
}

void snake() {
  digitalWrite(BOTTOM, HIGH);
  
  zigzag();
  
  digitalWrite(BOTTOM, LOW);
  digitalWrite(MIDDLE, HIGH);
  
  rev_zigzag();
  
  digitalWrite(MIDDLE, LOW);
  digitalWrite(TOP, HIGH);
  
  zigzag();
}

void column_swerve() {
  digitalWrite(BOTTOM, HIGH);
  digitalWrite(MIDDLE, HIGH);
  digitalWrite(TOP, HIGH);
  
  swerve();
}

void row_zigzag() {
  digitalWrite(MIDDLE, LOW);
  digitalWrite(TOP, LOW);
  
  digitalWrite(FAR_RIGHT, HIGH);
  digitalWrite(FAR_MIDDLE, HIGH);
  digitalWrite(FAR_LEFT, HIGH);
  
  flash(BOTTOM);
  flash(MIDDLE);
  flash(TOP);
  
  digitalWrite(FAR_RIGHT, LOW);
  digitalWrite(FAR_MIDDLE, LOW);
  digitalWrite(FAR_LEFT, LOW);
  
  digitalWrite(MIDDLE_RIGHT, HIGH);
  digitalWrite(MIDDLE_MIDDLE, HIGH);
  digitalWrite(MIDDLE_LEFT, HIGH);
  
  flash(TOP);
  flash(MIDDLE);
  flash(BOTTOM);
  
  digitalWrite(MIDDLE_RIGHT, LOW);
  digitalWrite(MIDDLE_MIDDLE, LOW);
  digitalWrite(MIDDLE_LEFT, LOW);
  
  digitalWrite(NEAR_RIGHT, HIGH);
  digitalWrite(NEAR_MIDDLE, HIGH);
  digitalWrite(NEAR_LEFT, HIGH);
  
  flash(BOTTOM);
  flash(MIDDLE);
  flash(TOP);
  
  digitalWrite(NEAR_RIGHT, LOW);
  digitalWrite(NEAR_MIDDLE, LOW);
  digitalWrite(NEAR_LEFT, LOW);
  
  digitalWrite(MIDDLE_RIGHT, HIGH);
  digitalWrite(MIDDLE_MIDDLE, HIGH);
  digitalWrite(MIDDLE_LEFT, HIGH);
  
  flash(TOP);
  flash(MIDDLE);
  flash(BOTTOM);
  
  digitalWrite(MIDDLE_RIGHT, LOW);
  digitalWrite(MIDDLE_MIDDLE, LOW);
  digitalWrite(MIDDLE_LEFT, LOW);
  
  digitalWrite(FAR_RIGHT, HIGH);
  digitalWrite(FAR_MIDDLE, HIGH);
  digitalWrite(FAR_LEFT, HIGH);
  
  flash(BOTTOM);
  flash(MIDDLE);
  flash(TOP);
}

void wall() {
  digitalWrite(TOP, HIGH);
  digitalWrite(MIDDLE, HIGH);
  digitalWrite(BOTTOM, HIGH);
  
  for (int i = 0; i < 3; i++) {
    flash3(FAR_LEFT, FAR_MIDDLE, FAR_RIGHT);
    flash3(MIDDLE_LEFT, MIDDLE_MIDDLE, MIDDLE_RIGHT);
    flash3(NEAR_LEFT, NEAR_MIDDLE, NEAR_RIGHT);
    flash3(MIDDLE_LEFT, MIDDLE_MIDDLE, MIDDLE_RIGHT);
  }
  flash3(FAR_LEFT, FAR_MIDDLE, FAR_RIGHT);
}

void elevator() {
  digitalWrite(TOP, LOW);
  digitalWrite(MIDDLE, LOW);
  digitalWrite(BOTTOM, LOW);
  
  digitalWrite(FAR_LEFT, HIGH);
  digitalWrite(FAR_MIDDLE, HIGH);
  digitalWrite(FAR_RIGHT, HIGH);
  digitalWrite(MIDDLE_LEFT, HIGH);
  digitalWrite(MIDDLE_MIDDLE, HIGH);
  digitalWrite(MIDDLE_RIGHT, HIGH);
  digitalWrite(NEAR_LEFT, HIGH);
  digitalWrite(NEAR_MIDDLE, HIGH);
  digitalWrite(NEAR_RIGHT, HIGH);
  
  for (int i = 0; i < 3; i++) {
    flash(BOTTOM);
    flash(MIDDLE);
    flash(TOP);
    flash(MIDDLE);
  }
  flash(BOTTOM);
}

void all() {
  digitalWrite(BOTTOM, HIGH);
  digitalWrite(MIDDLE, HIGH);
  digitalWrite(TOP, HIGH);
  delay(1000);
  digitalWrite(BOTTOM, LOW);
  digitalWrite(MIDDLE, LOW);
  digitalWrite(TOP, LOW);
  
  digitalWrite(FAR_LEFT, LOW);
  digitalWrite(FAR_MIDDLE, LOW);
  digitalWrite(FAR_RIGHT, LOW);
  digitalWrite(MIDDLE_LEFT, LOW);
  digitalWrite(MIDDLE_MIDDLE, LOW);
  digitalWrite(MIDDLE_RIGHT, LOW);
  digitalWrite(NEAR_LEFT, LOW);
  digitalWrite(NEAR_MIDDLE, LOW);
  digitalWrite(NEAR_RIGHT, LOW);
}
 
void loop() {
  digitalWrite(BOTTOM, LOW);
  digitalWrite(MIDDLE, LOW);
  digitalWrite(TOP, LOW);
  
  snake();
  column_swerve();
  row_zigzag();
  wall();
  elevator();
  all();
}
