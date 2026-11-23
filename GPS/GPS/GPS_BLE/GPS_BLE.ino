#include <Adafruit_GPS.h>
#include "Adafruit_BluefruitLE_UART.h"

namespace pins{
    //ble pins
    const int BLE_RX_PIN = 9;    
    const int BLE_TX_PIN = 10;   
    const int BLE_CTS_PIN = 11;   
    const int BLE_RTS_PIN = -1;   // -1 = unused
    const int BLE_MODE_PIN = -1;   // -1 = unused
}
using namespace pins;

//GPS stuff
#define GPSSerial Serial1
Adafruit_GPS GPS(&GPSSerial);

//BLE stuff
const bool VERBOSE_MODE = false;
const int RESET = 1; //1 = factory reset on startup; 0 = don"t do that

SoftwareSerial bleSS = SoftwareSerial(BLE_TX_PIN,BLE_RX_PIN);
Adafruit_BluefruitLE_UART ble(bleSS, BLE_MODE_PIN, BLE_CTS_PIN, BLE_RTS_PIN);

void setup(){
    Serial.begin(115200);
    //BLE stuff
    ble.begin(VERBOSE_MODE);
    if (RESET) ble.factoryReset();
    ble.echo(false);

    //wait for device connection
    while(!ble.isConnected()) delay(500);


    //GPS stuff
    GPS.begin(9600);
    GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); //activates streaming of fix data
    GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); //sets update rate
    GPS.sendCommand(PGCMD_ANTENNA);
    GPSSerial.println(PMTK_Q_RELEASE);
}


void loop(){
    // read data from the GPS in the 'main loop'
  char c = GPS.read();
  // if you want to debug, this is a good time to do it!

  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences!
    // so be very wary if using OUTPUT_ALLDATA and trying to print out data
    Serial.print(GPS.lastNMEA()); // this also sets the newNMEAreceived() flag to false
    if (!GPS.parse(GPS.lastNMEA())) // this also sets the newNMEAreceived() flag to false
      return; // we can fail to parse a sentence in which case we should just wait for another
  }
    Serial.println(GPS.fix);
    ble.print("AT+BLEUARTTX=");
    ble.println(GPS.fix);
    delay(3000);
}