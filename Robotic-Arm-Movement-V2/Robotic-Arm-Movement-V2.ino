const int jointSelectPin = 11; // PWM for joint select
const int movementPin = 12; // PWM for movement

// Joint select ranges (µs)
const int jointRanges[4][2] = {
{1000, 1300}, // Shoulder
{1300, 1520}, // Elbow
{1520, 1800}, // Wrist
{1800, 2000} // Gripper
};

// Movement ranges (µs)
const int moveOpenMin = 1000;
const int moveCloseMax = 2000;

// Sweep settings
int jointStage = 0; // Current joint
int jointValue = jointRanges[0][0];
int jointStep = 20; // Step through joint select slowly

int moveValue = moveOpenMin;
int moveStep = 10; // Step through movement

unsigned long lastUpdate = 0;
const unsigned long interval = 20; // 50Hz frame

void setup() {
Serial.begin(9600);
Serial.println("Starting Joint Select + Movement Sweep");

pinMode(jointSelectPin, OUTPUT);
pinMode(movementPin, OUTPUT);

// Configure Timer1 for 50Hz PWM
TCCR1A = 0;
TCCR1B = 0;

// Fast PWM mode 14 (ICR1 = TOP)
TCCR1A |= (1 << WGM11);
TCCR1B |= (1 << WGM13) | (1 << WGM12);

// Non-inverting PWM on OC1A (pin 11) and OC1B (pin 12)
TCCR1A |= (1 << COM1A1) | (1 << COM1B1);

// Prescaler = 8 → 2 MHz timer clock
TCCR1B |= (1 << CS11);

// TOP value for 50Hz
ICR1 = 40000;

// Initialize PWM signals
OCR1A = jointValue * 2;
OCR1B = moveValue * 2;
}

void loop() {
unsigned long now = millis();
if (now - lastUpdate >= interval) {
lastUpdate = now;

// Update PWM
OCR1A = jointValue * 2;  // Joint select
OCR1B = moveValue * 2;   // Movement

// Print serial output
Serial.print("Joint: ");
switch (jointStage) {
  case 0: Serial.print("Shoulder"); break;
  case 1: Serial.print("Elbow"); break;
  case 2: Serial.print("Wrist"); break;
  case 3: Serial.print("Gripper"); break;
}
Serial.print(" | JointPulse: "); Serial.print(jointValue);
Serial.print(" µs | MovePulse: "); Serial.println(moveValue);

// Sweep movement
moveValue += moveStep;
if (moveValue >= moveCloseMax || moveValue <= moveOpenMin) {
  moveStep = -moveStep; // reverse direction
}

// Step joint select slowly when movement reaches open
if (moveValue <= moveOpenMin) {
  jointValue += jointStep;
  if (jointValue > jointRanges[jointStage][1]) {
    // Move to next joint
    jointStage = (jointStage + 1) % 4;
    jointValue = jointRanges[jointStage][0];
  }
}

}
}
