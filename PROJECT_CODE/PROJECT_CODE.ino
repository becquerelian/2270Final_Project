/*
  Scroll to bottom for code loop
  
  ULTRASONIC SENSOR WIRING:
  VCC --> VCC
  D3 --> Echo
  D5 --> Trig
  GND --> GND

  PRESENCE SENSOR WIRING:
  ARDUINO --> STHS34PF80
  SDA (A4) --> SDA
  SCL (A5) --> SCL
  INT (2) --> INT
  3.3V --> 3.3V
  GND --> GND

  SPEAKER WIRING:
  BLACK --> GND
  RED --> D?
*/

#include "SparkFun_STHS34PF80_Arduino_Library.h"
#include <Wire.h>
#include "pitches.h"

STHS34PF80_I2C mySensor;

// Motor control pins
const int pinRightForward = 7;  // D7 = right FWD
const int pinRightBackward = 8; // D8 = right BACK
const int pinRightPWM = 9;      // D9 = right Vref
const int pinLeftPWM = 10;      // D10 = left Vref
const int pinLeftForward = 11;  // D11 = left FWD
const int pinLeftBackward = 12; // D12 = left BACK

// Ultrasonic sensor pins
const int echoPin = 3;          // D3 = receives pulse, reads distance
const int triggerPin = 5;       // D5 = sends pulse

// Presence sensor pins
const int intPin = 2;           // D2 = interrupt

// Other pins
const int buttonPin = 6;        // D6 = button, active LOW
const int LEDPin = 13;          // D13 = onboard LED (for testing)

// Constants
const int maxPWM = 200;
int noteDuration = 20;

// Variables
volatile int rightPulses = 0;
volatile int leftPulses = 0;
int16_t presenceVal = 0;
bool volatile interruptFlag = false;


void setup() {
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
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // PRESENCE SENSOR

  // Begin I2C
  Wire.begin();

  // Establish communication with device 
  if(mySensor.begin() == false) {
    Serial.println("Error setting up device - please check wiring.");
    while(1);
  }

  pinMode(intPin, INPUT);

  // OTHER
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(LEDPin, OUTPUT);

  // INTERRUPTS
  attachInterrupt(digitalPinToInterrupt(2), rightCounter, RISING);
  attachInterrupt(digitalPinToInterrupt(4), leftCounter, RISING);
  attachInterrupt(digitalPinToInterrupt(6), buttonInterrupt, RISING);

  // Presence sensor
  attachInterrupt(digitalPinToInterrupt(intPin), humanDetected, CHANGE);

  // Route all interrupts from device to interrupt pin
  mySensor.setTmosRouteInterrupt(STHS34PF80_TMOS_INT_OR);

  // Enable the presence interrupt source 
  // (see page 17 of application note AN5867 for more information)
  mySensor.setTmosInterruptOR(STHS34PF80_TMOS_INT_PRESENCE);

  // Set interrupt value to pulsed on the INT pin
  mySensor.setInterruptPulsed(0);

  // SERIAL MONITOR
  Serial.begin(9600);
}


/* CODE LOOP */

void loop() {
  // Roll forward as long as no obstacle
  while(readDistance() > 50){
    moveForward(100);
  }

  // OBSTACLE DETECTED

  // If interrupt is triggered
  // (can trigger due to PRESENCE, MOTION, or AMBIENT TEMP CHANGE)
  if(interruptTriggered()){
    // Get presence sensor data
    sths34pf80_tmos_func_status_t status;
    getData(status);

    // As long as there is a presence
    while(presenceDetected(status)){
      // Turn either TOWARDS or AWAY FROM the presence
      // then run forward
      // and activate speaker sound

      // until presence flag == 0 ?
    }
  }

  // Turn away from obstacle
  delay(500);
  turnClockwise(100);
}