// Define pins
const int pinPulse = 5;
const int pinON = 6;            // D6 is on/off switch, active LOW
const int pinRightForward = 7;  // connect D7 to FWD
const int pinRightBackward = 8; // connect D8 to BACK
const int pinRightPWM = 9;      // connect D9 to right Vref via Left RC LPF
const int pinLeftPWM = 10;      // connect D10 to left Vref via Left RC LPF
const int pinLeftForward = 11;  // connect D11 to FWD
const int pinLeftBackward = 12; // connect D12 to BACK

// Define variables
volatile int rightPulses = 0;
volatile int leftPulses = 0;

// Define const
const int maxPWM = 200;

/* CODE */

void setup() {
  pinMode(pinPulse, INPUT);
  pinMode(pinON, INPUT_PULLUP);
  pinMode(pinLeftForward, OUTPUT);
  pinMode(pinLeftBackward, OUTPUT);
  pinMode(pinLeftPWM, OUTPUT);
  pinMode(pinRightForward, OUTPUT);
  pinMode(pinRightBackward, OUTPUT);
  pinMode(pinRightPWM, OUTPUT);
  pinMode(13, OUTPUT);  // LED

  // Stop
  digitalWrite(pinLeftForward, LOW);
  digitalWrite(pinLeftBackward, LOW);
  digitalWrite(pinRightForward, LOW);
  digitalWrite(pinRightBackward, LOW);

  // Set up interrupts
  attachInterrupt(digitalPinToInterrupt(6), service6, RISING);
  attachInterrupt(digitalPinToInterrupt(2), service2, RISING);
  attachInterrupt(digitalPinToInterrupt(4), service4, RISING);

  // Set up serial monitor
  Serial.begin(9600);
}

void loop() {
  // Roll forward
  moveForward(500);

  // Put out ultrasonic pulses
  long duration = pulseIn(5, HIGH);
  int distance = duration * 0.034/2;
  Serial.println(distance);
  delay(1000);

  // Check for obstacle
  if(distance < 100){
    turnClockwise(500);
  }
}


/* FUNCTIONS */

void moveForward(int numPulses) {
  int slowDownThreshold = numPulses - (numPulses / 4);
  int currentPWM = 100;
  rightPulses = 0;
  leftPulses = 0;

  // roll
  while((rightPulses < numPulses) && (leftPulses < numPulses)) {
    if(rightPulses < slowDownThreshold) {
        currentPWM = min(currentPWM + 2, maxPWM);
    }

    if(rightPulses > slowDownThreshold) {
        currentPWM = max(currentPWM - 0.5, 100);
    }

    // set Vref
    analogWrite(pinLeftPWM, currentPWM);
    analogWrite(pinRightPWM, currentPWM);

    // move
    digitalWrite(pinLeftForward, HIGH);
    digitalWrite(pinRightForward, HIGH);
  }

  // stop
  digitalWrite(pinLeftForward, LOW);
  digitalWrite(pinRightForward, LOW);

  Serial.println(rightPulses);
  Serial.println(leftPulses);

  Serial.println("Forward");
}

void turnClockwise(int numPulses) {
  int slowDownThreshold = numPulses - (numPulses / 4);
  int currentPWM = 100;
  rightPulses = 0;
  leftPulses = 0;

  // turn
  while((leftPulses < numPulses)) {
    if(leftPulses < slowDownThreshold) {
        currentPWM = min(currentPWM + 2, maxPWM);
    }

    if(leftPulses > slowDownThreshold) {
        currentPWM = max(currentPWM - 0.5, 100);
    }

    // set Vref
    analogWrite(pinLeftPWM, currentPWM);
    analogWrite(pinRightPWM, currentPWM);

    // move
    digitalWrite(pinLeftForward, HIGH);
    digitalWrite(pinRightBackward, HIGH);
  }

  // stop
  digitalWrite(pinLeftForward, LOW);
  digitalWrite(pinRightBackward, LOW);

  Serial.println(rightPulses);
  Serial.println(leftPulses);

  Serial.println("CW");
}

void turnCounterClockwise(int numPulses) {
  int slowDownThreshold = numPulses - (numPulses / 4);
  int currentPWM = 100;
  rightPulses = 0;
  leftPulses = 0;

  // turn
  while((rightPulses < numPulses)) {
    if(rightPulses < slowDownThreshold) {
        currentPWM = min(currentPWM + 2, maxPWM);
    }

    if(rightPulses > slowDownThreshold) {
        currentPWM = max(currentPWM - 0.5, 100);
    }

    // set Vref
    analogWrite(pinRightPWM, currentPWM);
    analogWrite(pinLeftPWM, currentPWM);

    // move
    digitalWrite(pinRightForward, HIGH);
    digitalWrite(pinLeftBackward, HIGH);
  }

  // stop
  digitalWrite(pinRightForward, LOW);
  digitalWrite(pinLeftBackward, LOW);

  Serial.println(rightPulses);
  Serial.println(leftPulses);

  Serial.println("CCW");
}