volatile bool var = LOW;

void setup() {
  pinMode(6, INPUT);
  attachInterrupt(digitalPinToInterrupt(6), service6, RISING);
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, var);
}

// Interrupt Service Routine
void service6() {
  var != var;
}
