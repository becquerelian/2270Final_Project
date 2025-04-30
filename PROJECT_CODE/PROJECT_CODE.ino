/*
  ULTRASONIC SENSOR WIRING:
  Left
    VCC --> VCC
    D3 --> Echo
    D5 --> Trig
    GND --> GND

  Right
    VCC --> VCC
    D20 --> Echo
    D21 --> Trig
    GND --> GND

  PRESENCE SENSOR WIRING:
    ARDUINO --> STHS34PF80
    SDA (A4 / D18) --> SDA
    SCL (A5 / D19) --> SCL
    INT (D14) --> INT
    3.3V --> 3.3V
    GND --> GND

  SPEAKER WIRING:
    BLACK --> GND
    RED --> D15
*/

#include "SparkFun_STHS34PF80_Arduino_Library.h"
#include <Wire.h>
#include "pitches.h"

STHS34PF80_I2C mySensor;

// Motor control
const int pinRightForward = 7;  // D7 = right FWD
const int pinRightBackward = 8; // D8 = right BACK
const int pinRightPWM = 9;      // D9 = right Vref
const int pinLeftPWM = 10;      // D10 = left Vref
const int pinLeftForward = 11;  // D11 = left FWD
const int pinLeftBackward = 12; // D12 = left BACK

const int maxPWM = 200;

volatile int rightPulses = 0;
volatile int leftPulses = 0;

// Ultrasonic sensor
const int leftEchoPin = 3;          // D3 = receives pulse, reads distance
const int leftTriggerPin = 5;       // D5 = sends pulse
const int rightEchoPin = 20;        // D20 = receives pulse, reads distance
const int rightTriggerPin = 21;     // D21 = sends pulse

const int obstacleDistance = 10;

// Presence sensor
const int interruptPin = 14;        // D14 = interrupt

int16_t presenceVal = 0;
volatile bool interruptFlag = false;

// Speaker
const int speakerPin = 15;     // D15 = speaker

int melody[] = {NOTE_DS8, END};
int noteDurations[] = {20,20,};
int speed = 90;

// Other pins
const int rightEncoderPin = 2;  // D2 = right encoder interrupt
const int leftEncoderPin = 4;   // D4 = left encoder interrupt
const int buttonPin = 6;        // D6 = button, active LOW
const int LEDPin = 13;          // D13 = onboard LED (for testing)


void setup() {
  // SERIAL MONITOR
  Serial.begin(9600);

  // MOTOR CONTROL
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

  // ULTRASONIC SENSOR
  pinMode(leftTriggerPin, OUTPUT);
  pinMode(leftEchoPin, INPUT);
  pinMode(rightTriggerPin, OUTPUT);
  pinMode(rightEchoPin, INPUT);

  // PRESENCE SENSOR

  // Begin I2C
  Wire.begin();

  // Establish communication with device 
  if(mySensor.begin() == false) {
    Serial.println("Error setting up presence sensor - please check wiring.");
    while(1);
  }

  pinMode(interruptPin, INPUT);

  // OTHER
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(LEDPin, OUTPUT);

  // INTERRUPTS
  attachInterrupt(digitalPinToInterrupt(rightEncoderPin), rightCounter, RISING);
  attachInterrupt(digitalPinToInterrupt(leftEncoderPin), leftCounter, RISING);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonInterrupt, RISING);

  // Presence sensor
  attachInterrupt(digitalPinToInterrupt(interruptPin), humanDetected, CHANGE);

  // Route all interrupts from device to interrupt pin
  mySensor.setTmosRouteInterrupt(STHS34PF80_TMOS_INT_OR);

  // Enable the presence interrupt source 
  // (see page 17 of application note AN5867 for more information)
  mySensor.setTmosInterruptOR(STHS34PF80_TMOS_INT_PRESENCE);

  // Set interrupt value to pulsed on the INT pin
  mySensor.setInterruptPulsed(0);

  Serial.println("Begin");
}


/****************************************
  CODE LOOP

****************************************/

void loop() {
  // Roll forward as long as no obstacle
  while(obstacleDetected() == 0){
    moveForward(3000);
  }

  // OBSTACLE DETECTED
  
  // If interrupt is triggered
  // (can trigger due to PRESENCE, MOTION, or AMBIENT TEMP CHANGE)
  if(interruptFlag == true){
    interruptFlag = false;
    
    sths34pf80_tmos_func_status_t status;
    mySensor.getStatus(&status);
    
    Serial.println("Data ready!");

    // If there is a presence
    if(status.pres_flag == 1){
      // Activate speaker sound
      playTone();
      // Turn either TOWARDS or AWAY FROM the presence
      // (currently away)
      turnCounterClockwise(1100);
      // then run forward
      moveForward(2900);
    }
  }
  
  // Turn away from obstacle

  // Both sensors detect obstacle
  if(obstacleDetected() == 1){
    int distanceRight = readDistanceRight();
    int distanceLeft = readDistanceLeft();

    // Pick the best direction to turn in
    if(distanceRight < distanceLeft){
      turnCounterClockwise(100);
    }
    else{
      turnClockwise(100);
    }
  }
  // Right sensor detects obstacle
  else if(obstacleDetected() == 2){
    turnCounterClockwise(100);
  }
  // Left sensor detects obstacle
  else if(obstacleDetected() == 3){
    turnClockwise(100);
  }
}