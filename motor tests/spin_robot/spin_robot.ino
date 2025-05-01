// define pins
const int pinON = 6;            // D6 is on/off switch, active LOW
const int pinRightForward = 7;  // connect D7 to FWD
const int pinRightBackward = 8; // connect D8 to BACK
const int pinRightPWM = 9;      // connect D9 to right Vref via Left RC LPF
const int pinLeftPWM = 10;      // connect D10 to left Vref via Left RC LPF
const int pinLeftForward = 11;  // connect D11 to FWD
const int pinLeftBackward = 12; // connect D12 to BACK

// setup pins and initial values
void setup() {
  pinMode(pinON, INPUT_PULLUP);
  pinMode(pinLeftForward, OUTPUT);
  pinMode(pinLeftBackward, OUTPUT);
  pinMode(pinLeftPWM, OUTPUT);
  pinMode(pinRightForward, OUTPUT);
  pinMode(pinRightBackward, OUTPUT);
  pinMode(pinRightPWM, OUTPUT);

  digitalWrite(pinLeftForward, LOW);  // stop forward
  digitalWrite(pinLeftBackward, LOW); // stop backward
  digitalWrite(pinRightForward, LOW);
  digitalWrite(pinRightBackward, LOW);

  analogWrite(pinLeftPWM, 200);       // set Vref, duty-cycle 200/255
  analogWrite(pinRightPWM, 200);
}

void loop() {
  do {} while (digitalRead(pinON) == HIGH); // wait for ON switch

  delay(1000);

  // go CW
  digitalWrite(pinLeftForward, HIGH);
  digitalWrite(pinRightBackward, HIGH);
  delay(3500);
  // stop
  digitalWrite(pinLeftForward, LOW);
  digitalWrite(pinRightBackward, LOW);

  delay(1000);

  // go CCW
  //digitalWrite(pinRightForward, HIGH);
  //digitalWrite(pinLeftBackward, HIGH);
  //delay(3500);
  // stop
  //digitalWrite(pinRightForward, LOW);
  //digitalWrite(pinLeftBackward, LOW);
}
