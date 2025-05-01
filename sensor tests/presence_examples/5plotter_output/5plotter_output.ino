/******************************************************************************
  Example5_ArduinoPlotterOutput.ino
  
  Read human presence detection values from the STHS34PF80 sensor, print them
  to Arduino Serial Plotter. 
  Prints raw IR presence values (cm^-1).

  SparkFun STHS34PF80 Arduino Library
  Madison Chodikov @ SparkFun Electronics
  Original Creation Date: September 19th, 2023
  https://github.com/sparkfun/SparkFun_STHS34PF80_Arduino_Library

  Wire up the connections using the header pins like so:

  ARDUINO --> STHS34PF80
  SDA (A4) --> SDA
  SCL (A5) --> SCL
  3.3V --> 3.3V
  GND --> GND
******************************************************************************/

#include "SparkFun_STHS34PF80_Arduino_Library.h"
#include <Wire.h>

STHS34PF80_I2C mySensor;

// Global Presence Value
int16_t presenceVal = 0;

void setup()
{
    Serial.begin(9600);
    Serial.println("STHS34PF80 Example 5: Arduino Serial Plotter Output");

    // Begin I2C
    Wire.begin();

    // Establish communication with device 
    if(mySensor.begin() == false)
    {
      Serial.println("Error setting up device - please check wiring.");
      while(1);
    }

    Serial.println("Open the Serial Plotter for graphical viewing");

    delay(1000);
}

void loop()
{
  sths34pf80_tmos_drdy_status_t dataReady;
  mySensor.getDataReady(&dataReady);

  // Check whether sensor has new data - run through loop if data is ready
  if(dataReady.drdy == 1)
  {
    sths34pf80_tmos_func_status_t status;
    mySensor.getStatus(&status);
    
    
    // If the flag is high, then read out the information
    if(status.pres_flag == 1)
    {
      mySensor.getPresenceValue(&presenceVal);
      Serial.println(presenceVal);
    }
  }
      
}