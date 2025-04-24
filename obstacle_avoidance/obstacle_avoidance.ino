/* SETUP */

// Define pins
const int triggerPin = 5;
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

void setup() {
  pinMode(triggerPin, INPUT);
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

  // Set up serial monitor
  Serial.begin(9600);
}

/* LOOP */

void loop() {
  // Roll forward
  moveForward(500);

  // Put out ultrasonic pulses
  long duration = pulseIn(triggerPin, HIGH);
  int distance = duration * 0.034/2;
  Serial.println(distance);
  delay(1000);

  // Check for obstacle
  if(distance < 100){
    turnClockwise(500);
  }
}