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
  digitalWrite(13, HIGH); // turn LED on
}