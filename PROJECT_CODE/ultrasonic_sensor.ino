// Reads the sensor data and calculates the distance
float readDistanceRight() {
  digitalWrite(rightTriggerPin, LOW);  // Set trig pin to low to ensure a clean pulse
  delayMicroseconds(2);           // Delay for 2 microseconds
  digitalWrite(rightTriggerPin, HIGH); // Send a 10 microsecond pulse by setting trig pin to high
  delayMicroseconds(10);
  digitalWrite(rightTriggerPin, LOW);  // Set trig pin back to low

  // Measure the pulse width of the echo pin and calculate the distance value
  float distance = pulseIn(rightEchoPin, HIGH) / 58.00;  // Formula: (340m/s * 1us) / 2
  return distance;
}

float readDistanceLeft() {
  digitalWrite(leftTriggerPin, LOW);  // Set trig pin to low to ensure a clean pulse
  delayMicroseconds(2);           // Delay for 2 microseconds
  digitalWrite(leftTriggerPin, HIGH); // Send a 10 microsecond pulse by setting trig pin to high
  delayMicroseconds(10);
  digitalWrite(leftTriggerPin, LOW);  // Set trig pin back to low

  // Measure the pulse width of the echo pin and calculate the distance value
  float distance = pulseIn(leftEchoPin, HIGH) / 58.00;  // Formula: (340m/s * 1us) / 2
  return distance;
}