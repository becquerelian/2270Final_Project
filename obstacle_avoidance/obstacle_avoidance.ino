/* SETUP */

// Motor control pins
const int pinRightForward = 7;  // D7 = right FWD
const int pinRightBackward = 8; // D8 = right BACK
const int pinRightPWM = 9;      // D9 = right Vref
const int pinLeftPWM = 10;      // D10 = left Vref
const int pinLeftForward = 11;  // D11 = left FWD
const int pinLeftBackward = 12; // D12 = left BACK

// Ultrasonic pins
const int echoPin = 3;          // D3 = receives pulse, reads distance
const int triggerPin = 5;       // D5 = sends pulse

// Other pins
const int pinON = 6;            // D6 = button, active LOW
const int LEDPin = 13;          // D13 = onboard LED (for testing)

// Variables
volatile int rightPulses = 0;
volatile int leftPulses = 0;

// Constants
const int maxPWM = 200;

void setup() {
  // Motor control
  pinMode(pinLeftForward, OUTPUT);
  pinMode(pinLeftBackward, OUTPUT);
  pinMode(pinLeftPWM, OUTPUT);
  pinMode(pinRightForward, OUTPUT);
  pinMode(pinRightBackward, OUTPUT);
  pinMode(pinRightPWM, OUTPUT);

  // Stop motor
  digitalWrite(pinLeftForward, LOW);
  digitalWrite(pinLeftBackward, LOW);
  digitalWrite(pinRightForward, LOW);
  digitalWrite(pinRightBackward, LOW);

  // Ultrasonic
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Other
  pinMode(pinON, INPUT_PULLUP);
  pinMode(LEDPin, OUTPUT);

  // Set up serial monitor
  Serial.begin(9600);
}

/* CODE LOOP */

void loop() {
  // Define distance
  float distance = 0;

  // Roll forward
  moveForward(100);

  // Check distance
  distance = readDistance();
  Serial.println(distance);

  // Check for obstacle
  if(distance < 50){
    Serial.println("Turning");
    turnClockwise(100);
  }
}