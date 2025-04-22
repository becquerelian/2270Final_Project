void setup() {
  pinMode(5, INPUT);
  pinMode(9, OUTPUT);

  // set Vref
  analogWrite(9, 200);

  // Set up serial monitor
  Serial.begin(9600);
}

void loop() {
  long duration = pulseIn(5, HIGH);
  int distance = duration * 0.034/2;
  Serial.println(distance);
  delay(1000);
}
