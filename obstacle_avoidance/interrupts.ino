// Count encoder pulses
void rightCounter() {
  rightPulses++;
}
void leftCounter() {
  leftPulses++;
}

// Button
void buttonInterrupt() {
  digitalWrite(13, HIGH); // turn LED on
}