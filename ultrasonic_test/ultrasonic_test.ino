const int echoPin = 5;
const int trigPin = 9;

void setup() {
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  // set Vref
  analogWrite(trigPin, 200);

  // Set up serial monitor
  Serial.begin(9600);
}

void loop() {
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034/2;
  Serial.println(distance);
  delay(1000);
}
