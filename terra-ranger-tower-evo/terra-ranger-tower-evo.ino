#define START_BYTE 0xFC       // Start byte for streaming packets
#define PACKET_SIZE 7         // Total bytes per distance packet
#define RESPONSE_SIZE 4       // Command response size

uint8_t packetBuffer[PACKET_SIZE];
int packetIndex = 0;

uint8_t response[RESPONSE_SIZE];
int responseIndex = 0;

void setup() {
  Serial.begin(115200);         // Debug
  Serial2.begin(921600, SERIAL_8N1);        // UART to Tower Evo

  Serial.println("Waiting 5 seconds for sensor to power up...");
  delay(5000);

  // Commands
  byte printout_mode[] = {0x00, 0x11, 0x02, 0x4C};
  byte operating_mode[] = {0x00, 0x31, 0x02, 0xE2};
  byte activate_streaming[] = {0x00, 0x52, 0x02, 0x01, 0xDF};
  byte update_rate[] = {0x00, 0x52, 0x03, 0x01, 0xCA};

  sendCommand(printout_mode, sizeof(printout_mode));
  sendCommand(operating_mode, sizeof(operating_mode));
  sendCommand(activate_streaming, sizeof(activate_streaming));
  sendCommand(update_rate, sizeof(update_rate));

  Serial.println("Sensor initialization complete. Streaming should start now.");
}

void loop() {
  // Handle incoming data from sensor
  while (Serial2.available() > 0) {
    Serial.println("Serial2 data available");
    uint8_t inChar = Serial2.read();

    // Detect start of distance packet
    if (inChar == START_BYTE) {
      packetIndex = 0;
      packetBuffer[packetIndex++] = inChar;
    } else if (packetIndex > 0) {
      packetBuffer[packetIndex++] = inChar;
    }

    // Full packet received
    if (packetIndex == PACKET_SIZE) {
      parseDistancePacket(packetBuffer);
      packetIndex = 0;
    }

    // Handle command response if we’re waiting for one
    if (responseIndex < RESPONSE_SIZE) {
      response[responseIndex++] = inChar;
      if (responseIndex == RESPONSE_SIZE) {
        parseCommandResponse(response);
        responseIndex = 0;
      }
    }
  }
}

// Send command and wait for ACK/NACK
void sendCommand(uint8_t* cmd, size_t len) {
  Serial.print("Sending command: ");
  for (size_t i = 0; i < len; i++) {
    Serial.print(cmd[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  Serial2.write(cmd, len);
  waitForResponse();
}

// Wait for 4-byte ACK/NACK response
void waitForResponse() {
  unsigned long start = millis();
  responseIndex = 0;

  while (responseIndex < RESPONSE_SIZE) {
    if (Serial2.available() > 0) {
      response[responseIndex++] = Serial2.read();
    }
    if (millis() - start > 1000) { // 1 sec timeout
      Serial.println("Timeout waiting for response");
      return;
    }
  }
  parseCommandResponse(response);
}

// Parse command response
void parseCommandResponse(uint8_t* resp) {
  Serial.print("Response: ");
  for (int i = 0; i < RESPONSE_SIZE; i++) {
    Serial.print(resp[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  if (resp[2] == 0x00) {
    Serial.println("Command ACKed ✅");
  } else {
    Serial.println("Command NACK ❌");
  }
}

// Parse distance packet
void parseDistancePacket(uint8_t* packet) {
  // Example packet structure: [Start][Command][Length][Distance_H][Distance_L][Signal][CRC]
  uint16_t distance = (packet[3] << 8) | packet[4];
  uint8_t signal = packet[5];

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm | Signal: ");
  Serial.println(signal);
}
