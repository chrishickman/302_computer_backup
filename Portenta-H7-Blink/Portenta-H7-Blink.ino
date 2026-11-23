const int pause = 200;

void setup() {
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
}

void loop() {
  // Red
  digitalWrite(LEDR, LOW);  // Active LOW on Portenta H7
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);
  delay(pause);

  // Green
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, HIGH);
  delay(pause);

  // Blue
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, LOW);
  delay(pause);

  // All off
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);
  delay(pause);
}
