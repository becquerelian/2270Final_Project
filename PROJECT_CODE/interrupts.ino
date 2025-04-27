// Count encoder pulses
void rightCounter() {
  rightPulses++;
}
void leftCounter() {
  leftPulses++;
}

// Presence sensor
void humanDetected() {
  interruptFlag = true;
}

// Button
void buttonInterrupt() {
  digitalWrite(LEDPin, HIGH); // turn LED on
}