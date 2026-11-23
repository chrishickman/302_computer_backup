
// roboClaw Library Installation
  // Download the RoboClaw Arduino Library: https://github.com/basicmicro/roboclaw_arduino_library
  // Add it to your Arduino Environment 
  
// Wiring Instructions 
  // Connect Singal #1 (blue) to RX1 (19) on the Mega 2560 
  // Connect Singal #2 (white) to TX1 (18) on the Mega 2560 


//Includes required to use Roboclaw library
#include <SoftwareSerial.h>
#include "RoboClaw.h"

//See limitations of Arduino SoftwareSerial
SoftwareSerial serial(18,19);  
RoboClaw roboclaw(&serial,10000);

#define address 0x80

void setup() {
  //Open roboclaw serial ports
  roboclaw.begin(38400);
}

void loop() {

  Serial.println("Motors Stopped");
  roboclaw.ForwardM1(address,0);
  roboclaw.ForwardM2(address,0);

  
  // Motor 1 FORWARD:  25 SLOW (forward), 127 (FAST)
  roboclaw.ForwardM1(address,64); 
  
  // Motor 2 FORWARD: 25 SLOW (forward), 127 (FAST)
  roboclaw.BackwardM2(address,64); 
  
  delay(3000); // wait 3 seconds

  Serial.println("Motors Stopped");
  roboclaw.ForwardM1(address,0);
  roboclaw.ForwardM2(address,0);
  delay(3000); // wait 3 seconds

  // Motor 1 BACKWARD:  25 SLOW (forward), 127 (FAST)
  roboclaw.BackwardM1(address,64); 
  
  // Motor 2 BACKWARD: 25 SLOW (forward), 127 (FAST)
  roboclaw.ForwardM2(address,64); 
  delay(3000); // wait 3 seconds

  



}
