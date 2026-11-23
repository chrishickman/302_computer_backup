
#include <Servo.h>

Servo arm;
int joint = 2;

void setup() {
  Serial.begin(9600);
  pinMode(joint, OUTPUT);
  arm.attach(3);

  jointSelect(1400);                    // select elbow
  arm.writeMicroseconds(1500);          // stop movement
  delay(1000);
  
  Serial.println("Setup Complete");
}

void loop() {

  Serial.println("Elbow: Opening");
  jointSelect(1400);
  arm.writeMicroseconds(1800);
  delay(2000);

  Serial.println("Stopped");
  arm.writeMicroseconds(1500);
  delay(2000);

  Serial.println("Elbow: Closing");
  jointSelect(1400);
  arm.writeMicroseconds(1250);
  delay(2000);

}


void jointSelect(int widthMicros) {
  digitalWrite(joint, HIGH);
  delayMicroseconds(widthMicros);
  digitalWrite(joint, LOW);
}
