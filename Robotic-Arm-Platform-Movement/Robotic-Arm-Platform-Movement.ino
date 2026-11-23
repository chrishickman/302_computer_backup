
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

  while(!Serial && !Serial1);
  Serial.println("Setup Complete");
}

void loop() {
  Serial1.write(0); // stop all motors
  delay(5000);
  
  // M1: 1 Full Reverse, 64 stop, 127 Full Forward
  // M2: 128 Full Reverse, 192 stop, 255 Full Forward
  //forward_stop_reverse();

   Serial1.write(127); // forward (right)
   Serial1.write(128); // reverse (left)
   delay(5000);
   Serial1.write(1);    // reverse (right)
   Serial1.write(255); // forward (left)
   delay(5000);
}

void forward_stop_reverse() {
  Serial.println("Forward");
  Serial1.write(127);
  Serial1.write(255);
  delay(5000);
  Serial.println("Stopped");
  Serial1.write(0);
  delay(5000);
  Serial.println("Reverse");
  Serial1.write(1);
  Serial1.write(128);
  delay(5000);
}
