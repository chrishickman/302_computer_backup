
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
  delay(100);

  // Green
  // digitalWrite(LEDR, HIGH);
  // digitalWrite(LEDG, LOW);
  // digitalWrite(LEDB, HIGH);
  // delay(1000);

  // Blue
  // digitalWrite(LEDR, HIGH);
  // digitalWrite(LEDG, HIGH);
  // digitalWrite(LEDB, LOW);
  // delay(100);

  // All off
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);
  delay(100);
}
