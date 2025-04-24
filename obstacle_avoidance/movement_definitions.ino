void moveForward(int numPulses) {
  int slowDownThreshold = numPulses - (numPulses / 4);
  int currentPWM = 100;
  rightPulses = 0;
  leftPulses = 0;

  // roll
  while((rightPulses < numPulses) && (leftPulses < numPulses)) {
    if(rightPulses < slowDownThreshold) {
        currentPWM = min(currentPWM + 2, maxPWM);
    }

    if(rightPulses > slowDownThreshold) {
        currentPWM = max(currentPWM - 0.5, 100);
    }

    // set Vref
    analogWrite(pinLeftPWM, currentPWM);
    analogWrite(pinRightPWM, currentPWM);

    // move
    digitalWrite(pinLeftForward, HIGH);
    digitalWrite(pinRightForward, HIGH);
  }

  // stop
  digitalWrite(pinLeftForward, LOW);
  digitalWrite(pinRightForward, LOW);

  Serial.println(rightPulses);
  Serial.println(leftPulses);

  Serial.println("Forward");
}

void turnClockwise(int numPulses) {
  int slowDownThreshold = numPulses - (numPulses / 4);
  int currentPWM = 100;
  rightPulses = 0;
  leftPulses = 0;

  // turn
  while((leftPulses < numPulses)) {
    if(leftPulses < slowDownThreshold) {
        currentPWM = min(currentPWM + 2, maxPWM);
    }

    if(leftPulses > slowDownThreshold) {
        currentPWM = max(currentPWM - 0.5, 100);
    }

    // set Vref
    analogWrite(pinLeftPWM, currentPWM);
    analogWrite(pinRightPWM, currentPWM);

    // move
    digitalWrite(pinLeftForward, HIGH);
    digitalWrite(pinRightBackward, HIGH);
  }

  // stop
  digitalWrite(pinLeftForward, LOW);
  digitalWrite(pinRightBackward, LOW);

  Serial.println(rightPulses);
  Serial.println(leftPulses);

  Serial.println("CW");
}

void turnCounterClockwise(int numPulses) {
  int slowDownThreshold = numPulses - (numPulses / 4);
  int currentPWM = 100;
  rightPulses = 0;
  leftPulses = 0;

  // turn
  while((rightPulses < numPulses)) {
    if(rightPulses < slowDownThreshold) {
        currentPWM = min(currentPWM + 2, maxPWM);
    }

    if(rightPulses > slowDownThreshold) {
        currentPWM = max(currentPWM - 0.5, 100);
    }

    // set Vref
    analogWrite(pinRightPWM, currentPWM);
    analogWrite(pinLeftPWM, currentPWM);

    // move
    digitalWrite(pinRightForward, HIGH);
    digitalWrite(pinLeftBackward, HIGH);
  }

  // stop
  digitalWrite(pinRightForward, LOW);
  digitalWrite(pinLeftBackward, LOW);

  Serial.println(rightPulses);
  Serial.println(leftPulses);

  Serial.println("CCW");
}