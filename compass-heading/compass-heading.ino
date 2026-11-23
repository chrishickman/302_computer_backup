#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

// magnetic offsets
float mXOffset = 18;
float mYOffset = 20;

// raw offsets
float rXOffset = 150;
float rYOffset = 200;

void setup(void)
{
  #ifndef ESP8266
    while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
  #endif
  Serial.begin(9600);
  Serial.println("Setup Complete"); Serial.println("");

  /* Enable auto-gain */
  mag.enableAutoRange(true);

  /* Initialise the sensor */
  if(!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
}

void loop(void)
{
  /* Get a new sensor event */
  sensors_event_t event;
  mag.getEvent(&event);

  //Serial.println(String(event.magnetic.x) + "\t" + String(event.magnetic.y));
  
  //float mX = event.magnetic.x + mXOffset;
  //float mY = event.magnetic.y + mYOffset;
  //Serial.println(String(mX) + "\t" + String(mY));

  Serial.println(String(mag.raw.x) + "\t" + String(mag.raw.y));
  float rX = mag.raw.x + rXOffset;
  float rY = mag.raw.y + rYOffset;
  Serial.println(String(rX) + "\t" + String(rY));

  //float Pi = 3.14159;
  //float heading = (atan2(y,x) * 180) / Pi;
  //Serial.println("Heading: " + String(heading));
  


  /* Delay before the next sample */
  delay(500);
}
