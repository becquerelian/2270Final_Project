// Reads the sensor data and calculates the distance
float readDistance() {
  digitalWrite(triggerPin, LOW);  // Set trig pin to low to ensure a clean pulse
  delayMicroseconds(2);           // Delay for 2 microseconds
  digitalWrite(triggerPin, HIGH); // Send a 10 microsecond pulse by setting trig pin to high
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);  // Set trig pin back to low

  // Measure the pulse width of the echo pin and calculate the distance value
  float distance = pulseIn(echoPin, HIGH) / 58.00;  // Formula: (340m/s * 1us) / 2
  return distance;
}