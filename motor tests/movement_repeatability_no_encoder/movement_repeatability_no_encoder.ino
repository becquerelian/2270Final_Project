// Robot Movement Repeatability Test

// Define pins
const int pinON = 6;            // D6 is on/off switch, active LOW
const int pinRightForward = 7;  // connect D7 to FWD
const int pinRightBackward = 8; // connect D8 to BACK
const int pinRightPWM = 9;      // connect D9 to right Vref via Left RC LPF
const int pinLeftPWM = 10;      // connect D10 to left Vref via Left RC LPF
const int pinLeftForward = 11;  // connect D11 to FWD
const int pinLeftBackward = 12; // connect D12 to BACK

// Setup pins and initial values
void setup() {
  pinMode(pinON, INPUT_PULLUP);
  pinMode(pinLeftForward, OUTPUT);
  pinMode(pinLeftBackward, OUTPUT);
  pinMode(pinLeftPWM, OUTPUT);
  pinMode(pinRightForward, OUTPUT);
  pinMode(pinRightBackward, OUTPUT);
  pinMode(pinRightPWM, OUTPUT);

  // Stop
  digitalWrite(pinLeftForward, LOW);
  digitalWrite(pinLeftBackward, LOW);
  digitalWrite(pinRightForward, LOW);
  digitalWrite(pinRightBackward, LOW);

  // set Vref
  analogWrite(pinLeftPWM, 200);
  analogWrite(pinRightPWM, 200);
}

void loop() {
  // polling button
  do {} while (digitalRead(pinON) == HIGH);

  delay(1000);
  moveForward(3);   // 2 ft
  delay(1000);
  turnClockwise(2); // 180deg
  delay(1000);
  moveForward(3);   // 2 ft
  delay(1000);
  turnCounterClockwise(2);  // 180deg
}

/* FUNCTIONS */

void moveForward(int time) {
  // move
  digitalWrite(pinLeftForward, HIGH);
  digitalWrite(pinRightForward, HIGH);
  delay(time * 1000);

  // stop
  digitalWrite(pinLeftForward, LOW);
  digitalWrite(pinRightForward, LOW);
}

void turnClockwise(int time) {
  // move
  digitalWrite(pinLeftForward, HIGH);
  digitalWrite(pinRightBackward, HIGH);
  delay(time * 1000);

  // stop
  digitalWrite(pinLeftForward, LOW);
  digitalWrite(pinRightBackward, LOW);
}

void turnCounterClockwise(int time) {
  // move
  digitalWrite(pinRightForward, HIGH);
  digitalWrite(pinLeftBackward, HIGH);
  delay(time * 1000);

  // stop
  digitalWrite(pinRightForward, LOW);
  digitalWrite(pinLeftBackward, LOW);
}