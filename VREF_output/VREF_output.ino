// define pins
const int pinRightPWM = 9;
const int pinLeftPWM = 10;

void setup() {
  pinMode(pinRightPWM, OUTPUT);
  pinMode(pinLeftPWM, OUTPUT);
  analogWrite(pinRightPWM, 4*51); // Vref = 4 V
  analogWrite(pinLeftPWM, 4*51); // Vref = 4 V
  // 4*51 = 204 = 80% duty cycle @ 976 Hz
}

void loop() {
  // put your main code here, to run repeatedly:

}
