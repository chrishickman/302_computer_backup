#define BAUDRATE 921600

void setup() {
  Serial.begin(115200);          // Debug output to PC
  Serial3.begin(BAUDRATE);       // UART to Tower Evo
  while(!Serial3);
  byte activate_streaming[] = {0x00, 0x52, 0x02, 0x01, 0xDF};
  Serial3.write(activate_streaming, sizeof(activate_streaming));
  Serial.println("Sensor should now be streaming data...");
}

void loop() {
  while (Serial3.available() > 0) {
    uint8_t inChar = Serial3.read();
    Serial.println(inChar, HEX);
  }
}
